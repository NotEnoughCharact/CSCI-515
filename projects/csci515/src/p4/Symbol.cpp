#include "Symbol.h"
#include "Expression.h"
#include <iostream>


Symbol::Symbol(const std::string& name, double* value) : name(name), value(value) {count = 0; type = GPL::DOUBLE;}
Symbol::Symbol(const std::string& name, double* value, int count) : name(name), value(value), count(count){type = GPL::DOUBLE;}
Symbol::Symbol(const std::string& name, int* value) : name(name), value(value){count = 0; type = GPL::INT;}
Symbol::Symbol(const std::string& name, int* value, int count) : name(name), value(value), count(count){type = GPL::INT;}
Symbol::Symbol(const std::string& name, std::string* value) : name(name), value(value){count = 0; type = GPL::STRING;}
Symbol::Symbol(const std::string& name, std::string* value, int count) : name(name), value(value), count(count){type = GPL::STRING;}

Symbol::~Symbol()
{

  if(this->type == 4 && this->count > 0)
  {
    delete []this->value.string_pointer;
  }
  else if(this->type == 4)
  {
    delete this->value.string_pointer ;
  }
  else if(this->type == 1 && this->count > 0)
  {
    delete []this->value.int_pointer;
  }
  else if(this->type == 1)
  {
    delete this->value.int_pointer;
  }
  else if (this->type == 2 && this->count > 0)
  {
    delete []this->value.double_pointer;
  }
  else
    delete this->value.double_pointer;
}



std::ostream& operator<<(std::ostream& os, const Symbol& sym)
{

  int num = sym.type;
  if(sym.count > 0)
  {
    for(int i = 0; i < sym.count; i++)
    {
        if(num == 1)
        {
          os << to_string(sym.type) << " " << sym.name << "[" << i << "] = " << sym.value.int_pointer[i] << "";
        }
        if(num == 2)
        {
          os << to_string(sym.type) << " " << sym.name << "[" << i << "] = " << sym.value.double_pointer[i] << "";
        }
        if(num == 4)
        {
          os << to_string(sym.type) << " " << sym.name << "[" << i << "] = \"" << sym.value.string_pointer[i] << "\"";
        }
        if(i < sym.count-1)
          os << "\n";
    }

  }
  else
  {
    os << to_string(sym.type) << " " << sym.name << " = ";
    if(num == 1)
    {
      os << *sym.value.int_pointer;
    }
    if(num == 2)
    {
      os << *sym.value.double_pointer;
    }
    if(num == 4)
    {
      os << "\"" << *sym.value.string_pointer << "\"";
    }
  }

  return os;
}

const Constant* Symbol::as_constant() const
{
  int num = type;
  //std::cerr << num << "\n";
  if(num == 1)
  {
    //std::cerr << *value.int_pointer << "\n";
    return new Integer_constant(*value.int_pointer);
  }
  if(num == 2)
  {
    //std::cerr << *value.double_pointer << "\n";
    return new Double_constant(*value.double_pointer);
  }
  if(num == 4)
  {
    //std::cerr << *value.string_pointer << "\n";
    return new String_constant(*value.string_pointer);
  }
  return nullptr;
}

const Constant* Symbol::as_constant(int index) const
{
  int num = type;
  if(num == 1)
  {
    //std::cerr << *value.int_pointer << "\n";
    return new Integer_constant(value.int_pointer[index]);
  }
  if(num == 2)
  {
    //std::cerr << *value.int_pointer << "\n";
    return new Double_constant(value.double_pointer[index]);
  }
  if(num == 4)
  {
    //std::cerr << value.string_pointer[0] << "\n";
    return new String_constant(value.string_pointer[index]);
  }
  return nullptr;
}

GPL::Type Symbol::get_type() const
{
  return type;
}
