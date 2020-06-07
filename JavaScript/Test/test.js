// https://segmentfault.com/a/1190000016788484

const setDelay = (millisecond) => {
  return new Promise((resolve, reject)=>{
      if (typeof millisecond != 'number') reject(new Error('参数必须是number类型'));
      setTimeout(()=> {
        resolve(`我延迟了${millisecond}毫秒后输出的`)
      }, millisecond)
  })
}

const setDelaySecond = (seconds) => {
  return new Promise((resolve, reject)=>{
      if (typeof seconds != 'number' || seconds >= 10) {
        reject(new Error('参数必须是number类型，并且小于等于10'));
        return;
      }
      setTimeout(()=> {
        resolve(`我延迟了${seconds}秒后输出的，是第二个函数`)
      }, seconds * 1000)
  })
}

/*
setDelay(3000)
.then((result)=>{
    console.log(result) // 输出“我延迟了2000毫秒后输出的”
});

setDelay('我是字符串')
.then((result)=>{
    console.log(result) // 不进去了
})
.catch((err)=>{
    console.log(err) // 输出错误：“参数必须是number类型”
})

setDelaySecond(3).then((result)=>{
  console.log(result)
}).catch((err)=>{
  console.log(err);
})

setDelay(2000)
.then((result)=>{
  console.log(result)
  console.log('我进行到第一步的');
  return setDelaySecond(3)
})
.then((result)=>{
  console.log('我进行到第二步的');
  console.log(result);
}).catch((err)=>{
  console.log(err);
})
*/
/*
setDelay(2000)
.then((result)=>{
  console.log(result)
  console.log('我进行到第一步的');
  return setDelaySecond(10)
})
.then((result)=>{
  console.log('我进行到第二步的');
  console.log(result);
}, (_err)=> {
  console.log('我出错啦，进到这里捕获错误，但是不经过catch了');
})
.then((result)=>{
  console.log('我还是继续执行的！！！！')
})
.catch((err)=>{
  console.log(err);
})
*/

setDelay(2000).then((result)=>{
  console.log('第一步完成了');
  console.log(result);
  let message = '这是我自己想处理的值'; 
  return Promise.resolve(message) // 这里返回我想在下一阶段处理的值
})
.then((result)=>{
  console.log('第二步完成了');
  console.log(result); // 这里拿到上一阶段的返回值
  //return Promise.resolve('这里可以继续返回')
})
.catch((err)=>{
  console.log(err);
})