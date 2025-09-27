#pragma once

#include "BaseDrawable.h"
#include "../Utils/Utils.h"

#include <vector>
#include <glm.hpp>

class Brick : public BaseDrawable
{
public:
	Brick(const Drawable::Config& config) : BaseDrawable(config)
	{
	}

	static const uint32_t defaultColor = Utils::rgb_to_uint32(255, 255, 255);

	// TODO, remake bricks generator
	static std::vector<Brick> GenerateBricks(const glm::vec2& brickSize, const glm::vec2& startDraw, const glm::vec2& endDraw)
	{
		auto getBrickPosition = [&startDraw, &brickSize](size_t i, size_t j, const glm::vec2& distance)
		{
			return startDraw + glm::vec2(i * (brickSize.x + distance.x), j * (brickSize.y + distance.y));
		};

		size_t bricksX = static_cast<size_t>((endDraw.x - startDraw.x) / brickSize.x);
		size_t bricksY = static_cast<size_t>((endDraw.y - startDraw.y) / brickSize.y);

		auto lastBrickCoord = getBrickPosition(bricksX - 1, bricksY - 1, { 0, 0 }) + brickSize;

		glm::vec2 distanceBetweenBricks = { endDraw - lastBrickCoord };
		distanceBetweenBricks.x /= bricksX;
		distanceBetweenBricks.y /= bricksY;

		std::vector<Brick> bricks;
		bricks.reserve(bricksX * bricksY);

		for (size_t i = 0; i < bricksX; i++)
		{
			for (size_t j = 0; j < bricksY; j++)
			{
				glm::vec2 brickPosition = getBrickPosition(i, j, distanceBetweenBricks);
				bricks.emplace_back(Brick(Drawable::Config{ brickSize, brickPosition, Brick::defaultColor }));
			}
		}

		return bricks;
	}
};
