#pragma once
#include "ofMain.h"

//created and implemented by alisha velji

class Player;

class PowerUp {
public:
    enum class Type { 
        HEALTH, BONUS
    };

    ofVec2f position;
    int duration;
    float speed;
    Type type;

    ofImage heartImage;
    ofImage boosterImage;

    PowerUp();
    void setup(float x, float y, Type type, int duration);
    void updatePos();
    void draw();
    void applyEffect(Player& player);

   
    
};
