Date.prototype.getWeek = function () {
    var date = new Date(this.getTime());
    date.setHours(0, 0, 0, 0), date.setDate(date.getDate() + 3 - (date.getDay() + 6) % 7);
    var week1 = new Date(date.getFullYear(), 0, 4);
    return 1 + Math.round(((date.getTime() - week1.getTime()) / 864e5 - 3 + (week1.getDay() + 6) % 7) / 7)
},chrome.runtime.onMessage.addListener(function (request, sender, sendResponse) {
    return sendResponse({ message: "colorize" }), !0
});

var custom_format = null;
function getMonthIndexForString(str) {
    for (var date = new Date, i = 0; i < 12; i++)
        if (date.setMonth(i), -1 < str.indexOf(date.toLocaleString(document.documentElement.lang, { month: "long" })))
            return i;
    for (i = 0; i < 12; i++)
        if (date.setMonth(i), -1 < str.indexOf(date.toLocaleString(document.documentElement.lang, { month: "short" })))
            return i;
    return null
}

function pad(str) {
    return 1 == (str += "").length ? "0" + str : str
}

chrome.storage.sync.get({ format: "gmail", format_custom_value: "%Y-%m-%d %H:%M" },
    function (items) {
        "custom" == items.format && (custom_format = items.format_custom_value)
    }
);
var cache = {}, stopcallingme = !1;
function getDateObjectForString(str) {
    if (stopcallingme || null == custom_format)
        return str;
    if (!cache.hasOwnProperty(str)) {
        var y = null, mo = null, d = null, h = null, nd = null;
        y = null == (y = /\d{4}/.exec(str)) ? null : parseInt(y[0], 10);
        var mo = getMonthIndexForString(str), ret = /(\d{1,2})\.?,? /.exec(str), d = null == ret ? null : parseInt(ret[1], 10), ret = / (\d{1,2})(\.|:)(\d{1,2})/.exec(str), h = null == ret ? null : parseInt(ret[1], 10), nd = null == ret ? null : parseInt(ret[3], 10); 
        if (null != /PM/.exec(str) && h < 12 && (h += 12), null != /AM/.exec(str) && 12 == h && (h = 0), "ja" == document.documentElement.lang && (mo = str.match(/(\d{1,2})月/)[1] - 1, d = str.match(/(\d{1,2})日/)[1]), null == y || null == mo || null == d || null == h || null == nd) 
            return stopcallingme = !0, null; 
        nd = new Date(y, mo, d, h, nd); 
        cache[str] = custom_format.replace(/%Y/g, nd.getFullYear()).replace(/%y/g, nd.getFullYear().toString().substr(2, 2)).replace(/%m/g, pad(nd.getMonth() + 1)).replace(/%-m/g, nd.getMonth() + 1).replace(/%b/g, nd.toLocaleString(document.documentElement.lang, { month: "short" })).replace(/%B/g, nd.toLocaleString(document.documentElement.lang, { month: "long" })).replace(/%U/g, nd.getWeek()).replace(/%d/g, pad(nd.getDate())).replace(/%-d/g, nd.getDate()).replace(/%a/g, nd.toLocaleString(document.documentElement.lang, { weekday: "short" })).replace(/%A/g, nd.toLocaleString(document.documentElement.lang, { weekday: "long" })).replace(/%H/g, pad(nd.getHours())).replace(/%-H/g, nd.getHours()).replace(/%I/g, pad((nd.getHours() + 11) % 12 + 1)).replace(/%-I/g, (nd.getHours() + 11) % 12 + 1).replace(/%M/g, pad(nd.getMinutes())).replace(/%p/g, 11 < nd.getHours() ? "PM" : "AM")
    } 
    return cache[str]
} 
function getDateString(str) { 
    var newval = getDateObjectForString(str); return null != newval ? newval : str 
} 
function parentsFirstWidth(element) { 
    if ("BODY" == element.nodeName) 
        return null; 
    var w = parseInt(element.style.width, 10); 
    return isNaN(w) ? parentsFirstWidth(element.parentNode) : w 
} 
function renderlistitem(summaries) { 
    for (var stringWidth = 0, collection = document.getElementsByClassName("xW"), a = 0; a < collection.length; a++) { 
        parentsFirstWidth(collection[a].parentNode) && parentsFirstWidth(collection[a].parentNode) < 500 || (collection[a].style.maxWidth = "none"); 
        for (var spans = collection[a].getElementsByTagName("span"), b = 0; b < spans.length; b++) { 
            var datestring = getDateString(spans[b].getAttribute("title")); 
            spans[b].textContent = datestring, stringWidth = Math.max(stringWidth, spans[b].offsetWidth) 
        } 
    } 
    if (0 != stringWidth) 
        for (collection = document.getElementsByClassName("xX"), a = 0; a < collection.length; a++)
            collection[a].style.width = stringWidth + 28 + "px" 
} 
function renderlistitemcol1(summaries) { 
    for (var stringWidth = 0, collection = document.getElementsByClassName("yf"), a = 0; a < collection.length; a++)
        for (var spans = collection[a].getElementsByTagName("span"), b = 0; b < spans.length; b++) { 
            var datestring = getDateString(spans[b].getAttribute("title")); 
            spans[b].textContent = datestring, stringWidth = Math.max(stringWidth, spans[b].offsetWidth) 
        } 
        if (0 != stringWidth) 
            for (collection = document.getElementsByClassName("xX"), a = 0; a < collection.length; a++)
                collection[a].style.width = stringWidth + 28 + "px" 
} 
function renderdetailitem(summaries) { 
    for (var spans = document.getElementsByClassName("g3"), b = 0; b < spans.length; b++) { 
        var datestring = getDateString(spans[b].getAttribute("title")); 
        spans[b].textContent = datestring 
    } 
} 
new MutationSummary({ callback: renderlistitem, queries: [{ element: "td.xW" }, { characterData: !0 }] }), 
new MutationSummary({ callback: renderlistitemcol1, queries: [{ element: "td.yf" }, { characterData: !0 }] }), 
new MutationSummary({ callback: renderdetailitem, queries: [{ element: "span.g3" }] });
