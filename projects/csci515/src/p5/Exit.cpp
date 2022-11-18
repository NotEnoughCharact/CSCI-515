#include "Exit.h"
#include "Constant.h"
#include <iostream>

Exit::~Exit()
{
  delete exp_ptr;
}

void Exit::execute() const
{
  const Constant* c = exp_ptr->evaluate();
  std::cout << "gpl[" << line_number << "]: exit(" << c->as_int() << ")\n";
  exit(c->as_int());
}
