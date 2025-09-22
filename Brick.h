#pragma once

#include "BaseDrawable.h"
#include "Utils.h"

#include <glm.hpp>

class Brick : public BaseDrawable
{
public:
	Brick(const glm::vec2& size_, const glm::vec2& position_, uint32_t color_ = Utils::rgb_to_uint32(255, 255, 255));
	glm::vec2 GetVelocity() const;
};

