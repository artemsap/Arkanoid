#pragma once

#include "Drawable.h"
#include "Utils.h"

#include <glm.hpp>

class Wall : public Drawable
{
public:
	Wall(const glm::vec2& size_, glm::vec2 position_);

	virtual void Draw() override;

	const glm::vec2& GetPosition() const;
	glm::vec2 GetSize() const;
private:
	glm::vec2 size;
	glm::vec2 position;
	uint32_t color = Utils::rgb_to_uint32(120, 120, 120);
};

