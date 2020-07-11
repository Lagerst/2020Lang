impl Solution {
    pub fn min_moves2(mut nums: Vec<i32>) -> i32 {
        let (mid, mut res) = ((nums.len() - 1) / 2, 0);
        nums.sort();
        for i in &nums {
            res += (*i - nums[mid]).abs();
        }
        res
    }
}