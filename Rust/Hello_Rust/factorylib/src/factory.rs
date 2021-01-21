pub mod producer_refrigerator {
    pub fn produce_r() {
        println!("  Inmod: refrigerator produced");
    }
}
pub mod producer_washingmachine {
    pub fn produce_w() {
        println!("  Inmod: washing machine produced");
    }
}

pub mod a {
    #[derive(Debug)]
    pub struct B {
        pub num: i32,
        name: String,
    }
    impl B {
        pub fn new_b() -> B {
            B{
                num: 1,
                name: String::from("B"),
            }
        }
        pub fn print_b(&self) {
            println!("  Inmod_struct: num = {}, name = {}",self.num,self.name);
        }
    }
}