#include "Game_attribute_constant.h"

int Game_attribute_constant::as_int() const
{
  GPL::Type t = gop->attribute_type(attribute_name);
  if(t == GPL::INT)
  {
    int temp;
    gop->read_attribute(attribute_name, temp);
    return temp;
  }
  else
    throw type();
}

double Game_attribute_constant::as_double() const
{
  GPL::Type t = gop->attribute_type(attribute_name);
  if(t == GPL::STRING)
  {
    throw type();
  }
  else
  {
    double temp;
    gop->read_attribute(attribute_name, temp);
    return temp;
  }
}

std::string Game_attribute_constant::as_string() const
{
  GPL::Type t = gop->attribute_type(attribute_name);
  if(t == GPL::STRING)
  {
    std::string temp;
    gop->read_attribute(attribute_name, temp);
    return temp;
  }
  else
    throw type();
    
}
