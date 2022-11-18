#ifndef IF_H
#define IF_H

#include "Statement.h"
#include "Expression.h"

class If : public Statement
{
public:
  If(const Expression* exp, const Statement* if_ptr, const Statement* else_ptr = new NullStatement()) : exp_ptr(exp), if_ptr(if_ptr), else_ptr(else_ptr){}
  void execute() const;
  ~If();

private:
  const Expression* exp_ptr;
  const Statement* if_ptr;
  const Statement* else_ptr;
};

#endif
