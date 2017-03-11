#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

class Module;

class Transaction {
  Module* m_module;

  public:
    Transaction(Module* module) 
      : m_module(module) {}
};

#endif /* __TRANSACTION_H__ */

