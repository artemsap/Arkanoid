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
		for (int i = 0; i < size.y; i++)
		{
			int index_height = static_cast<int>(position.y) + i;
			if (index_height < 0 || index_height >= SCREEN_HEIGHT)
			{
				continue;
			}

			int fill_size = static_cast<int>(size.x);
			if (int coord_right_point = static_cast<size_t>(position.x) + static_cast<int>(size.x); coord_right_point >= SCREEN_WIDTH)
			{
				fill_size -= coord_right_point - SCREEN_WIDTH;
			}

			if (fill_size > 0)
			{
				auto ptr = buffer[index_height] + static_cast<size_t>(position.x);
				std::fill(ptr, ptr + fill_size, color);
			}
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
