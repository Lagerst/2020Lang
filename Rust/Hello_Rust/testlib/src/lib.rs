pub mod animal;

#[cfg(test)]
mod tests {
    #[test]
    fn it_works() {
        assert_eq!(2 + 2, 4);
    }

    use crate::animal::*;

    #[test]
    fn cat_works() {
        assert_eq!(cat::write(),true);
    }

    #[test]
    fn dog_works() {
        assert_eq!(dog::write(),true);
    }
}
