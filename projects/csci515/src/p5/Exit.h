#ifndef EXIT_H
#define EXIT_H

#include "Statement.h"
#include "Expression.h"

class Exit : public Statement
{
public:
  Exit(const Expression* exp, int line_number) : exp_ptr(exp), line_number(line_number){}
  void execute() const;
  ~Exit();

private:
  const Expression* exp_ptr;
  int line_number;
};

#endif
