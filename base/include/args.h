#ifndef __ARGS_H__
#define __ARGS_H__

#include <vector>
#include <string>
#include <utility>
#include <algorithm>

class Args {
  typedef std::pair<std::string, std::string> ArgT;
  std::vector<ArgT> m_args;

  public:
    Args(int argc, char *argv[]) {

      for (int i = 1; i < argc; ++i) {
        std::string param(argv[i]);

        std::size_t pos = param.find("=");
        if (pos != std::string::npos) {
          m_args.push_back(std::make_pair(param.substr(0, pos),
                                          param.substr(pos + 1)));
        } else {
          m_args.push_back(std::make_pair(param.substr(0, pos), ""));
        }
      }
    }

    bool Has(const char *arg) {
      return m_args.end() != std::find_if(m_args.begin(), m_args.end(),
                             [&arg](ArgT& p) { return (arg == p.first); });
    }

    std::string Get(const char *arg) {
      std::vector<ArgT>::iterator it = std::find_if(m_args.begin(), m_args.end(),
                                       [&arg](ArgT& p) { return (arg == p.first); });
      if (it != m_args.end()) {
        return it->second;
      } else {
        return "";
      }
   }
};

#endif /* __ARGS_H__ */

