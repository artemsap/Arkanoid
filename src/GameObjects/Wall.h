#pragma once

#include "BaseDrawable.h"
#include "../Utils/Utils.h"

#include <glm.hpp>

class Wall : public BaseDrawable
{
public:
	enum class Orientation
	{
		RIGHT,
		LEFT,
		TOP,
		BOTTOM
	};

public:
	Wall(const Drawable::Config& config) : BaseDrawable(config)
	{}

	static const uint32_t defaultColor = Utils::rgb_to_uint32(120, 120, 120);
};

