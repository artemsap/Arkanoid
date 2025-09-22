#pragma once

#include "StaticObject.h"
#include "Utils.h"

#include <glm.hpp>

class Wall : public StaticObject
{
public:
	Wall(const glm::vec2& size_, glm::vec2 position_, uint32_t color_) : StaticObject(size_, position_, color_)
	{}

	static const uint32_t defaultColor = Utils::rgb_to_uint32(120, 120, 120);
};

