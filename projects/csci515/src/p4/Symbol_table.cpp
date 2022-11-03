#include "Symbol_table.h"
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
