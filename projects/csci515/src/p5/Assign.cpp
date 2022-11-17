#include "Assign.h"
#include "Locator.h"
#include "Constant.h"

void Assign::execute() const
{
  const std::shared_ptr<Locator> left = lhs->modify();
  const Constant* c = rhs->evaluate();
  if(left->type() == GPL::INT)
  {
    if(c->type() != GPL::INT)
    {

    }
    else
    {
      left->mutate(c->as_int());
    }
  }
  else if(left->type() == GPL::DOUBLE)
  {
    if(c->type() == GPL::STRING)
    {

    }
    else
    {
      left->mutate(c->as_double());
    }
  }
  else if(left->type() == GPL::STRING)
  {
    left->mutate(c->as_string());
  }
  else
    throw left->type();
  //std::cerr << left->ret_string() << "\n";
  if(next!=nullptr) next->execute();

}

Assign::~Assign()
{
  delete lhs;
  delete rhs;
}
