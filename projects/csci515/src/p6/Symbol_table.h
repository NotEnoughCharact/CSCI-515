#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H
#include "Symbol.h"
#include <unordered_map>
#include <memory>
#include <iostream>
#include <string>

class Symbol_table {
  public:
    Symbol_table(){};
    std::shared_ptr<Symbol> lookup(const std::string& name);
    bool insert(std::shared_ptr<Symbol> sym);
    friend std::ostream& operator<<(std::ostream& os, const Symbol_table& symtab);
    void erase(const std::string& name);

    //prevent compiler from generating these functions
    Symbol_table(const Symbol_table&) = delete;
    Symbol_table& operator=(const Symbol_table&) = delete;
  private:
    std::unordered_map<std::string, std::shared_ptr<Symbol>> symbols;
};




#endif
