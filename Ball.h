#pragma once

#include "BaseDrawable.h"
#include "Actable.h"
#include "Utils.h"
#include "Platform.h"
#include "Wall.h"
#include "Brick.h"

#include <vector>
#include <glm.hpp>

class Ball : public BaseDrawable, public Actable
{
public:
	Ball(const glm::vec2& size_, const glm::vec2& position_, uint32_t color_, const glm::vec2& velocity);

	virtual void Act(float dt) override;
	bool IsEnd();

	static const uint32_t defaultColor = Utils::rgb_to_uint32(255, 255, 255);
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

	template<typename T>
	bool processCollidingWithObject(T* object)
	{
		if (!Utils::checkAABBIntersection(position, size, object->GetPosition(), object->GetSize()))
		{
			return false;
		}

		auto side = getCollisionSide(object);
		if (side == CollisionSide::RIGHT || side == CollisionSide::LEFT)
		{
			velocity.x = -velocity.x;
			velocity.y += object->GetVelocity().y * 0.3f;

			if (side == CollisionSide::LEFT)
			{
				position.x = object->GetPosition().x - size.x - 0.1f;
			}
			else
			{
				position.x = object->GetPosition().x + object->GetSize().x + 0.1f;
			}
		}
		if (side == CollisionSide::BOTTOM || side == CollisionSide::TOP)
		{
			velocity.y = -velocity.y;
			velocity.x += object->GetVelocity().x * 0.3f;

			if (side == CollisionSide::TOP)
			{
				position.y = object->GetPosition().y - size.y - 0.1f;
			}
			else
			{
				position.y = object->GetPosition().y + object->GetSize().y + 0.1f;
			}
		}

		return true;
	}

	void processCollidingWithBrick(size_t indexBrick);

	glm::vec2 velocity;
	bool end = false;
};
