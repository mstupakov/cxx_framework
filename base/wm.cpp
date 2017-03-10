#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include "wm.h"
#include "work.h"

template<typename Out>
void split(const std::string &s, char delim, Out result) {
    std::stringstream ss;
    ss.str(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        *(result++) = item;
    }
}

std::vector<std::string> split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split(s, delim, std::back_inserter(elems));
    return elems;
}


class MyWorkStop: public Work {
  WM* sys;

  public:
    MyWorkStop(WM* system)
      : sys(system) {  }

    virtual int Execute() {
      sys->Stop();
    }
};

int WM::Init() {

  std::string wm_cfg("xp70.gv");

  if (m_args.Has("-c")) {
    wm_cfg = m_args.Get("-c");
  }

  ParseGv(wm_cfg);

  if (m_args.Has("-d")) {
    ShowModules();
  }

  CreateInfrastructure();

  std::for_each(m_modules.begin(), m_modules.end(), 
                [this](Module* m) { m->Notify(PHASE_INIT); });

  DoWork(new MyWorkStop(this), ASYNC);
  return 0;
}

int WM::DeInit() {
  std::for_each(m_modules.begin(), m_modules.end(), 
                [this](Module* m) { m->Notify(PHASE_DEINIT); });

  std::cout << "! Func: " << __PRETTY_FUNCTION__ << std::endl;
  return 0;
}

void WM::GetBlockInfo(std::string line) {
  if (std::string::npos != line.find("image")) {
    std::vector<std::string> tokens = split(line, ' ');
    std::string type = split(tokens[0], '_')[0];
    
    BlockInfo info = {
      .type = type,
      .name = tokens[0]
    };

    m_blocks.push_back(info);
  }
}

void WM::GetConnInfo(std::string line) {
  if (std::string::npos != line.find("->")) {
    std::vector<std::string> tokens = split(line, ' ');
    bool dir = (std::string::npos != line.find("both"));

    std::vector<std::string> labels;

    std::size_t pos_start = line.find("label=\"");
    if (std::string::npos != pos_start) {
      pos_start += std::string("label=\"").size();

      std::size_t pos_end = line.substr(pos_start).find("\"");
      labels = split(line.substr(pos_start, pos_end), ';');      
    }

    ConnInfo info = {
      .name_what = tokens[0],
      .name_with = tokens[2],
      .is_direction_both = dir,
      .labels = labels
    };

    m_connections.push_back(info);
  }
}

void WM::ParseGv(std::string name) {

  std::ifstream file(name);
  if (file.is_open()) {
    std::string line;

    while (std::getline(file, line)) {
      if (std::string::npos == line.find("//")) {

        GetBlockInfo(line);
        GetConnInfo(line);
      }
    }

    file.close();
  } else {
    throw Error();
  }
}

void WM::ShowModules() {
  std::cout << "--- Blocks:" << std::endl;
  for (auto it = m_blocks.begin(); it != m_blocks.end(); ++it) {
    std::cout << "Type: " << it->type << ", name: " << it->name << std::endl;
  }

  std::cout << std::endl << std::endl;
  std::cout << "--- Connnections: " << std::endl;
  for (auto it = m_connections.begin(); it != m_connections.end(); ++it) {
    std::string labels;
    
    for (auto it_string = it->labels.begin(); 
        it_string != it->labels.end(); ++it_string) {
      labels += " [" + *it_string + "] ";
    }

    std::cout << "Conn: " << it->name_what << " + " << it->name_with 
      << "  : is_direction_both: " << it->is_direction_both 
      << "  : labels: " << labels << std::endl;
  }
}

void WM::CreateInfrastructure() {

  for (auto it = m_blocks.begin(); it != m_blocks.end(); ++it) {
    Module* obj = CreateModule(it->type, it->name);
    RegModule(obj);
  }
}

