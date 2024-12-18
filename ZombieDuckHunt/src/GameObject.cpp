#include "GameObject.h"

//created by alisha velji
//worked on by alisha and vainya 


void GameObject::setup() {

    //set screen size to window size 
    int screenWidth = ofGetScreenWidth();
    int screenHeight = ofGetScreenHeight();
    ofSetWindowShape(screenWidth, screenHeight);

    int windowWidth = ofGetWindowWidth();
    int windowHeight = ofGetWindowHeight();

    //centered the buttons to the screen 
    int buttonWidth = 300;
    int buttonHeight = 70;
    int centerX = windowWidth / 2 - buttonWidth / 2;

    int baseOffsetY = windowHeight / 2 - 30; 

    //buttons
    int buttonSpacing = 150;
    startButton.set(centerX, baseOffsetY, buttonWidth, buttonHeight);
    optionsButton.set(centerX, baseOffsetY + buttonSpacing, buttonWidth, buttonHeight);

    //back button
    backButton.set(50, 50, 100, 40);

    //volume slider 
    int sliderOffsetY = baseOffsetY + 2 * buttonSpacing;
    sliderTrack.set(centerX, sliderOffsetY, buttonWidth, 10);
    sliderKnob.set(sliderTrack.getX() + sliderTrack.getWidth() * volume - 10,
        sliderTrack.getY() - 5,
        20, 20);

    //first wave
    wave = 1;

    //setting up the main game screen
    gameBg.load("game_bg.png");
    main_screen.load("main_screen.png");
    instructions.load("instructions.png");

    //load game over screen
    gameOverImage.load("gameOverScreen.png");
    font.load("Tomorrow-Medium.ttf", 35);
    font1.load("Tomorrow-Medium.ttf", 15);
    heartImage.load("heart.png");

    powerupSound.load("yippee.mp3");
    gameOverSound.load("wompwomp.mp3");
    bgSound.load("tropicala.mp3");
    enemyCollideSound.load("oof.mp3");
    enemySpawnSound.load("zombieGrowl.mp3");
    enemyDeadSound.load("zombieDead.mp3");

    bgSound.setLoop(true);
    bgSound.play();

    gameState = START;
}


void GameObject::update() {

    if (gameState == PLAYING) {
        //if user health reaches 0, game is over
        if (player.hearts == 0 || enemiesReachedBottom >= 15) {
            gameState = GAME_OVER;
            return; 
        }

        //setup the player 
        if (!player.isInitialized()) {  
            player.setup(ofGetWidth() / 2, ofGetHeight() - 100, 3);  
        }
        player.update();

        float currentTime = ofGetElapsedTimef();
        if (currentTime - lastSpawnTime >= spawnDelay) {
            spawnEnemies();
            lastSpawnTime = currentTime;
            spawnDelay = ofRandom(3.0f, 4.5f);
        }

        //spawn power-ups at random intervals
        if (ofRandom(0, 1) < 0.002) { 
            PowerUp powerup;
            powerup.setup(ofRandom(0, ofGetWidth()), 0,
                static_cast<PowerUp::Type>(ofRandom(0, 2)), 300);
            powerups.push_back(powerup);
        }

        //update enemies and powerups
        for (auto& enemy : enemies) {
            enemy.update();
        }
        for (auto& powerup : powerups) {
            powerup.updatePos();
        }

        checkCollision();
    }
    else if (gameState == GAME_OVER) {
        std::cout << "Game Over! Hearts are " << player.hearts << std::endl;

        //check for Enter key press to restart the game
        if (ofGetKeyPressed(OF_KEY_RETURN)) {
            std::cout << "ENTER key pressed in GAME_OVER state" << std::endl;
            //restart game when Enter is pressed
            resetGame();  
            gameState = PLAYING;  
            //std::cout << "Changed to PLAYING state after resetting game" << std::endl;
        }
    }

  
}

void GameObject::draw() {

    std::cout << "Current game state: " << gameState << std::endl;

    //clear the screen if the game state is GAME_OVER to ensure no game is going on
    //if (gameState == GAME_OVER) {
       // ofClear(0);
    //}

     if (gameState == START) {
        ofSetColor(255);
        main_screen.draw(0, 0, ofGetWidth(), ofGetHeight());

       
        // Start Button
        std::string startText = "Start Game";
        ofRectangle startBox = font.getStringBoundingBox(startText, 0, 0);

        ofSetColor(100, 200, 100); // Green color
        ofDrawRectangle(startButton);
        ofSetColor(255);
        font.drawString(startText, startButton.getX() + (startButton.getWidth() - startBox.getWidth()) / 2, startButton.getY() + (startButton.getHeight() + startBox.getHeight()) / 2);

        // Options Button
        std::string optionsText = "Options";
        ofRectangle optionsBox = font.getStringBoundingBox(optionsText, 0, 0);

        ofSetColor(100, 100, 200); // Blue color
        ofDrawRectangle(optionsButton);
        ofSetColor(255);
        font.drawString(optionsText, optionsButton.getX() + (optionsButton.getWidth() - optionsBox.getWidth()) / 2, optionsButton.getY() + (optionsButton.getHeight() + optionsBox.getHeight()) / 2);

        // Slider Track
        ofSetColor(200); // Gray for track
        ofDrawRectangle(sliderTrack);

        // Slider Knob
        ofSetColor(100, 100, 255); // Blue for knob
        ofDrawRectangle(sliderKnob);
        ofSetColor(255);

        // Volume Text
        std::string volumeText = "Volume: " + std::to_string(static_cast<int>(volume * 100)) + "%";
        ofRectangle volumeBox = font.getStringBoundingBox(volumeText, 0, 0);
        font.drawString(volumeText, sliderTrack.getX() + (sliderTrack.getWidth() - volumeBox.getWidth()) / 2, sliderTrack.getY() - 10);
    }
    else if (gameState == PLAYING) {
        ofSetColor(255);
        gameBg.draw(0, 0, ofGetWidth(), ofGetHeight());
        player.draw();

        for (auto& enemy : enemies) {
            enemy.draw();
        }
        for (auto& powerup : powerups) {
            powerup.draw();
        }
        //display the score
        ofSetColor(255);
        font1.drawString("Score: " + std::to_string(player.score), 20, 20);

        //draw health hearts 
        ofSetColor(255);
        font1.drawString("Health:", 20, 50);

        ofSetColor(255);
        for (int i = 0; i < player.hearts; i++) {
            heartImage.draw(20 + i * (heartImage.getWidth() + 2), 60);
        }

        //display the score
        ofSetColor(255);
        font1.drawString("Enemies reached the Swamp: "+ std::to_string(enemiesReachedBottom), ofGetWidth() - 350, 20);
        
    }

    else if (gameState == OPTIONS) {
        ofSetColor(255);
        instructions.draw(0, 0, ofGetWidth(), ofGetHeight());

        // Back Button
        std::string backText = "Back";
        ofRectangle backBox = font.getStringBoundingBox(backText, 0, 0);

        ofSetColor(150, 150, 150); // Gray color
        ofDrawRectangle(backButton);
        ofSetColor(255);
        font.drawString(backText, backButton.getX() + (backButton.getWidth() - backBox.getWidth()) / 2, backButton.getY() + (backButton.getHeight() + backBox.getHeight()) / 2);

    }
    //game over logic
    else if (gameState == GAME_OVER) {
        ofSetColor(255);

        gameOverImage.draw(0, 0, ofGetWidth(), ofGetHeight());

        ofSetColor(255);
        std::string scoreText = "Score: " + std::to_string(player.score);

        ofRectangle textRect = font.getStringBoundingBox(scoreText, 0, 0);
        font.drawString(scoreText, ofGetWidth() / 2 - textRect.getWidth() / 2, ofGetHeight() / 2 + textRect.getHeight() / 2);
    }

}


void GameObject::spawnEnemies() {
    int numEnemies = ofRandom(2, 4); // Spawn 3 to 5 enemies per wave
    for (int i = 0; i < numEnemies; ++i) {
        Enemy enemy;
        float speed = ofRandom(0.5f, 1.0f); // Base speed
        enemy.setup(ofRandom(0, ofGetWidth()), 0, speed, wave); // Pass wave to setup
        enemies.push_back(enemy);

        enemySpawnSound.play();
        
    }
    wave++; // Increment wave for progression

}


void GameObject::checkCollision() {
    //player v bullets
    for (auto bulletIt = player.bullets.begin(); bulletIt != player.bullets.end();) {
        bool bulletHit = false;
        for (auto enemyIt = enemies.begin(); enemyIt != enemies.end();) {
            if (enemyIt->detectCollision(bulletIt->getBoundingBox())) {
                player.score += 10; 

                
                enemyDeadSound.play();


                enemyIt = enemies.erase(enemyIt);
                bulletHit = true;
                break;
            }
            else {
                ++enemyIt;
            }
        }
        bulletHit ? bulletIt = player.bullets.erase(bulletIt) : ++bulletIt;
    }

    //player v enemy
    for (auto it = enemies.begin(); it != enemies.end();) {
        if (std::abs(it->position.x - player.position.x) < 60 &&
            std::abs(it->position.y - player.position.y) < 60) { 

            enemyCollideSound.play();

            if (player.hearts > 0) {
                player.hearts -= 1;
                std::cout << "Player hit! Hearts left: " << player.hearts << std::endl;
            }
            it = enemies.erase(it); 
        }
        else if (it->position.y > ofGetHeight()) { // Enemy reaches bottom of the screen
            ++enemiesReachedBottom; // Increment the counter
            std::cout << "Enemy reached the bottom! Total: " << enemiesReachedBottom << std::endl;

            // Remove the enemy from the list
            it = enemies.erase(it);

            // Check if the game should end
            if (enemiesReachedBottom >= 15) {
               
                std::cout << "Game Over! 15 or more enemies reached the bottom." << std::endl;
                //return;
            }
        }
        else {
            ++it;
        }
    }

    //player v powerup
    for (auto it = powerups.begin(); it != powerups.end();) {
        if (std::abs(it->position.x - player.position.x) < 30 &&
            std::abs(it->position.y - player.position.y) < 30) {
            // Apply the power-up effect to the player
            //player.collectPowerup(*it);
            it->applyEffect(player);
            powerupSound.play();
            it = powerups.erase(it);
        }
        else {
            ++it;
        }
    }

    //check if the player's hearts are 0, and if so, transition to GAME_OVER state
    if (player.hearts == 0 || enemiesReachedBottom >= 15) {
        gameOverSound.play();
        bgSound.stop();
        gameState = GAME_OVER;
    }
}

void GameObject::mousePressed(int x, int y, int button) {
    if (gameState == START) {
        if (startButton.inside(x, y)) {
            gameState = PLAYING;
            player.setup(ofGetWidth() / 2, ofGetHeight() - 100, 100); // Initialize player on game start
        }
        else if (optionsButton.inside(x, y)) {
            gameState = OPTIONS;
        }
        else if (sliderKnob.inside(x, y)) {
            isDraggingKnob = true;
        }
    }
    else if (gameState == OPTIONS) {
        if (backButton.inside(x, y)) {
            gameState = START; // Go back to the start menu
        }
    }
}

void GameObject::mouseDragged(int x, int y, int button) {
    if (isDraggingKnob) {
        // Constrain knob within the slider track
        float newKnobX = ofClamp(x, sliderTrack.getX(), sliderTrack.getX() + sliderTrack.getWidth());
        sliderKnob.setX(newKnobX - sliderKnob.getWidth() / 2);

        // Calculate new volume level
        volume = (newKnobX - sliderTrack.getX()) / sliderTrack.getWidth();
        ofSoundSetVolume(volume); // Set the volume globally
    }
}


void GameObject::mouseReleased(int x, int y, int button) {
    if (isDraggingKnob) {
        isDraggingKnob = false;
    }
}

void GameObject::keyPressed(int key) {
    if (gameState == START) {
        if (key == OF_KEY_RETURN) {
            gameState = PLAYING;
        }
    }
    else if (gameState == GAME_OVER) {
        if (key == OF_KEY_RETURN) {
            resetGame();
            gameState = PLAYING;
        }
    }
}

void GameObject::resetGame() {
    //reset all variables to start a new game
    player.score = 0;
    player.hearts = 3;  
    wave = 1;  // Reset wave counter
    enemiesReachedBottom = 0;  // Reset the enemy bottom counter
    enemies.clear();    
    powerups.clear();   
    lastSpawnTime = ofGetElapsedTimef();
    spawnDelay = ofRandom(3.0f, 4.5f); 

    bgSound.stop();
    bgSound.play();


}