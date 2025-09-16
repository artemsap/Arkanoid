#include "Ball.h"
#include <limits>

Ball::Ball(float size_, 
		   float speed_, 
		   Platform* platform_,
		   Wall* wallLeft_,
		   Wall* wallRight_,
		   Wall* wallUp_,
		   Wall* wallDown_):
	size(size_, size_),
	speed(speed_), 
	platform(platform_),
	wallLeft(wallLeft_),
	wallRight(wallRight_),
	wallUp(wallUp_),
	wallDown(wallDown_)
{
	position = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	direction = glm::normalize(glm::vec2(1, 1));
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
	auto delta = direction * speed * dt;
	position += delta;

	//chect платформа тут , с учетом скорости платформы изменить направление мяча
	if (Utils::checkAABBIntersection(position, glm::vec2(size, size), platform->GetPosition(), platform->GetSize()))
	{
		color = Utils::rgb_to_uint32(0, 255, 0);

		//glm::vec2 ballCenter = position + size * 0.5f;
		//glm::vec2 paddleCenter = platform->GetPosition() + platform->GetSize() * 0.5f;

		direction = { direction.x, -direction.y };
		//direction += platform->GetDirection() * platform->GetSpeed();
	}
	else
	{
		color = Utils::rgb_to_uint32(255, 0, 0);
	}

	//проверить пересечение с кирпичом, если пересеклись, то отскакиваем и ломаем кирпич (меняем направление, будто бы луч от зеркала)

	//проверка пересечения со стеной (меняем направление, будто бы луч от зеркала)
	if (Utils::checkAABBIntersection(position, glm::vec2(size, size), wallLeft->GetPosition(), wallLeft->GetSize()))
	{
		direction = { -direction.x, direction.y };
	} 	
	else if (Utils::checkAABBIntersection(position, glm::vec2(size, size), wallRight->GetPosition(), wallRight->GetSize()))
	{
		direction = { -direction.x, direction.y };
	}

	if (Utils::checkAABBIntersection(position, glm::vec2(size, size), wallUp->GetPosition(), wallUp->GetSize()))
	{
		direction = { direction.x, -direction.y };
	}
	else if (Utils::checkAABBIntersection(position, glm::vec2(size, size), wallDown->GetPosition(), wallDown->GetSize()))
	{
		direction = { direction.x, -direction.y }; //DEAD HERE
	}
}
