#include "InGameScreen.h"
#include <cmath>
#include <iostream>

InGameScreen::InGameScreen() {
	
	//initial settings
	screenType = INGAME;
	levelType = Level1;


	//playerScore is a global variable throughout the levels
	playerScore = 0;
};

void InGameScreen::setLevel(LevelType level) {
	//every time we change levels, stop the emitters, and then init()

	gunEmitter.stop();
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].emitting = false;
	}

	emitters.clear();

	levelType = level;
	init();
};

//only use this to transition from level 1 to level 2 to level 3
void InGameScreen::setLevel(int level) {
	
	switch (level) {
	case 1:
		setLevel(Level1);
		//levelType = Level1;
		break;
	case 2:
		setLevel(Level2);
		//levelType = Level2;
		break;
	case 3:
		setLevel(Level1);
		//levelType = Level3;
		break;
	}
}

//this is run everytime a level is switched, or when user starts game, or when user selects a specific level
void InGameScreen::init()
{
	//player HP gets reset at each level
	gunEmitter.hp = 500;

	//only create the gunEmitter once
	gunEmitter = Emitter(GUN);
	gunEmitter.init();
	//emitters.push_back(gunEmitter);
	
	Emitter emitterA = Emitter(EMITTERA);
	Emitter emitterB = Emitter(EMITTERB);
	Emitter emitterC = Emitter(EMITTERC);

	switch (levelType) {
	case Level1:
		emitterA.init();
		emitters.push_back(emitterA);
		cout << "switched to level 1" << endl;
		break;
	case Level2:

		/*emitterA.init();
		emitters.push_back(emitterA);*/
		emitterB.init();
		emitters.push_back(emitterB);
		//create emitter A & B
		cout << "switched to level 2" << endl;
		break;
	case Level3:
		emitterC.init();
		emitters.push_back(emitterC);
		//create emitter A & B & C
		cout << "switched to level 3" << endl;
		break;
	}
	
	//initialize start menu elements
	text.load("arial.ttf", 32);
	background.load("northofthewall.jpg");

	//load starting bg music
	bgMusic.load("battle.mp3");
	bgMusic.play();
	bgMusic.setLoop(true);
};

void InGameScreen::terminate() {

	//stop music, reset transition variable, set the level back to 1, reset score
	bgMusic.stop();
	transition = false;
	levelType = Level1;
	playerScore = 0;

	//stop emitters from firing
	gunEmitter.stop();
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].emitting = false;
	}

	emitters.clear();

}

void InGameScreen::draw()
{
	//draw background image
	/*background.resize(ofGetWindowWidth(), ofGetWindowHeight());
	background.draw(0, 0);*/
	/*text.drawString(to_string(gunEmitter.hp), 50, 50);
	text.drawString(to_string(playerScore), 50, 150);*/
	ofClear(0);
	ofDrawBitmapString("HP: " + to_string(gunEmitter.hp), 20, 20);
	ofDrawBitmapString(to_string(playerScore), 20, 40);
	

	switch (levelType) {
	case Level1:
		//a.draw();
		//draw emitter A only
		
		ofDrawBitmapString("LEVEL 1: S to start, Q to quit, SPACE to fire", 20, ofGetWindowHeight() - 20);
		//text.drawString("level 1; press s to start, q to quit, space to fire", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	case Level2:
		//b.draw();
		ofClear(0);
		ofDrawBitmapString("LEVEL 2", 20, ofGetWindowHeight() - 20);
		//text.drawString("level 2; press s to start, q to quit, space to fire", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	case Level3:
		//c.draw();
		ofClear(0);
		ofDrawBitmapString("LEVEL 3", 20, ofGetWindowHeight() - 20);
		//text.drawString("level 3; press s to start, q to quit, space to fire", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	}

	gunEmitter.draw();
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].draw();
	}

	//test
	ofDrawRectangle(ofVec3f(20, 20, 0), 2, 2);

};

void InGameScreen::update() {
	

	gunEmitter.update();
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].update();
	}

	//check if bullets hit enemy sprites
	checkCollisions();

	switch (levelType) {
	
	case Level1:
		if (playerScore >= 500) {
			setLevel(2);
		}
		break;
	case Level2:
		break;
	case Level3:
		break;
	}

	//if hp hits 0 or below, transition the screen to home
	if (gunEmitter.hp <= 0) {
		transition = true;
		transitionScreen = HOME;

	}

};

void InGameScreen::checkCollisions() {
	for (int i = 0; i < emitters.size(); i++) {
		//checks if bullets hit emitter enemy sprites
		playerScore += gunEmitter.sys->checkCollisions(emitters[i].sys);
		

		//checks if emitter enemy sprites hit the gun emitter
		gunEmitter.checkCollision(emitters[i].sys);
	}

};

void InGameScreen::keyPressed(int key) {
	switch (key) {
	case ' ':
		//start gun emitter
		gunEmitter.start();
		break;
	case 's':
		//start emitters
		for (size_t i = 0; i < emitters.size(); i++) {
			emitters[i].start();
		}
		break;
	case 'q':
		//cout << "pressing q in game" << endl;
		transition = true;
		transitionScreen = HOME;
		break;
	/*case 'w':
		gunEmitter.moving = true;
		gunEmitter.movingVector += ofVec3f(0, -300, 0);
		cout << "w pressed " << endl;
		break;
	case 'a':
		gunEmitter.moving = true;
		gunEmitter.movingVector += ofVec3f(0, 300, 0);
		break;
	case 's':
		gunEmitter.moving = true;
		gunEmitter.movingVector += ofVec3f(-300, 0, 0);
		break;
	case 'd':
		gunEmitter.moving = true;
		gunEmitter.movingVector += ofVec3f(300, 0, 0);
		break;*/
	}
};

void InGameScreen::keyReleased(int key) {
	switch (key) {
	case ' ':
			//only stop the gunEmitter from firing when space is released
		gunEmitter.stop();
		
		break;
	/*case 'w':
		
		gunEmitter.movingVector.y = 0;
		break;
	case 'a':
	
		gunEmitter.movingVector.y = 0;
		break;
	case 's':
		
		gunEmitter.movingVector.x = 0;
		break;
	case 'd':
		gunEmitter.movingVector.x = 0;
		break;*/
	}
	
	
};

void InGameScreen::mouseMoved(int x, int y) {
	//cout << "mouse moving: " << x << ", " << y << endl;
	
	gunEmitter.translate(x, y);
}