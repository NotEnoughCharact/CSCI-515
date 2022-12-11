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
    for(int j = 0; j < (int)head_arr[i].size(); j++)
    {
      delete head_arr[i][j];
    }
  }
}

void Event_manager::execute_handlers(Window::Keystroke keystroke) const
{
  for(int j = 0; j < (int)head_arr[keystroke].size(); j++)
  {
    if(head_arr[keystroke][j] != nullptr)
    {
      head_arr[keystroke][j]->execute();
    }
  }
}

void Event_manager::add_handler(Window::Keystroke key, const Statement* statement)
{
  if(key >= Window::SPACE && key < Window::NUMBER_OF_KEYS)
  {
    head_arr[key].push_back(statement);
  }
  else
    assert(false);
}
