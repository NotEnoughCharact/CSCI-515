// File: Expression.cpp
#include "Expression.h"
#include "Constant.h"
#include "error.h"
#include "Game_object.h"
#include <iostream>
#include <string>
#include <cmath>
#include <numbers>
#include <cassert>
using std::string;

Expression::~Expression(){delete evaluated_constant;}

// This wrapper ensures that Constant objects created by evaluate() are
// properly released when a subsequent call to evaluate() will otherwise
// overwrite the pointer.
const Constant* Expression::ret(const Constant* new_evald_constant) const
{
  delete evaluated_constant;
  return evaluated_constant=new_evald_constant;
}
/**********************************************/
/************* Other operators ****************/
/**********************************************/

const Constant* Plus::evaluate() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==GPL::STRING || rht==GPL::STRING)
    return ret(new String_constant(lhs_constant->as_string() + //<--addition
                                   rhs_constant->as_string()));
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() + //<--addition
                                   rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() +     //<--addition
                                  rhs_constant->as_int()));
}

GPL::Type Plus::type() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  if(lht==GPL::STRING || rht==GPL::STRING)
    return GPL::STRING;
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}

const Constant* Multiply::evaluate() const
{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() * //<--multiply
                                   rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() *     //<--multiply
                                  rhs_constant->as_int()));
}

GPL::Type Multiply::type() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}

const Constant* Minus::evaluate() const
{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE)
    return ret(new Double_constant(lhs_constant->as_double() - //<--subtract
                                   rhs_constant->as_double()));
  return ret(new Integer_constant(lhs_constant->as_int() -     //<--subtract
                                  rhs_constant->as_int()));
}

GPL::Type Minus::type() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}

const Constant* Mod::evaluate() const
{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(rhs_constant->as_int() == 0)
  {
    Error::error(Error::MOD_BY_ZERO_AT_PARSE_TIME);
    return ret(new Integer_constant(0));
  }
  return ret(new Integer_constant(lhs_constant->as_int() %     //<--mod
                                  rhs_constant->as_int()));
}

GPL::Type Mod::type() const
{
  return GPL::INT;
}

GPL::Type Divide::type() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
    return GPL::DOUBLE;
  return GPL::INT;
}

const Constant* Divide::evaluate() const
{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lhs->type()==GPL::DOUBLE || rhs->type()==GPL::DOUBLE)
  {
    if(rhs_constant->as_double() == 0.0)
    {
     Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
     return ret(new Integer_constant(0));
    }
    return ret(new Double_constant(lhs_constant->as_double() / //<--subtract
                                   rhs_constant->as_double()));
  }

  if(rhs_constant->as_int() == 0)
  {
   Error::error(Error::DIVIDE_BY_ZERO_AT_PARSE_TIME);
   return ret(new Integer_constant(0));
  }
  return ret(new Integer_constant(lhs_constant->as_int() /     //<--subtract
                                  rhs_constant->as_int()));
}
const Constant* Or::evaluate() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
  {
    if(lhs_constant->as_double() != 0.0 || rhs_constant->as_double() != 0.0)
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
  if(lhs_constant->as_int() != 0 || rhs_constant->as_int() != 0)
    return ret(new Integer_constant(1));
  else
    return ret(new Integer_constant(0));
}

GPL::Type Or::type() const
{
  return GPL::INT;
}

const Constant* And::evaluate() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht==GPL::DOUBLE || rht==GPL::DOUBLE)
  {
    if(lhs_constant->as_double() != 0.0 && rhs_constant->as_double() != 0.0)
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
  if(lhs_constant->as_int() != 0 && rhs_constant->as_int() != 0)
    return ret(new Integer_constant(1));
  else
    return ret(new Integer_constant(0));
}

GPL::Type And::type() const
{
  return GPL::INT;
}

const Constant* Less_Equal::evaluate() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht == GPL::STRING || rht == GPL::STRING)
  {
    if(lhs_constant->as_string() <= rhs_constant->as_string())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
  else if(lht == GPL::DOUBLE || rht == GPL::DOUBLE)
  {
    if(lhs_constant->as_double() <= rhs_constant->as_double())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
  else
  {
    if(lhs_constant->as_int() <= rhs_constant->as_int())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
}

GPL::Type Less_Equal::type() const
{
  return GPL::INT;
}

const Constant* Greater_Equal::evaluate() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht == GPL::STRING || rht == GPL::STRING)
  {
    if(lhs_constant->as_string() >= rhs_constant->as_string())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
  else if(lht == GPL::DOUBLE || rht == GPL::DOUBLE)
  {
    if(lhs_constant->as_double() >= rhs_constant->as_double())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
  else
  {
    if(lhs_constant->as_int() >= rhs_constant->as_int())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
}

GPL::Type Greater_Equal::type() const
{
  return GPL::INT;
}

const Constant* Less::evaluate() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht == GPL::STRING || rht == GPL::STRING)
  {
    if(lhs_constant->as_string() < rhs_constant->as_string())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
  else if(lht == GPL::DOUBLE || rht == GPL::DOUBLE)
  {
    if(lhs_constant->as_double() < rhs_constant->as_double())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
  else
  {
    if(lhs_constant->as_int() < rhs_constant->as_int())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
}

GPL::Type Less::type() const
{
  return GPL::INT;
}

const Constant* Greater::evaluate() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht == GPL::STRING || rht == GPL::STRING)
  {
    if(lhs_constant->as_string() > rhs_constant->as_string())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
  else if(lht == GPL::DOUBLE || rht == GPL::DOUBLE)
  {
    if(lhs_constant->as_double() > rhs_constant->as_double())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
  else
  {
    if(lhs_constant->as_int() > rhs_constant->as_int())
      return ret(new Integer_constant(1));
    else
      return ret(new Integer_constant(0));
  }
}

GPL::Type Greater::type() const
{
  return GPL::INT;
}

const Constant* Equal::evaluate() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht == GPL::STRING || rht == GPL::STRING)
  {
    if(lhs_constant->as_string() == rhs_constant->as_string())
      return ret(new Integer_constant(1));
    return ret(new Integer_constant(0));
  }
  else if(lht == GPL::DOUBLE || rht == GPL::DOUBLE)
  {
    if(lhs_constant->as_double() == rhs_constant->as_double())
      return ret(new Integer_constant(1));
    return ret(new Integer_constant(0));
  }
  else
  {
    if(lhs_constant->as_int() == rhs_constant->as_int())
      return ret(new Integer_constant(1));
    return ret(new Integer_constant(0));
  }
}

GPL::Type Equal::type() const
{
  return GPL::INT;
}

const Constant* Not_Equal::evaluate() const
{
  GPL::Type lht=lhs->type();
  GPL::Type rht=rhs->type();
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  if(lht == GPL::STRING || rht == GPL::STRING)
  {
    if(lhs_constant->as_string() == rhs_constant->as_string())
      return ret(new Integer_constant(0));
    return ret(new Integer_constant(1));
  }
  else if(lht == GPL::DOUBLE || rht == GPL::DOUBLE)
  {
    if(lhs_constant->as_double() == rhs_constant->as_double())
      return ret(new Integer_constant(0));
    return ret(new Integer_constant(1));
  }
  else
  {
    if(lhs_constant->as_int() == rhs_constant->as_int())
      return ret(new Integer_constant(0));
    return ret(new Integer_constant(1));
  }
}

GPL::Type Not_Equal::type() const
{
  return GPL::INT;
}

const Constant* Neg::evaluate() const
{
  GPL::Type t = data->type();
  const Constant* d = data->evaluate();
  if(t == GPL::INT)
  {
    return ret(new Integer_constant(d->as_int()*-1));
  }
  else if(t == GPL::DOUBLE)
  {
    return ret(new Double_constant(d->as_double()*-1));
  }
  return ret(new Integer_constant(-1));
}

GPL::Type Neg::type() const
{
  return data->type();
}

const Constant* Not::evaluate() const
{
  GPL::Type t = data->type();
  const Constant* d = data->evaluate();
  if(t == GPL::INT)
  {
    if(d->as_int() == 0)
      return ret(new Integer_constant(1));
    return ret(new Integer_constant(0));
  }
  else if(t == GPL::DOUBLE)
  {
    if(d->as_double() == 0)
      return ret(new Integer_constant(1));
    return ret(new Integer_constant(0));
  }
  return ret(new String_constant("0"));
}

GPL::Type Not::type() const
{
  return GPL::INT;
}

const Constant* Sin::evaluate() const
{
  GPL::Type t = data->type();
  const Constant* d = data->evaluate();
  if(t == GPL::INT)
  {
    return ret(new Double_constant(std::sin((std::numbers::pi/180)*d->as_int())));
  }
  else if(t == GPL::DOUBLE)
  {
    return ret(new Double_constant(std::sin((std::numbers::pi/180)*d->as_double())));
  }
  return ret(new Double_constant(0.0));
}

GPL::Type Sin::type() const
{
  return GPL::DOUBLE;
}

const Constant* Cos::evaluate() const
{
  GPL::Type t = data->type();
  const Constant* d = data->evaluate();
  if(t == GPL::INT)
  {
    return ret(new Double_constant(std::cos((std::numbers::pi/180)*d->as_int())));
  }
  else if(t == GPL::DOUBLE)
  {
    return ret(new Double_constant(std::cos((std::numbers::pi/180)*d->as_double())));
  }
  return ret(new Double_constant(0.0));
}

GPL::Type Cos::type() const
{
  return GPL::DOUBLE;
}

const Constant* Tan::evaluate() const
{
  GPL::Type t = data->type();
  const Constant* d = data->evaluate();
  if(t == GPL::INT)
  {
    return ret(new Double_constant(std::tan((std::numbers::pi/180)*d->as_int())));
  }
  else if(t == GPL::DOUBLE)
  {
    return ret(new Double_constant(std::tan((std::numbers::pi/180)*d->as_double())));
  }
  return ret(new Double_constant(0.0));
}

GPL::Type Tan::type() const
{
  return GPL::DOUBLE;
}

const Constant* Asin::evaluate() const
{
  GPL::Type t = data->type();
  const Constant* d = data->evaluate();
  if(t == GPL::INT)
  {
    if(d->as_int() > 1)
      return ret(new Double_constant(NAN));
    return ret(new Double_constant(std::asin(d->as_int())*(180/std::numbers::pi)));
  }
  else if(t == GPL::DOUBLE)
  {
    if(d->as_double() > 1)
      return ret(new Double_constant(NAN));
    return ret(new Double_constant(std::asin(d->as_double())*(180/std::numbers::pi)));
  }
  return ret(new Double_constant(0.0));
}

GPL::Type Asin::type() const
{
  return GPL::DOUBLE;
}

const Constant* Acos::evaluate() const
{
  GPL::Type t = data->type();
  const Constant* d = data->evaluate();
  if(t == GPL::INT)
  {
    if(d->as_int() > 1)
      return ret(new Double_constant(NAN));
    return ret(new Double_constant(std::acos(d->as_int())*(180/std::numbers::pi)));
  }
  else if(t == GPL::DOUBLE)
  {
    if(d->as_double() > 1)
      return ret(new Double_constant(NAN));
    return ret(new Double_constant(std::acos(d->as_double())*(180/std::numbers::pi)));
  }
  return ret(new Double_constant(0.0));
}

GPL::Type Acos::type() const
{
  return GPL::DOUBLE;
}

const Constant* Atan::evaluate() const
{
  GPL::Type t = data->type();
  const Constant* d = data->evaluate();
  if(t == GPL::INT)
  {
    return ret(new Double_constant(std::atan(d->as_int())*(180/std::numbers::pi)));
  }
  else if(t == GPL::DOUBLE)
  {
    return ret(new Double_constant(std::atan(d->as_double())*(180/std::numbers::pi)));
  }
  return ret(new Double_constant(0.0));
}

GPL::Type Atan::type() const
{
  return GPL::DOUBLE;
}

const Constant* Sqrt::evaluate() const
{
  GPL::Type t = data->type();
  const Constant* d = data->evaluate();
  if(t == GPL::INT)
  {
    return ret(new Double_constant(std::sqrt(d->as_int())));
  }
  else if(t == GPL::DOUBLE)
  {
    return ret(new Double_constant(std::sqrt(d->as_double())));
  }
  return ret(new Double_constant(0.0));
}

GPL::Type Sqrt::type() const
{
  return GPL::DOUBLE;
}

const Constant* Abs::evaluate() const
{
  GPL::Type t = data->type();
  const Constant* d = data->evaluate();
  if(t == GPL::INT)
  {
    return ret(new Integer_constant(std::abs(d->as_int())));
  }
  else if(t == GPL::DOUBLE)
  {
    return ret(new Double_constant(std::abs(d->as_double())));
  }
  return ret(new Integer_constant(0));
}

GPL::Type Abs::type() const
{
  return data->type();
}

const Constant* Floor::evaluate() const
{
  GPL::Type t = data->type();
  const Constant* d = data->evaluate();
  if(t == GPL::INT)
  {
    return ret(new Integer_constant(std::floor(d->as_int())));
  }
  else if(t == GPL::DOUBLE)
  {
    return ret(new Integer_constant(std::floor(d->as_double())));
  }
  return ret(new Integer_constant(0));
}

GPL::Type Floor::type() const
{
  return GPL::INT;
}

const Constant* Random::evaluate() const
{
  const Constant* d = data->evaluate();
  int denominator=floor(d->as_double());
  if(denominator<2)
  {
    Error::error(Error::INVALID_ARGUMENT_FOR_RANDOM, d->as_string());
    denominator=2;
  }
  return ret(new Integer_constant(rand()%denominator));
}

GPL::Type Random::type() const
{
  return GPL::INT;
}

const Constant* Near::evaluate() const
{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  return new Integer_constant(lhs_constant->as_game_object()->near(rhs_constant->as_game_object()));
}

GPL::Type Near::type() const
{
  return GPL::INT;
}

const Constant* Touches::evaluate() const
{
  const Constant* lhs_constant=lhs->evaluate();
  const Constant* rhs_constant=rhs->evaluate();
  return new Integer_constant(lhs_constant->as_game_object()->touches(rhs_constant->as_game_object()));
}

GPL::Type Touches::type() const
{
  return GPL::INT;
}
