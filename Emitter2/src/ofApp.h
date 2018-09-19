#pragma once

#include "ofMain.h"

typedef enum { MoveStop, MoveLeft, MoveRight, MoveUp, MoveDown } MoveDir;

// This is a base object that all drawable object inherit from
// It is possible this will be replaced by ofNode when we move to 3D
//
class BaseObject {
public:
	BaseObject() {
		trans = ofVec2f(0,0);
		scale = ofVec2f(1);
		rot = 0;
	};
	ofVec2f trans, scale;
	float	rot;
	bool	bSelected;
	void setPosition(ofVec3f p) { 
		trans = p; }
};

//  General Sprite class  (similar to a Particle)
//
class Sprite : public BaseObject {
public:
	//ofVec2f pos;
	Sprite() {
		speed = 5;
		birthtime = ofGetElapsedTimeMillis(); 
		lifespan = 50;
		//haveImage = false;
		width = 15;
		height = 15;
		velocity = ofVec3f(1, 1, 1);
	};
	//void translate() {
	//	pos.x + speed;
	//	pos.y + speed;
	//}
	void draw()	{
			ofSetColor(ofColor::blue);
			ofDrawRectangle(trans, 50, 50);
		};
	float age() {
		return ofGetElapsedTimeMillis() - birthtime;
	};
	void setImage(ofImage);
	float speed;    //   in pixels/sec
	ofVec3f velocity; // in pixels/sec
	ofImage image;
	float birthtime; // elapsed time in ms
	float lifespan;  //  time in ms
	string name; //give names to sprite for debugging purposes
	bool haveImage;
	float width, height;
};

//  Manages all Sprites in a system.  You can create multiple systems
//
class SpriteSystem {
public:
	void add(Sprite s) {
		sprites.push_back(s);
		cout << sprites.size() << endl;
		//adds sprites to the vector array
	};
	void remove(int) {
		//removes sprite at index[int]
	}	;
	void update() {

		for (int i = 0; i < sprites.size(); i++) {
			cout << sprites[i].age();
		}

		for (int i = 0; i < sprites.size(); i++) {
			sprites[i].trans += sprites[i].velocity / ofGetFrameRate();
		}
		
		//cout << "updating" << endl;
		//keeps track of age of sprites & removes those who are too old
		//animate sprites by updating the positions; update their pos vectors
	};
	void draw() {
		for (int i = 0; i < sprites.size(); i++) {
			sprites[i].draw();
		}
		//cout << "drawing" << endl;
	};
	vector<Sprite> sprites; //array of all sprites

};


//  General purpose Emitter class for emitting sprites
//  This works similar to a Particle emitter
//
class Emitter : public BaseObject {
public:
	ofVec2f pos = ofVec2f(50, 50);
	Emitter(SpriteSystem s) {
		//Emitter holds a SpriteSystem
		sys = s;
		width = 20;
		height = 20;
	};
	void draw() {
		//draws the Emitter
		ofSetColor(ofColor::red);
		ofDrawRectangle(pos, width, height);
	};
	void start() {
		Sprite * sprite = new Sprite();
		sprite->setPosition(pos);
		sys.add(*sprite);
	}; //create sprites depending on the rate
	void stop() {
	
	};
	void setLifespan(float);
	void setVelocity(ofVec3f);
	void setChildImage(ofImage); //refers to sprites that come out of the emitter
	void setImage(ofImage);
	void setRate(float);
	void update() {
		//cout << ofGetElapsedTimeMillis() << endl;
	//only updates if started, otherwise return nothing
	//if started n called, checked ellapsedTime & firing them based off of rate
		//creates new sprite & gives it image, velocity, lifespan; can put all in constructor parameters, or use set methods
	};
	void translate(int x, int y) {
		pos.x = x;
		pos.y = y;
	}
	SpriteSystem sys;	//manager of sprites
	float rate;	//rate of firing sprites
	ofVec3f velocity;
	float lifespan; //life span of sprites
	bool started;
	float lastSpawned;
	ofImage childImage; //sprite image
	ofImage image;	//emitter image
	bool drawable; //visibility flag; don't draw if false
	bool haveChildImage;
	bool haveImage;
	float width, height; //size of emitter, set in constructor
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		//SpriteSystem sys; 
		Emitter emitter = Emitter(SpriteSystem());
		//Sprite sprite;
};
