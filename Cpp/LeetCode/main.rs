pub mod leetcode0703;

fn main() {
    let k = 3;
    let nums: Vec<i32> = vec![4,5,8,2];
    let mut obj = leetcode0703::KthLargest::new(k, nums);
    println!("{}",obj.add(3));
    println!("{}",obj.add(5));
    println!("{}",obj.add(10));
    println!("{}",obj.add(9));
    println!("{}",obj.add(4));
    /*
    kthLargest.add(3);   // returns 4
    kthLargest.add(5);   // returns 5
    kthLargest.add(10);  // returns 5
    kthLargest.add(9);   // returns 8
    kthLargest.add(4);   // returns 8
    */
}