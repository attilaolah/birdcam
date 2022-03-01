#include "sub.h"

#include "gtest/gtest.h"

namespace ls_sec {
namespace {

TEST(Sub, entangle) {
  EXPECT_EQ(entangle({}), 578437695752307201ULL);
  EXPECT_EQ(entangle({1}), 1669531122762555401LLU);
  EXPECT_EQ(entangle({1, 2, 3}), 15820024228735435700LLU);
  EXPECT_EQ(entangle({1, 2, 3, 4}), 5425026146954082698LLU);
}

TEST(Sub, sub_1A40) {
  EXPECT_EQ(sub_1A40(0x00000000), 0x00000000);
  EXPECT_EQ(sub_1A40(0xaabbccdd), 0xddccbbaa);
  EXPECT_EQ(sub_1A40(0x12345678), 0x78563412);
  EXPECT_EQ(sub_1A40(0xffffffff), 0xffffffff);
}

} // namespace
} // namespace ls_sec
