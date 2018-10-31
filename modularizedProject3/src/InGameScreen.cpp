#include "InGameScreen.h"


InGameScreen::InGameScreen() {
	
	screenType = INGAME;
	levelType = Level1;

	gunEmitter = Emitter(GUN);
	gunEmitter.init();
	emitters.push_back(gunEmitter);
	//init();

};

//InGameScreen::InGameScreen(LevelName lname) {
//	levelName = lname;
//	init();
//
//};

void InGameScreen::setLevel(LevelType level) {
	levelType = level;
};

void InGameScreen::setLevel(int level) {
	switch (level) {
	case 1:
		levelType = Level1;
		break;
	case 2:
		levelType = Level2;
		break;
	case 3:
		levelType = Level3;
		break;
	}
}

void InGameScreen::init()
{
	//always create a gun emitter
	

	switch (levelType) {
	case Level1:
		//create emitter A
		cout << "switched to level 1" << endl;
		break;
	case Level2:
		//create emitter A & B
		cout << "switched to level 2" << endl;
		break;
	case Level3:
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
	bgMusic.stop();
	transition = false;
}

void InGameScreen::draw()
{
	//draw background image

	background.resize(ofGetWindowWidth(), ofGetWindowHeight());
	background.draw(0, 0);



	switch (levelType) {
	case Level1:
		//a.draw();
		text.drawString("level 1; press q to quit", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	case Level2:
		//b.draw();
		text.drawString("level 2; press q to quit", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	case Level3:
		//c.draw();
		text.drawString("level 3; press q to quit", ofGetWindowWidth() * 3 / 10, ofGetWindowHeight() * 13 / 20);
		break;
	}
	
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].draw();
	}

};

void InGameScreen::update() {
	
	for (size_t i = 0; i < emitters.size(); i++) {
		emitters[i].update();
	}

};

void InGameScreen::keyPressed(int key) {
	switch (key) {
	case ' ':
		//cout << "pressing space in game" << endl;
		emitters[0].emitting = true;
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
	/*switch (key) {
	case ' ':
		cout << "released space in game" << endl;
		break;
	case 'w':
		cout << "w released" << endl;
		gunEmitter.movingUp = false;
		gunEmitter.movingVector.y = 0;
		break;
	case 'a':
		gunEmitter.movingLeft = false;
		gunEmitter.movingVector.y = 0;
		break;
	case 's':
		gunEmitter.movingDown = false;
		gunEmitter.movingVector.x = 0;
		break;
	case 'd':
		gunEmitter.movingRight = false;
		gunEmitter.movingVector.x = 0;
		break;
	}*/
};

void InGameScreen::mouseMoved(int x, int y) {
	//cout << "mouse moving: " << x << ", " << y << endl;
	
	emitters[0].translate(x, y);
}