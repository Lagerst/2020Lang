    //trait 对象
    pub trait Draw {
        fn draw(&self);
    }

    pub struct Screen {
        pub components: Vec<Box<dyn Draw>>, //trait对象,使用dyn关键字
    }

    impl Screen {
        pub fn run(&self) {
            for comp in self.components.iter() {
                comp.draw();
            }
        }
    }

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

#[cfg(test)]
mod tests {
    use crate::Screen;
    use crate::Button;
    use crate::SelectBox;
    #[test]
    fn it_works() {
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
    }
}
