#ifndef AGENTS_H
#define AGENTS_H

#include "Vehicle.h"
#include "SteeringBehaviors.h"


class Follower : public Vehicle
{
private :
	bool isFollowing;

public :

	Follower(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale);

	void Update(double time_elapsed);
};


class Leader : public Vehicle
{
private :

public :
	Leader(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale);
	
};

#endif