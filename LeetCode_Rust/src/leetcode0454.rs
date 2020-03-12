use std::collections::HashMap;

impl Solution {
    pub fn four_sum_count(a: Vec<i32>, b: Vec<i32>, c: Vec<i32>, d: Vec<i32>) -> i32 {
        let mut hashmap: HashMap<i32, i32> = HashMap::new();
        for i in &a {
            for j in &b {
                let score = hashmap.entry(*i + *j).or_insert(0);
                *score += 1;
            }
        }
        let mut res: i32 = 0;
        for i in &c {
            for j in &d {
                let score = hashmap.get(&(0 - *i - *j));
                if let Some(value) = score {
                    res += value;
                }
            }
        }
        res
    }
}