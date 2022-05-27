#include "Agents.h"

Follower::Follower(GameWorld* world,
	Vector2D position,
	double mass,
	double max_force,
	double max_speed,
	double max_turn_rate,
	double scale) : Vehicle(world,
		position,                 //initial position
		RandFloat()* TwoPi,        //start rotation
		Vector2D(0, 0),            //velocity
		mass,          //mass
		max_force,     //max force
		max_speed,             //max velocity
		max_turn_rate, //max turn rate
		scale) {
	this->Steering()->FlockingOn();
}


