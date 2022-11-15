// updated Mon Nov  9 22:38:22 PST 2020

#include <memory>
#include <cassert>
#include "Event_manager.h"


/* static */ Event_manager&  Event_manager::instance()
{
  static Event_manager the_manager;
  return the_manager;
}

Event_manager::~Event_manager()
{
  for(int i = 0; i < Window::NUMBER_OF_KEYS; i++)
  {
    delete head_arr[i];
  }
}

void Event_manager::execute_handlers(Window::Keystroke keystroke) const
{
  for(int i = 0; i < Window::NUMBER_OF_KEYS; i++)
  {
    if(head_arr[i] != nullptr)
    {
      head_arr[i]->execute();
    }
  }
}

void Event_manager::add_handler(Window::Keystroke key, const Statement* statement)
{
  if(key >= Window::SPACE && key < Window::NUMBER_OF_KEYS)
  {
    head_arr[key] = statement;
  }
  else
    assert(false);
}
