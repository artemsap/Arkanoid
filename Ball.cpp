#include "Ball.h"
#include <limits>

Ball::Ball(float size_, 
		   glm::vec2 velocity_,
		   Platform* platform_,
		   Wall* wallLeft_,
		   Wall* wallRight_,
		   Wall* wallUp_,
		   Wall* wallDown_,
		   std::vector<Brick>* bricks_) 
	: BaseDrawable(glm::vec2{ size_, size_ }, glm::vec2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, Utils::rgb_to_uint32(255, 0, 0)),
	platform(platform_),
	wallLeft(wallLeft_),
	wallRight(wallRight_),
	wallUp(wallUp_),
	wallDown(wallDown_),
	bricks(bricks_),
	velocity(velocity_)
{}


void Ball::Act(float dt)
{
	auto delta = velocity * dt;
	position += delta;

	processCollidingWithObject(platform);

	for (size_t i = 0; i < (*bricks).size(); i++)
	{
		processCollidingWithBrick(i);
	}

	if (Utils::checkAABBIntersection(position, size, wallLeft->GetPosition(), wallLeft->GetSize()))
	{
		velocity.x = -velocity.x;
	} 	
	else if (Utils::checkAABBIntersection(position, size, wallRight->GetPosition(), wallRight->GetSize()))
	{
		velocity.x = -velocity.x;
	}

	if (Utils::checkAABBIntersection(position, size, wallUp->GetPosition(), wallUp->GetSize()))
	{
		velocity.y = -velocity.y;
	}
	else if (Utils::checkAABBIntersection(position, size, wallDown->GetPosition(), wallDown->GetSize()))
	{
		end = true;
	}
}

bool Ball::IsEnd()
{
	return end;
}
