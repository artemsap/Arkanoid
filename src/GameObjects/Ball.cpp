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
	auto res = std::partition(bricks.begin(), bricks.end(), [&](const Brick& brick) { return !processCollidingWithStaticObject(&brick); });
	if (res != bricks.end())
	{
		bricks.erase(res, std::end(bricks));
	}

	for (const auto& [orient, object] : level->GetWalls())
	{
		if (processCollidingWithStaticObject(&object) && orient == Wall::Orientation::BOTTOM)
		{
			end = true;
		}
	}
}

bool Ball::IsEnd()
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
		velocity.x = -velocity.x;
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
		velocity.y = -velocity.y;
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

Ball::CollisionSide Ball::getCollisionSide(const BaseDrawable* const object)
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