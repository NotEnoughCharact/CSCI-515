#include "symbol.h"
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
    delete(this->value.string_pointer);
  }

  else if(this->type == 1)
  {
    delete(this->value.int_pointer);
  }
  else
  {
    delete(this->value.double_pointer);
  }
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


/*int main()
{
  double* oneofem=new double(3.141592);
  double* bunchofem=new double[4] {1.123, 2.234, 3.456, 7.899};
  int* oneofemi=new int(1);
  int* bunchofemi=new int[4] {1,2,3,4};
  std::string* oneofems=new std::string("ta");
  std::string* bunchofems=new std::string[4] {"ta","ta","ta","ta"};
  Symbol one("pi", oneofem);
  Symbol two("racetimes", bunchofem, 4);
  Symbol three("dink", oneofemi);
  Symbol four("donk", bunchofemi, 4);
  Symbol five("ss", oneofems);
  Symbol six("ss", bunchofems, 4);
  std::cout << two << "\n";
  std::cout << one << "\n";
  std::cout << three << "\n";
  std::cout << four << "\n";
  std::cout << five << "\n";
  std::cout << six << "\n";


}*/
