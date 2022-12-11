#ifndef GAME_OBJECT_CONSTANT_H
#define GAME_OBJECT_CONSTANT_H
#include "Constant.h"
#include "Game_object.h"
#include "Scope_manager.h"
#include "Symbol.h"

class Game_object_constant : public Constant {
  public:
    Game_object_constant(const Game_object* gop)
      : Constant(GPL::GAME_OBJECT),
        gop(gop) {}

    virtual const Game_object* as_game_object() const;

  private:
    const Game_object* gop;
};

#endif
