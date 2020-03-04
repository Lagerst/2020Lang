struct Scanner {
    buffer : std::collections::VecDeque<String>
 }

 impl Scanner {

    fn new() -> Scanner {
       Scanner {
          buffer: std::collections::VecDeque::new()
       }
    }

    fn next<T : std::str::FromStr >(&mut self) -> T {
       if self.buffer.len() == 0 {
          let mut input = String::new();
          std::io::stdin().read_line(&mut input).ok();
          for word in input.split_whitespace() {
             self.buffer.push_back(word.to_string())
          }
       }
       let front = self.buffer.pop_front().unwrap();
       front.parse::<T>().ok().unwrap()
    }

}

fn main() {
    let mut scanner = Scanner::new();
    let n : usize = scanner.next();
    for _ in 0..n {
        let num : i32 = scanner.next();
        println!("{}", num);
    }
}