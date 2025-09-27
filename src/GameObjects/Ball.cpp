#include "Ball.h"
#include <limits>
#include "Level.h"

Ball::Ball(const Drawable::Config& config, const glm::vec2& velocity_) : BaseDrawable(config)
{
	velocity = velocity_;
}

void Ball::Act(float dt)
{
	auto delta = velocity * dt;
	position += delta;

	auto level = Level::Get();

	processCollidingWithPlatform(&(level->GetPlatform()));

	auto& bricks = level->GetBricks();
	std::erase_if(bricks, [&](const Brick& brick) { return processCollidingWithStaticObject(&brick); });

	for (const auto& [orient, object] : level->GetWalls())
	{
		if (processCollidingWithStaticObject(&object) && orient == Wall::Orientation::BOTTOM)
		{
			end = true;
		}
	}
}

bool Ball::IsEnd() const
{
	return end;
}

bool Ball::processCollidingWithPlatform(const Platform* const object)
{
	return processCollidingWithObject(object, object->GetVelocity());
}

bool Ball::processCollidingWithStaticObject(const BaseDrawable* const object)
{
	return processCollidingWithObject(object, { 0,0 });
}

bool Ball::processCollidingWithObject(const BaseDrawable* const object, const glm::vec2& objectVelocity)
{
	const auto& objectPosition = object->GetPosition();
	const auto& objectSize = object->GetSize();

	if (!Utils::checkAABBIntersection(position, size, objectPosition, objectSize))
	{
		return false;
	}

	auto side = getCollisionSide(object);
	if (side == CollisionSide::RIGHT || side == CollisionSide::LEFT)
	{
		velocity.x = -velocity.x + objectVelocity.x * 0.3f;
		velocity.y += objectVelocity.y * 0.3f;

		if (side == CollisionSide::LEFT)
		{
			position.x = objectPosition.x - size.x - 0.1f;
		}
		else
		{
			position.x = objectPosition.x + objectSize.x + 0.1f;
		}
	}
	if (side == CollisionSide::BOTTOM || side == CollisionSide::TOP)
	{
		velocity.y = -velocity.y + objectVelocity.y * 0.3f;
		velocity.x += objectVelocity.x * 0.3f;

		if (side == CollisionSide::TOP)
		{
			position.y = objectPosition.y - size.y - 0.1f;
		}
		else
		{
			position.y = objectPosition.y + objectSize.y + 0.1f;
		}
	}

	return true;
}

Ball::CollisionSide Ball::getCollisionSide(const BaseDrawable* const object) const
{
	glm::vec2 objectPosition = object->GetPosition();
	glm::vec2 objectSize = object->GetSize();

	// Вычисляем перекрытия по осям
	float overlapLeft = (position.x + size.x) - objectPosition.x; //distance between right side of ball and left side of object
	float overlapRight = (objectPosition.x + objectSize.x) - position.x; //distance between left side of ball and right side of object
	float overlapTop = (position.y + size.y) - objectPosition.y; //distance between bottom side of ball and top side of object
	float overlapBottom = (objectPosition.y + objectSize.y) - position.y; //distance between top side of ball and bottom side of object

	// Находим минимальное перекрытие
	float minOverlap = std::min({ overlapLeft, overlapRight, overlapTop, overlapBottom });

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