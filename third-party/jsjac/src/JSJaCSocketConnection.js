/**
 * Instantiates a Socket session.
 * @class Implementation of Javascript socket
 * @extends JSJaCConnection
 * @constructor
 * @param oArg connection properties.
 * @param oArg.port is the port for the jabber
 * @param oArg.ssl is is a boolean whether connect as SSL
 * @param [oArg.allow_plain] controls if plaintext authentication is
 * allowed.
 * @param [oArg.oDbg] a reference to a debugger interface.
 */
function JSJaCSocketConnection(oArg) {
  this.base = JSJaCConnection;
  this.base(oArg);

  this._socket = null;

  this.registerHandler('onerror', JSJaC.bind(this._cleanupSocket, this));
}

JSJaCSocketConnection.prototype = new JSJaCConnection();

JSJaCSocketConnection.prototype._cleanupSocket = function() {
  if (this._socket !== null) {
    this._socket.close();
    this._socket = null;
  }
};

JSJaCSocketConnection.prototype.connect = function(oArg) {
  this._setStatus('connecting');

  this.domain = oArg.domain || 'localhost';
  this.username = oArg.username;
  this.resource = oArg.resource;
  this.pass = oArg.pass;
  this.register = oArg.register;
  this.ssl = oArg.ssl;
  this.hostname = oArg.hostname;
  this.port = oArg.port;

  this.authhost = oArg.authhost || this.domain;
  this.authtype = oArg.authtype || 'sasl';

  this.jid = this.username + '@' + this.domain;
  this.fulljid = this.jid + '/' + this.resource;

  if (typeof net === 'undefined') {
    this._handleEvent('onerror', JSJaCError('503', 'cancel', 'service-unavailable'));
    return;
  }

  if (this.ssl)
  {
      this._socket = net.sslsocket();
  }
  else
  {
      this._socket = net.socket();
  }
    
  this._socket.onclose(JSJaC.bind(this._onclose, this));
  this._socket.onerror(JSJaC.bind(this._onerror, this));
  this._socket.onopen(JSJaC.bind(this._onopen, this));
  this._socket.connect(this.hostname, this.port);
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._onopen = function() {
  var reqstr = this._getInitialRequestString();

  this.oDbg.log(reqstr, 4);

  this._socket.onmessage(JSJaC.bind(this._handleOpenStream, this));
  this._socket.send(reqstr);
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._handleOpenStream = function(data) {
  var open, stream;

  this.oDbg.log(data, 4);

  open = data;
  // skip XML prolog if any
  open = open.substr(open.indexOf('<stream:stream'));
  if (open.substr(-2) !== '/>' && open.substr(-16) !== '</stream:stream>') {
    // some servers send closed opening tag, some not
    open += '</stream:stream>';
  }
  stream = this._parseXml(open);
  if(!stream) {
    this._handleEvent('onerror', JSJaCError('503', 'cancel', 'service-unavailable'));
    return;
  }

  // extract stream id used for non-SASL authentication
  this.streamid = stream.getAttribute('id');

  this.oDbg.log('got streamid: ' + this.streamid, 2);
  this._socket.onmessage(JSJaC.bind(this._handleInitialResponse, this));
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._handleInitialResponse = function(data) {
  var doc = this._parseXml(data);
  if (!this._parseStreamFeatures(doc)) {
    this._handleEvent('onerror', JSJaCError('503', 'cancel', 'service-unavailable'));
    return;
  }

  this._connected = true;

  if (this.register) {
    this._doInBandReg();
  } else {
    this._doAuth();
  }
};

JSJaCSocketConnection.prototype.disconnect = function() {
  this._setStatus('disconnecting');

  if (!this.connected()) {
    return;
  }
  this._connected = false;

  this.oDbg.log('Disconnecting', 4);
  this._cleanupSocket();

  this.oDbg.log('Disconnected', 2);
  this._handleEvent('ondisconnect');
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._onclose = function() {
  this.oDbg.log('socket closed', 2);
  if (this._status !== 'disconnecting') {
    this._connected = false;
    this._handleEvent('onerror', JSJaCError('503', 'cancel', 'service-unavailable'));
  }
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._onerror = function() {
  this.oDbg.log('socket error', 1);
  this._connected = false;
  this._handleEvent('onerror', JSJaCError('503', 'cancel', 'service-unavailable'));
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._onmessage = function(data) {
  var stanza, node, packet;

  stanza = data;
  this._setStatus('processing');
  if (!stanza || stanza === '') {
    return;
  }

  // WebSocket works only on modern browsers, so it is safe to assume
  // that namespaceURI and getElementsByTagNameNS are available.
  node = this._parseXml(stanza);
  if (node.namespaceURI === NS_STREAM && node.localName === 'error') {
    if (node.getElementsByTagNameNS(NS_STREAMS, 'conflict').length > 0) {
      this._setStatus('session-terminate-conflict');
    }
    this._connected = false;
    this._handleEvent('onerror', JSJaCError('503', 'cancel', 'remote-stream-error'));
    return;
  }

  packet = JSJaCPacket.wrapNode(node);
  if (!packet) {
    return;
  }

  this.oDbg.log('async recv: ' + data, 4);
  this._handleEvent('packet_in', packet);

  if (packet.pType && !this._handlePID(packet)) {
    this._handleEvent(packet.pType() + '_in', packet);
    this._handleEvent(packet.pType(), packet);
  }
};

/**
 * Parse single XML stanza. As proposed in XMPP Sub-protocol for
 * WebSocket draft, it assumes that every stanza is sent in a separate
 * WebSocket frame, which greatly simplifies parsing.
 * @private
 */
JSJaCSocketConnection.prototype._parseXml = function(s) {
  var doc;

  this.oDbg.log('Parsing: ' + s, 4);
  try {
    doc = XmlDocument.create('stream', NS_STREAM);
    if(s.indexOf('<stream:stream') === -1) {
      // Wrap every stanza into stream element, so that XML namespaces work properly.
      doc.loadXML("<stream:stream xmlns:stream='" + NS_STREAM + "' xmlns='jabber:client'>" + s + "</stream:stream>");
      return doc.documentElement.firstChild;
    } else {
      doc.loadXML(s);
      return doc.documentElement;
    }
  } catch (e) {
    this.oDbg.log('Error: ' + e);
    this._connected = false;
    this._handleEvent('onerror', JSJaCError('500', 'wait', 'internal-service-error'));
  }

  return null;
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._getInitialRequestString = function() {
  var streamto, reqstr;

  streamto = this.domain;
  if (this.authhost) {
    streamto = this.authhost;
  }

  reqstr = '<stream:stream to="' + streamto + '" xmlns="jabber:client" xmlns:stream="' + NS_STREAM + '"';
  if (this.authtype === 'sasl' || this.authtype === 'saslanon') {
    reqstr += ' version="1.0"';
  }
  reqstr += '>';
  return reqstr;
};

JSJaCSocketConnection.prototype.send = function(packet, cb, arg) {
  this._socket.onmessage(JSJaC.bind(this._onmessage, this));
  if (!packet || !packet.pType) {
    this.oDbg.log('no packet: ' + packet, 1);
    return false;
  }

  if (!this.connected()) {
    return false;
  }

  // remember id for response if callback present
  if (cb) {
    if (!packet.getID()) {
      packet.setID('JSJaCID_' + this._ID++); // generate an ID
    }

    // register callback with id
    this._registerPID(packet.getID(), cb, arg);
  }

  try {
    this._handleEvent(packet.pType() + '_out', packet);
    this._handleEvent('packet_out', packet);
    this._socket.send(packet.xml());
  } catch (e) {
    this.oDbg.log(e.toString(), 1);
    return false;
  }

  return true;
};

JSJaCSocketConnection.prototype.resume = function() {
  return false; // not supported for websockets
};

JSJaCSocketConnection.prototype.suspend = function() {
  return false; // not supported for websockets
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._doSASLAuthDigestMd5S1 = function(data) {
  var el = this._parseXml(data);
  return JSJaC.bind(JSJaCConnection.prototype._doSASLAuthDigestMd5S1, this)(el);
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._doSASLAuthDigestMd5S2 = function(data) {
  var el = this._parseXml(data);
  return JSJaC.bind(JSJaCConnection.prototype._doSASLAuthDigestMd5S2, this)(el);
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._doSASLAuthDone = function(data) {
  var el = this._parseXml(data);
  return JSJaC.bind(JSJaCConnection.prototype._doSASLAuthDone, this)(el);
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._reInitStream = function(cb) {
  var reqstr, streamto = this.domain;
  if (this.authhost) {
    streamto = this.authhost;
  }

  reqstr = '<stream:stream xmlns:stream="' + NS_STREAM + '" xmlns="jabber:client" to="' + streamto + '" version="1.0">';
  this._sendRaw(reqstr, cb);
};

/**
 * @private
 */
JSJaCSocketConnection.prototype._sendRaw = function(xml, cb, arg) {
  if (cb) {
    this._socket.onmessage(JSJaC.bind(cb, this, arg));
  }

  this._socket.send(xml);
  return true;
};
