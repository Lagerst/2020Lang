impl Solution {
    pub fn gcd_of_strings(str1: String, str2: String) -> String {
        if (str1.clone() + &str2.clone() != str2.clone() + &str1.clone()) { return "".to_string(); };
        return str1.as_str()[0..Solution::gcd(str1.len(), str2.len())].to_string();
    }
    pub fn gcd(a: usize, b: usize) -> usize{
        if b == 0 {
            a
        }  else {
            Solution::gcd(b , a % b)
        }
    }
}