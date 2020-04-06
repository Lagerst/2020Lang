impl Solution {
    pub fn fib(n: i32) -> i32 {
        let (mut a, mut b, mut c) = (1, 2, 2);
        if n == 2 || n == 1 {
            c = 1;
        } else if n == 0 {
            c = 0;
        } else {
            for i in 4..n + 1 {
                c = a + b;
                a = b;
                b = c;
            }
        }
        c
    }
}