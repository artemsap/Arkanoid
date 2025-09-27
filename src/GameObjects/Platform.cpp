#include "Platform.h"
#include <limits>

Platform::Platform(const Drawable::Config& config, float speed_) :
	BaseDrawable(config),
	default_speed(speed_)
{}

void Platform::Act(float dt)
{
	move(dt);
	checkWallCollision();
}

const glm::vec2& Platform::GetVelocity() const
{
	return velocity;
}

void Platform::move(float dt)
{
	float current_speed = default_speed;

	if (is_key_pressed(VK_SPACE))
	{
		current_speed *= shift_speed_multiplier;
	}

	if (is_key_pressed(VK_LEFT))
	{
		velocity = glm::vec2{ -1, 0 } * current_speed;
		position += velocity * dt;
	}
	else if (is_key_pressed(VK_RIGHT))
	{
		velocity = glm::vec2{ 1, 0 } * current_speed;
		position += velocity * dt;
	}
	else
	{
		velocity = glm::vec2{ 0, 0 };
	}
}

void Platform::checkWallCollision()
{
	if (position.x + size.x > SCREEN_WIDTH)
	{
		position.x = SCREEN_WIDTH - size.x;
	}
	if (position.x < 0)
	{
		position.x = 0;
	}
}
