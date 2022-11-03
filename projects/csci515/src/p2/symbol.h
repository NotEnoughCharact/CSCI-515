#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include "types_and_ops.h"


union symbol_type {
  double* double_pointer;
  int* int_pointer;
  std::string* string_pointer;

  symbol_type(double* val) : double_pointer(val){}
  symbol_type(int* val) : int_pointer(val){}
  symbol_type(std::string* val) : string_pointer(val){}
};




class Symbol{
private:
  std::string name;
  symbol_type value;
  GPL::Type type;
  int count;

public:
  Symbol(const std::string& name, double* value);
  Symbol(const std::string& name, double* value, int count);
  Symbol(const std::string& name, int* value);
  Symbol(const std::string& name, int* value, int count);
  Symbol(const std::string& name, std::string* value);
  Symbol(const std::string& name, std::string* value, int count);

  GPL::Type get_type() const;
  std::string get_name() const{return this->name;};
  virtual ~Symbol();
  friend std::ostream& operator<<(std::ostream& os, const Symbol& sym);

  //prevent compiler from generating these functions
  Symbol(const Symbol&) = delete;
  Symbol& operator=(const Symbol&) = delete;
};

#endif
