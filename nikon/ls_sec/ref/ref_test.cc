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
}

namespace ls_sec {
namespace {

constexpr uint64_t kOk = 0;
constexpr uint64_t kWrongStage = std::numeric_limits<uint32_t>::max() - 102;

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

  constexpr uint64_t seed = 1;
  constexpr uint64_t stage_1 = 14277390700105796459ULL;

  LsSecInit(&buf[0], seed);
  EXPECT_EQ(LsSec1stStage(&buf[0], &res), kOk);
  EXPECT_EQ(res, stage_1);

  LsSec ls_sec(seed);
  EXPECT_EQ(ls_sec.stage_1(), stage_1);

  for (const uint8_t& b : buf) {
    EXPECT_EQ(b, (&b - &buf[0] == 8400) ? 3 : 0);
  }
}

} // namespace
} // namespace ls_sec
