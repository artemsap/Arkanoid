#pragma once

#include "BaseDrawable.h"
#include "Interfaces/Actable.h"
#include "../Utils/Utils.h"

#include <glm.hpp>

class Platform : public BaseDrawable, public Actable
{
public:
	Platform(const Drawable::Config& config, float speed_);

	virtual void Act(float dt) override;
	const glm::vec2& GetVelocity() const;

	static const uint32_t defaultColor = Utils::rgb_to_uint32(0, 255, 0);

private:
	void move(float dt);
	void checkWallCollision();

	const float default_speed;
	const float shift_speed_multiplier = 3.0f;
	glm::vec2 velocity = { 0, 0 };
};
