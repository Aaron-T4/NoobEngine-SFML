#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"


class Mario :
    public GameObject
{



    sf::Texture marioSpriteSheet;

    Animation Walk;
    Animation Duck;
    Animation Swim;
    Animation* currentAnimation;


public:

    Mario();
    ~Mario();

    void update(float dt) override;
    void handleInput(float dt) override;

};

