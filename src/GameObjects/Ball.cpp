#include "Ball.h"
#include <limits>
#include "Level.h"

Ball::Ball(const Drawable::Config& config, const glm::vec2& velocity_) : BaseDrawable(config)
{
	velocity = velocity_;
}


void Ball::Act(float dt)
{
	auto delta = velocity * dt;
	position += delta;

	processCollidingWithObject(&(Level::Get()->GetPlatform()));

	auto& bricks = Level::Get()->GetBricks();
	for (auto iter = bricks.begin(); iter != bricks.end();)
	{
		if (processCollidingWithObject(&(*iter)))
		{
			iter = bricks.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	auto wallLeft = Level::Get()->GetWall(Wall::Orientation::LEFT);
	auto wallRight = Level::Get()->GetWall(Wall::Orientation::RIGHT);
	auto wallUp = Level::Get()->GetWall(Wall::Orientation::TOP);
	auto wallDown = Level::Get()->GetWall(Wall::Orientation::BOTTOM);

	if (Utils::checkAABBIntersection(position, size, wallLeft.GetPosition(), wallLeft.GetSize()))
	{
		velocity.x = -velocity.x;
	} 	
	else if (Utils::checkAABBIntersection(position, size, wallRight.GetPosition(), wallRight.GetSize()))
	{
		velocity.x = -velocity.x;
	}

	if (Utils::checkAABBIntersection(position, size, wallUp.GetPosition(), wallUp.GetSize()))
	{
		velocity.y = -velocity.y;
	}
	else if (Utils::checkAABBIntersection(position, size, wallDown.GetPosition(), wallDown.GetSize()))
	{
		end = true;
	}
}

bool Ball::IsEnd()
{
	return end;
}
