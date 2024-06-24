function isActive(tabId){
    chrome.tabs.sendMessage(tabId,{},{},function(response){
        chrome.runtime.lastError||(null==response?chrome.action.disable():"colorize"==response.message&&chrome.action.enable())
    })
}

chrome.action.disable(),
chrome.action.onClicked.addListener(function(){
    chrome.runtime.openOptionsPage(function(){})
}),
chrome.runtime.onStartup.addListener(function(){
    chrome.action.setBadgeText({text:""})
}),
chrome.runtime.onInstalled.addListener(function(details){
    var currentVersion;
    "install"==details.reason&&chrome.runtime.openOptionsPage(function(){}),
    "update"==details.reason&&(currentVersion=chrome.runtime.getManifest().version,details.previousVersion!=currentVersion&&(chrome.action.setBadgeBackgroundColor({color:[96,161,83,255]}),chrome.action.setBadgeText({text:"!"}),chrome.runtime.openOptionsPage()))
}),
chrome.tabs.onActivated.addListener(function(tab){isActive(tab.tabId)}),
chrome.tabs.onUpdated.addListener(function(tabId,changeInfo,tab){isActive(tabId)});
