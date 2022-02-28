#include "sub.h"

#include "gtest/gtest.h"

namespace ls_sec {
namespace {

TEST(Sub, entangle) {
  EXPECT_EQ(entangle({}), 578437695752307201ULL);
  EXPECT_EQ(entangle({1}), 12502495346761032393ULL);
  EXPECT_EQ(entangle({1, 2, 3}), 6787725047722962626ULL);
  EXPECT_EQ(entangle({1, 2, 3, 4}), 16450132560130177968ULL);
}

TEST(Sub, sub_1480) {
  {
    const auto pair = sub_1480(0, 0);
    EXPECT_EQ(pair.first, 321767095);
    EXPECT_EQ(pair.second, 4107634734);
  }
  {
    const auto pair = sub_1480(1234, 5678);
    EXPECT_EQ(pair.first, 1550836812);
    EXPECT_EQ(pair.second, 595538120);
  }
}

TEST(Sub, sub_1A40) {
  EXPECT_EQ(sub_1A40(0x00000000), 0x00000000);
  EXPECT_EQ(sub_1A40(0xaabbccdd), 0xddccbbaa);
  EXPECT_EQ(sub_1A40(0x12345678), 0x78563412);
  EXPECT_EQ(sub_1A40(0xffffffff), 0xffffffff);
}

} // namespace
} // namespace ls_sec
