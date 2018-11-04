
//  Kevin M. Smith - CS 134 SJSU

#include "ParticleEmitter.h"

ParticleEmitter::ParticleEmitter() {
	sys = new ParticleSystem();
	createdSys = true;
	init();

	cout << "particleEmitter created" << endl;
}

ParticleEmitter::ParticleEmitter(ParticleSystem *s) {
	if (s == NULL)
	{
		cout << "fatal error: null particle system passed to ParticleEmitter()" << endl;
		ofExit();
	}
	sys = s;
	createdSys = false;
	init();
}

ParticleEmitter::~ParticleEmitter() {

	// deallocate particle system if emitter created one internally
	//
	if (createdSys) delete sys;
}

void ParticleEmitter::init() {
	rate = 1;
	velocity = ofVec3f(0, 20, 0);
	lifespan = 3;
	mass = 1;
	randomLife = true;
	lifeMinMax = ofVec3f(2, 4);
	started = false;
	oneShot = true;
	fired = false;
	lastSpawned = 0;
	radius = 5;
	particleRadius = 5;
	visible = true;
	type = DiscEmitter;
	groupSize = 15;
	damping = .99;
	particleColor = ofColor::red;
	position = ofVec3f(0, 0, 0);

	//added stuff for project
	sys->addForce(new RadialForce());
}



void ParticleEmitter::draw() {
	if (visible) {
		switch (type) {
		case DirectionalEmitter:
			ofDrawSphere(position, radius/10);  // just draw a small sphere for point emitters 
			break;
		case SphereEmitter:
		case RadialEmitter:
			ofDrawSphere(position, radius/10);  // just draw a small sphere as a placeholder
			break;
		case DiscEmitter:
			ofDrawRectangle(position, 2, 2);
			break;
		default:
			break;
		}
	}
	sys->draw();  
}
void ParticleEmitter::start() {
	if (started) return;
	started = true;
	lastSpawned = ofGetElapsedTimeMillis();
	cout << "particleEmitter started" << endl;
}

void ParticleEmitter::stop() {
	started = false;
	fired = false;
}
void ParticleEmitter::update() {

	float time = ofGetElapsedTimeMillis();

	if (oneShot && started) {
		if (!fired) {

			// spawn a new particle(s)
			//
			for (int i = 0; i < groupSize; i++) {
				spawn(time);
			}

			lastSpawned = time;
		}
		fired = true;
		stop();
	}

	else if (((time - lastSpawned) > (60 / rate)) && started) {
		cout << "shooting" << endl;
		// spawn a new particle(s)
		//
		for (int i= 0; i < groupSize; i++)
			spawn(time);
	
		lastSpawned = time;
	}

	sys->update();
}

// spawn a single particle.  time is current time of birth
//
void ParticleEmitter::spawn(float time) {

	Particle particle;

	// set initial velocity and position
	// based on emitter type
	//
	switch (type) {
		
	case DiscEmitter: {
		ofVec3f direction = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), 0 );
		ofVec3f circleRange = ofVec3f(ofRandom(-15, 15), ofRandom(-15, 15), 0);
		float speed = velocity.length();
		particle.velocity = speed * direction.getNormalized();
		particle.position.set(position);
	}
	
		break;
	case RadialEmitter:
	  {
		ofVec3f dir = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
		float speed = velocity.length();
		particle.velocity = dir.getNormalized() * speed;
		particle.position.set(position);
	  }
	break;
	case SphereEmitter:
		break;
	case DirectionalEmitter:
		particle.velocity = velocity;
		particle.position.set(position);
		break;
	
	}

	// other particle attributes
	//
	if (randomLife) {
		particle.lifespan = ofRandom(lifeMinMax.x, lifeMinMax.y);
	}
	else particle.lifespan = lifespan;
	particle.birthtime = time;
	particle.radius = particleRadius;
	particle.mass = mass;
	particle.damping = damping;
	//particle.color = particleColor;

	// add to system
	//
	sys->add(particle);
}
