impl Solution {
    pub fn can_three_parts_equal_sum(a: Vec<i32>) -> bool {
        let mut sum: i32 = 0;
        for i in &a {
            sum += *i;
        }
        if sum / 3 * 3 != sum {
            return false;
        }
        sum /= 3;
        let mut now_sum: i32 = 0;
        let mut cnt = 0;
        let mut reset = true;
        for i in &a {
            now_sum += *i;
            reset = false;
            if now_sum == sum && cnt != 2 {
                now_sum = 0;
                cnt += 1;
                reset = true;
            }
        }
        if cnt != 2 || now_sum != sum || reset {
            false
        } else {
            true
        }
    }
}