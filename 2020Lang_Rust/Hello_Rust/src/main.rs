// Hello Rust!

fn _printline(){
    println!("--------------------------------------------");
}

//变量
fn _varible(){
    _printline();
    println!("varible() - begin");

    const MAX_POINT: u32 = 100000;//常量定义

    //let mut name: type = initvalue;

    let mut a: u32 = 1;//可变性
    let b: u32 = a;//不可变性
    a = 2;
    println!("  a = {}",a);
    println!("  b = {}",b);

    println!("  hide b");
    let b: f32 = 1.1;//隐藏性
    println!("  b = {}",b);

    //常量输出
    println!("  MAX_POINT = {}",MAX_POINT);
    println!("  Hello, world!");

    println!("varible() - end");
}

//类型
fn _type(){
    _printline();
    println!("type() - begin");

    //bool 布尔类型
    let flag: bool = true;
    println!("  bool flag = {}",flag);

    //char 字符类型
    // * in Rust, char is 32 bits.
    let a : char = 'a';
    println!("  char a = '{}'",a);
    let b : char = '早';
    println!("  char b = '{}'",b);

    //i8,i16,i32,i64,u8,u16,u32,u64,f32,f64 数值类型
    let c : i8 = -128;
    println!("  i8 c = {}",c);
    let d : f32 = 0.0008;
    println!("  f32 d = {}",d);

    //isize,usize 自适应类型
    println!("  isize::max_value = {}",isize::max_value());
    println!("  usize::max_value = {}",usize::max_value());

    //数组
    //[type: size] , size是数组类型的一部分
    fn show(arr:[u32;5]){
        println!("  show(arr):");
        for i in &arr {
            println!("      arr[{}] = {}",i,i);
        }
    };
    let arr : [u32; 5] = [1,2,3,4,5];
    println!("  [u32; 5] array arr = {{1,2,3,4,5}}");
    show(arr);

    //元组
    let tup : (i32, f32, char) = (-3, 3.69, '晚');
    println!("  tuple tup = ({},{},{})",tup.0,tup.1,tup.2);
    let (x,y,z) = tup;
    println!("  let (x,y,z) = tup //拆解 \n      x = {}, y = {}, z = {}",x,y,z);

    println!("type() - end");
}

//函数
fn _function(){
    _printline();
    println!("function() - begin");

    fn fn1(){
        println!("  This is a function : fn1()");
    }

    fn fn2(a: i32, b: i32) -> i32{
        let result = a + b;
        println!("  This is a function : fn2(i32) :: fn2({},{})",a,b);
        //result作为返回值
        result
    }

    fn fn3(a: i32, b: i32) -> i32{
        a + b
    }

    fn1();
    let a : i32 = -1;
    let b : i32 = 2;
    println!("  fn2(i32:-1, i32:2) = {}",fn2(a,b));
    println!("  fn3(i32:-1, i32:2) = {}",fn3(a,b));

    //语句是执行一些操作，但不返回值的指令
    //let x = (let y = 1);    //Wrong
    let x = {
        let y = 1;
        y
    };    //Right
    println!("  x = {{let y = 1; y}} = {}", x);

    println!("function() - end");
}

//控制流
fn _controlflow(flag : bool){
    _printline();
    println!("controlflow() - begin");

    // if - else if - else ...
    if flag == true {
        println!("  check ! flag == true");
    } else {
        println!("  check ! flag != true");
    }

    //let中使用if
    let reverse_flag = if flag {
        false
    } else {
        // 6    //wrong 两个分支必须同一类型
        true
    };
    println!("  reverse_flag = {}",reverse_flag);

    //loop 循环
    println!("  loop - begin");
    let mut counter = 0;
    loop {
        counter += 1;
        println!("      in loop : {}",counter);
        if counter==3 {
            break;
        };
    };
    println!("  loop - end");

    //let中使用loop
    let result = loop {
        counter +=1;
        if counter == 20 {
            break counter * 2;
        }
    };
    println!("  result (let - loop) = {}",result);

    //for
    println!("  for - begin");
    println!("    arr.iter()");
    let arr:[u32; 3] = [1,2,3];
    for iterator in arr.iter(){
        println!("      iterator = {}",iterator);
    }
    // or
    println!("    or &arr");
    for iterator in &arr{
        println!("      iterator = {}",iterator);
    }
    println!("  for - end");

    println!("controlflow() - end");
}

//所有权
fn _ownership(){
    _printline();
    println!("ownership() - begin");

    //1 rust通过所有权机制来管理内存，编译器在编译就会根据所有权规则对内存的使用进行检查
    //2 堆和栈
    //3 作用域:{}
    //4 String内存回收
    //5 移动
    //6 clone
    //7 栈上数据拷贝
    //8 函数和作用域

    {
        let s1 = String::from("hello");
        //s1.push_str(" world"); //s1 should be mutable
        println!("  s1 = {}", s1); //String类型离开作用域的时候会调用drop方法

        let s2 = s1;
        println!("  s2 = {} //move s1 to s2, s1 invalid", s2);
        //println!("  s1= {}", s1); //move to s2, s1 invalid

        //clone
        let s3 = s2.clone();
        println!("  s3 = {} //clone s2 to s3, s2 valid", s3);
        println!("  s2 = {}", s2);
    }

    println!("  copy trait - 所有的整型,浮点型,布尔值 bool,字符类型 char,元组");
    //copy trait
    let a = 1;
    let b = a;
    println!("      a = {}, b = {} // a valid", a, b);
    //常用的具有copy trait有：
    //所有的整型,浮点型,布尔值 bool,字符类型 char,元组

    println!("  Test");

    fn take_ownership(st : String){
        println!("      take_ownership : {}",st);
    }

    fn  string_as_para(st : String) -> String{
        println!("      String_as_para : {}",st);
        st
    }

    fn make_copy(i : i32){
        println!("      make_copy : i = {}",i);
    }

    let st = String::from("Hello");
    let st = string_as_para(st);
    println!("      st = {} // st valid",st);
    take_ownership(st);
    //println!("      {}",st);
    println!("      st : \"Hello\" become invalid");

    let x = 5;
    make_copy(x);
    println!("      x : 1 valid");

    println!("ownership() - end");
}

//引用
fn _reference(){
    _printline();
    println!("reference() - begin");

    //1 有了可变引用之后不能再有不可变引用
    //2 引用必须有效

    let mut s = String::from("hello");

    //& 引用
    //让我们创建一个指向值的应用，但是并不拥有它，因为不拥有这个值，所以，当引用离开其值指向的作用域后也不会被丢弃
    fn calculate_length(s: & String) -> usize {
        s.len()
    }
    //& mut 借用
    fn modify(s : & mut String){
        s.push_str(" world!");
    }
    println!("  s.len() = {}",calculate_length(&s));
    modify(&mut s);
    println!("  s.len() = {} //modify(& mut s)",calculate_length(&s));
    let s2 = & s;
    println!("  s2.len() = {} // s2 = & s",calculate_length(&s2));
    let ms = & mut s;
    modify(ms);
    //println!("  s2.len() = {}",calculate_length(&s2));    //wrong : immutable reference ms make s2 invalid
    println!("  cdafter modify:\n      immutable reference ms make s2 invalid");
    println!("  ms.len() = {} //ms = & mut s",calculate_length(&ms));

    //悬垂引用
    //fn dangle() -> &String {
    //    let s = String::from("hello");
    //    &s
    //}
    //let ref_s = dangle();    //wrong : function return value which is out of scope

    println!("reference() - end");
}

//slice
fn _slice(){
    _printline();
    println!("slice() - begin");

    //1 字符串slice是String中一部分值的引用,字面值就是slice
    //特别注意::中文字符特殊使用
    let s = String::from("hello world");
    println!("  s = \"{}\"",s);
    let j = &s[0..5];   //[0..=4],[..=4],[..5]
    println!("  j = &s[0..5] = {}",j);
    let w = &s[6..11];  //[6..=11],[6..]
    println!("  w = &s[6..11] = {}",w);
    //let s2 = "hh";  //&str 类似C++,不可变

    //2 其它类型slice
    let a = [1,2,3,4];
    println!("  a = [1,2,3,4]");
    let b = &a[1..3];
    println!("  len(b = &a[1..3]) = {}",b.len());

    println!("slice() - end");
}

//结构体
fn _struct(){
    _printline();
    println!("struct() - begin");


    //define struct
    #[derive(Debug)]//结构体声明的注解 用于输出{:?}和{:#?}
    struct User {
        name:     String,
        account:  String,
        nonce:    u64,
        active:   bool,
    };

    //make a example
    let mut e = User{
        name:     String::from("xiaoming"),
        account:  String::from("80001000"),
        nonce:    10000,
        active:   true,
    };

    //modify the example
    e.nonce = 20000;

    //参数名字和字段名字同名的简写方法
    let name = String::from("xiaohuang");
    let account = String::from("89077777");
    let nonce = 200000;
    let active = false;
    let user1 = User {
        name,
        account,
        nonce,
        active,
    };

    //make struct example from another struct
    let user2 = User{
        ..user1
    };
    println!("  user2 = {{{},{},{},{}}}",user2.name,user2.account,user2.nonce,user2.active);

    //元组结构体
    struct Point(i32,i32);
    let a = Point(10,20);
    let b = Point(30,11);
    println!("  a = ({},{})",a.0,a.1);
    println!("  b = ({},{})",b.0,b.1);

    //无任何字段的类单元结构体
    //struct A{};

    //print struct  一行打印{:?}    自动换行{:#?}
    println!("  e = {:?}",e);

    #[derive(Debug)]
    struct Dog {
        name   : String,
        weight : f32,
        height : f32,
    };

    impl Dog {
        fn get_name(&self) -> &str {
            &(self.name[..])
        }
        fn get_weight(&self) -> f32 {
            self.weight
        }
        fn get_height(&self) -> f32 {
            self.height
        }
    };

    impl Dog {
        fn bark(){
            println!("      Dog is barking! //static method without \"&self\"");
        }
    }

    let dog = Dog {
        name   : String::from("cc"),
        weight : 100.0,
        height : 70.0,
    };

    println!("  dog = {:?}",dog);
    println!("  method show():");
    println!("      dog.get_name() = {}",dog.get_name());
    println!("      dog.get_weight() = {}",dog.get_weight());
    println!("      dog.get_height() = {}",dog.get_height());
    Dog::bark();

    println!("struct() - end");
}

//枚举
fn _enum(){
    _printline();
    println!("enum() - begin");

    //1 类似于c语言的方式定义
    println!("  IPAddress enum:");
    enum IpAddrType {
        V4,
        V6,
    }

    struct IpAddr {
        kind:    IpAddrType,
        address: String,
    }

    impl IpAddr {
        fn prin(&self){
            match (*self).kind {
                IpAddrType::V4
                    =>println!("      This is an IPv4 Address: {}",(*self).address),
                IpAddrType::V6
                    =>println!("      This is an IPv6 Address: {}",(*self).address),
            }
        }
    }

    let addr_1 = IpAddr {
        kind:    IpAddrType::V4,
        address: String::from("127.0.0.1"),
    };
    addr_1.prin();

    let addr_2 = IpAddr {
        kind:    IpAddrType::V6,
        address: String::from("::1"),
    };
    addr_2.prin();

    //2 rust语言提倡的方式定义
    //enum Ipaddr2 {
    //    V4(String),
    //    V6(String),
    //}
    //let addr_3 = Ipaddr2::V4(String::from("127.0.0.1"));
    //let addr_4 = Ipaddr2::V6(String::from("::1"));

    //3 可以是不同类型
    println!("  another IPAddress enum:");
    enum IpAddr3 {
        V4(u8, u8, u8, u8),
        V6(String),
    }
    let addr_5 = IpAddr3::V4(127, 0, 0, 1);
    let addr_6 = IpAddr3::V6(String::from("::1"));
    impl IpAddr3 {
        fn prin(&self){
            match *self {
                IpAddr3::V4(a, b, c, d)
                    => println!("      V4: {}.{}.{}.{}",a,b,c,d),
                //Message::Write(&s)
                    //=> println!(" Write"),
                _
                    => println!("      Other")
            }
        }
    }
    addr_5.prin();
    addr_6.prin();

    //4 经典用法
    println!("  Message enum:");
    enum Message {
        Quit,
        Move{x: i32, y: i32},
        Write(String),
        Change(i32, i32, i32),
    }
    //等同于
    //struct QuitMessage; //类单元结构体
    //struct MoveMessage {
    //  x: i32,
    //  y: i32,
    //}
    //struct WriteMessage(String)
    //struct Change(i32, i32, i32)

    //5 枚举类型的方法以及match
    impl Message {
        fn prin(&self){
            match self {
                Message::Quit
                    => println!("      Quit"),
                Message::Move{x,y}
                    => println!("      Move x = {}, y = {}", x, y),
                Message::Change(a, b, c)
                    => println!("      Change a = {}, b = {}, c = {}", a, b, c),
                Message::Write(s)
                    => println!("      Write {}",s),
                //_
                //    => println!("      Other")
            }
        }
    }

    let quit = Message::Quit;
    quit.prin();

    let change = Message::Change(1,2,3);
    change.prin();

    let moven = Message::Move{x:4, y:5};
    moven.prin();

    let writen = Message::Write(String::from("678"));
    writen.prin();

    //6 Option是标准库定义的一个枚举
    println!("  Option:");
    //enum Option<T> {
    //  Some(T),
    //  None,
    //}

    let some_string = Some(String::from("a string"));
    match some_string {
        Some(i)
            => {println!("      some_string = {}",i);}
        None
            => {println!("      Do nothing!");}
    }

    let absent_number: Option<i32> = None;
    match absent_number {
        Some(i)
            => {println!("      absent_number = {}",i);}
        None
            => {println!("      Do nothing");}
    }

    let x: i32 = 5;
    let y: Option<i32> = Some(5);
    //let sum = x + y;  //Wrong
    let mut temp = 0;
    match y {
        Some(i)
            => {temp = i;}
        None
            => {println!("      Do nothing!");}
    }
    let sum = x + temp;
    println!("      x + y = {}",sum);

    fn plus_one(x: Option<i32>) -> Option<i32>{
        match x {
            Some(i)
                =>  {Some(i+1)}
            None
                =>  {None}
        }
    }
    let result = plus_one(y);
    match result {
        Some(i)
            => {println!("      result = plus_one(Option<i32>: y = 5) = {}",i);}
        None
            => {println!("      Do nothing");}
    }

    if let Some(value) = plus_one(y) {
        println!("      value = {}",value);
    } else {
        println!("      Do nothing");
    }

    println!("enum() - end");
}

//向量
fn _vector(){
    _printline();
    println!("vector() - begin");

    //1 创建空的vector: Vec<T>
    let mut v: Vec<i32> = Vec::new();
    v.push(1);

    //2 创建包含初始值的vector
    let mut v = vec![1,2,3];
    v.push(4);

    //3 丢弃vector
    {
        //let mut v = vec![1,2,3];
    }

    //4 读取元素
    let one: &i32 = &v[0];
    println!("  one = v[0] = {} //\"one\"",one);
    println!("  one = v[0] = {} //\"*one\", the same as previous \"one\"",*one);

    match v.get(1) {
        Some(value)
            => {println!("  value = v.get(1) = {}",value);}
        _
            => {println!("  None");}
    }

    //let six = v[5];   //Wrong, index out of bound.

    //5 更新
    let mut v: Vec<i32> = Vec::new();
    v.push(1);
    v.push(2);
    v.push(3);

    //6 遍历
    let mut flag = 0;
    //  不可变遍历
    println!("  in &v:");
    for i in &v {
        println!("      v[{}] = {}",flag,i);
        flag += 1;
    }
    //  可变遍历
    flag = 0;
    println!("  in &mut v:");
    for i in &mut v {
        *i += 1;
        println!("      v[{}] = {}",flag,i);
        flag += 1;
    }

    //7 使用枚举
    enum Context {
        Text(String),
        Float(f32),
        Int(i32),
    };
    let mut v = vec![
        Context::Text(String::from("string")),
        Context::Int(-1),
        Context::Float(0.001),
    ];
    v.push(Context::Int(0));

    //8 补充
    //let mut v = vec![1,2,3,4,5];
    //let first = &v[0];  //first mutable borrow occurs here
    //v.push(6);  //Wrong,  second mutable borrow occurs here
    //println!("  first = &v[0] = {}",first);

    println!("vector() - end");
}

//字符串
fn _string(){
    _printline();
    println!("string() - begin");

    //1   创建一个空String
    let mut s0 = String::new();
    s0.push_str("hello");
    println!("  string s0 = {}", s0);

    //2   通过字面值创建一个String
    //2.1 使用String::from()
    let s1 = String::from("init");
    println!("  string s1 = {} //String::from(\"init\")", s1);
    //2.2 使用str的方式
    let s2 = "init".to_string();
    println!("  string s2 = {} //\"init\".to_string()", s2);

    //3   更新String
    //3.1 push_str
    s0.push_str(", world");
    println!("  s0.push_str(\", world!\") = {}", s0);
    //3.2 push
    s0.push('!');
    println!("  s0.push('!') = {}", s0);
    //3.3 使用"+"合并字符串
    //let s3 = s0 + &s2;  //s0 become invalid
    let s3 = s0.clone() + &s2;  //use this instead
    println!("  s0 = {}",s0);
    println!("  s3 = s0.clone() + &s2 = {}", s3);
    //3.4 使用format!
    let ss1 = String::from("192");
    let ss2 = String::from("168");
    let ss3 = String::from("0");
    let ss4 = String::from("1");
    let ss = format!("{}.{}.{}.{}", ss1, ss2, ss3, ss4);
    println!("  ss = format!(\"{{}}.{{}}.{{}}.{{}}\",String::from(\"192\"),String::from(\"168\"),String::from(\"0\"),String::from(\"1\")) = {}", ss);

    //4   String 索引
    //    String 不能被索引!!!

    //5   str 索引
    let hello = "你好";
    let h5 = & hello[0..3];
    println!("  h5 = &hello[0..3] = {}", h5);

    //6   遍历
    //6.1 chars
    print!("  (chars) hello =");
    for c in hello.chars() {
        print!(" {}", c);
    }
    println!("");
    //6.2 bytes
    print!("  (bytes) hello =");
    for c in hello.bytes() {
        print!(" {}", c);
    }
    println!("");

    println!("string() - end");
}

//hashmap
fn _hashmap() {
    _printline();
    println!("hashmap() - begin");

    use std::collections::HashMap;
    //1 HashMap<K, V>
    //2 创建HashMap
    let keys = vec![String::from("Blue"),String::from("Red")];
    let values = vec![20,10];
    let scores: HashMap<_, _> = keys.iter().zip(values.iter()).collect();
    println!("  scores = {:?}",scores);

    let mut scores: HashMap<String,i32> = HashMap::new();
    scores.insert(String::from("Red"), 10);
    scores.insert(String::from("Blue"), 20);

    //3 读取
    let key = String::from("Red");  //返回Option类型
    if let Some(score) = scores.get(&key){
        println!("  score = scores[\"Red\"] = {}", score);
    }
    //或
    let score = scores.get(&key);
    match score {
        Some(value)
            => println!("  score = scores[\"Red\"] = {}", value),
        None
            => println!("  Nothing"),
    }

    //4 遍历(任意顺序)
    println!("  scores:");
    for (key, value) in &scores {
        println!("      {{\"{}\": {}}}",key,value);
    }

    //5 更新
    //  插入新的键值对
    scores.insert(String::from("Yellow"), 30);
    //  键不存在的时候才插入
    scores.entry(String::from("Yellow")).or_insert(29);
    //  删除 remove
    scores.remove(&String::from("Blue"));
    println!("  scores = {:?}", scores);
    //  根据旧值来更新一个值
    let text = "hello world wonderful world";
    let mut wordmap = HashMap::new();
    for word in text.split_whitespace() {
        let count = wordmap.entry(word).or_insert(0);
        *count += 1;
    }
    println!("  wordmap = {:?}", wordmap);

    //对于HashMap<&str, Vec<f32>>类型，要对最里面Vec<f32>进行增加元素的操作（假设里面有“rust”key），可以：
    //hd.get_mut("rust").unwrap().push(3.0_f32);
    //对于HashMap<&str, HashMap<&str, Box<Vec<f32>>>>类型，要对最里面进行增加元素操作：
    //hd.get_mut("rust").unwrap().get_mut("book1").unwrap().push(3.0_f32);

    let mut m:HashMap<&str,Vec<i32>> = HashMap::new();
    m.insert("what",Vec::new());
    m.get_mut("what").unwrap().push(1);
    m.get_mut("what").unwrap().push(2);
    println!("  value_count => m:{:?}", m);

    println!("hashmap() - end");
}

//模块
fn _module() {
    _printline();
    println!("module() - begin");

    mod factory {
        pub mod producer_refrigerator {
            pub fn produce_r() {
                println!("  Inmain: refrigerator produced");
            }
        }
        pub mod producer_washingmachine {
            pub fn produce_w() {
                println!("  Inmain: washing machine produced");
            }
        }
    }
    factory::producer_refrigerator::produce_r();
    factory::producer_washingmachine::produce_w();

    factorylib::factory::producer_refrigerator::produce_r();
    factorylib::factory::producer_washingmachine::produce_w();

    use factorylib::factory::producer_refrigerator as F;
    F::produce_r();

    use factorylib::factory::producer_washingmachine::*;
    produce_w();

    use factorylib::factory::a::B;
    let b:B = B::new_b();
    b.print_b();

    /*
        extern crate crypto;
        use crypto::digest::Digest;
        use crypto::sha3::Sha3;
        let mut hasher = Sha3::sha3_256();
        hasher.input_str("hello world");
        let result = hasher.result();
        println!("  sha3(\"{}\") = {}", "hello world", result);
    */

    println!("module() - end");
}

//出错
fn _error() {
    _printline();
    println!("error() - begin");

    //1 rust语言将错误分为两个类别：可恢复错误和不可恢复错误
    //  1 可恢复错误通常代表向用户报告错误和重试操作是合理的情况，例如未找到文件。rust中使用Result<T,E>来实现。
    //  2 不可恢复错误是bug的同义词，如尝试访问超过数组结尾的位置。rust中通过panic！来实现。

    //2 panic!
    if false {
        panic!("crash here!");
    }

    //3 使用BACKTRACE=1
    //cargo run RUST_BACKTRACE=1

    //4 Result<T, E>
    /*
        enum Result<T, E> {
        Ok(T),
        Err(E),
        }
    */
    use std::fs::File;
    let f = File::open("hello.txt");
    match f {
        Ok(file)
            => {
                println!("  File open succeed!");
                file
            },
        Err(error)
            => panic!("error: {:?}",error),
    };

    //5 简写
    let _f = File::open("hello.txt").unwrap();
    let _f = File::open("hello.txt").expect("  Failed to open hello.txt");

    //6 传播错误 当编写一个函数，但是该函数可能会失败，此时除了在函数中处理错误外，还可以将错误传给调用者，让调用者决定如何处理，这被称为传播错误。
    use std::io;
    use std::io::Read;
    fn read_text_from_file() -> Result<String, io::Error> {
        let f = File::open("hello.txt");
        let mut f = match f {
            Ok(file)
                => {
                    println!("  File open succeed!");
                    file
                },
            Err(error)
                => return Err(error),
        };
        let mut s = String::new();
        match f.read_to_string(&mut s){
            Ok(_)
                => Ok(s),
            Err(error)
                => Err(error),
        }
    }
    let r = read_text_from_file();
    match r {
        Ok(s)
            => println!("      s = {}", s),
        Err(error)
            => println!("      error = {:?}", error),
    }

    //7 传播错误的简写方式，提倡的方式
    fn read_text_from_file_simplified() -> Result<String, io::Error> {
        let mut s = String::new();
        File::open("hello.txt")?.read_to_string(&mut s)?;
        println!("  File open succeed!");
        Ok(s)
    }
    let r = read_text_from_file_simplified();
    match r {
        Ok(s)
            => println!("      s = {}", s),
        Err(error)
            => println!("      error = {:?}", error),
    }

    //8 什么时候用panic!,什么时候用Result
    //  1 示例,代码原型,测试用panic!\unwrap\expect
    //  2 实际项目中应该用Result
    //9 Option和Result

    println!("error() - end");
}

fn _test(){
    _printline();
    println!("test() - begin");

    println!("  details in /testlib");
    println!("  run \"cargo test\"");

    println!("test() - end");
}

fn main() {
    _varible();
    _type();
    _function();
    _controlflow(true);
    _ownership();
    _reference();
    _slice();
    _struct();
    _enum();
    _vector();
    _string();
    _hashmap();
    _module();
    _error();
    _test();
    _printline();
}
