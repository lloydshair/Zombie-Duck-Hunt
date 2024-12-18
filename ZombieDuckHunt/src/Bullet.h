#pragma once
#include "ofMain.h"

//created and implemented by alisha velji

class Bullet {
public:
    ofVec2f position;
    float speed;
    ofImage bulletImage;

    Bullet();
    void setup(float x, float y, float speed);
    void updatePos();
    void draw();

    //added this function to return the bullet's bounding box for collision to work
    ofRectangle getBoundingBox() const;
};
