#pragma once

#include "Drawable.h"
#include "Engine.h"
#include <glm.hpp>
#include <algorithm>

class BaseDrawable : public Drawable
{
public:
	BaseDrawable(const glm::vec2& size_, const glm::vec2& position_, uint32_t color_)
		: size(size_), position(position_), color(color_)
	{}

	void Draw() override
	{
		for (size_t i = 0; i < size.y; i++)
		{
			auto ptr = buffer[static_cast<size_t>(position.y) + i] + static_cast<size_t>(position.x);
			std::fill(ptr, ptr + (int)size.x, color);
		}
	}

	const glm::vec2& GetPosition() const
	{
		return position;
	}

	glm::vec2 GetSize() const
	{
		return size;
	}

protected:
	glm::vec2 size;
	glm::vec2 position;
	uint32_t color;
};
