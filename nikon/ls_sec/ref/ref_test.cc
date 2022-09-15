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

extern "C" {
int64_t LsSecInit(uint8_t *a1, int64_t a2);
int64_t LsSec1stStage(int64_t a1, int64_t a2);
}

#include "gtest/gtest.h"

namespace ls_sec::ref {
namespace {

TEST(LsSec, LsSec) {
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
}

} // namespace
} // namespace ls_sec::ref
