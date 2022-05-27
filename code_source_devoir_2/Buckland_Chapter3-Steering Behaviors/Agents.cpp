#include "Agents.h"
#include "SteeringBehaviors.h"
#include "GameWorld.h"

// Constructor of the Followers
Follower::Follower(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale, Vector2D offset)
    : Vehicle(world, position, rotation, velocity, mass, max_force, max_speed, max_turn_rate, scale) {
	this->Steering()->WanderOn();
    this->SetIsFollowed(false);
    this->SetFollowLeader(false);
    m_offset = offset;
}

// Each agent will wander until it finds another agent to follow. The agents
// will decide to follow the nearest free agent.
void Follower::ChangeBehavior()
{
    // If the agent already follows someone, the program doesn't run
    if (!this->GetFollowLeader())
    {
        std::vector<Vehicle*> vehicles = this->World()->Agents();
        Vehicle* target = vehicles[0];
        double min = 1000;

        // Scanning all vehicles to seek a free one
        for (auto vehicle : vehicles)
        {
            // If the agent isn't free, continue to the next agent
            if (vehicle->GetIsFollowed())
                continue;

            // If the agent isn't linked to the leader, same
            if (!vehicle->GetFollowLeader())
                continue;

            // Else, calculate the distance between the 2 agents, if this distance
            // is too high, we continue to the next agent
            double dist = this->Pos().Distance(vehicle->Pos());
            if (dist > 100)
                continue;

            // We do keep only the nearest agent bye taking the minimum distance
            if (dist > 0 && dist < min)
            {
                min = dist;
                target = vehicle;
            }
        }

        // Once the nearest free agent is found, we first check if it is near enough
        if (min < 100)
        {
            // Then we set all the necessary variables in order to activate the pursuit
            target->SetIsFollowed(true);
            this->SetFollowLeader(true);
            this->Steering()->WanderOff();
            this->Steering()->OffsetPursuitOn(target, m_offset);
        }
    }

}

// Constructor of the Leader
Leader::Leader(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale)
    : Vehicle(world, position, rotation, velocity, mass, max_force, max_speed, max_turn_rate, scale)
{
    this->SetScale(Vector2D(10, 10));
    this->Steering()->WanderOn();
    this->SetMaxSpeed(70);
    this->SetIsFollowed(false);
    this->SetFollowLeader(true);
}