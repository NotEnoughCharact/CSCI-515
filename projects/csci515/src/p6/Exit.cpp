#include "Exit.h"
#include "Constant.h"
#include <iostream>
#include "Event_manager.h"
#include "Window.h"

Exit::~Exit()
{
  delete exp_ptr;
}

void Exit::execute() const
{
  Event_manager::instance().execute_handlers(Window::TERMINATE);
  const Constant* c = exp_ptr->evaluate();
  std::cout << "gpl[" << line_number << "]: exit(" << c->as_int() << ")\n";
  exit(c->as_int());
}
