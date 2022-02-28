#include "sub.h"

#include "gtest/gtest.h"

namespace ls_sec {
namespace {

TEST(Sub, sub_1A10) {
  EXPECT_EQ(sub_1A10(0x00000000), 0x00000000);
  EXPECT_EQ(sub_1A10(0xaabbccdd), 0xddccbbaa);
  EXPECT_EQ(sub_1A10(0x12345678), 0x78563412);
  EXPECT_EQ(sub_1A10(0xffffffff), 0xffffffff);
}

TEST(Sub, sub_1A40) {
  EXPECT_EQ(sub_1A40(0x00000000), 0x00000000);
  EXPECT_EQ(sub_1A40(0xaabbccdd), 0xddccbbaa);
  EXPECT_EQ(sub_1A40(0x12345678), 0x78563412);
  EXPECT_EQ(sub_1A40(0xffffffff), 0xffffffff);
}

} // namespace
} // namespace ls_sec
