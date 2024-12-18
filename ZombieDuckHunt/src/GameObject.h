#pragma once
#include "ofMain.h"
#include "Enemy.h"
#include "Player.h" 
#include "PowerUp.h" 

//created by alisha velji
//worked on by alisha and vaniya 

enum GameState {
    START,
    PLAYING,
    OPTIONS,
    GAME_OVER
};

class GameObject {
public:
    GameState gameState = START;

    ofRectangle startButton;
    ofRectangle optionsButton;
    //ofRectangle volumeButton;
    ofRectangle backButton;

    ofRectangle sliderTrack;  // Slider track rectangle
    ofRectangle sliderKnob;   // Slider knob rectangle
    bool isDraggingKnob = false; // To check if the knob is being dragged
    float volume = 0.5f;      // Volume level (0.0 to 1.0)

    Player player;                
    std::vector<Enemy> enemies;
    std::vector<PowerUp> powerups; 
    int hearts = 3; 
    int enemiesReachedBottom = 0;

    int wave;                     // Current wave
    float enemySpawnRate;         // Time between enemy spawns
    float lastSpawnTime;
    float spawnDelay;

    ofImage gameOverImage; 
    ofTrueTypeFont font;
    ofTrueTypeFont font1;
    ofImage gameBg;
    ofImage main_screen;
    ofImage instructions;

    ofImage heartImage;
    ofSoundPlayer powerupSound;
    ofSoundPlayer gameOverSound;
    ofSoundPlayer enemyCollideSound;
    ofSoundPlayer bgSound;
    ofSoundPlayer enemySpawnSound;
    ofSoundPlayer enemyDeadSound;

    void setup();
    void update();
    void draw();
    void spawnEnemies();
    void checkCollision();
    void mousePressed(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);

    void resetGame();
};
