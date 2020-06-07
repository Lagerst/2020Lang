var http = require('http');
//onst fs = require('fs');
const urllib = require('url');

/*
fs.readFile('input.txt', function (err, data) {
    if (err) {
        console.log(err);
    } else {
        console.log(data.toString());
    }
}); */
//fs.writeFile();

console.log('Server Start');

http.createServer(function (request, response) {
    var Parsed_url = urllib.parse(request.url, true);
    //console.log(Parsed_url);
    //var url = Parsed_url.pathname;
    var Content = Parsed_url.query;
    var sum = Number(Content['a']) + Number(Content['b']);

    console.log("Receive Request Message");
    console.log(Content, sum);

    response.writeHead(200, {"Content_Type": "text/html; charset=utf-8"});
    response.write("<script> alert('A + B = "+ sum.toString() +"'); history.go(-1); </script>");//sum.toString());
    response.end()
}).listen(8080)