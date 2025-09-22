#pragma once

#include "BaseDrawable.h"
#include "Actable.h"
#include "Utils.h"

#include <glm.hpp>

class Platform : public BaseDrawable, public Actable
{
public:
	Platform(const glm::vec2& size_, float speed_, const glm::vec2& position_);

	virtual void Act(float dt) override;
	const glm::vec2& GetVelocity() const;

private:
	const float speed_multiplier = 3.0f;
	float current_speed;
	const float default_speed;
	const float shift_speed;
	glm::vec2 velocity;
};

