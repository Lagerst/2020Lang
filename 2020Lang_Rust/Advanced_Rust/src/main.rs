// Advanced Rust!

fn _printline(){
    println!("--------------------------------------------");
}

//泛型
fn _generic(){
    _printline();
    println!("generic() - begin");

    //1 泛型是具体类型或者其它属性的抽象替代,用于减少代码重复.
    //2 在函数定义中使用泛型.
    //3 在结构体中使用泛型.
    //4 枚举中的泛型.
    //5 方法中的泛型.
    //6 总结:
    //    使用泛型并不会造成程序性能上的损失.
    //    rust通过在编译时进行泛型代码的单态化来保证效率.
    //    单态化时通过填充编译时使用的具体类型,将通用代码转换为特定代码的过程.

    //  PartialOrd可顺序比较 + Copy可复制
    fn list_max<T: PartialOrd + Copy>(list: &[T]) -> T {
        let mut result = list[0];
        for &item in list.iter() {
            if item > result {
                result = item;
            }
        }
        result
    }

    let i32_list = vec![1,3,5,7,9,11,2];
    println!("  list_max(vec![1,3,5,7,9,11,2]) = {}",list_max(&i32_list));
    let char_list = vec!['a','b','c','e'];
    println!("  list_max(vec!['a','b','c','e']) = {}",list_max(&char_list));

    #[derive(Debug)]
    struct Point<T> {
        x:  T,
        y:  T,
    }
    let mut coordinate_i32 = Point{x:1, y:2};
    let coordinate_f32 = Point{x:1.0, y:2.0};
    println!("  Point<i32> = {:#?}", coordinate_i32);
    println!("  Point<f32> = {:#?}", coordinate_f32);

    #[derive(Debug)]
    struct PointMixed<T, U> {
        x:  T,
        y:  U,
    }
    let coordinate_i32_f32 = PointMixed{x:1, y:2.0};
    let coordinate_f32_i32 = PointMixed{x:1.0, y:2};
    println!("  Point<i32, f32> = {:#?}", coordinate_i32_f32);
    println!("  Point<f32, i32> = {:#?}", coordinate_f32_i32);

    ////----------在枚举中使用泛型------------
    //enum Option<T> {
    //    Some(T),
    //    None,
    //}
    //
    //enum Result<T, E> {
    //    Ok(T),
    //    Err(E)
    //}
    ////----------------------------------------

    impl<T> Point<T> {
        fn get_x(&self) -> &T{
            &self.x
        }
        fn get_y(&self) -> &T{
            &self.y
        }
    }
    println!("  coordinate_i32");
    println!("      coordinate_i32.get_x() = {}", coordinate_i32.get_x());
    println!("      coordinate_i32.get_y() = {}", coordinate_i32.get_y());

    impl Point<i32> {
        fn add(&mut self, shift: i32){
            self.x += shift;
            self.y += shift;
        }
    }
    coordinate_i32.add(1);
    println!("  after coordinate_i32.add(1)");
    println!("      coordinate_i32.get_x() = {}", coordinate_i32.get_x());
    println!("      coordinate_i32.get_y() = {}", coordinate_i32.get_y());

    impl<T, U> PointMixed<T, U> {
        fn creat_point<V, W>(self, other: PointMixed<V, W>) -> PointMixed<T, W> {
            PointMixed {
                x: self.x,
                y: other.y,
            }
        }
    }
    let p1 = PointMixed{x: 5, y: 1.1};
    let p2 = PointMixed{x: "hello", y: 'c'};
    let coordinate_mixed = p1.creat_point(p2);
    println!("  coordinateMixed");
    println!("      coordinateMixed.x = {}", coordinate_mixed.x);
    println!("      coordinateMixed.y = {}", coordinate_mixed.y);

    println!("generic() - end");
}

//trait
fn _trait() {
    _printline();
    println!("trait() - begin");

    //1 trait用于定义与其它类型共享的功能，类似于其它语言中的接口。
    //  1 可以通过trait以抽象的方式定义共享的行为。
    //  2 可以使用trait bounds指定泛型是任何拥有特定行为的类型。
    //2 定义trait
    pub trait GetInformation {
        fn get_name(&self) -> &String;
        fn get_age(&self) -> u32;
    }

    pub trait SchoolName {
        fn get_school_name(&self) -> String {
            String::from("UESTC")
        }
    }

    //3 实现trait

    pub struct Student {
        pub name: String,
        pub age: u32,
    }

    impl SchoolName for Student{   }

    impl GetInformation for Student {
        fn get_name(&self) -> &String {
            &self.name
        }
        fn get_age(&self) -> u32 {
            self.age
        }
    }

    pub struct Teacher {
        pub name: String,
        pub age: u32,
        pub subject: String,
    }

    impl SchoolName for Teacher{
        fn get_school_name(&self) -> String {
            String::from("JLHS")
        }
    }

    impl GetInformation for Teacher{
        fn get_name(&self) -> &String {
            &self.name
        }

        fn get_age(&self) -> u32 {
            self.age
        }
    }

    let s = Student{name: "Jack".to_string(), age: 10};
    let t = Teacher{name: "Rose".to_string(), age: 30, subject: String::from("math")};
    println!("  student, name = {}, age = {}", s.get_name(), s.get_age());
    println!("  teacher, name = {}, age = {}", t.get_name(), t.get_age());

    let s_school_name = s.get_school_name();
    println!("  student school name = {}", s_school_name);
    let t_school_name = t.get_school_name();
    println!("  teacher school name = {}", t_school_name);

    //4 默认实现: 可以在定义trait的时候提供默认的行为，trait的类型可以使用默认的行为。
    //5 trait作为参数
    fn print_information(item: &impl GetInformation) {
        println!("      name = {}", item.get_name());
        println!("      age = {}", item.get_age());
    }

    println!("  Student:");
    print_information(&s);
    println!("  Teacher:");
    print_information(&t);

    //6 trait_bound语法
    //7 指定多个trait_bound
    fn print_information_trait_bound<T: GetInformation>(item: &T)
        //fn print_information_trait_bound<T>(item: &T)     //Optional
        //where T: GetInformation                           //Optional
    {
        println!("      name = {}", item.get_name());
        println!("      age = {}", item.get_age());
    }
    println!("  Trait_bound_Student:");
    print_information_trait_bound(&s);
    println!("  Trait_bound_Teacher:");
    print_information_trait_bound(&t);

    //8 返回trait的类型
    fn produce_item_with_age() -> impl SchoolName {
        Student {
            name: String::from("Wang"),
            age:  15,
        }
    }
    let _s = produce_item_with_age();

    //10 使用trait bound有条件的实现方法
    struct PeopleMatchInformation<T, U> {
        master: T,
        student: U,
    }

    impl<T: GetInformation, U: GetInformation> PeopleMatchInformation<T, U> {
        fn print_all_information(&self) {
            println!("  in print_all_information:");
            println!("      master name = {}", self.master.get_name());
            println!("      master age = {}", self.master.get_age());
            println!("      student name = {}", self.student.get_name());
            println!("      student age = {}", self.student.get_age());
        }
    }

    let s = Student{name: "Jack".to_string(), age:15};
    let t = Teacher{name: "Rose".to_string(), age:30, subject: String::from("math")};
    let m = PeopleMatchInformation{master: t, student: s};
    m.print_all_information();

    //11 对任何实现了特定trait的类型有条件的实现trait
    trait GetName {
        fn get_name(&self) -> &String;
    }

    trait PrintName {
        fn print_name(&self);
    }

    impl<T: GetName> PrintName for T {
        fn print_name(&self) {
            println!("  name = {}", self.get_name());
        }
    }

    struct _Student {
        name: String,
    }

    impl GetName for _Student {
        fn get_name(&self) -> &String {
            &(self.name)
        }
    }

    let s = _Student{name: String::from("Jase")};
    s.print_name();

    println!("trait() - end");
}

//生命周期
fn _lifetimes() {
    _printline();
    println!("lifetimes() - begin");

    //1 Rust中每一个引用都有其生命周期，也就是引用保持有效的作用域。大部分时候生命周期是隐含并可以推断的，正如大部分时候类型可以推断一样。
    //2 生命周期的主要目标是避免悬垂引用。
    //3 Rust编译器使用借用检查器来检查生命周期是否有效。

    ////错误例子1
    //let r;                        //---------------------------+------------'a
    //{                             //                           +
    //    let x = 5;                //-------+------'b           |
    //    r = &x;                   //       |                   |
    //}                             //-------+                   |
    //println!("r = {}", r);        //                           |
    //                              //                           |
    //println!("Hello, world!");    //                           |
    //                              //---------------------------+

    {
        let r;                      //---------------------------+------------'a
                                    //                           +
        let x = 5;                  //-------+------'b           |
        r = &x;                     //       |                   |
                                    //       |                   |
        println!("  r = {}", r);    //       |                   |
    }                               //---------------------------+

    //4 函数中的生命周期
    fn longer<'a>(x: &'a str, y: &'a str) -> &'a str {
        if x.len() > y.len() {
            x
        } else {
            y
        }
    }
    let s1 = String::from("abcde");
    let s2 = String::from("ab");
    let r = longer(s1.as_str(), s2.as_str());
    println!("  longer = \"{}\"", r);

    //5 结构体中的生命周期
    #[derive(Debug)]
    struct Info<'a> {
        name: &'a str,
    }
    let name = String::from("hello");
    let info = Info{name: &name};
    println!("  {:?}", info);

    //6 生命周期省略
    fn _get_a_str(s: &str) -> &str {
        s
    }
    //  1 没有生命周期注解却能够编译，原因：早期的rust中必须显式的声明生命周期，后来rust团队将很明确的模式进行了注解的简化。
    //  2 遵守生命周期省略规则的情况下能明确变量的声明周期，则无需明确指定生命周期。函数或者方法的参数的生命周期称为输入生命周期，而返回值的生命周期称为输出生命周期。
    //  3 编译器采用三条规则判断引用何时不需要生命周期注解，当编译器检查完这三条规则后仍然不能计算出引用的生命周期，则会停止并生成错误。
    //  4 生命周期注解省略规则适用于fn定义以及impl块定义，如下：
    //   a 每个引用的参数都有它自己的生命周期参数。例如如下：
    //         一个引用参数的函数，其中有一个生命周期： fn foo<'a>(x: &'a i32)
    //         两个引用参数的函数，则有两个生命周期 ：fn foo<'a, 'b>(x: &'a i32, y: &'b i32)
    //         以此类推。
    //   b 如果只有一个输入生命周期参数，那么它被赋予所有输出生命周期参数：
    //         fn foo(x: &i32) -> &i32   等价于  fn foo<'a>(x: &'a i32) -> &'a i32
    //   c 如果方法有多个输入生命周期参数，不过其中之一因为方法的缘故为&self或者&mut self，那么self的生命周期被赋予所有输出生命周期参数。例子在下面来看。
    //         fn function(&self, x: &str, y: &str, ....) -> &str

    //7 方法中的生命周期
    #[derive(Debug)]
    struct Student<'a> {
        _name: &'a str,
    }
    impl<'b> Student<'b> {
        fn dosomething(&self) -> i32 {
            0
        }
        fn dosomething2(&self, s: &str) -> i32 {
        // 规则省略 = fn dosomething2<'b>(&'b self, s: &str) -> 'b i32 {
            println!("  {} meet {}", self._name, s);
            1
        }
    }
    let s = Student{_name: "Jack"};
    s.dosomething();
    s.dosomething2("Rose");
    println!("  {:?}", s);

    //8 静态生命周期
    //定义方式： 'static
    //其生命周期存活于整个程序期间，所有的字符字面值都拥有static生命周期。
    let _static_str: &'static str = "hello";

    //9 同时具有泛型和生命周期声明
    use std::fmt::Display;

    fn display<'a, T: Display>(x: &'a str, y: &'a str, _a: T) -> &'a str {
        print!("  {} + {} + ", x, y);
        "finish"
    }
    println!("{}",display("begin","process",3));

    println!("lifetimes() - end");
}

//闭包
fn _closure() {
    _printline();
    println!("closure() - begin");

    //1 闭包是可以保存进变量或者作为参数传递给其它函数的匿名函数。闭包和函数不同的是，闭包允许捕获调用者作用域中的值。
    //2 闭包的使用方式
    //3 使用带有泛型和Fn trait的闭包

    let use_closure = || {
        println!("  This is a closure!");
    };
    use_closure();

    //语法格式
    //闭包定义会为每个参数和返回值类型推导一个具体的类型，但是不能推导两次
    fn add_one_1(x: u32) -> u32 {
        x + 1
    }
    let add_one_2 = |x: u32| -> u32 {x + 1};
    let add_one_3 = |x| {x + 1};
    let add_one_4 = |x| x + 1;

    let mut test:[u32;4] = [0; 4];
    test[0] = add_one_1(5);
    test[1] = add_one_2(5);
    test[2] = add_one_3(5) as u32;
    test[3] = add_one_4(5) as u32;

    for i in 0..4 {
        println!("  test[{}] = {}", i , test[i]);
    }

    //不能推导两次的例子
    let example_closure = |x| x;
    let s = example_closure(String::from("hello"));
    println!("  s = {}", s);

    //let n = example_closure(5);   //Wrong
    let n = example_closure(5.to_string());
    println!("  n = {}", n);

    //捕捉环境中的变量
    let i = 1;
    let envr = |x| x + i;
    println!("  envr_catch = {}", envr(5));

    let x = 4;
    let equal_to_x = |z| z == x;
    let y = 4;
    assert!(equal_to_x(y));

    let x = vec![1, 2, 3];
    let equal_to_x = move |z| {z == x};     //x borrowed
    //println!("x === {:?}", x);            //value used after move

    let y = vec![1, 2, 3];
    assert!(equal_to_x(y));

    //闭包可以通过三种方式捕获其环境，它们对应函数的三种获取参数的方式，分别是获取所有权、可变借用、不可变借用。
    //这三种捕获值的方式被编码为如下三个Fn trait：
    //  1 FnOnce消费从周围作用域捕获的变量，闭包周围的作用域被称为其环境。为了消费捕获到的变量，闭包必须获取其所有权并在定义闭包时将其移进闭包。
    //    其名称的Once部分代表了闭包不能多次获取相同变量的所有权。
    //  2 FnMut获取可变的借用值，所以可以改变其环境。
    //  3 Fn从其环境获取不可变的借用值。
    //当创建一个闭包时，rust会根据其如何使用环境中的变量来推断我们希望如何引用环境。由于所有闭包都可以被调用至少一次，因此所有闭包都实现了FnOnce。
    //没有移动被捕获变量的所有权到闭包的闭包也实现了FnMut，而不需要对捕获的变量进行可变访问的闭包实现了Fn。

    //实现一个缓存，只处理第一次传入的值并保存
    struct Cacher<T>
        where T: Fn(u32) -> u32
    {
        calcuation: T,
        value: Option<u32>,
    }

    impl<T> Cacher<T>
        where T: Fn(u32) -> u32
    {
        fn new(calcuation: T) -> Cacher<T> {
            Cacher {
                calcuation,
                value: None,
            }
        }

        fn value(&mut self, arg: u32) -> u32 {
            match self.value {
                Some(v) => v,    //already exist
                None => {
                    let v = (self.calcuation)(arg);
                    self.value = Some(v);
                    v
                },
            }
        }
    }

    let mut c = Cacher::new(|x| x+1);
    let v1 = c.value(1);
    println!("  v1 = {}", v1);

    let v2 = c.value(43);
    println!("  v2 = {}", v2);

    println!("closure() - end");
}

//迭代器
fn _iterator() {
    _printline();
    println!("iterator() - begin");

    //1 迭代器负责遍历序列中的每一项和决定序列何时结束的逻辑。
    //2 创建迭代器：迭代器是惰性的，意思就是在调用方法使用迭代器之前，不会有任何效果
    //3 每个迭代器都实现了iterator trait, iterator trait定义在标准库中：
    //      trait Iterator {
    //          type Item;
    //          fn next(mut self) -> Option<Self::Item>;
    //              //type Item和Self::Item这种用法叫做定义trait的关联类型
    //      }
    //next是Iterator被要求实现的唯一的一个方法，next一次返回一个元素，当迭代器结束时候，返回None

    let v1 = vec![1, 2, 3];
    let mut v1_iter = v1.iter(); //到目前为止，不会对v1产生任何影响

    //  for val in v1_iter {
    //      println!("val = {}", val);
    //  }

    println!("  in v1:");
    loop {
        if let Some(v) = v1_iter.next() {
            println!("      v = {}", v);//1
        } else {
            println!("      At end");
            break;
        }
    }

    //-----迭代可变引用-----
    println!("  in v2:");
    let mut v2 = vec![1, 2, 3];
    let mut v2_iter = v2.iter_mut();
    if let Some(v) = v2_iter.next() {
        *v = 3;
    }
    println!("  v2 = {:?}", v2);

    //-----消费适配器------
    let v1 = vec![1, 2, 3];
    let v1_iter = v1.iter();
    let total: i32 = v1_iter.sum(); //调用消费适配器sum来求和
    println!("  total = {}", total);

    //-----迭代适配器------
    println!("  迭代适配器");
    let v1 = vec![-4, 2, 3];
    println!("      v1 = {:?}", v1);

    let v2: Vec<_> = v1.iter().map(|x| x + 1).collect();
    println!("      v2 = {:?} = v1.iter().map(|x| x + 1).collect()", v2);

    let v1 = vec![1, 12, 3, 45];
    println!("      v1 = {:?}", v1);

    let v2: Vec<_> = v1.into_iter().filter(|x| *x > 5).collect();
    println!("      v2 = {:?} = v1.into_iter().filter(|x| *x > 5).collect()", v2);

    //-----自定义迭代器------
    println!("  Customize iterator:");
    struct Counter {
        count: u32,
    }
    impl Counter {
        fn new() -> Counter {
            Counter {
                count : 0
            }
        }
    }
    impl Iterator for Counter {
        type Item = u32;
        fn next(&mut self) -> Option<Self::Item> {
            self.count += 1;
            if self.count < 6 {
                Some(self.count)
            } else {
                None
            }
        }
    }
    let mut counter = Counter::new();
    for i in 0..6 {
        if let Some(v) = counter.next() {
            println!("      i = {}, v = {}", i, v);
        } else {
            println!("      i = {}, at end", i);
            break;
        }
    }

    println!("iterator() - end");
}

//cargo
fn _cargo() {
    _printline();
    println!("cargo() - begin");

    println!("  cargo run/build --release");

    println!("cargo() - end");
}

//智能指针
fn _box() {
    _printline();
    println!("box() - begin");

    //1 最简单最直接的智能指针是box，其类型为Box<T>。box允许将值放在堆上而不是栈上，留着栈上的则是指向堆数据的指针。
    //  除了数据被存储在堆上外，box没有任何性能损失。
    //2 box适合用于如下场景：
    //  1 当有一个在编译时未知大小的类型，而又需要再确切大小的上下文中使用这个类型值的时候；（举例子：在一个list环境下，存放数据，但是每个元素的大小在编译时又不确定）
    //  2 当有大量数据并希望在确保数据不被拷贝的情况下转移所有权的时候；
    //  3 当希望拥有一个值并只关心它的类型是否实现了特定trait而不是其具体类型时。

    let b = Box::new(5); //b存储于栈上，5存储在堆上，b指向5所在的内存
    println!("  b = {}", b);

    //enum List {
    //    Cons(i32, List),
    //    Nil,
    //}

    enum List {
        Cons(i32, Box<List>),
        Nil,
    }

    //struct List {
    //    int value;
    //    struct List *next;
    //    //struct List l;
    //};

    //

    use List::Cons;
    use List::Nil;
    //let list = Cons(1, Cons(2, Cons(3, Nil)));

    let _list = Cons(1,
                    Box::new(Cons(2,
                        Box::new(Cons(3,
                            Box::new(Nil))))));

    println!("box() - end");
}

//解引用
fn _deref() {
    _printline();
    println!("box() - begin");


    //实现Deref trait允许我们重载解引用运算符。
    //let a: A = A::new();
    //let b = &a;
    //let c = *b;//解引用
    //前提：A类型必须实现Deref trait

    let x = 5;
    let y = &x;
    assert_eq!(5, x);
    assert_eq!(5, *y); //解引用

    let z = Box::new(x);
    assert_eq!(5, *z);

    //实现deref trait
    use std::ops::Deref;

    struct Mybox<T>(T);

    impl<T> Mybox<T> {
        fn new(x: T) -> Mybox<T> {
            Mybox(x)
        }
    }

    impl<T> Deref for Mybox<T> {
        type Target = T;
        fn deref(&self) -> &T {
            &self.0
        }
    }

    let x = 5;
    let y = Mybox::new(x);

    assert_eq!(x, 5);
    assert_eq!(x, *y);

    //解引用的多态
    fn func(name: &str) {
        println!("  func: {}", name);
    }
    let r = Mybox::new(String::from("Rust"));
    func(&r);   //将MyBox变为&String，再将String的解引用，变为字符串slice。  &str

    //解引用多态与可变性交互:
    // 1 当T：Deref<Target=U>时，从&T到&U
    // 2 当T：DerefMut<Target=U>时，从&mut T 到&mut U
    // 3 当T：Deref<Target=U>时，从&mut T到&U

    println!("box() - end");
}

//析构
fn _drop() {
    _printline();
    println!("drop() - begin");

    enum Status {
        Alive,
        Dead,
    }

    struct Dog {
        num : i32,
        stat: Status,
    }

    impl Dog {
        fn new(x: i32) -> Dog {
            println!("  The dog {} is born.", x);
            Dog{
                num :   x,
                stat:   Status::Alive
            }
        }
    }

    impl Drop for Dog {
        fn drop(&mut self) {
            println!("  The dog {} is dead.", self.num);
            self.stat = Status::Dead;
        }
    }

    let _jack = Dog::new(1);
    let _rose = Dog::new(2);
    let _carl = Dog::new(3);
    println!("  同名隐藏未调用析构函数，被隐藏的变量离开作用域析构");
    let _carl = Dog::new(4);    //隐藏不会调用析构函数
    drop(_carl);                //drop before function end

    println!("  After function drop(), the dog is dropped.");

    println!("drop() - end");
}

//引用计数
fn _rc() {
    _printline();
    println!("rc() - begin");

    //通过Rc<T>允许程序的多个部分之间只读的共享数据，因为相同位置的多个可变引用可能会造成数据竞争和不一致。
    enum List {
        Cons(i32, Rc<List>),
        Nil,
    }

    use List::{Cons, Nil};
    use std::rc::Rc;

    let _a = Rc::new(Cons(5, Rc::new(Cons(10, Rc::new(Nil)))));
    println!("  count after creating a = {}", Rc::strong_count(&_a));

    let _b = Cons(3, _a.clone());
    println!("  count after bind to b, a count = {}", Rc::strong_count(&_a));

    {
        let _c = Cons(4, Rc::clone(&_a));
        println!("  count after bind to c, a count = {}", Rc::strong_count(&_a));
    }

    println!("  count at end, c finished, a = {}", Rc::strong_count(&_a));

    println!("rc() - end");
}

fn _refcell() {
    _printline();
    println!("refcell() - begin");

    //1 内部可变性:允许在使用不可变引用时改变数据.

    //2 通过RefCell<T>在运行时检查借用规则(通常情况下，是在编译时检查借用规则),RefCell<T>代表其数据的唯一所有权。
    //  类似于Rc<T>,RefCell<T>只能用于单线程场景。

    //3 选择Box<T>,Rc<T>或RefCell<T>的理由：
    //  Rc<T>允许相同数据有多个所有者; Box<T>和RefCell<T>有单一所有者。
    //  Box<T>允许在编译时执行不可变或可变借用检查; Rc<T>仅允许在编译时执行不可变借用检查;RefCell<T>允许在运行时执行不可变或可变借用检查。
    //  因为RefCell<T>允许在运行时执行可变借用检查,所以我们可以在即便RefCell<T>自身是不可变的情况下修改其内部的值。

    #[derive(Debug)]
    enum List {
        Cons(Rc<RefCell<i32>>, Rc<List>),
        Nil,
    }

    use List::{Cons, Nil};
    use std::rc::Rc;
    use std::cell::RefCell;

    let value = Rc::new(RefCell::new(5));

    let a = Rc::new(Cons(Rc::clone(&value), Rc::new(Nil)));
    let b = Cons(Rc::new(RefCell::new(6)), Rc::clone(&a));
    let c = Cons(Rc::new(RefCell::new(7)), Rc::clone(&a));
    println!("  a before: {:?}", a);
    println!("  b before: {:?}", b);
    println!("  c before: {:?}", c);

    *value.borrow_mut() += 10;

    println!("  a after: {:?}", a);
    println!("  b after: {:?}", b);
    println!("  c after: {:?}", c);

    println!("refcell() - end");
}

fn _advanced_ref() {
    _printline();
    println!("advanced_ref() - begin");

    {
        println!("  环形链表");

        #[derive(Debug)]
        enum List {
            Cons(i32, RefCell<Rc<List>>),
            Nil,
        }

        impl List{
            fn tail(&self) -> Option<&RefCell<Rc<List>>> {
                match self {
                    Cons(_, item) => Some(item),
                    Nil => None,
                }
            }
        }

        use std::rc::Rc;
        use std::cell::RefCell;
        use List::{Cons, Nil};

        let a = Rc::new(Cons(5, RefCell::new(Rc::new(Nil))));
        println!("      1, a rc count = {}", Rc::strong_count(&a));
        println!("      1, a tail = {:?}", a.tail());

        {
            let b = Rc::new(Cons(10, RefCell::new(Rc::clone(&a))));
            println!("      2, a rc count = {}", Rc::strong_count(&a));
            println!("      2, b rc count = {}", Rc::strong_count(&b));
            println!("      2, b tail = {:?}", b.tail());

            if let Some(link) = a.tail() {
                *link.borrow_mut() = Rc::clone(&b);
            }

            println!("      3, a rc count = {}", Rc::strong_count(&a));
            println!("      3, b rc count = {}", Rc::strong_count(&b));
            // println!("       3, a tail = {:?}", a.tail()); //error
        }
    }

    {
        println!("  弱引用Weak<T>");
        //弱引用Weak<T>
        //特点:
        //  1 弱引用通过Rc::downgrade传递Rc实例的引用，调用Rc::downgrade会得到Weak<T>类型的智能指针，同时将weak_count加1（不是将strong_count加1）。
        //  2 区别在于 weak_count 无需计数为 0 就能使 Rc 实例被清理。只要strong_count为0就可以了。
        //  3 可以通过Rc::upgrade方法返回Option<Rc<T>>对象。

        #[derive(Debug)]
        enum List {
            //Cons(i32, RefCell<Rc<List>>),
            Cons(i32, RefCell<Weak<List>>),
            Nil,
        }
        let _nil = List::Nil;

        impl List {
            fn tail(&self) -> Option<&RefCell<Weak<List>>> {
                match self {
                    Cons(_, item) => Some(item),
                    Nil => None,
                }
            }
        }

        use std::rc::Rc;
        use std::cell::RefCell;
        use List::{Cons, Nil};
        use std::rc::Weak;
        let a = Rc::new(Cons(5, RefCell::new(Weak::new())));
        println!("      1, a strong count = {}, weak count = {}", Rc::strong_count(&a), Rc::weak_count(&a));
        println!("      1, a tail = {:?}", a.tail());

        let b = Rc::new(Cons(10, RefCell::new(Weak::new())));
        if let Some(link) = b.tail() {
            *link.borrow_mut() = Rc::downgrade(&a);
        }
        println!("      2, a strong count = {}, weak count = {}", Rc::strong_count(&a), Rc::weak_count(&a));
        println!("      2, b strong count = {}, weak count = {}", Rc::strong_count(&b), Rc::weak_count(&b));
        println!("      2, b tail = {:?}", b.tail());

        if let Some(link) = a.tail() {
            *link.borrow_mut() = Rc::downgrade(&b);
        }
        println!("      3, a strong count = {}, weak count = {}", Rc::strong_count(&a), Rc::weak_count(&a));
        println!("      3, b strong count = {}, weak count = {}", Rc::strong_count(&b), Rc::weak_count(&b));
        println!("      3, a tail = {:?}", a.tail());
    }

    println!("advanced_ref() - end");
}

fn _tree() {
    _printline();
    println!("tree() - begin");

    use std::rc::{Rc, Weak};
    use std::cell::RefCell;

    #[derive(Debug)]
    struct Node {
        value: i32,
        parent: RefCell<Weak<Node>>,
        children: RefCell<Vec<Rc<Node>>>,
    }

    let leaf = Rc::new(
        Node {
            value   : 1,
            parent  : RefCell::new(Weak::new()),
            children: RefCell::new(vec![]),
        }
    );
    println!("  leaf parent = {:?}", leaf.parent.borrow().upgrade());
    println!(
    "   1 leaf strong = {}, weak = {}",
        Rc::strong_count(&leaf),
        Rc::weak_count(&leaf)
    );
    {
        let root = Rc::new(
            Node {
                value   : 0,
                parent  : RefCell::new(Weak::new()),
                children: RefCell::new(vec![Rc::clone(&leaf)]),
            }
        );
        println!(
        "   1 root strong = {}, weak = {}",
            Rc::strong_count(&root),
            Rc::weak_count(&root)
            );
        *leaf.parent.borrow_mut() = Rc::downgrade(&root);
        println!(
        "   2 root strong = {}, weak = {}",
            Rc::strong_count(&root),
            Rc::weak_count(&root)
            );
        println!(
        "   2 leaf strong = {}, weak = {}",
            Rc::strong_count(&leaf),
            Rc::weak_count(&leaf)
            );
        println!("  leaf parent = {:?}", leaf.parent.borrow().upgrade());
    }

    println!(
    "   3 leaf strong = {}, weak = {}",
        Rc::strong_count(&leaf),
        Rc::weak_count(&leaf)
        );

    println!("tree() - end");
}

//多线程
fn _thread() {
    _printline();
    println!("thread() - begin");

    //1 进程是资源分配的最小单位，线程是CPU调度的最小单位。
    //2 在使用多线程时，经常会遇到的一些问题：
    //  1 竞争状态：多个线程以不一致的顺序访问数据或资源；
    //  2 死锁：两个线程相互等待对方停止使用其所拥有的资源，造成两者都永久等待；
    //  3 只会发生在特定情况下且难以稳定重现和修复的bug
    //3 编程语言提供的线程叫做绿色线程，如go语言，在底层实现了M:N的模型，即M个绿色线程对应N个OS线程。但是，Rust标准库只提供1：1的线程模型的实现，即一个Rust线程对应一个Os线程。
    //  运行时代表二进制文件中包含的由语言本身提供的代码，这些代码根据语言的不同可大可小，不过非汇编语言都会有一定数量的运行时代码。
    //  通常，大家说一个语言“没有运行时”，是指这个语言的“运行时”很小。Rust、C都是几乎没有运行时的。

    use std::thread;
    use std::time::Duration;
    use std::sync::mpsc;

    let handle = thread::spawn(
        || {
            for i in 0..5 {
                println!("  spawn thread run {}", i);
                thread::sleep(Duration::from_millis(1));
            }
        }
    );

    for i in 0..5 {
        println!("  main thread run {}", i);
        thread::sleep(Duration::from_millis(1));
    }

    handle.join().unwrap();

    //move闭包
    let v = vec![1, 2, 3];

    let handle = thread::spawn(
        move || {
            println!("  v = {:?}", v);
        }
    );
    //println!("  v = {:?}", v);    //unvalid, v borrowed
    handle.join().unwrap();

    //通道channel

    //1 发送者的send方法返回的是一个Result<T,E>,
    //  如果接收端已经被丢弃了，将没有发送值的目标，此时发送会返回错误。
    //2 接受者的recv返回值也是一个Result类型，当通道发送端关闭时，返回一个错误值。
    //3 接收端这里使用的recv方法，会阻塞到有一个消息到来。我们也可以使用try_recv()，不会阻塞，会立即返回。

    //1 Rust中一个实现消息传递并发的主要工具是通道。
    //  通道由两部分组成，一个是发送端，一个是接收端，发送端用来发送消息，接收端用来接收消息。
    //  发送者或者接收者任一被丢弃时就可以认为通道被关闭了。
    //
    //2 通道介绍
    //  1 通过mpsc::channel，创建通道，mpsc是多个生产者，单个消费者；
    //  2 通过spmc::channel，创建通道，spmc是一个生产者，多个消费者；
    //  3 创建通道后返回的是发送者和消费者，示例：
    //      let (tx, rx) = mpsc::channel();
    //      let (tx, rx) = spmc::channel();

    let (tx, rx) = mpsc::channel();
    let handle = thread::spawn(
        move || {
            let val = String::from("thread");
            tx.send(val.clone()).unwrap();
            println!("  1 Spawn thread Sent: {}", val);
        }
    );
    let received = rx.recv().unwrap();
    println!("  1 Main thread Received: {}", received);
    handle.join().unwrap();

    let (tx, rx) = mpsc::channel();
    let handle = thread::spawn(
        move || {
            let vals = vec![
                String::from("hi"),
                String::from("from"),
                String::from("the"),
                String::from("thread"),
            ];
            for val in vals {
                tx.send(val.clone()).unwrap();
                println!("  2 Spawn thread Sent: {}", val);
                //thread::sleep(Duration::from_secs(1));
            }
        }
    );
    for recv in rx {
        println!("  2 Main thread Received: {}", recv);
    }
    handle.join().unwrap();

    //单个消费者多个生产者的例子
    let (tx1, rx) = mpsc::channel();
    let tx2 = mpsc::Sender::clone(&tx1);

    thread::spawn(
        move || {
            let vals = vec![
                String::from("hi"),
                String::from("from"),
                String::from("the"),
                String::from("thread"),
            ];
            for val in vals {
                tx1.send(val.clone()).unwrap();
                println!("  3 Spawn thread Sent: {}", val);
                thread::sleep(Duration::from_secs(1));
            }
        }
    );

    thread::spawn(
        move || {
            let vals = vec![
                String::from("hi"),
                String::from("from"),
                String::from("the"),
                String::from("thread"),
            ];
            for val in vals {
                tx2.send(val.clone()).unwrap();
                println!("  3 Spawn thread Sent: {}", val);
                thread::sleep(Duration::from_secs(1));
            }
        }
    );

    for recv in rx {
        println!("  3 Main thread Received: {}", recv);
    }

    //1、通道类似于单所有权的方式，值传递到通道后，发送者就无法再使用这个值；
    //2、共享内存类似于多所有权，即多个线程可以同时访问相同的内存位置。

    //互斥器：mutex
    //1、任意时刻，只允许一个线程来访问某些数据;
    //2、互斥器使用时，需要先获取到锁，使用后需要释放锁。
    //Mutex<T>

    use std::sync::Mutex;

    let mutex = Mutex::new(5);

    {
        let mut num = mutex.lock().unwrap();
        *num = 6;
    }   //离开作用域时，自动释放

    println!("  mutex = {:?}", mutex);

    //Mutex<T>是一个智能指针，lock调用返回一个叫做MutexGuard的智能指针
    //内部提供了drop方法，实现当MutexGuard离开作用域时自动释放锁。

    use std::sync::Arc;
    //RefCell<T>/Rc<T> 与Mutex<T>/Arc<T>
    //1、Mutex<T>提供内部可变性，类似于RefCell
    //2、RefCell<T>/Rc<T>是非线程安全的， Mutex<T>/Arc<T>是线程安全的
    //Rc<T> 不是线程安全的
    //let counter = Rc::new(Mutex::new(0));
    //Arc<T>
    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..10 {
        let cnt = Arc::clone(&counter);
        let handle = thread::spawn(
            move || {
                let mut num = cnt.lock().unwrap();
                *num += 1;
            }
        );
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("  result = {}", *counter.lock().unwrap());

    // Sync & Send trait
    // Send trait:
    //   允许在线程间转移所有权
    // Sync trait:
    //   允许多线程访问，可以安全地在多个线程中拥有其值的引用

    println!("thread() - end");
}

//面向对象
fn _object_oriented() {
    _printline();
    println!("object_oriented() - begin");

    //对象与封装
    //Rust里面,结构体,枚举类型加上impl块

    //use get_average;
    //details in "../get_average/src/lib.rs"
    let mut list = get_average::AverCollect::new();
    list.add(1);
    list.add(3);
    println!("  list.average() = {}", list.average());

    //继承
    //Rust无继承,可以通过Trait进行行为共享

    trait A {
        fn sum(&self) {
            //Do something
        }
    };
    struct XXX {}
    impl XXX {
        fn new() -> XXX {
            XXX {}
        }
    }
    impl A for XXX {}

    let x = XXX::new();
    x.sum();

    //trait 对象
    pub trait Draw {
        fn draw(&self);
    }

    pub struct Screen {
        pub components: Vec<Box<dyn Draw>>, //trait对象,使用dyn关键字
    }

    //pub struct Screen<T: Draw> {
    //    pub components: Vec<T>,
    //}

    impl Screen {
        pub fn run(&self) {
            for comp in self.components.iter() {
                comp.draw();
            }
        }
    }

    //impl<T> Screen <T>
    //    where T: Draw {
    //    pub fn run(&self) {
    //        for comp in self.components.iter() {
    //            comp.draw();
    //        }
    //    }
    //}

    pub struct Button {
        pub width:  u32,
        pub height: u32,
        pub label:  String,
    }

    impl Draw for Button {
        fn draw(&self) {
            println!("  draw button, width = {}, height = {}, label = {}", self.width, self.height, self.label);
        }
    }

    pub struct SelectBox {
        pub width:  u32,
        pub height: u32,
        pub opt:    Vec<String>,
    }

    impl Draw for SelectBox {
        fn draw(&self) {
            println!("  draw select_box, width = {}, height = {}, option = {:?}", self.width, self.height, self.opt);
        }
    }

    let s = Screen {
        components: vec![
            Box::new(Button{
                width:   50,
                height:  10,
                label:   String::from("button"),
            }),
            Box::new(SelectBox{
                width:   50,
                height:  10,
                opt:  vec![
                    String::from("Yes"),
                    String::from("No"),
                    String::from("MayBe"),
                ]
            })
        ],
    };
    s.run();

    //1 trait对象动态分发
    //  1 在上述例子中，对泛型类型使用 trait bound 编译器进行的方式是单态化处理，单态化的代码进行的是静态分发（就是说编译器在编译的时候就知道调用了什么方法）。
    //  2 使用 trait 对象时，Rust 必须使用动态分发。
    //    编译器无法知晓所有可能用于 trait 对象代码的类型，所以它也不知道应该调用哪个类型的哪个方法实现。
    //    为此，Rust 在运行时使用 trait 对象中的指针来知晓需要调用哪个方法。
    //
    //2 trait对象要求对象安全
    //  只有 对象安全(object safe)的 trait 才可以组成 trait 对象。trait的方法满足以下两条要求才是对象安全的：
    //    1 返回值类型不为 Self
    //    2 方法没有任何泛型类型参数

    //Clone
    //pub trait Clone {
    //    fn clone(&self) -> Self;
    //}

    //pub struct _Screen {
    //    pub com: Vec<Box<dyn Clone>>,
    //}

    println!("object_oriented() - end");
}

//模式
fn _pattern() {
    _printline();
    println!("pattern() - begin");

    //1 模式是Rust中特殊的语法，模式用来匹配值的结构。
    //
    //2 模式由如下内容组成：
    //  1 字面值
    //  2 解构的数组、枚举、结构体或者元组
    //  3 变量
    //  4 通配符
    //  5 占位符

    //1 match
    println!("  1 match");
    //match VALUE {
    //    PATTERN => EXPRESSION,
    //    PATTERN => EXPRESSION,
    //    PATTERN => EXPRESSION,
    //}
    //必须匹配完所有的情况
    //fn main() {
    //    let a = 1;
    //    match a {
    //        0 => println!("Zero"),
    //        1 => println!("One"),
    //        _ => println!("other"),
    //    };
    //    println!("Hello, world!");
    //}

    //if let
    println!("  2 if let");
    //fn main() {
    //    let color: Option<&str> = None;
    //    let is_ok = true;
    //    let age: Result<u8, _> = "33".parse();
    //
    //    if let Some(c) = color {
    //        println!("color: {}", c);
    //    } else if is_ok {
    //        println!("is ok");
    //    } else if let Ok(a) = age {
    //        if a > 30 {
    //            println!("oh, mature man");
    //        } else {
    //            println!("oh, young man");
    //        }
    //    } else {
    //        println!("in else");
    //    }
    //}

    //while let
    println!("  3 while let");
    //只要模式匹配就一直执行while循环
    //fn main() {
    //    let mut stack = Vec::new();
    //    stack.push(1);
    //    stack.push(2);
    //    stack.push(3);
    //
    //    while let Some(top) = stack.pop() {
    //        println!("top = {}", top);
    //    }//只要匹配Some(value),就会一直循环
    //}

    //for
    println!("  4 for");
    ////在for循环中，模式是直接跟随for关键字的值，例如 for x in y，x就是对应的模式
    //fn main() {
    //    let v = vec!['a', 'b', 'c'];
    //    for (index, value) in v.iter().enumerate() {
    //        println!("index: {}, value: {}", index, value);
    //    }
    //}
    //此处的模式是(index, value)

    //let
    println!("  5 let");
    //let PATTERN = EXPRESSION
    //fn main() {
    //    let (x, y, z) = (1, 2, 3); //(1, 2, 3)会匹配(x, y, z)，将1绑定到x，2绑定到y，3绑定到z
    //    println!("{}, {}, {}", x, y, z);
    //
    //    let (x, .., z) = (1, 2, 3);
    //    println!("{}, {}", x, z);
    //}

    //函数 函数的参数也是模式
    println!("  6 function");
    //fn print_point(&(x, y): &(i32, i32)) {
    //    println!("x: {}, y: {}", x, y);
    //}

    //模式在使用它的地方并不都是相同的，模式存在不可反驳的和可反驳的
    //1 模式有两种：refutable（可反驳的）和 irrefutable（不可反驳的）。
    //  能匹配任何传递的可能值的模式被称为是不可反驳的。
    //  对值进行匹配可能会失败的模式被称为可反驳的。
    //
    //2 只能接受不可反驳模式的有：函数、let语句、for循环。
    //  原因：因为通过不匹配的值程序无法进行有意义的工作。
    //
    //3 if let和while let表达式被限制为只能接受可反驳的模式，因为它们的定义就是为了处理有可能失败的条件。

    //1 匹配字面值
    //fn main() {
    //    let x = 1;
    //    match x {
    //        1 => println!("one"),
    //        2 => println!("two"),
    //        _ => println!("xx"),
    //    };
    //
    //    println!("Hello, world!");
    //}

    //2 匹配命名变量
    //fn main() {
    //    let x = Some(5);
    //    let y = 10; //位置1
    //    match x {
    //        Some(50) => println!("50"),
    //        Some(y) => println!("value = {}", y), //此处的y不是位置1的y
    //        _ => println!("other"),
    //    };
    //
    //    println!("x = {:?}, y = {:?}", x, y); //此处的y是位置1的y
    //}

    //3 多个模式
    //fn main() {
    //    let x = 1;
    //    match x {
    //        1|2 => println!("1 or 2"), //|表示是或，匹配1或者2
    //        3 => println!("3"),
    //        _ => println!("xx"),
    //    };
    //}

    //4 通过..匹配
        //let x = 5;

    //match x {
    //    1..=5 => println!("1 to 5"), // 1|2|3|4|5 => println!("1 to 5"),
    //    _ => println!("xx"),
    //};

    //let x = 'c';
    //match x {
    //    'a'..='j' => println!("1"),
    //    'k'..='z' => println!("2"),
    //    _ => println!("other"),
    //}

    //解构并分解值
    //解构元祖、结构体、枚举、引用
    //
    //解构结构体
    struct Point {
        x: i32,
        y: i32,
    }

    let p = Point{x: 1, y: 2};
    let Point{x: a, y: b} = p;//变量a和变量b匹配x和y
    assert_eq!(1, a);
    assert_eq!(2, b);

    let Point{x, y} = p;
    assert_eq!(1, x);
    assert_eq!(2, y);

    let p = Point{x: 1, y: 0};
    match p {
        Point{x: _, y: 0} => println!("  x axis"),
        Point{x: 0, y: _} => println!("  y axis"),
        Point{x: _, y: _} => println!("  other"),
    };

    /*
    enum Message {
        Quit,
        Move{x: i32, y: i32},
        Write(String),
        ChangeColor(i32, i32, i32),
    }
    let msg = Message::ChangeColor(0, 160, 255);
    match msg {
        Message::Quit => {
            println!("quit");
        },
        Message::Move{x, y} => {
            println!("move, x: {}, y: {}", x, y);
        },
        Message::Write(text) => println!("write msg: {}", text),
        Message::ChangeColor(r, g, b) => {
            println!("clolor, r: {}, g: {}, b: {}", r, g, b);
        },
    };

    enum Color {
    Rgb(i32, i32, i32),
    Hsv(i32, i32, i32),
    }

    enum Message {
    Quit,
    Move{x: i32, y: i32},
    Write(String),
    ChangeColor(Color),
    }

    let msg = Message::ChangeColor(Color::Hsv(0, 160, 255));
    match msg {
        Message::ChangeColor(Color::Rgb(r, g, b)) => {
            println!("rgb color, r: {}, g: {}, b: {}", r, g, b);
        },
        Message::ChangeColor(Color::Hsv(h, s, v)) => {
            println!("hsv color, h: {}, s: {}, v: {}", h, s, v);
        },
         _ => ()
    };

    let ((a, b), Point{x, y}) = ((1, 2), Point{x: 3, y: 4});

    */

    //忽略模式中的值
    //fn foo(_: i32, y: i32) {
    //    println!("y = {}", y);
    //}
    //
    //trait A {
    //    fn bar(x: i32, y: i32);
    //}
    //
    //struct B {}
    //
    //impl A for B {
    //    fn bar(_: i32, y: i32) {
    //        println!("y = {}", y);
    //    }
    //}

    //foo(1, 2);
    //
    //let numbers = (1, 2, 3, 4);
    //match numbers {
    //    (one, _, three, _) => {
    //        println!("one: {}, three: {}", one, three);
    //    },
    //}

    //let s = Some(String::from("hello"));
    //if let Some(_c) = s {
    ////if let Some(c) = s {
    //    println!("found a string");
    //}
    ////println!("s: {:?}", s);

    let s = Some(String::from("hello"));
    if let Some(_) = s {
        println!("  found a string");
    }

    let numbers = (1, 2, 3, 4, 5, 6, 7);
    match numbers {
        (first, .., last) => {
            println!("  first: {}, last: {}", first, last);
        },
    };

    //error
    //match numbers {
    //    (.., second, ..) => {
    //        println!("  {}", second);
    //    },
    //};

    //7 匹配守卫提供额外的条件
    //匹配守卫是一个指定于match分之模式之后的额外的if条件，必须满足才能选择此分支。
    //fn main() {
    //    let num = Some(4);
    //    match num {
    //        Some(x) if x < 5 => println!("< 5"),
    //        Some(x) => println!("x: {}", x),
    //        None => (),
    //    };
    //
    //    println!("Hello, world!");
    //}

    let num = Some(4);
    let y = 10; //位置1
    match num {
        Some(x) if x == y => println!("  num == y"),//此处的y是位置1处的y
        Some(x) => println!("  x: {}", x),
        None => (),
    };

    let x = 4;
    let y = false;
    match x {
        4|5|6 if y => println!("  1"),//4|5|6 if y  a: 4|5|(6 if y)   b: ((4|5|6) if y)(等价于此种)
        _ => println!("  2"),
    }

    //@运算符允许我们在创建一个存放值的变量的同时，测试这个变量的值是否匹配模式。
    enum Message {
        Hello{id: i32},
    }
    let msg = Message::Hello{id: 25};
    match msg {
        Message::Hello{id: id_va @ 3..=7} => {
            println!("  id_va: {}", id_va);
        },
        Message::Hello{id: 10..=20} => {
            println!("  large");
        },
        Message::Hello{id} => {
            println!("  id: {}", id);
        },
    }

    println!("pattern() - end");
}

fn main() {
    _generic();
    _trait();
    _lifetimes();
    _closure();
    _iterator();
    _cargo();
    _box();
    _deref();
    _drop();
    _rc();
    _refcell();
    _advanced_ref();
    _tree();
    _thread();
    _object_oriented();
    _pattern();
    _printline();
}
