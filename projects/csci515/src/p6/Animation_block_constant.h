#ifndef ANIMATION_BLOCK_CONSTANT_H
#define ANIMATION_BLOCK_CONSTANT_H
#include "Constant.h"
#include "Animation_code.h"
#include "Scope_manager.h"
#include "Symbol.h"

class Animation_block_constant : public Constant {
  public:
    Animation_block_constant(const Animation_code* a)
      : Constant(GPL::GAME_OBJECT),
        a_code(a) {}

    virtual const Animation_code* as_animation_block() const { return a_code; }

  private:
    const Animation_code* a_code;
};

#endif
