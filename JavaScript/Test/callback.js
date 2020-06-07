function func(a, b, callback) {
    console.log("Printed: " + a + b)
    if (callback && typeof(callback) === "function") {
        callback();
    }
}

func('1', '2', function(){
    console.log('callback');
})

function haveBreakfast(food, drink, callback) {
    console.log('早餐' + food + ', ' + drink);
    if (callback && typeof(callback) === "function") {
      callback();
    }
  }
  
  haveBreakfast('toast', 'coffee', function() {
    console.log('早餐吃完了，工作了啦!');
  });