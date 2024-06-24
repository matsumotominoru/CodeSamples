function options_save() {
    var format = document.querySelector('input[name="format"]:checked').value, format_custom_value = document.getElementById("format_custom_value").value; 
    chrome.storage.sync.set({ format: format, format_custom_value: format_custom_value }, function () { 
        var status = document.getElementById("status"); status.textContent = "Options saved.", setTimeout(function () { status.textContent = "" }, 750) 
    })
} function options_restore() { 
    chrome.storage.sync.get({ format: "gmail", format_custom_value: "%Y-%m-%d %H:%M", errors: "" }, function (items) { 
        document.getElementById("format_" + items.format).checked = !0, document.getElementById("format_custom_value").value = items.format_custom_value, "" != items.errors && (document.getElementById("errorlog").textContent = "Logged errors:<br>" + items.errors) 
    }) 
} function options_clear() { 
    chrome.storage.sync.clear(options_restore); 
    var status = document.getElementById("status"); 
    status.textContent = "Options reset.", setTimeout(function () { 
        status.textContent = "" 
    }, 750) 
} function tab_switcher(e) {
    for (var tabs = document.getElementsByClassName("tab"), t = 0; t < tabs.length; t++)
        tabs[t].classList.remove("active");
    for (var tabs_content = document.getElementsByClassName("tab_content"), t = 0; t < tabs_content.length; t++)
        tabs_content[t].style.display = "none"; 
    document.getElementById(e.target.id + "_content").style.display = "block", e.target.classList.add("active")
} 
document.getElementById("save").addEventListener("click", options_save), document.addEventListener("DOMContentLoaded", options_restore), document.getElementById("reset").addEventListener("click", options_clear); 
for (var tabs = document.getElementsByClassName("tab"), t = 0; t < tabs.length; t++)
    tabs[t].addEventListener("click", tab_switcher); 
tabs[0].click();
