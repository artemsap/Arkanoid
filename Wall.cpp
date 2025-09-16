#include "Wall.h"

Wall::Wall(const glm::vec2& size_, glm::vec2 position_, uint32_t color_) : 
	size(size_), position(position_), color(color_)
{}

void Wall::Draw()
{
	for (size_t i = 0; i < size.y; i++)
	{
		for (size_t j = 0; j < size.x; j++)
		{
			buffer[static_cast<size_t>(position.y) + j][static_cast<size_t>(position.x) + i] = color;
		}
	}
}

const glm::vec2& Wall::GetPosition() const
{
	return position;
}

glm::vec2 Wall::GetSize() const
{
	return { size.y, size.x }; // разобраться
}
