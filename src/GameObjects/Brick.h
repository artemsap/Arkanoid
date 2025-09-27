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

	static std::vector<Brick> GenerateBricks(const glm::vec2& brickSize, const glm::vec2& startDraw, const glm::vec2& endDraw)
	{
		auto getBrickPosition = [&startDraw, &brickSize](size_t i, size_t j, const glm::vec2& distance)
		{
			return startDraw + glm::vec2(i * brickSize.x + (i + 1) * distance.x, j * brickSize.y + (j + 1) * distance.y);
		};

		// всегда на 1 меньше, чтобы гарантировать, что расстояние между блоками адекватное
		size_t bricksX = static_cast<size_t>((endDraw.x - startDraw.x) / brickSize.x) - 1; 
		size_t bricksY = static_cast<size_t>((endDraw.y - startDraw.y) / brickSize.y);

		auto lastBrickCoord = getBrickPosition(bricksX - 1, bricksY - 1, { 0, 0 }) + brickSize;

		glm::vec2 distanceBetweenBricks = { endDraw - lastBrickCoord };
		distanceBetweenBricks.x /= (bricksX + 1);
		distanceBetweenBricks.y = distanceBetweenBricks.x;

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
