#include "ls_sec.h"

#include "gtest/gtest.h"

namespace ls_sec {
namespace {

TEST(LsSec, LsSec) { const LsSec ls_sec(42); }

TEST(LsSec, stage_1) {
  LsSec ls_sec(4);

  std::array<uint8_t, 8> exp = {{0, 1, 2, 3, 4, 5, 6, 7}};
  EXPECT_EQ(ls_sec.stage_1(), exp);
}

} // namespace
} // namespace ls_sec
