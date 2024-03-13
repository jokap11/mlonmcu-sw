#include "mlonmcu.h"
#include "target.h"
#include "exit.h"
#include "bench.h"
#include "printing.h"
#include <stdio.h>

// void init_target();
// void deinit_target();

int main() {
  int ret = 0;
  // pre
  target_init();
  mlonmcu_printf("Program start.\n");

  // main
  start_bench(TOTAL);
  start_bench(INIT);
  ret = mlonmcu_init();
  stop_bench(INIT);
  if (ret) {
    goto cleanup;
  }
  start_bench(RUN);
    ret = mlonmcu_check();
  stop_bench(RUN);
  if (ret) {
    goto cleanup;
  }
  // start_bench(DEINIT);
  ret = mlonmcu_deinit();
  // stop_bench(DEINIT);
  if (ret) {
    goto cleanup;
  }

cleanup:
  stop_bench(TOTAL);

  // post
  print_bench(INIT);
  print_bench(RUN);
  // print_bench(DEINIT);
  print_bench(TOTAL);
  mlonmcu_printf("Program finish.\n");
  target_deinit();

  mlonmcu_exit(ret);
  return ret;
}
