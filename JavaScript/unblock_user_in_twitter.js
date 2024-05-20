Run on Chrome browser console.
The following code sets up an interval which fires every second (1000 milliseconds).
After each second it scrolls down one page, selects all unblockable accounts and clicks the unblock button.

let autoUnblock = setInterval(function() {
    window.scrollBy(0, window.innerHeight);
    document.querySelectorAll('[aria-label="Blocked"]').forEach(function(account) {
        account.click()
    });
}, 1000);
