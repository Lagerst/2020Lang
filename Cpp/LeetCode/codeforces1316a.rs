use std::cmp::min;

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

pub fn main() {
   let mut scanner = Scanner::new();
   let t: usize = scanner.next();
   for _ in 0..t {
      let n: usize = scanner.next();
      let m: usize = scanner.next();
      let mut sum = 0;
      for _ in 0..n {
         let now: usize = scanner.next();
         sum += now;
      }
      println!("{}", min(sum, m));
   }
}