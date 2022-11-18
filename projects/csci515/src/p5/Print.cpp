#include "Print.h"
#include "Constant.h"
#include "error.h"
#include <iostream>

Print::~Print()
{
  delete argument;
}

void Print::execute() const
{
  const Constant* c = argument->evaluate();
  if(c != nullptr)
  {
    if(c->type() == GPL::INT || c->type() == GPL::DOUBLE || c->type() == GPL::STRING)
      std::cout << "print[" << line_number << "]: " << c->as_string() << "\n";
  }
  else
  {
    Error::error(Error::INVALID_TYPE_FOR_PRINT_STMT_EXPRESSION);
  }
  if(next != nullptr)
    next->execute();
}
