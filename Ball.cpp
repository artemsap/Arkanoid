#include "Ball.h"
#include <limits>

Ball::Ball(float size_, 
		   glm::vec2 velocity_,
		   Platform* platform_,
		   Wall* wallLeft_,
		   Wall* wallRight_,
		   Wall* wallUp_,
		   Wall* wallDown_):
	size(size_, size_),
	platform(platform_),
	wallLeft(wallLeft_),
	wallRight(wallRight_),
	wallUp(wallUp_),
	wallDown(wallDown_)
{
	position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	velocity = velocity_;
}

void Ball::Draw()
{
	for (size_t i = 0; i < size.y; i++)
	{
		for (size_t j = 0; j < size.x; j++)
		{
			buffer[static_cast<size_t>(position.y) + j][static_cast<size_t>(position.x) + i] = color;
		}
	}
}

void Ball::Act(float dt)
{
	auto delta = velocity * dt;
	position += delta;

	//chect платформа тут , с учетом скорости платформы изменить направление мяча
	processCollidingWithPlatform();

	//проверить пересечение с кирпичом, если пересеклись, то отскакиваем и ломаем кирпич (меняем направление, будто бы луч от зеркала)

	//проверка пересечения со стеной (меняем направление, будто бы луч от зеркала)
	if (Utils::checkAABBIntersection(position, size, wallLeft->GetPosition(), wallLeft->GetSize()))
	{
		velocity.x = -velocity.x;
	} 	
	else if (Utils::checkAABBIntersection(position, size, wallRight->GetPosition(), wallRight->GetSize()))
	{
		velocity.x = -velocity.x;
	}

	if (Utils::checkAABBIntersection(position, size, wallUp->GetPosition(), wallUp->GetSize()))
	{
		velocity.y = -velocity.y;
	}
	else if (Utils::checkAABBIntersection(position, size, wallDown->GetPosition(), wallDown->GetSize()))
	{
		velocity.y = -velocity.y; //DEAD HERE
	}
}

void Ball::processCollidingWithPlatform()
{
	if (!Utils::checkAABBIntersection(position, size, platform->GetPosition(), platform->GetSize()))
	{
		return;
	}

	auto side = getCollisionSide(platform);
	if (side == CollisionSide::RIGHT || side == CollisionSide::LEFT)
	{
		velocity.x = -velocity.x;
		velocity.y += platform->GetVelocity().y * 0.3f;

		if (side == CollisionSide::LEFT)
		{
			position.x = platform->GetPosition().x - size.x - 0.1f;
		}
		else
		{
			position.x = platform->GetPosition().x + platform->GetSize().x + 0.1f;
		}
	}
	if (side == CollisionSide::BOTTOM || side == CollisionSide::TOP)
	{
		velocity.y = -velocity.y;
		velocity.x += platform->GetVelocity().x * 0.3f;

		// Корректируем позицию
		if (side == CollisionSide::TOP)
		{
			position.y = platform->GetPosition().y - size.y - 0.1f;
		}
		else
		{
			position.y = platform->GetPosition().y + platform->GetSize().y + 0.1f;
		}
	}
}
