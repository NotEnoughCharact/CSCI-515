#include<ostream>
#include<string>
#include<iostream>
#include<memory>
#include"Scope_manager.h"

  Scope_manager& Scope_manager::instance()
  {
    static Scope_manager the_instance;
    return the_instance;
  }

void Scope_manager::push_table()
{
  std::shared_ptr<Symbol_table> temp = std::make_shared<Symbol_table>();
  tables.push_back(temp);
}

void Scope_manager::pop_table()
{
  if(tables.size() > 1)
  {
    tables.pop_back();
  }
  else
  {
    throw std::underflow_error("Can't pop global symbol table");
  }
}

bool Scope_manager::add_to_current_scope(std::shared_ptr<Symbol> sym)
{
  std::shared_ptr<Symbol_table> temp = tables.back();
  bool b = temp->insert(sym);
  return b;
}

std::shared_ptr<Symbol> Scope_manager::lookup(const std::string& name)
{
  std::shared_ptr<Symbol> temp;
  for(int i = tables.size()-1; i >= 0; i--)
  {
    temp = tables[i]->lookup(name);
    if(temp != nullptr)
      return temp;
  }
  return nullptr;
}

bool Scope_manager::defined_in_current_scope(const std::string& name)
{
  std::shared_ptr<Symbol> temp;
  temp = tables.back()->lookup(name);
  if(temp == nullptr)
    return false;
  return true;
}

std::ostream& operator<<(std::ostream& os, const Scope_manager& sh)
{
  for(int i = sh.tables.size()-1; i >= 0; i--)
  {
      os << *sh.tables[i];
  }
  return os;
}

Scope_manager::Scope_manager()
{
  static std::shared_ptr<Symbol_table> temp = std::make_shared<Symbol_table>();
  tables.push_back(temp);
}

void Scope_manager::erase(const std::string& name)
{
  std::shared_ptr<Symbol> temp;
  for(int i = tables.size()-1; i >= 0; i--)
  {
    temp = tables[i]->lookup(name);
    if(temp != nullptr)
      tables[i]->erase(name);
  }
}
