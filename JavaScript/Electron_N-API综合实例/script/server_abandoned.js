var http = require('http');
const urllib = require('url');

var express = require('express');
var app = express();
var calculator = require("./build/Release/calculator.node");
console.log(calculator.hello())

app.all('*', function(req, res, next) {
　　//设置允许跨域的域名，*代表允许任意域名跨域
    res.header("Access-Control-Allow-Origin", "*");
　　//允许的header类型
    res.header('Access-Control-Allow-Headers', 'Content-type');
　　//跨域允许的请求方式
    res.header("Access-Control-Allow-Methods", "PUT,POST,GET,DELETE,OPTIONS,PATCH");
　　//可选，用来指定本次预检请求的有效期，单位为秒。在此期间，不用发出另一条预检请求。
    res.header('Access-Control-Max-Age',1728000);//预请求缓存20天
    next(); 
});

console.log('Server Start');

http.createServer(function (request, response) {
    var Parsed_url = urllib.parse(request.url, true);
    //console.log(Parsed_url);
    //var url = Parsed_url.pathname;
    var Content = Parsed_url.query;
    //var sum = Number(Content['a']) + Number(Content['b']);

    console.log("Receive Request Message");
    console.log(Content);

    var obj = {response: calculator.Calculate(Number(Content['a']), Number(Content['b'])).toString()}

    response.writeHead(200, {"Content_Type": "application/json;; charset=utf-8"});
    response.write(JSON.stringify(obj));//sum.toString());
    response.end()
}).listen(8080)