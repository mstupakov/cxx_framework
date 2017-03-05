#include <iostream>

#include "args.h"
#include "system.h"

int main(int argc, char *argv[]) {

  try {
    System(Args(argc, argv)).Run();
  } catch (...) {
    std::cerr << "Unexpected error..." << std::endl;
  }

  return 0;
}
