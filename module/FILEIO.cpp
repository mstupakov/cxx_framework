#include <string>
#include "FILEIO.h"
#include "work.h"

static FILEIO module;

char packet[] = {

};

class FileIOWork : public Work {
  FILEIO* obj;

  public:
    FileIOWork(FILEIO* p) {
      obj = p;
    }
    virtual int Execute() {
      obj->FILEIO::MainLoop();
    }  
};

void FILEIO::Notify(Phase phase) {

  switch (phase) {
    case PHASE_INIT: Init(); break;
    case PHASE_DEINIT: DeInit(); break;
    case PHASE_RUNNING: Running(); break;
    case PHASE_STOP: Stop(); break;

    default:
      throw Error();
  }
}

void FILEIO::Init() {

    if (m_args->Has("-f")) {

      std::string file = m_args->Get("-f");
      std::cout << "Open pcap file: " 
        << file << std::endl;
      /* ... Open file .... */
    } else {

    }
}

void FILEIO::DeInit() {
  /* .... Close file/tap ..... */
}

void FILEIO::Running() {

  FileIOWork* p = new FileIOWork(this);
  DoWork(p, ASYNC);
}

void FILEIO::Stop() {

}

void FILEIO::MainLoop() {

  int port = 7;

  if (port < 64) {
    m_connections[0].module->Send(new Transaction(this));
  } else {
    m_connections[1].module->Send(new Transaction(this));
  }

  FileIOWork* p = new FileIOWork(this);
  DoWork(p, ASYNC);

  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

