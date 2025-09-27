#include "Level.h"

std::shared_ptr<Level> Level::Get()
{
	static std::shared_ptr<Level> level(new Level);
	return level;
}

Level::Level()
{
	glm::vec2 brickSize{ 100, 70 };
	bricks = Brick::GenerateBricks(brickSize, glm::vec2(wallThinkness, wallThinkness), glm::vec2(SCREEN_WIDTH - wallThinkness, SCREEN_HEIGHT / 2));
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
