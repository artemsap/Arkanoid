#include "Brick.h"

Brick::Brick(const glm::vec2& size_, const glm::vec2& position_, uint32_t color_) :
	size(size_), position(position_), color(color_)
{}

void Brick::Draw()
{
	for (size_t i = 0; i < size.x; i++)
	{
		for (size_t j = 0; j < size.y; j++)
		{
			buffer[static_cast<size_t>(position.y) + j][static_cast<size_t>(position.x) + i] = color;
		}
	}
}

const glm::vec2& Brick::GetPosition() const
{
	return position;
}

glm::vec2 Brick::GetSize() const
{
	return size;
}

glm::vec2 Brick::GetVelocity() const
{
	return { 0,0 };
}
