#ifndef AGENTS_H
#define AGENTS_H

#include <vector>

#include "Vehicle.h"
#include "SteeringBehaviors.h"


class Follower : public Vehicle
{
private :
	Vector2D m_offset;
	Vehicle* m_leader;


public :
	Follower(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale, Vector2D offset, Vehicle* leader);
	void ChangeBehavior();
	Vector2D GetForces();
};


class Leader : public Vehicle
{
public :
	Leader(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale);
	void ChangeBehavior(Vector2D* input);
	Vector2D GetForces();
};

#endif