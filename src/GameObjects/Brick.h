#pragma once

#include "StaticObject.h"
#include "../Utils/Utils.h"

#include <glm.hpp>

class Brick : public StaticObject
{
public:
	Brick(const glm::vec2& size_, const glm::vec2& position_, uint32_t color_) : StaticObject(size_, position_, color_)
	{}

	static const uint32_t defaultColor = Utils::rgb_to_uint32(255, 255, 255);
};
