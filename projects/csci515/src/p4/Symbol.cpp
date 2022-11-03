#include "Symbol.h"
#include "Expression.h"
#include <iostream>


Symbol::Symbol(const std::string& name, double* value) : name(name), value(value) {count = 0; type = GPL::DOUBLE;}
Symbol::Symbol(const std::string& name, double* value, int count) : name(name), value(value), count(count){type = GPL::DOUBLE;}
Symbol::Symbol(const std::string& name, int* value) : name(name), value(value){count = 0; type = GPL::INT;}
Symbol::Symbol(const std::string& name, int* value, int count) : name(name), value(value), count(count){type = GPL::INT;}
Symbol::Symbol(const std::string& name, std::string* value) : name(name), value(value){count = 0; type = GPL::STRING;}
Symbol::Symbol(const std::string& name, std::string* value, int count) : name(name), value(value), count(count){type = GPL::STRING;}

Symbol::Symbol(const std::string& name, Pixmap* value) : name(name), value(value){count = 0; type = GPL::PIXMAP;}
Symbol::Symbol(const std::string& name, Pixmap* value, int count) : name(name), value(value), count(count){type = GPL::PIXMAP;}
Symbol::Symbol(const std::string& name, Rectangle* value) : name(name), value(value){count = 0; type = GPL::RECTANGLE;}
Symbol::Symbol(const std::string& name, Rectangle* value, int count) : name(name), value(value), count(count){type = GPL::RECTANGLE;}
Symbol::Symbol(const std::string& name, Circle* value) : name(name), value(value){count = 0; type = GPL::CIRCLE;}
Symbol::Symbol(const std::string& name, Circle* value, int count) : name(name), value(value), count(count){type = GPL::CIRCLE;}
Symbol::Symbol(const std::string& name, Textbox* value) : name(name), value(value){count = 0; type = GPL::TEXTBOX;}
Symbol::Symbol(const std::string& name, Textbox* value, int count) : name(name), value(value), count(count){type = GPL::TEXTBOX;}
Symbol::Symbol(const std::string& name, Triangle* value) : name(name), value(value){count = 0; type = GPL::TRIANGLE;}
Symbol::Symbol(const std::string& name, Triangle* value, int count) : name(name), value(value), count(count){type = GPL::TRIANGLE;}

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

        os << to_string(sym.type) << " " << sym.name << "[" << i << "] = ";
        if(num == 1)
        {
          os << sym.value.int_pointer[i];
        }
        else if(num == 2)
        {
          os << sym.value.double_pointer[i];
        }
        else if(num == 4)
        {
          os << "\"" << sym.value.string_pointer[i] << "\"";
        }
        else if(num == 32)
        {
          os << sym.value.circle_pointer[i];
        }
        else if(num == 64)
        {
          os << sym.value.rectangle_pointer[i];
        }
        else if(num == 128)
        {
          os << sym.value.triangle_pointer[i];
        }
        else if(num == 256)
        {
          os << sym.value.textbox_pointer[i];
        }
        else if(num == 512)
        {
          os << sym.value.pixmap_pointer[i];
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
    else if(num == 32)
    {
      os << *sym.value.circle_pointer;
    }
    else if(num == 64)
    {
      os << *sym.value.rectangle_pointer;
    }
    else if(num == 128)
    {
      os << *sym.value.triangle_pointer;
    }
    else if(num == 256)
    {
      os << *sym.value.textbox_pointer;
    }
    else if(num == 512)
    {
      os << *sym.value.pixmap_pointer;
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
