#include "ofApp.h"

void ofApp::setup() {
    ofSetWindowTitle("Zombie Duck Hunt");
    ofSetFrameRate(60);
    game.setup();
}

void ofApp::update() {
    game.update();
}

void ofApp::draw() {
    game.draw();
}

void ofApp::keyPressed(int key) {
    game.player.playerMovement(key);

    if (key == ' ') {
        game.player.shoot();
    }

    game.keyPressed(key);
}

void ofApp::keyReleased(int key) {
}

void ofApp::mousePressed(int x, int y, int button) {
    game.mousePressed(x, y, button); // Forward the mouse click to the game
}

void ofApp::mouseDragged(int x, int y, int button) {
    game.mouseDragged(x, y, button); // Forward the mouse click to the game
}

void ofApp::mouseReleased(int x, int y, int button) {
    game.mouseReleased(x, y, button); // Forward the mouse click to the game
}