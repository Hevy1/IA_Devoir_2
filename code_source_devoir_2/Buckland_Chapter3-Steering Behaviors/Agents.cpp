#include "Agents.h"
#include "SteeringBehaviors.h"

// Functions related to Follower class
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
	this->Steering()->WanderOn();
    this->Steering()->SetOffset()
}

void Follower::Update(double time_elapsed)
{
    this->Vehicle::Update(time_elapsed);

    if (!isFollowing)
    {
        
        Vehicle* target;

        target->SetIsFollowed(true);
        target->Steering()->SetTargetAgent2(this);
        this->Steering()->SetTargetAgent1(this);
        this->Steering()->OffsetPursuitOn();
    }

}

// Functions related to Leader class
Leader::Leader(GameWorld* world,
    Vector2D position,
    double    rotation,
    Vector2D velocity,
    double    mass,
    double    max_force,
    double    max_speed,
    double    max_turn_rate,
    double    scale) : Vehicle(world,
        position,
        rotation,
        velocity,
        mass,
        max_force,
        max_speed,
        max_turn_rate,
        scale)
{
    this->SetScale(Vector2D(10, 10));
    this->Steering()->WanderOn();
    this->SetMaxSpeed(70);
}