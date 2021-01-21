//虽然没有去执行setTimeOut函数，但是Promise会自动执行，所以，一般需要将Promise写在一个function里面
new Promise(function(resolve,reject){
    setTimeout(function(){
        let num = Math.random();
        console.log(num)
        //当随机数小于0.5，当前promise完成了执行
        if(num<0.5){
            resolve(num);
        }else{
            reject("错误，num>=0.5");
        }
        console.log('执行完成');
    },200);
});