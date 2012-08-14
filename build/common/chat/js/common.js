function centerWindow(width, height)
{
    var size = window.ui.screenSize();
    var posx = (size.width - width)/2;
    var posy = (size.height - height)/2;
    window.sys.log("size:" + String(size.width) + "x" + String(size.height));
    window.ui.move(posx, posy);
}

function bindTitleBar()
{
    $(".close-button").click(function () { window.ui.close(); });

    $(".titlebar").mousedown(function () { window.ui.startMove(); }).mouseup(function () { window.ui.stopMove(); });
    
    $(".resize").mousedown(function () { window.ui.startResize(); }).mouseup(function () { window.ui.stopResize(); });
}

