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
    let n : usize = scanner.next();
    let mut r: Vec<i32> = Vec::new();
    let (mut r_win, mut b_win) = (0, 0);
    for _ in 0..n {
        let num : i32 = scanner.next();
        r.push(num);
    }
    for i in 0..n {
        let num : i32 = scanner.next();
        if num > r[i] {
            b_win += 1;
        } else if num < r[i] {
            r_win += 1;
        }
    }
    if r_win == 0 {
        println!("-1");
    } else {
        println!("{}", b_win / r_win + 1);
    }
}