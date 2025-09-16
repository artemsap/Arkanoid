#pragma once

#include "Drawable.h"
#include "Actable.h"
#include "Utils.h"

#include <glm.hpp>

class Platform : public Drawable, public Actable
{
public:
	Platform(const glm::vec2& size_, float speed_, const glm::vec2& position_);

	virtual void Draw() override;
	virtual void Act(float dt) override;
	const glm::vec2& GetPosition() const;
	glm::vec2 GetSize() const;
	const glm::vec2& GetDirection() const;
	const float GetSpeed() const;

private:
	glm::vec2 size;
	const float speed_multiplier = 5.0f;
	float current_speed;
	const float default_speed;
	const float shift_speed;
	glm::vec2 position;
	glm::vec2 direction;
	uint32_t color = Utils::rgb_to_uint32(0, 255, 0);
};

