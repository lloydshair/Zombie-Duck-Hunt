#include "Enemy.h"

//created and implemented by vaniya sharma 

void Enemy::setup(float x, float y, float speed, int wave) {
    position.set(x, y);
    this->speed = speed + wave * 0.2;  // Increase speed with wave
    frameTime = 8;                    // 8 frames per second
    currentFrame = 0;                 // Start with the first frame
    lastFrameTime = ofGetElapsedTimef(); // Record the start time

    // Load individual sprite images
    zombieFrames[0].load("enemy_0.png");
    zombieFrames[1].load("enemy_1.png");
    zombieFrames[2].load("enemy_2.png");
    zombieFrames[3].load("enemy_3.png");
}

void Enemy::update() {
    // Move the enemy downwards
    position.y += speed;

    // Update the animation frame based on time
    float currentTime = ofGetElapsedTimef();
    if (currentTime - lastFrameTime >= 1.0f / frameTime) {
        currentFrame = (currentFrame + 1) % 4;  // Cycle through frames 0-3
        lastFrameTime = currentTime;           // Reset timer
    }
}

void Enemy::draw() {
    ofSetColor(255); // Reset color to avoid tinting the sprites
    zombieFrames[currentFrame].draw(position.x, position.y, 60, 60); // Adjust size as needed
}


bool Enemy::detectCollision(const ofRectangle& bulletRect) {
    ofRectangle enemyRect(position.x, position.y, 60, 60);
    return enemyRect.intersects(bulletRect); // Check if bullet and enemy intersect
}
