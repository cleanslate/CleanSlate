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

String.prototype.format = function() {
    var args = arguments;
    return this.replace(/{(\d+)}/g, function(match, number) { 
                        return typeof args[number] != 'undefined'
                        ? args[number]
                        : match
                        ;
                        });
};

String.prototype.startsWith = function (str){
    return this.indexOf(str) == 0;
};

