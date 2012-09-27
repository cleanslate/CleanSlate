function JabberClient() {
    var _socket;
    var _recvStanza;
    var _tagHandler;
    
    this.connect = function (hostname, port, ssl) {
        if (ssl)
            _socket = net.sslsocket(hostname, port);
        else
            _socket = net.socket(hostname, port);
        
        _socket.recv(this.recv);
        
        // open stream tag
        _socket.send("<?xml version='1.0'?>" +
                     "<stream:stream to='{0}' xmlns='jabber:client' ".format(hostname) + 
                     "xmlns:stream='http://etherx.jabber.org/streams' " +
                     "version='1.0'>");
        
        _tagHandler = {
            'stream:features': this.parseStreamFeatures,
            'stream:features': this.parseFeatures
        };
    }
    
    this.close = function() {
        _socket.close();
    }
    
    this.login = function(username, password) {
        
    }
    
    // callbacks
    this.recvStanza = function(cb) {
        _recvStanza = cb;
    }
    
    
    this.recv = function(data, len) {
        sys.log(data);
        if (data.startsWith("<stream:stream"))
        {
            // remove opening <stream:stream> tag
            data = data.replace(/<stream:stream.*?>/, "");
            sys.log(data);
        }

        // parse the xml and figure out the stanza
        $xml = $(data);
        sys.log("data = " + data);
        $m = $xml.find("mechanism");
        sys.log($m.length);
        for (var i = 0; i < $m.length; i++)
        {
            sys.log("mechanisms {0}".format($m[i].innerHTML))
        }
    }
}
