#include<ostream>
#include<string>
#include<iostream>
#include<memory>
#include"scope_manager.h"

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


/*int main()
{
  Scope_manager& symtab = Scope_manager::instance();

  double* double_oneofem=new double(3.141592);
  double* double_bunchofem=new double[4] {1.123, 2.234, 3.456, 7.899};
  std::string* string_oneofem=new std::string("hi there");
  std::string* string_bunchofem=new std::string[4]
    {"one", "two two", "three three three", "fo fo fo fo"};
  int* int_oneofem=new int(321);
  int* int_bunchofem=new int[4] {12, 34, 56, 78};

  symtab.add_to_current_scope(std::make_shared<Symbol>("alpha", string_oneofem));
  symtab.add_to_current_scope(std::make_shared<Symbol>("gamma", string_bunchofem, 4));
  symtab.add_to_current_scope(std::make_shared<Symbol>("beta", double_oneofem));
  symtab.add_to_current_scope(std::make_shared<Symbol>("delta", double_bunchofem, 4));
  symtab.add_to_current_scope(std::make_shared<Symbol>("zeta", int_oneofem));
  symtab.add_to_current_scope(std::make_shared<Symbol>("eta", int_bunchofem, 4));

  std::cout << symtab << "\n";
  return 0;
}*/
