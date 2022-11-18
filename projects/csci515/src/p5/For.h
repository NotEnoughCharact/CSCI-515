#ifndef FOR_H
#define FOR_H

#include "Statement.h"
#include "Expression.h"

class For : public Statement
{
public:
  For(const Expression* cond, const Statement* init_ptr, const Statement* inc_ptr, const Statement* body_ptr)
  : cond_ptr(cond), init_ptr(init_ptr), inc_ptr(inc_ptr), body_ptr(body_ptr){}
  void execute() const;
  ~For();

private:
  const Expression* cond_ptr;
  const Statement* init_ptr;
  const Statement* inc_ptr;
  const Statement* body_ptr;
};

#endif
