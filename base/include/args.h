#ifndef __ARGS_H__
#define __ARGS_H__

#include <vector>
#include <string>
#include <algorithm>

class Args {
  std::vector<std::string> m_args;

  public:
    Args(int argc, char *argv[]) {
      for (int i = 0; i < argc; ++i) {
        m_args.push_back(std::string(argv[i]));
      }
    }

    bool Has(const char *arg) {
      return m_args.end() != std::find(m_args.begin(),
                                       m_args.end(), std::string(arg));
   }
};

#endif /* __ARGS_H__ */

