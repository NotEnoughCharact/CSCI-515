#ifndef REFERENCE_H
#define REFERENCE_H
#include "Symbol.h"

class Reference : public Symbol {
  public:
    Reference(const std::string& parameter_name,
              GPL::Type          parameter_type,
              Game_object*       gop)
    : Symbol(parameter_name, parameter_type, gop) {}
    virtual ~Reference() { value.game_object_pointer=nullptr; }
};


#endif
