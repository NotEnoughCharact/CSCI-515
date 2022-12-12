#ifndef SYMBOL_H
#define SYMBOL_H

#include <string>
#include "types_and_ops.h"
#include "Constant.h"
#include "Pixmap.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Textbox.h"
#include "Triangle.h"
#include "Locator.h"
#include "Animation_code.h"
#include "Game_object.h"



union symbol_type {
  double* double_pointer;
  int* int_pointer;
  std::string* string_pointer;
  Pixmap* pixmap_pointer;
  Rectangle* rectangle_pointer;
  Circle* circle_pointer;
  Textbox* textbox_pointer;
  Triangle* triangle_pointer;
  Animation_code* a_code_pointer;
  Game_object* game_object_pointer;

  symbol_type(double* val) : double_pointer(val){}
  symbol_type(int* val) : int_pointer(val){}
  symbol_type(std::string* val) : string_pointer(val){}
  symbol_type(Pixmap* val) : pixmap_pointer(val){}
  symbol_type(Rectangle* val) : rectangle_pointer(val){}
  symbol_type(Circle* val) : circle_pointer(val){}
  symbol_type(Textbox* val) : textbox_pointer(val){}
  symbol_type(Triangle* val) : triangle_pointer(val){}
  symbol_type(Animation_code* val) : a_code_pointer(val){}
  symbol_type(Game_object* val) : game_object_pointer(val){}
};




class Symbol{



private:
  std::string name;
protected:
  symbol_type value;
private:
  GPL::Type type;
  int count;


public:
  Symbol(const std::string& name, double* value);
  Symbol(const std::string& name, double* value, int count);
  Symbol(const std::string& name, int* value);
  Symbol(const std::string& name, int* value, int count);
  Symbol(const std::string& name, std::string* value);
  Symbol(const std::string& name, std::string* value, int count);

  Symbol(const std::string& name, Pixmap* value);
  Symbol(const std::string& name, Pixmap* value, int count);
  Symbol(const std::string& name, Rectangle* value);
  Symbol(const std::string& name, Rectangle* value, int count);
  Symbol(const std::string& name, Circle* value);
  Symbol(const std::string& name, Circle* value, int count);
  Symbol(const std::string& name, Textbox* value);
  Symbol(const std::string& name, Textbox* value, int count);
  Symbol(const std::string& name, Triangle* value);
  Symbol(const std::string& name, Triangle* value, int count);

  Symbol(const std::string& name, Animation_code* value);

protected:
  Symbol(const std::string& name, GPL::Type type, Game_object* value);

public:



  const Constant* as_constant() const;          //Symbol value is not an array
  const Constant* as_constant(int index) const; //Symbol value is an array
  const Constant* as_constant(           const std::string& attribute_name) const; // non-arrays
  const Constant* as_constant(int index, const std::string& attribute_name) const; // arrays

  std::shared_ptr<Locator> as_lvalue() const;
  std::shared_ptr<Locator> as_lvalue(int index) const;
  std::shared_ptr<Locator> as_lvalue(const std::string& attribute_name) const;
  std::shared_ptr<Locator> as_lvalue(int index, const std::string& attribute_name) const;

  GPL::Type get_type() const;
  std::string get_name() const{return this->name;};
  int get_count() const{return this->count;};
  virtual ~Symbol();
  friend std::ostream& operator<<(std::ostream& os, const Symbol& sym);

  //prevent compiler from generating these functions
  Symbol(const Symbol&) = delete;
  Symbol& operator=(const Symbol&) = delete;



};

#endif
