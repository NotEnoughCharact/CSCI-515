//File: Constant.cpp
#include "Constant.h"
#include <iostream>

GPL::Type  Constant::type() const
{ return intrinsic_type; }

const Constant* Constant::evaluate() const
{ return this; }
