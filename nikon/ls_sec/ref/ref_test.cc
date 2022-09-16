/*
 * This file aims to test against the LSSec reference implementation.
 *
 * The original shared object files are disassembel and individual funcions are
 * then re-assembled using assembly as close to the original as possible, then
 * the data they operate on is checked to see if it matches what our
 * implementation would do with the same data.
 *
 */

#include <cstdint>
#include <vector>

#include "../ls_sec.h"

#include "gtest/gtest.h"


extern "C" {
int64_t LsSecInit(uint8_t *a1, uint64_t a2);
int64_t LsSec1stStage(uint8_t *a1, uint64_t *a2);
int64_t LsSec2ndStage(uint8_t *a1, uint64_t *a2, uint64_t *a3, uint64_t *a4);
}

namespace ls_sec {
namespace {

constexpr uint64_t kOk = 0;
constexpr uint64_t kWrongStage = std::numeric_limits<uint32_t>::max() - 102;

constexpr uint64_t kSeed = 1;
constexpr uint64_t kStage1 = 14277390700105796459ULL;
constexpr uint64_t kStage2 = 14486366436481708883ULL;

TEST(LsSec, Init) {
  std::vector<uint8_t> buf(8408);

  srand(1);
  uint64_t rand_1 = rand();

  srand(1);
  // RNG is not touched:
  LsSecInit(&buf[0], 0);

  EXPECT_EQ(rand(), rand_1);
  for (const uint8_t& b : buf) {
    EXPECT_EQ(b, (&b - &buf[0] == 8400) ? 1 : 0);
  }

  // RNG is reset:
  LsSecInit(&buf[0], 1);

  EXPECT_EQ(rand(), rand_1);
  for (const uint8_t& b : buf) {
    EXPECT_EQ(b, (&b - &buf[0] == 8400) ? 1 : 0);
  }
}

TEST(LsSec, Stage1) {
  uint64_t res;
  std::vector<uint8_t> buf(8408);

  EXPECT_EQ(LsSec1stStage(&buf[0], &res), kWrongStage);

  LsSecInit(&buf[0], kSeed);
  EXPECT_EQ(LsSec1stStage(&buf[0], &res), kOk);
  EXPECT_EQ(res, kStage1);

  LsSec ls_sec(kSeed);
  EXPECT_EQ(ls_sec.stage_1(), kStage1);

  for (const uint8_t& b : buf) {
    EXPECT_EQ(b, (&b - &buf[0] == 8400) ? 3 : 0);
  }
}

TEST(LsSec, Stage2) {
  std::pair<uint64_t, uint64_t> res;
  std::vector<uint8_t> buf(8408);

  uint64_t stage_1 = kStage1;
  EXPECT_EQ(LsSec2ndStage(&buf[0], &stage_1, &res.first, &res.second), kWrongStage);
  EXPECT_EQ(stage_1, kStage1);

  LsSecInit(&buf[0], kSeed);
  EXPECT_EQ(LsSec2ndStage(&buf[0], &stage_1, &res.first, &res.second), kOk);
  EXPECT_EQ(stage_1, kStage1);

  EXPECT_EQ(res.first, kStage1);
  EXPECT_EQ(res.second, kStage2);

  LsSec ls_sec(kSeed);
  const std::pair<uint64_t, uint64_t> stage_2 = ls_sec.stage_2(kStage1);
  EXPECT_EQ(stage_2.first, kStage1);
  EXPECT_EQ(stage_2.second, kStage2);

  // index_
  const uint8_t index = 1;
  EXPECT_EQ(buf[0], index);
  // EXPECT_EQ(ls_sec.index_, index); // private

  const uint64_t secret = 7441507252709985025ULL;
  EXPECT_EQ(ls_sec.secret_, secret);
  EXPECT_EQ(*reinterpret_cast<uint64_t*>(&buf[0]), secret);

  EXPECT_EQ(buf[8400], 2);
}

} // namespace
} // namespace ls_sec
