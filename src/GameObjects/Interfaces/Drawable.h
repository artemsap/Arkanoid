#pragma once
#include <glm.hpp>

class Drawable
{
public:
	struct Config
	{
		glm::vec2 size;
		glm::vec2 position;
		uint32_t color;
	};

public:
	virtual void Draw() const = 0;
};

