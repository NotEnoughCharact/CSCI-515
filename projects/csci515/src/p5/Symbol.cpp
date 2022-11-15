#include "Symbol.h"
#include "Expression.h"
#include "Game_attribute_constant.h"
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

  if(this->type == GPL::STRING && this->count > 0)
  {
    delete []this->value.string_pointer;
  }
  else if(this->type == GPL::STRING)
  {
    delete this->value.string_pointer ;
  }
  else if(this->type == GPL::INT && this->count > 0)
  {
    delete []this->value.int_pointer;
  }
  else if(this->type == GPL::INT)
  {
    delete this->value.int_pointer;
  }
  else if (this->type == GPL::DOUBLE && this->count > 0)
  {
    delete []this->value.double_pointer;
  }
  else if (this->type == GPL::DOUBLE)
    delete this->value.double_pointer;
}



std::ostream& operator<<(std::ostream& os, const Symbol& sym)
{

  int num = sym.type;
  if(sym.count > 0)
  {
    for(int i = 0; i < sym.count; i++)
    {
        if(num < 5)
          os << to_string(sym.type) << " " << sym.name << "[" << i << "] = ";
        else
          os << to_string(sym.type) << " " << sym.name << "[" << i << "]";
        if(num == GPL::INT)
        {
          os << sym.value.int_pointer[i];
        }
        else if(num == GPL::DOUBLE)
        {
          os << sym.value.double_pointer[i];
        }
        else if(num == GPL::STRING)
        {
          os << "\"" << sym.value.string_pointer[i] << "\"";
        }
        else if(num == GPL::CIRCLE)
        {
          os << sym.value.circle_pointer[i];
        }
        else if(num == GPL::RECTANGLE)
        {
          os << sym.value.rectangle_pointer[i];
        }
        else if(num == GPL::TRIANGLE)
        {
          os << sym.value.triangle_pointer[i];
        }
        else if(num == GPL::TEXTBOX)
        {
          os << sym.value.textbox_pointer[i];
        }
        else if(num == GPL::PIXMAP)
        {
          os << sym.value.pixmap_pointer[i];
        }
        if(i < sym.count-1)
          os << "\n";
    }

  }
  else
  {
    if(num < 5)
      os << to_string(sym.type) << " " << sym.name << " = ";
    else
      os << to_string(sym.type) << " " << sym.name;
    if(num == GPL::INT)
    {
      os << *sym.value.int_pointer;
    }
    if(num == GPL::DOUBLE)
    {
      os << *sym.value.double_pointer;
    }
    if(num == GPL::STRING)
    {
      os << "\"" << *sym.value.string_pointer << "\"";
    }
    else if(num == GPL::CIRCLE)
    {
      os << *sym.value.circle_pointer;
    }
    else if(num == GPL::RECTANGLE)
    {
      os << *sym.value.rectangle_pointer;
    }
    else if(num == GPL::TRIANGLE)
    {
      os << *sym.value.triangle_pointer;
    }
    else if(num == GPL::TEXTBOX)
    {
      os << *sym.value.textbox_pointer;
    }
    else if(num == GPL::PIXMAP)
    {
      os << *sym.value.pixmap_pointer;
    }
  }

  return os;
}

const Constant* Symbol::as_constant() const
{
  int num = type;
  if(num == GPL::INT)
  {
    return new Integer_constant(*value.int_pointer);
  }
  else if(num == GPL::DOUBLE)
  {
    return new Double_constant(*value.double_pointer);
  }
  else if(num == GPL::STRING)
  {
    return new String_constant(*value.string_pointer);
  }
  return nullptr;
}

const Constant* Symbol::as_constant(int index) const
{
  int num = type;
  if(num == GPL::INT)
  {
    return new Integer_constant(value.int_pointer[index]);
  }
  else if(num == GPL::DOUBLE)
  {
    return new Double_constant(value.double_pointer[index]);
  }
  else if(num == GPL::STRING)
  {
    return new String_constant(value.string_pointer[index]);
  }
  return nullptr;
}

const Constant* Symbol::as_constant(const std::string& attribute_name) const
{
  int num = type;
  if(num == GPL::CIRCLE)
  {
    return new Game_attribute_constant(value.circle_pointer, attribute_name);
  }
  else if(num == GPL::RECTANGLE)
  {
    return new Game_attribute_constant(value.rectangle_pointer, attribute_name);
  }
  else if(num == GPL::TRIANGLE)
  {
    return new Game_attribute_constant(value.triangle_pointer, attribute_name);
  }
  else if(num == GPL::TEXTBOX)
  {
    return new Game_attribute_constant(value.textbox_pointer, attribute_name);
  }
  else if(num == GPL::PIXMAP)
  {
    return new Game_attribute_constant(value.pixmap_pointer, attribute_name);
  }
  throw type;
}

const Constant* Symbol::as_constant(int index, const std::string& attribute_name) const
{
  int num = type;
  if(num == GPL::CIRCLE)
  {
    return new Game_attribute_constant(&value.circle_pointer[index], attribute_name);
  }
  else if(num == GPL::RECTANGLE)
  {
    return new Game_attribute_constant(&value.rectangle_pointer[index], attribute_name);
  }
  else if(num == GPL::TRIANGLE)
  {
    return new Game_attribute_constant(&value.triangle_pointer[index], attribute_name);
  }
  else if(num == GPL::TEXTBOX)
  {
    return new Game_attribute_constant(&value.textbox_pointer[index], attribute_name);
  }
  else if(num == GPL::PIXMAP)
  {
    return new Game_attribute_constant(&value.pixmap_pointer[index], attribute_name);
  }
  throw type;
}

GPL::Type Symbol::get_type() const
{
  return type;
}

std::shared_ptr<Locator> Symbol::as_lvalue() const
{
  return nullptr; /*CHANGE*/
}
