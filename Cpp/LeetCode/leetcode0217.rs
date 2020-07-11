use std::collections::HashSet;
impl Solution {
    pub fn contains_duplicate(nums: Vec<i32>) -> bool {
        let mut map: HashSet<i32> = HashSet::new();
        for i in &nums {
            if let Some(_) = map.get(i){
                return true;
            } else {
                map.insert(*i);
            }
        }
        false
    }
}