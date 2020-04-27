const say = require("./scripts/module").sayHello;

console.log(say());

const say_2 = require('./build/Release/hello.node');

console.log(say_2.hello());