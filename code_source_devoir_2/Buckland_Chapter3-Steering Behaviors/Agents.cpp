#include "Agents.h"
#include "SteeringBehaviors.h"
#include "GameWorld.h"

// Constructor of the Followers
Follower::Follower(GameWorld* world, Vector2D position, double rotation, Vector2D velocity, double mass, double max_force, double max_speed, double max_turn_rate, double scale, Vector2D offset, Vehicle* leader)
    : Vehicle(world, position, rotation, velocity, mass, max_force, max_speed, max_turn_rate, scale) {
	this->Steering()->WanderOn();
    this->SetIsFollowed(false);
    this->SetFollowLeader(false);
    m_offset = offset;
    m_leader = leader;
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
        int nb = 0;

        // Scanning all vehicles to seek a free one
        for (unsigned int i = 0; i < vehicles.size(); i++)
        {
            Vehicle* vehicle = vehicles[i];
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
            else if (dist == 0)
                nb = i;
        }

        // Once the nearest free agent is found, we first check if it is near enough
        if (!this->World()->GetHuman() && min < 100)
        {
            // Then we set all the necessary variables in order to activate the pursuit
            target->SetIsFollowed(true);
            this->SetFollowLeader(true);
            this->Steering()->WanderOff();
            this->Steering()->OffsetPursuitOn(target, m_offset);
        }
        else if (this->World()->GetHuman())
        {
            double angle = nb * pi * 2 / (vehicles.size() - 1);
            Vector2D offsetHuman = Vector2D(cos(angle), sin(angle));
            this->Steering()->OffsetPursuitOn(m_leader, offsetHuman);
        }
    }

}

Vector2D Follower::GetForces()
{
    return m_pSteering->Calculate();
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

void Leader::ChangeBehavior(Vector2D* input)
{
    m_input = input;
//    std::string str = "ICI = x : " + std::to_string(m_input.x) + ", y : " + std::to_string(m_input.y) + "\n";
//    OutputDebugString(str.c_str());
    if (this->World()->GetHuman())
    {
        m_vVelocity = Vector2D(0, 0);
    }
}

Vector2D Leader::GetForces()
{
    if (World()->GetHuman())
    {
        return m_dMaxSpeed * (*m_input) * 0.5f;
    }
    else
    {
        return m_pSteering->Calculate();
    }
}