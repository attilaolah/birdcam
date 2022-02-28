#include "ls_sec.h"

#include "gtest/gtest.h"

namespace ls_sec {
namespace {

TEST(LsSec, LsSec) { const LsSec ls_sec(42); }

TEST(LsSec, stage_1) {
  LsSec ls_sec(4);

  std::array<uint8_t, 8> exp = {{0x75, 0x4E, 0x7D, 0xDD, 0x11, 0x26, 0x52, 0x33}};
  EXPECT_EQ(ls_sec.stage_1(), exp);
}

} // namespace
} // namespace ls_sec
