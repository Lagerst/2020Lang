impl Solution {
    pub fn is_unique(astr: String) -> bool {
        let mut s: [i32; 256] = [0; 256];
        for i in astr.chars() {
            if s[i as usize] == 1 {
                return false;
            }
            s[i as usize] = 1;
        }
        true
    }
}