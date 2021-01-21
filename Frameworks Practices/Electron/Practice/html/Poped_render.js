function self_close() {
    window.opener = null; 
    window.open('', '_self'); 
    window.close();
};
function sendMessageToParent() {
    window.opener.postMessage({
        status : 200,
        message: "Hello from Poped Message"
    });
}