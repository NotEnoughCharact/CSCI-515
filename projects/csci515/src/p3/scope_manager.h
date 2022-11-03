#ifndef SCOPE_MANAGER_H
#define SCOPE_MANAGER_H
#include<vector>
#include<stdexcept>
#include"symbol_table.h"

class Scope_manager {
  public:
    static Scope_manager& instance();
    void push_table();
    void pop_table();
    bool add_to_current_scope(std::shared_ptr<Symbol> sym);
    std::shared_ptr<Symbol> lookup(const std::string& name);
    bool defined_in_current_scope(const std::string& name);
    friend std::ostream& operator<<(std::ostream& os, const Scope_manager& sh);
  private:
    std::vector<std::shared_ptr<Symbol_table>> tables;
    Scope_manager();
  };

  #endif
