#include <cstdint>
#include <cstdio>
#include <cstdlib>

extern "C" {

extern void LsSecInit(void *, int);
extern int LsSec1stStage(void *, void *);

}

int main() {
  void *data = std::malloc(8408);

  LsSecInit(data, 20220307);

  uint64_t stage_1;

  auto err = LsSec1stStage(data, &stage_1);

  printf("err = %d; stage_1 = %lu;\n", err, stage_1);

  return 0;
}
