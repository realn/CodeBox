
#include <CBCore/Flags.h>

ENUM_FLAG(TestFlag) {
  Flag1, Flag2
};

void func(TestFlags flags) {

}

int main(int argc, char* argv[]) {
  TestFlags flag = TestFlag::Flag1;

  flag |= TestFlag::Flag2;

  func(TestFlags(TestFlag::Flag1) | TestFlag::Flag2);

  return 0;
}