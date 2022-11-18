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

class Plus_assign : public Statement {
  public:
    Plus_assign(const Variable* lhs, const Expression* rhs) : lhs(lhs), rhs(rhs){}
    virtual void execute() const;
    virtual ~Plus_assign();
  private:
    const Variable* lhs;
    const Expression* rhs;
};

class Minus_assign : public Statement {
  public:
    Minus_assign(const Variable* lhs, const Expression* rhs) : lhs(lhs), rhs(rhs){}
    virtual void execute() const;
    virtual ~Minus_assign();
  private:
    const Variable* lhs;
    const Expression* rhs;
};

class Plus_plus : public Statement {
  public:
    Plus_plus(const Variable* lhs) : lhs(lhs){}
    virtual void execute() const;
    virtual ~Plus_plus();
  private:
    const Variable* lhs;
};

class Minus_minus : public Statement {
  public:
    Minus_minus(const Variable* lhs) : lhs(lhs){}
    virtual void execute() const;
    virtual ~Minus_minus();
  private:
    const Variable* lhs;
};

#endif
