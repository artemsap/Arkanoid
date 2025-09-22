#include "Brick.h"
#include <algorithm>

Brick::Brick(const glm::vec2& size_, const glm::vec2& position_, uint32_t color_) : BaseDrawable(size_, position_, color_)
{}

glm::vec2 Brick::GetVelocity() const
{
	return { 0,0 };
}
