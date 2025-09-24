#include "Platform.h"
#include <limits>

Platform::Platform(const glm::vec2& size_, float speed_, const glm::vec2& position_, uint32_t color_) :
	BaseDrawable(size_, position_, color_),
	default_speed(speed_), 
	shift_speed(default_speed * speed_multiplier), 
	current_speed(default_speed)
{}

void Platform::Act(float dt)
{
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

	if (is_key_pressed(VK_SPACE))
	{
		current_speed = shift_speed;
	}
	else
	{
		current_speed = default_speed;
	}


	if (position.x + size.x > SCREEN_WIDTH)
	{
 		position.x = SCREEN_WIDTH - size.x;
	}
	if (position.x < 0)
	{
		position.x = 0;
	}
}

const glm::vec2& Platform::GetVelocity() const
{
	return velocity;
}
