#include "Member_variable.h"
#include "Game_attribute_constant.h"
#include "error.h"

Member_variable::Member_variable(const std::string& name, const::std::string& attribute) : Variable(name), attribute(attribute) {}
Member_variable::Member_variable(const std::string& name, const Expression* index_expr, const::std::string& attribute) : Variable(name, index_expr), attribute(attribute){}

const Constant* Member_variable::evaluate() const
{
  std::shared_ptr<Symbol> temp = symbol();
  if(symbol_name == "")
  {
    return ret(new Integer_constant(0));
  }
  if(temp == nullptr && array_index_expression != nullptr)
  {
    Error::error(Error::UNDECLARED_VARIABLE, symbol_name+"[]");
    return ret(new Integer_constant(0));
  }
  if(temp == nullptr && array_index_expression == nullptr)
  {
    Error::error(Error::UNDECLARED_VARIABLE, symbol_name);
    return ret(new Integer_constant(0));
  }
  if(temp->get_count() == 0 && array_index_expression != nullptr)
  {
    Error::error(Error::VARIABLE_NOT_AN_ARRAY, temp->get_name());
    return ret(new Integer_constant(0));
  }
  if(temp->get_count() > 0 && array_index_expression == nullptr)
  {
    Error::error(Error::VARIABLE_IS_AN_ARRAY, temp->get_name());
    return ret(new Integer_constant(0));
  }
  if (array_index_expression != nullptr && (array_index_expression->evaluate()->as_int() >= temp->get_count() || array_index_expression->evaluate()->as_int() < 0))
  {
    Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, temp->get_name(), array_index_expression->evaluate()->as_string());
    return ret(new Integer_constant(0));
  }
  const Constant* c = temp->as_constant(attribute);
  return ret(c);
}

GPL::Type Member_variable::type() const
{

  return symbol()->as_constant(attribute)->type();
}
