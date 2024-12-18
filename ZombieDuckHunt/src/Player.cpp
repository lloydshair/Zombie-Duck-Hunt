#include "Player.h"

//created and implemented by alisha velji

Player::Player() : hearts(3), score(0), movementSpeed(5.0f), bulletSpeed(-10.0f), velocity(0, 0) {}

void Player::setup(float x, float y, int initialHearts) {
    position.set(x, y);
   // health = initialHealth;
    hearts = 3;
    score = 0;
    isSetup = true;

    playerImg.load("duck.png");
    playerLeft.load("duckLeft.png");
    shootSound.load("pew.mp3");
}


void Player::update() {
    //update bullets
    for (auto& bullet : bullets) {
        bullet.updatePos();
    }
   
    bullets.erase(remove_if(bullets.begin(), bullets.end(),
        [](Bullet& b) { return b.position.y < 0; }), bullets.end());

    //apply velocity to position
    position += velocity;

    velocity *= 0.9f; 

    if (hearts > 5) {
        hearts = 5; 
    }
    if (hearts < 0) {
        hearts = 0; 
    }
}

void Player::draw() {
    //draw player
    float offsetY = -20; 

    if (velocity.x < 0) {
        playerLeft.draw(position.x, position.y + offsetY);
    }
    else {
        playerImg.draw(position.x, position.y + offsetY);

    }

    // Draw bullets
    for (auto& bullet : bullets) {
        bullet.draw();
    }
}

void Player::playerMovement(int key) {
    float acceleration = 0.5f; 
    float maxSpeed = movementSpeed; 

    //check if keys are pressed and adjust velocity accordingly
    if (key == OF_KEY_LEFT) {
        velocity.x = -maxSpeed; 
    }
    else if (key == OF_KEY_RIGHT) {
        velocity.x = maxSpeed; 
    }

    //stop horizontal movement when no keys are pressed
    if (!(key == OF_KEY_LEFT || key == OF_KEY_RIGHT)) {
       
        if (velocity.x > 0) {
            velocity.x -= acceleration;
        }
        else if (velocity.x < 0) {
            velocity.x += acceleration; 
        }
    }

    //limit the player's movement to the screen bounds
    position.x = ofClamp(position.x, 0, ofGetWidth() - playerImg.getWidth());
}

void Player::shoot() {
    Bullet bullet;
    bullet.setup(position.x + 25, position.y, bulletSpeed);
    bullets.push_back(bullet);
    shootSound.play();
}

void Player::collectPowerup(PowerUp& powerup) {
    if (powerup.type == PowerUp::Type::HEALTH) {
        if (hearts < 5) {
            hearts += 1;
        }
    }
    else if (powerup.type == PowerUp::Type::BONUS) {
        score += 50; 
    }
}

void Player::reset(int initialHearts) {
    hearts = initialHearts;
    score = 0;
    position.set(ofGetWidth() / 2 - playerImg.getWidth() / 2, ofGetHeight() - 100);
}
