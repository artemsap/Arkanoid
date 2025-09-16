#pragma once

#include "Drawable.h"
#include "Actable.h"
#include "Utils.h"
#include "Platform.h"
#include "Wall.h"

#include <glm.hpp>

class Ball : public Drawable, public Actable
{
public:
	Ball(float size_,
		 float speed_, 
		 Platform* platform_, 
		 Wall* wallLeft_,
		 Wall* wallRight_,
		 Wall* wallUp_,
		 Wall* wallDown_);

	virtual void Draw() override;
	virtual void Act(float dt) override;

private:
	const glm::vec2 size;
	const float speed;
	glm::vec2 position;
	glm::vec2 direction;
	Platform* platform;			 
	Wall* wallLeft;
	Wall* wallRight;
	Wall* wallUp;
	Wall* wallDown;
	uint32_t color = Utils::rgb_to_uint32(255, 0, 0);
};

