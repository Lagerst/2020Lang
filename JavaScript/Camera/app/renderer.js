function updateimage() {
    document.getElementById("image").src = "./resources/now.jpg"
}

function readJSON(file, callback) {
    let ajax = new XMLHttpRequest();
    ajax.overrideMimeType("application/json");
    ajax.open("GET", file, true);
    ajax.onreadystatechange = function() {
        if (ajax.readyState === 4 && ajax.status == "200") {
            callback(ajax.responseText);
        }
    }
    ajax.send(null);
}