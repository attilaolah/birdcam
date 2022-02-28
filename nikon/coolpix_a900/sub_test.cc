#include "sub.h"

#include "gtest/gtest.h"

namespace ls_sec {
namespace {

TEST(Sub, sub_A80) {
  {
    std::array<uint64_t, 3> a = {{0}};
    EXPECT_EQ(sub_A80(a.data(), a.size() * 8), 6291260094789511032);
  }
  {
    std::array<uint64_t, 4> a = {{0}};
    EXPECT_EQ(sub_A80(a.data(), a.size() * 8), 15803886854701008152);
  }
}

TEST(Sub, sub_1480) {
  {
    const auto pair = sub_1480(0, 0);
    EXPECT_EQ(pair.first, 13206668983);
    EXPECT_EQ(pair.second, 4107634734);
  }
  {
    const auto pair = sub_1480(1234, 5678);
    EXPECT_EQ(pair.first, 1550836812);
    EXPECT_EQ(pair.second, 4890505416);
  }
}

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

TEST(Sub, sub_1A80) {
  std::array<uint8_t, 8> dst = {{0, 1, 2, 3, 4, 5, 6, 7}};
  std::array<uint8_t, 4> src = {{9, 8, 7, 6}};
  std::array<uint8_t, 8> exp;

  sub_1A80(dst.data(), src.data(), 2);
  exp = {{9, 8, 2, 3, 4, 5, 6, 7}};
  EXPECT_EQ(dst, exp);

  sub_1A80(dst.data(), src.data(), 4);
  exp = {{9, 8, 7, 6, 4, 5, 6, 7}};
  EXPECT_EQ(dst, exp);
}

TEST(Sub, sub_1C20) {
  {
    std::array<uint8_t, 0> a;
    EXPECT_FALSE(sub_1C20(a.data(), a.data(), 0));
  }
  {
    std::array<uint8_t, 6> a = {{0, 1, 2, 3, 4, 5}};
    EXPECT_FALSE(sub_1C20(a.data(), a.data(), 6));
  }
  {
    std::array<uint8_t, 8> a = {{0, 1, 2, 3, 4, 5, 6, 7}};
    std::array<uint8_t, 8> b = {{0, 1, 2, 3, 4, 5, 9, 7}};
    EXPECT_FALSE(sub_1C20(a.data(), b.data(), 6));
    EXPECT_TRUE(sub_1C20(a.data(), b.data(), 7));
    EXPECT_TRUE(sub_1C20(a.data(), b.data(), 8));
  }
}

} // namespace
} // namespace ls_sec
