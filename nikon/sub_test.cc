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

} // namespace
} // namespace ls_sec
