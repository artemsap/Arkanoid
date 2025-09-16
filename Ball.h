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
		 glm::vec2 velocity_,
		 Platform* platform_, 
		 Wall* wallLeft_,
		 Wall* wallRight_,
		 Wall* wallUp_,
		 Wall* wallDown_);

	virtual void Draw() override;
	virtual void Act(float dt) override;

private:
	enum class CollisionSide
	{
		NONE, LEFT, RIGHT, TOP, BOTTOM
	};

	template<typename T>
	CollisionSide getCollisionSide(T* object)
	{
		glm::vec2 objectPosition = object->GetPosition();
		glm::vec2 objectSize = object->GetSize();

		// Вычисляем перекрытия по осям
		float overlapLeft = (position.x + size.x) - objectPosition.x;
		float overlapRight = (objectPosition.x + objectSize.x) - position.x;
		float overlapTop = (position.y + size.y) - objectPosition.y;
		float overlapBottom = (objectPosition.y + objectSize.y) - position.y;

		// Находим минимальное перекрытие
		float minOverlap = glm::min(glm::min(overlapLeft, overlapRight),
									glm::min(overlapTop, overlapBottom));

		if (minOverlap == overlapLeft)
		{
			return CollisionSide::LEFT;
		}
		if (minOverlap == overlapRight)
		{
			return CollisionSide::RIGHT;
		}
		if (minOverlap == overlapTop)
		{
			return CollisionSide::TOP;
		}
		if (minOverlap == overlapBottom)
		{
			return CollisionSide::BOTTOM;
		}

		return CollisionSide::NONE;
	}

	void processCollidingWithPlatform();

	const glm::vec2 size;
	glm::vec2 position;
	glm::vec2 velocity;
	Platform* platform;			 
	Wall* wallLeft;
	Wall* wallRight;
	Wall* wallUp;
	Wall* wallDown;
	uint32_t color = Utils::rgb_to_uint32(255, 0, 0);
};

