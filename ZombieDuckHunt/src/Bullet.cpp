#include "Bullet.h"

//created and implemented by alisha velji

Bullet::Bullet() : speed(0.0f) {}

void Bullet::setup(float x, float y, float bulletSpeed) {
    position.set(x, y);
    speed = bulletSpeed;

    bulletImage.load("bullet.png");
}

void Bullet::updatePos() {
    position.y += speed;
}

void Bullet::draw() {

    bulletImage.draw(position.x - bulletImage.getWidth() / 2, position.y - bulletImage.getHeight() / 2);
}

// using the new function to get bullet's bounding box
ofRectangle Bullet::getBoundingBox() const {
    return ofRectangle(position.x - bulletImage.getWidth() / 2,
        position.y - bulletImage.getHeight() / 2,
        bulletImage.getWidth(),
        bulletImage.getHeight());
}