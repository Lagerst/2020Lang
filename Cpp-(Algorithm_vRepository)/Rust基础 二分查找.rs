impl Solution {
    pub fn search_insert(nums: Vec<i32>, target: i32) -> i32 {
        let mut left:i32 = 0;
        let mut right:i32 = nums.len() as i32 - 1;
        while (left<=right) {
            let mid:i32 = ( left + right ) / 2;
            if let Some(value) = nums.get(mid as usize) {
                if *value > target {
                    right = mid - 1;
                } else if *value < target {
                    left = mid + 1;
                } else {
                    return mid;
                }
            }
        }
        return left;
    }
}