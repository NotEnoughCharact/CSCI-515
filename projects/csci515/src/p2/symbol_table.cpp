#include "symbol_table.h"
#include <vector>
#include <algorithm>

std::shared_ptr<Symbol> Symbol_table::lookup(const std::string& name)
{
  if(this->symbols.find(name) == this->symbols.end())
    return nullptr;
  else
    return this->symbols[name];
}

bool Symbol_table::insert(std::shared_ptr<Symbol> sym)
{
  for(auto i : this->symbols)
  {
    if(i.second == sym)
    {
      return false;
    }
  }
  this->symbols[sym->get_name()] = sym;
  return true;
}



std::ostream& operator<<(std::ostream& os, const Symbol_table& symtab)
{
  std::vector<std::string> names;
  for(auto i : symtab.symbols)
  {
    names.push_back(i.first);
  }
  std::sort(names.begin(),names.end(), [](std::string a, std::string b) {return a<b;});
  for(int i = 0; i < (int)names.size(); i++)
  {
    os << *symtab.symbols.at(names[i]) << "\n";
  }
  return os;
}

/*int main()
{
  Symbol_table symtab;

  double* double_oneofem=new double(3.141592);
  double* double_bunchofem=new double[4] {1.123, 2.234, 3.456, 7.899};
  std::string* string_oneofem=new std::string("hi there");
  std::string* string_bunchofem=new std::string[4]
    {"one", "two two", "three three three", "fo fo fo fo"};
  int* int_oneofem=new int(321);
  int* int_bunchofem=new int[4] {12, 34, 56, 78};

  symtab.insert(std::make_shared<Symbol>("alpha", string_oneofem));
  symtab.insert(std::make_shared<Symbol>("gamma", string_bunchofem, 4));
  symtab.insert(std::make_shared<Symbol>("beta", double_oneofem));
  symtab.insert(std::make_shared<Symbol>("delta", double_bunchofem, 4));
  symtab.insert(std::make_shared<Symbol>("zeta", int_oneofem));
  symtab.insert(std::make_shared<Symbol>("eta", int_bunchofem, 4));

  std::cout << symtab << "\n";
  return 0;
}*/
