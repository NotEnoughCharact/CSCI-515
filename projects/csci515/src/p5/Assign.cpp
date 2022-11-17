#include "Assign.h"
#include "Locator.h"
#include "Constant.h"
#include "error.h"
#include <string>

void Assign::execute() const
{
  std::cerr << "here\n";
  const std::shared_ptr<Locator> left = lhs->modify();
  const Constant* c = rhs->evaluate();
  if(left->type() == GPL::INT)
  {
    if(c->type() != GPL::INT)
    {
      Error::error(Error::ASSIGNMENT_TYPE_ERROR, to_string(left->type()), to_string(c->type()));
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
      Error::error(Error::ASSIGNMENT_TYPE_ERROR, to_string(left->type()), to_string(c->type()));
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
  if(next!=nullptr) next->execute();

}

Assign::~Assign()
{
  delete lhs;
  delete rhs;
}
