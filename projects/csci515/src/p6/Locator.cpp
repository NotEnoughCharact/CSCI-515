//File: Locator.cpp
#include "Locator.h"
#include "Statement.h"

GPL::Type  Locator::type() const
{ return intrinsic_type; }

//
//Game_object
//
void Game_attribute_locator::mutate(int val)
{
  gop->write_attribute(attribute_name, val);
}

void Game_attribute_locator::mutate(double val)
{
  gop->write_attribute(attribute_name, val);
}

void Game_attribute_locator::mutate(const std::string& val)
{
  gop->write_attribute(attribute_name, val);
}

void Game_attribute_locator::mutate(const Animation_code* val)
{
  gop->write_attribute(attribute_name, val);
}

void Animation_code_locator::mutate(const std::string& val)
{
  a_code->set_parameter_name(val);
}

void Animation_code_locator::mutate(const Statement* val)
{
  a_code->set_block(val);
}
