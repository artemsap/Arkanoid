#pragma once
#include "Drawable.h"
#include "Utils.h"

#include <glm.hpp>

class Brick : public Drawable
{
public:
	Brick(const glm::vec2& size_, const glm::vec2& position_, uint32_t color_ = Utils::rgb_to_uint32(255, 255, 255));

	virtual void Draw() override;
	const glm::vec2& GetPosition() const;
	glm::vec2 GetSize() const;
	glm::vec2 GetVelocity() const;
private:
	glm::vec2 size;
	glm::vec2 position;
	uint32_t color;
};

