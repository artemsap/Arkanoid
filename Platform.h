#pragma once

#include "BaseDrawable.h"
#include "Actable.h"
#include "Utils.h"

#include <glm.hpp>

class Platform : public BaseDrawable, public Actable
{
public:
	Platform(const glm::vec2& size_, float speed_, const glm::vec2& position_, uint32_t color_);

	virtual void Act(float dt) override;
	const glm::vec2& GetVelocity() const;

	static const uint32_t defaultColor = Utils::rgb_to_uint32(0, 255, 0);

private:
	const float speed_multiplier = 3.0f;
	float current_speed;
	const float default_speed;
	const float shift_speed;
	glm::vec2 velocity;
};

