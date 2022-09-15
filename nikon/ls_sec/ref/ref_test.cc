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

#include "ref.h"

#include "gtest/gtest.h"

namespace ls_sec::ref {
namespace {

TEST(LsSec, LsSec) {
  std::vector<uint8_t> buf(8408);
  LsSecInit(&buf[0], 0);

  for (const uint8_t& b : buf) {
    EXPECT_EQ(b, (&b - &buf[0] == 8400) ? 1 : 0);
  }
}

} // namespace
} // namespace ls_sec::ref
