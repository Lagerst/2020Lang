#include <iostream>

enum Direction { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

namespace myenum {
// 一般的枚举
enum PieceType { PieceTypeKing, PieceTypeQueen, PieceTypeRook, PieceTypePawn };

// 设置了值得枚举
enum PieceTypeAnother {
  PieceTypeKingA = 1,
  PieceTypeQueenA,
  PieceTypeRookA = 10,
  PieceTypePawnA
};
// 强类型的枚举
enum class MyEnum { EnumValue1, EnumValue2 = 10, EnumValue3 };
// 改变了类型的强类型枚举
enum class MyEnumLong : unsigned long {
  EnumValueLong1,
  EnumValueLong2 = 10,
  EnumValueLong3
};

template <typename T>
std::ostream &operator<<(
    typename std::enable_if<std::is_enum<T>::value, std::ostream>::type &stream,
    const T &e) {
  return stream << static_cast<typename std::underlying_type<T>::type>(e);
}
} // namespace myenum

int main() {
  // enum Direction d = 1; //wrong

  std::cout << "test enum" << std::endl;
  std::cout << "一般的枚举" << myenum::PieceType::PieceTypeKing << std::endl;
  std::cout << "设置了值的枚举" << myenum::PieceTypeAnother::PieceTypeQueenA
            << std::endl;
  std::cout << "强类型的枚举" << myenum::MyEnum::EnumValue3 << std::endl;
  std::cout << "改变了类型的强类型枚举" << myenum::MyEnumLong::EnumValueLong1
            << std::endl;

  std::cout << "end of this program" << std::endl;
}