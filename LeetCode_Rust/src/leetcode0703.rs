pub struct KthLargest {
    heap:           Vec<i32>,
    size:           usize,
    heap_maxsize:   usize,
}

/*
 * `&self` means the method takes an immutable reference.
 * If you need a mutable reference, change it to `&mut self` instead.
 */
impl KthLargest {

    pub fn new(k: i32, nums: Vec<i32>) -> Self {
        let mut New_Heap = KthLargest {
            heap            :   vec![-1],
            size            :   0 as usize,
            heap_maxsize    :   k as usize,
        };
        for i in &nums {
            New_Heap.add(*i);
        }
        New_Heap
    }

    pub fn add(&mut self, val: i32) -> i32 {
        if self.size < self.heap_maxsize {
            self.heap.push(val);
            self.size += 1;
            self.up(self.size);
        } else if self.heap[1] < val {
            self.heap[1] = val;
            self.down(1);
        }
        self.heap[1]
    }

    fn up(&mut self, location: usize) {
        if (location >> 1 > 0) && (self.heap[location >> 1] > self.heap[location]) {
            self.adjust(location >> 1, location);
            self.up(location >> 1);
        }
    }

    fn down(&mut self, location: usize) {
        if ((location << 1) + 1 <= self.size) && (self.heap[(location << 1) + 1] <= self.heap[(location << 1)]) && (self.heap[(location << 1) + 1] < self.heap[location]) {
            self.adjust(((location << 1) + 1) as usize, location as usize);
        } else if ((location << 1) == self.size) && (self.heap[(location << 1)] < self.heap[location]) || ((location << 1) + 1 <= self.size) && (self.heap[(location << 1) + 1] >= self.heap[(location << 1)]) && (self.heap[(location << 1)] < self.heap[location]) {
            self.adjust((location << 1) as usize, location as usize);
        }
    }

    fn adjust(&mut self, i: usize, j: usize) {
        self.heap.swap(i, j);
        self.down(i);
    }
}

/*
 * Your KthLargest object will be instantiated and called as such:
 * let obj = KthLargest::new(k, nums);
 * let ret_1: i32 = obj.add(val);
 */