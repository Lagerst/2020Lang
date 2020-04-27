function print(x) {
    console.log(x + "ms");
}

setTimeout(
    print,
    0,
    1,
);

setImmediate(
    print,
    0
)

var x = 0
setInterval(
    () => {x += 500, print(x)}, 
    500
);

print(-1)

function sleep(ms) {
    return new Promise(
        function(resolve, reject) {
            setTimeout(resolve, ms);
        }
    )
}
sleep(600).then(() => console.log("finished, now x = " + x + "ms"))