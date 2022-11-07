#ifndef MEMBER_VARIABLE_H
#define MEMBER_VARIABLE_H

#include "Variable.h"


class Member_variable : public Variable {
  public:

    Member_variable(const std::string& name, const::std::string& attribute);
    Member_variable(const std::string& name, const Expression* index_expr, const::std::string& attribute);

    virtual const Constant* evaluate() const override;
    virtual GPL::Type type() const override;

  private:
    std::string attribute;

};

#endif
