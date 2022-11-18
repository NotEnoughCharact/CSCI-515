#include "For.h"
#include "Constant.h"

For::~For()
{
  delete cond_ptr;
  delete init_ptr;
  delete inc_ptr;
  delete body_ptr;
}


void For::execute() const
{
  const Statement* temp = new NullStatement();
  if(init_ptr != temp)
  {
    init_ptr->execute();
  }
  const Constant* c = cond_ptr->evaluate();
  while(c->as_int() == 1)
  {
    body_ptr->execute();
    if(inc_ptr != temp)
      inc_ptr->execute();
    c = cond_ptr->evaluate();
  }
  if(next != nullptr)
    next->execute();

  delete temp;

}
