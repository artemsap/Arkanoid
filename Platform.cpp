#include "Platform.h"
#include <limits>

Platform::Platform(const glm::vec2& size_, float speed_, const glm::vec2& position_) :
	size(size_),
	default_speed(speed_), 
	position(position_), 
	shift_speed(default_speed * speed_multiplier), 
	current_speed(default_speed)
{}

void Platform::Draw()
{
	for (size_t i = 0; i < size.y; i++)
	{
		for (size_t j = 0; j < size.x; j++)
		{
			buffer[static_cast<size_t>(position.y) + j][static_cast<size_t>(position.x) + i] = std::numeric_limits<uint32_t>::max();
		}
	}
}

void Platform::Act(float dt)
{
	if (is_key_pressed(VK_LEFT))
	{
		direction = glm::vec2{ -1, 0 };
		position += direction * current_speed * dt;
	}
	else if (is_key_pressed(VK_RIGHT))
	{
		direction = glm::vec2{ 1, 0 };
		position += direction * current_speed * dt;
	}
	else
	{
		direction = glm::vec2{ 0, 0 };
	}
	if (is_key_pressed(VK_SPACE))
	{
		current_speed = shift_speed;
	}
	else
	{
		current_speed = default_speed;
	}
}

const glm::vec2& Platform::GetPosition() const
{
	return position;
}

glm::vec2 Platform::GetSize() const
{
	return { size.y, size.x }; // разобраться
}

const glm::vec2& Platform::GetDirection() const
{
	return direction;
}

const float Platform::GetSpeed() const
{
	return current_speed;
}
