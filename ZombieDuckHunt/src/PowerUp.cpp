#include "PowerUp.h"
#include "Player.h"

//created and implemented by alisha velji

PowerUp::PowerUp() : speed(1.5f), duration(300) {}

void PowerUp::setup(float x, float y, Type powerType, int effectDuration) {
    position.set(x, y);
    type = powerType;
    duration = effectDuration;

    heartImage.load("heart.png");
    boosterImage.load("bonus.png");
}

void PowerUp::updatePos() {
    position.y += speed;
}

void PowerUp::draw() {
    ofColor(255);
    if (type == PowerUp::Type::HEALTH) {
        heartImage.draw(position.x, position.y);
    }
    else if (type == PowerUp::Type::BONUS) {
        boosterImage.draw(position.x, position.y);
    }

}

void PowerUp::applyEffect(Player& player) {
    if (type == PowerUp::Type::HEALTH) {
        //increase the number of hearts (up to a maximum of 5)
        if (player.hearts < 5) {
            player.hearts += 1;
        }
    }
    else if (type == PowerUp::Type::BONUS) {
        //increase score by 50
        player.score += 50;
    }
}