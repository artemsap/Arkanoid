#pragma once

#include "BaseDrawable.h"
#include "../Utils/Utils.h"

#include <glm.hpp>

class StaticObject : public BaseDrawable
{
public:
	StaticObject(const Drawable::Config& config) : BaseDrawable(config)
	{}

	glm::vec2 GetVelocity() const	 // DELETE
	{
		return { 0,0 };
	}
};
