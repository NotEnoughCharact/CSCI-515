#include "Assign.h"
#include "Locator.h"
#include "Constant.h"
#include "error.h"
#include <string>

void Assign::execute() const
{
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
  else if(left->type() == GPL::ANIMATION_BLOCK && (c->type() == GPL::ANIMATION_CODE || c->type() == GPL::ANIMATION_BLOCK))
  {
    const Animation_code* anim_block=c->as_animation_block();
    if(rhs->type() == GPL::ANIMATION_CODE)
    {
      Animation_code::used_blocklist.insert(anim_block->get_block_name());
      left->mutate(anim_block->get_block_name());
    }
    else
    {
      left->mutate(anim_block);
    }
  }
  else if(left->type() == GPL::ANIMATION_CODE)
  {
    Error::error(Error::CANNOT_ASSIGN_TO_ANIMATION_CODE);
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

void Plus_assign::execute() const
{
  const std::shared_ptr<Locator> left = lhs->modify();
  const Constant* lval = lhs->evaluate();
  const Constant* c = rhs->evaluate();
  if(left->type() == GPL::INT)
  {
    if(c->type() != GPL::INT)
    {
      Error::error(Error::ASSIGNMENT_TYPE_ERROR, to_string(left->type()), to_string(c->type()));
    }
    else
    {
      left->mutate(lval->as_int()+c->as_int());
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
      left->mutate(lval->as_double()+c->as_double());
    }
  }
  else if(left->type() == GPL::STRING)
  {
    left->mutate(lval->as_string()+c->as_string());
  }
  else
    throw left->type();
  if(next!=nullptr) next->execute();

}

Plus_assign::~Plus_assign()
{
  delete lhs;
  delete rhs;
}

void Minus_assign::execute() const
{
  const std::shared_ptr<Locator> left = lhs->modify();
  const Constant* lval = lhs->evaluate();
  const Constant* c = rhs->evaluate();
  if(left->type() == GPL::INT)
  {
    left->mutate(lval->as_int()-c->as_int());
  }
  else if(left->type() == GPL::DOUBLE)
  {
    left->mutate(lval->as_double()-c->as_double());
  }
  else
    throw left->type();
  if(next!=nullptr) next->execute();

}

Minus_assign::~Minus_assign()
{
  delete lhs;
  delete rhs;
}

void Plus_plus::execute() const
{
  const std::shared_ptr<Locator> left = lhs->modify();
  const Constant* lval = lhs->evaluate();
  if(left->type() == GPL::INT)
  {
    left->mutate(lval->as_int()+1);
  }
  else
    throw left->type();
  if(next!=nullptr) next->execute();

}

Plus_plus::~Plus_plus()
{
  delete lhs;
}

void Minus_minus::execute() const
{
  const std::shared_ptr<Locator> left = lhs->modify();
  const Constant* lval = lhs->evaluate();
  if(left->type() == GPL::INT)
  {
    left->mutate(lval->as_int()-1);
  }
  else
    throw left->type();
  if(next!=nullptr) next->execute();

}

Minus_minus::~Minus_minus()
{
  delete lhs;
}
