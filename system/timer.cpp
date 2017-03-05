#include <unistd.h>
#include <time.h>
#include "timer.h"

namespace SYS {
  unsigned int Sleep(unsigned int sec) {
    return ::sleep(sec);
  }

  unsigned int USleep(unsigned int usec) {
    return ::usleep(static_cast<useconds_t>(usec));
  }

  double GetCurrentTime() {
    timespec spec;

    ::clock_gettime(CLOCK_MONOTONIC, &spec);
    return ((spec.tv_sec * 1000000000) + spec.tv_nsec) / 1000;
  }
};

