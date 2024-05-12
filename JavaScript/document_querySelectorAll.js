//Print all links in a web page to another window. Run on the browser console.
var WinPrint = window.open('', '', 'left=0,top=0,width=800,height=900,toolbar=0,scrollbars=0,status=0');
document.querySelectorAll("a").forEach((item) => {
    WinPrint.document.write(item.innerHTML + "\n" + item.href + "<br>");
});

//Print all image sources in a web page to another window. Run on the browser console.
var WinPrint = window.open('', '', 'left=0,top=0,width=800,height=900,toolbar=0,scrollbars=0,status=0');
document.querySelectorAll("img").forEach((item) => {
    WinPrint.document.write(item.innerHTML + "\n" + item.src + "<br>");
});
