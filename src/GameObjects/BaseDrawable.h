#pragma once

#include "Interfaces/Drawable.h"
#include "../Engine.h"
#include <glm.hpp>
#include <algorithm>

class BaseDrawable : public Drawable
{
public:
	BaseDrawable(const Drawable::Config& config) : size(config.size), position(config.position), color(config.color)
	{}

	void Draw() const override
	{
		for (int i = 0; i < size.y; i++)
		{
			int index_height = static_cast<int>(position.y) + i;
			if (index_height < 0 || index_height >= SCREEN_HEIGHT)
			{
				continue;
			}

			int start_data = std::clamp(static_cast<int>(position.x), 0, SCREEN_WIDTH);
			int end_data = std::clamp(static_cast<int>(position.x + size.x), 0, SCREEN_WIDTH);

			if (start_data != end_data)
			{
				auto ptr_start = buffer[index_height] + start_data;
				auto ptr_end = buffer[index_height] + end_data;

				std::fill(ptr_start, ptr_end, color);
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
