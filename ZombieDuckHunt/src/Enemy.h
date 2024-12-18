#pragma once
#include "ofMain.h"

//created and implemented by vaniya sharma 

class Enemy {
public:
    float x, y;          // Position
    float speed;         // Speed of movement
    float size;          // Size of the enemy for collision
    ofVec2f position;

    ofImage zombieFrames[4]; // Array to hold enemy sprite images
    int currentFrame;     // Current animation frame index
    float frameTime;  // Duration per frame in seconds
    float lastFrameTime;  // Tracks time since the last frame switch

    void setup(float startX, float startY, float startSpeed, int wave);
    void update();
    void draw();
    bool detectCollision(const ofRectangle& bulletRect); // Collision detection
};
