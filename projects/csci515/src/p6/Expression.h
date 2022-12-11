//File: Expression.h
#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "types_and_ops.h"
class Constant;
class Expression {
  public:
    Expression():evaluated_constant(nullptr) {}
    virtual const Constant* evaluate() const=0;
    virtual GPL::Type type() const=0;
    virtual ~Expression();
    Expression(const Expression&) = delete;
    Expression& operator=(const Expression&) = delete;
  protected:
    //a wrapper around returned constants
    const Constant* ret(const Constant* new_evald_constant) const;
  private:
    //pointer to evaluate()'s created constant so it can be released
    mutable const Constant* evaluated_constant;
};

class Binary_operator : public Expression {
  public:
    Binary_operator(const Expression* lhs, const Expression* rhs) :lhs(lhs), rhs(rhs) {}
    virtual const Constant* evaluate() const=0;
    virtual ~Binary_operator() { delete lhs; delete rhs; }
  protected:
    const Expression* lhs;
    const Expression* rhs;
};

class Unary_operator : public Expression {
  public:
    Unary_operator(const Expression* data) :data(data) {}
    virtual const Constant* evaluate() const=0;
    virtual ~Unary_operator() { delete data;}
  protected:
    const Expression* data;
};

class Plus : public Binary_operator {
  public:
    Plus(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Multiply : public Binary_operator {
  public:
    Multiply(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Minus : public Binary_operator {
  public:
    Minus(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Mod : public Binary_operator {
  public:
    Mod(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Divide : public Binary_operator {
  public:
    Divide(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Or : public Binary_operator {
  public:
    Or(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class And : public Binary_operator {
  public:
    And(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Less_Equal : public Binary_operator {
  public:
    Less_Equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Greater_Equal : public Binary_operator {
  public:
    Greater_Equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Less : public Binary_operator {
  public:
    Less(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Greater : public Binary_operator {
  public:
    Greater(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Equal : public Binary_operator {
  public:
    Equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Not_Equal : public Binary_operator {
  public:
    Not_Equal(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Neg : public Unary_operator {
  public:
    Neg(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Not : public Unary_operator {
  public:
    Not(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Sin : public Unary_operator {
  public:
    Sin(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Cos : public Unary_operator {
  public:
    Cos(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Tan : public Unary_operator {
  public:
    Tan(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Asin : public Unary_operator {
  public:
    Asin(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Acos : public Unary_operator {
  public:
    Acos(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Atan : public Unary_operator {
  public:
    Atan(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Sqrt : public Unary_operator {
  public:
    Sqrt(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Abs : public Unary_operator {
  public:
    Abs(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Floor : public Unary_operator {
  public:
    Floor(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Random : public Unary_operator {
  public:
    Random(const Expression* data) : Unary_operator(data){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Near : public Binary_operator {
  public:
    Near(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};

class Touches : public Binary_operator {
  public:
    Touches(const Expression* lhs, const Expression* rhs) : Binary_operator(lhs, rhs){};
    virtual const Constant* evaluate() const;
    virtual GPL::Type type() const;
};
#endif
