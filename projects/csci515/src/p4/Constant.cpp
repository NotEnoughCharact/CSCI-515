//File: Constant.cpp
#include "Constant.h"
#include "Game_attribute_constant.h"
#include "Scope_manager.h"
#include "Symbol.h"
#include "Game_object.h"

GPL::Type  Constant::type() const
{ return intrinsic_type; }

const Constant* Constant::evaluate() const
{ return this; }

int Constant::as_int() const
{
  if(type() == GPL::INT)
  {
    static Scope_manager manager = Scope_manager::instance();
    std::shared_ptr<Symbol::Symbol> sym = manager.lookup(Game_attribute_constant::attribute_name);
    //return  *(sym.value.int_pointer);
    return 1;
  }
  else
    throw intrinsic_type;
}
