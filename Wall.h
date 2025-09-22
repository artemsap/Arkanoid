#pragma once

#include "BaseDrawable.h"
#include "Utils.h"

#include <glm.hpp>

class Wall : public BaseDrawable
{
public:
	Wall(const glm::vec2& size_, glm::vec2 position_, uint32_t color_ = Utils::rgb_to_uint32(120, 120, 120));
};

