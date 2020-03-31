var fs = require('fs');

/**
 * 
 * 回调作为异步最后一个
 * 错误对象作为回调第一个参数
 * 
 * */
fs.readFile('data.txt', function (err, data) {
    if (err) return console.error(err);
    console.log(data.toString());
 
})
console.log('Read_Completed程序执行完成!');

var events = require('events');
 
var eventEmitter = new events.EventEmitter();
var myeventHandler = function () {
    console.log('Event_Handler我是处理程序!');
}
eventEmitter.on('myevent', myeventHandler);
eventEmitter.emit('myevent');

var listerHandler0 = function () {
    console.log(0);
 
}
 
var listerHandler = function (a, b) {
    console.log(a, b);
 
}
 
var listerHandler2 = function (a) {
    console.log(a);
 
}
 
var listerHandler3 = function (a, b, c) {
    console.log(a);
 
}
 
/**
 * 
 * 一个事件多个监听器时
 * 会先后调用监听器回调函数
 * 
 */
eventEmitter.on('lister', listerHandler0);
eventEmitter.on('lister', listerHandler);
eventEmitter.on('lister', listerHandler2);
eventEmitter.on('lister', listerHandler3);

console.log(eventEmitter.emit('lister', 1, 2));     //true
console.log(eventEmitter.emit('lister2', 1, 2));    //false