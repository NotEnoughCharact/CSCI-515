#ifndef ASSIGN_H
#define ASSIGN_H

#include "Statement.h"
#include "Variable.h"
#include "Expression.h"


class Assign : public Statement {
  public:
    Assign(const Variable* lhs, const Expression* rhs) : lhs(lhs), rhs(rhs){}
    virtual void execute() const;
    virtual ~Assign();
  private:
    const Variable* lhs;
    const Expression* rhs;
};

#endif
