#include <iostream>

#include "args.h"
#include "wm.h"

int main(int argc, char *argv[]) {

  try {
    WM(Args(argc, argv)).Run();
  } catch (...) {
    std::cerr << "Unexpected error..." << std::endl;
  }

  return 0;
}
