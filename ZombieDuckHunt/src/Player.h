#pragma once
#include "ofMain.h"
#include "Bullet.h"
#include "PowerUp.h"

//created and implemented by alisha velji

class Player {
public:
    
    ofVec2f position;
    ofVec2f velocity;
    vector<Bullet> bullets;
    int health;
    int hearts = 3;
    int score;
    float movementSpeed;

    bool isSetup = false;
    ofImage playerImg;
    ofImage playerLeft;
    ofSoundPlayer shootSound;

    Player();
    void setup(float x, float y, int health);
    void update();
    void draw();
    void playerMovement(int key);
    void shoot();
    void collectPowerup(PowerUp& powerup);
    void reset(int initialHearts);

    bool isInitialized() const { return isSetup; }

private:
    float bulletSpeed;
};

