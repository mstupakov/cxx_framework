#ifndef __TIMER_H__
#define __TIMER_H__

namespace SYS {
  unsigned int Sleep(unsigned int sec);
  unsigned int USleep(unsigned int usec);
  double GetCurrentTime();
};

#endif /* __TIMER_H__ */

