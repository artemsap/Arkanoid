#pragma once

#include "BaseDrawable.h"
#include "Interfaces/Actable.h"
#include "../Utils/Utils.h"
#include "Platform.h"
#include "Wall.h"
#include "Brick.h"

#include <vector>
#include <glm.hpp>

class Ball : public BaseDrawable, public Actable
{
public:
	Ball(const Drawable::Config& config, const glm::vec2& velocity);

	virtual void Act(float dt) override;
	bool IsEnd();

	static const uint32_t defaultColor = Utils::rgb_to_uint32(255, 0, 0);
private:
	enum class CollisionSide
	{
		NONE, LEFT, RIGHT, TOP, BOTTOM
	};

	bool processCollidingWithPlatform(const Platform* const object);
	bool processCollidingWithStaticObject(const BaseDrawable* const object);
	bool processCollidingWithObject(const BaseDrawable* const object, const glm::vec2& objectVelocity);
	CollisionSide getCollisionSide(const BaseDrawable* const object);

	glm::vec2 velocity;
	bool end = false;
};
