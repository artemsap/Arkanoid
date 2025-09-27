#include "Level.h"

std::shared_ptr<Level> Level::Get()
{
	static std::shared_ptr<Level> level(new Level);
	return level;
}

Level::Level()
{
	size_t width = 10, height = 5;
	bricks.reserve(width * height);

	glm::vec2 brickSize{ 80, 50 };

	for (size_t i = 0; i < width; i++)
	{
		for (size_t j = 0; j < height; j++)
		{
			bricks.emplace_back(brickSize, glm::vec2(2 * wallThinkness + i * (brickSize.x + 10), 2 * wallThinkness + j * (brickSize.y + 10)), Brick::defaultColor);
		}
	}
}

void Level::Draw() const
{
	ball.Draw();
	platform.Draw();
	for (const auto& wall : walls)
	{
		wall.second.Draw();
	}
	for (auto& brick : bricks)
	{
		brick.Draw();
	}
}

void Level::Act(float dt)
{
	ball.Act(dt);
	platform.Act(dt);

	if (ball.IsEnd())
	{
		schedule_quit_game();
	}
}

const Platform& Level::GetPlatform() const
{
	return platform;
}

const Wall& Level::GetWall(Wall::Orientation orient) const
{
	return walls.at(orient);
}

std::vector<Brick>& Level::GetBricks()
{
	return bricks;
}
