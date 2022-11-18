#include "If.h"
#include "Constant.h"


If::~If()
{
  delete exp_ptr;
  delete if_ptr;
  delete else_ptr;
}

void If::execute() const
{
  const Constant* c = exp_ptr->evaluate();

  if(c != nullptr)
  {
    if(c->as_int() == 1)
    {
      if_ptr->execute();
    }
    else
    {
      else_ptr->execute();
    }
  }
  else
  {

  }
  if(next != nullptr)
    next->execute();
}
