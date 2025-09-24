#pragma once

#include "BaseDrawable.h"
#include "Utils.h"

#include <glm.hpp>

class StaticObject : public BaseDrawable
{
public:
	StaticObject(const glm::vec2& size_, glm::vec2 position_, uint32_t color_) : BaseDrawable(size_, position_, color_)
	{}

	glm::vec2 GetVelocity() const	 // DELETE
	{
		return { 0,0 };
	}
};

