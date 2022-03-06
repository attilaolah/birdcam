#include "ls_sec.h"

#include "gtest/gtest.h"

namespace ls_sec {
namespace {

TEST(LsSec, LsSec) { const LsSec ls_sec(42); }

TEST(LsSec, stage_1) {
  LsSec ls_sec(1);

  EXPECT_EQ(ls_sec.stage_1(), 7749363893351949254LLU);

  // Calling stage_1() again: wrong stage.
  EXPECT_THROW(ls_sec.stage_1(), ErrWrongStage);
}

TEST(LsSec, stage_2) {
  LsSec ls_sec(2);

  const uint64_t stage_1 = ls_sec.stage_1();

  const std::pair<uint64_t, uint64_t> stage_2 = LsSec(1).stage_2(stage_1);
  EXPECT_EQ(stage_2.first, 7749363893351949254LLU);
  EXPECT_EQ(stage_2.second, 3692570941250695308LLU);

  // Calling stage_2() again: wrong stage.
  EXPECT_THROW(ls_sec.stage_2(stage_1), ErrWrongStage);
}

TEST(LsSec, stage_3) {
  LsSec ls_sec(3);

  // Calling stage_3() before stage_1(): wrong stage.
  EXPECT_THROW(ls_sec.stage_3(0, 0, 0), ErrWrongStage);

  const uint64_t stage_1 = ls_sec.stage_1();

  // Calling stage_3() with wrong data: auth error.
  EXPECT_THROW(ls_sec.stage_3(0, 0, 0), ErrAuth);
  EXPECT_THROW(ls_sec.stage_3(1, stage_1, 3), ErrAuth);

  const std::pair<uint64_t, uint64_t> stage_2 = LsSec(1).stage_2(stage_1);
  const uint64_t stage_3 =
      ls_sec.stage_3(stage_2.first, stage_1, stage_2.second);
  EXPECT_EQ(stage_3, 1123151823067396199LLU);

  // Calling stage_3() again: wrong stage.
  EXPECT_THROW(ls_sec.stage_3(stage_2.first, stage_1, stage_2.second),
               ErrWrongStage);
}

TEST(LsSec, stage_4) {
  LsSec ls_sec_a(4);
  LsSec ls_sec_b(4);

  // Calling stage_4() before stage_2(): wrong stage.
  EXPECT_THROW(ls_sec_b.stage_4(0, 0, 0), ErrWrongStage);

  const uint64_t stage_1 = ls_sec_a.stage_1();
  const std::pair<uint64_t, uint64_t> stage_2 = ls_sec_b.stage_2(stage_1);
  const uint64_t stage_3 =
      ls_sec_a.stage_3(stage_2.first, stage_1, stage_2.second);

  // Calling stage_4() with wrong data: auth error.
  EXPECT_THROW(ls_sec_b.stage_4(0, 0, 0), ErrAuth);

  // No exception.
  ls_sec_b.stage_4(stage_2.first, stage_1, stage_3);

  // Calling stage_3() again: wrong stage.
  EXPECT_THROW(ls_sec_b.stage_4(stage_2.first, stage_1, stage_3),
               ErrWrongStage);
}

} // namespace
} // namespace ls_sec
