#ifndef AGENTS_H
#define AGENTS_H

#include "Vehicle.h"
#include "SteeringBehaviors.h"


class Follower : public Vehicle
{
private :



public :

	Follower::Follower(GameWorld* world, Vector2D position, double mass, double max_force, double max_speed, double max_turn_rate, double scale);

};


class Leader : public Vehicle
{

};

#endif