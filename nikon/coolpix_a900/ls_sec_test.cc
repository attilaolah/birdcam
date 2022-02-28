#include "ls_sec.h"

#include "gtest/gtest.h"

namespace ls_sec {
namespace {

TEST(LsSec, LsSec) { const LsSec ls_sec(42); }

TEST(LsSec, stage_1) {
  LsSec ls_sec(4);

  EXPECT_EQ(ls_sec.stage_1(), 0x33522611DD7D4E75LLU);

  // Calling stage_1() again: wrong stage!
  EXPECT_THROW(ls_sec.stage_1(), ErrWrongStage);
}

} // namespace
} // namespace ls_sec
