impl Solution {
    pub fn convert_to_title(n: i32) -> String {
        let map = vec!['A','B','C','D','E','F','G','H','I','J','K','I','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'];
        let (mut res, mut n2) = (String::new(), n);
        loop{
            n2 -= 1;
            res.push(map[(n2 % 26) as usize]);
            n2 /= 26;
            if (n2 == 0) {
                break;
            }
        }
        res.chars().rev().collect()
    }
}