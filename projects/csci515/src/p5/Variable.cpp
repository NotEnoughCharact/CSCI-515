#include "Variable.h"
#include "error.h"

Variable::Variable(const std::string& symbol_name) : symbol_name(symbol_name){array_index_expression = nullptr;}

Variable::Variable(const std::string& symbol_name, const Expression* index_expr) : symbol_name(symbol_name), array_index_expression(index_expr){}

const Constant* Variable::evaluate() const
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
  if(array_index_expression != nullptr)
  {
    if(array_index_expression->type() != GPL::INT)
    {
      Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, symbol_name, to_string(array_index_expression->type()));
      return ret(new Integer_constant(0));
    }
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
  if (array_index_expression != nullptr && array_index_expression->evaluate()->as_int() >= temp->get_count())
  {
    Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, temp->get_name(), array_index_expression->evaluate()->as_string());
    return ret(new Integer_constant(0));
  }
  if(array_index_expression != nullptr)
  {
    return ret(temp->as_constant(array_index_expression->evaluate()->as_int()));
  }
  return ret(temp->as_constant());

}

const std::shared_ptr<Locator> Variable::modify() const
{
  int i_temp = 0;
  std::shared_ptr<Symbol> temp = symbol();
  if(symbol_name == "")
  {
    return std::make_shared<Integer_locator>(i_temp);
  }
  if(temp == nullptr && array_index_expression != nullptr)
  {
    Error::error(Error::UNDECLARED_VARIABLE, symbol_name+"[]");
    return std::make_shared<Integer_locator>(i_temp);
  }
  if(temp == nullptr && array_index_expression == nullptr)
  {
    Error::error(Error::UNDECLARED_VARIABLE, symbol_name);
    return std::make_shared<Integer_locator>(i_temp);
  }
  if(array_index_expression != nullptr)
  {
    if(array_index_expression->type() != GPL::INT)
    {
      Error::error(Error::ARRAY_INDEX_MUST_BE_AN_INTEGER, symbol_name, to_string(array_index_expression->type()));
      return std::make_shared<Integer_locator>(i_temp);
    }
  }
  if(temp->get_count() == 0 && array_index_expression != nullptr)
  {
    Error::error(Error::VARIABLE_NOT_AN_ARRAY, temp->get_name());
    return std::make_shared<Integer_locator>(i_temp);
  }
  if(temp->get_count() > 0 && array_index_expression == nullptr)
  {
    Error::error(Error::VARIABLE_IS_AN_ARRAY, temp->get_name());
    return std::make_shared<Integer_locator>(i_temp);
  }
  if (array_index_expression != nullptr && array_index_expression->evaluate()->as_int() >= temp->get_count())
  {
    Error::error(Error::ARRAY_INDEX_OUT_OF_BOUNDS, temp->get_name(), array_index_expression->evaluate()->as_string());
    return std::make_shared<Integer_locator>(i_temp);
  }
  if(array_index_expression != nullptr)
  {
    return temp->as_lvalue(array_index_expression->evaluate()->as_int());
  }
  else
  {
    return temp->as_lvalue();
  }

}

GPL::Type Variable::type() const
{
  std::shared_ptr<Symbol> temp = symbol();
  if(symbol_name == "")
  {
    return GPL::INT;
  }
  if (temp == nullptr)
    return GPL::INT;
  GPL::Type t = temp->get_type();
  // failing in above line
  return t;
}

Variable::~Variable()
{
  delete array_index_expression;
}
