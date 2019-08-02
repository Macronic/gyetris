#ifndef ANIMATIONGAMEOFLIFE_H_DEFINED
#define ANIMATIONGAMEOFLIFE_H_DEFINED

#include <Engine/Graphics/Animation/AnimationLegacy.hpp>
#include <Engine/Helpers/Array2D.hpp>
#include <Engine/Helpers/Timer.hpp>

#include <vector>

/// Rules and behavior of the GameOfLife animation.
class AnimationGameOfLife: public AnimationLegacy
{
  public:
    AnimationGameOfLife(Window* window);
    virtual ~AnimationGameOfLife();

    void load();
    void update();
    void draw();

    void handleEvent(GameEvent type) override;

  private:
    Array2D<bool>* cells;

    Timer timer;
};

#endif //ANIMATIONGAMEOFLIFE_H_DEFINED

