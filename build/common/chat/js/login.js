$(function () {
  var width = 400;
  var height = 500;
  
  window.ui.setSize(400, 500);
  
  // center window
  var size = window.ui.screenSize();
  var posx = (size.width - width)/2;
  var posy = (size.height - height)/2;
  window.sys.log("size:" + String(size.width) + "x" + String(size.height));
  window.ui.move(posx, posy);
  $(".close-button").click(function () { window.ui.close(); });
   
  // bind the titlebar
  $(".titlebar").mousedown(function () { window.ui.startMove(); }).mouseup(function () { window.ui.stopMove(); });

  // focus on username
  $(".username").focus();   

  window.ui.show(true);
});