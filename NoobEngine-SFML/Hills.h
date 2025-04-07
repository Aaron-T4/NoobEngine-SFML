#pragma once
#include "Framework/Animation.h"
#include "Framework/GameObject.h"
class Hills :
    public GameObject
{

    
        sf::Texture HillBackgrond;
    public:

Hills();
        ~Hills();

        void update(float dt) override;
        void handleInput(float dt) override;


    
};

