#include "Level.h"

std::shared_ptr<Level> Level::Get()
{
	static std::shared_ptr<Level> level(new Level);
	return level;
}

Level::Level()
{
}

void Level::InitLevel()
{
	platform = Platform{ Drawable::Config{{100, 10}, {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT * 0.8f}, Platform::defaultColor}, 100 };
	walls =
	{
		{Wall::Orientation::LEFT, Wall{ Drawable::Config{{wallThinkness, SCREEN_HEIGHT}, {0, 0}, Wall::defaultColor}}},
		{Wall::Orientation::RIGHT, Wall{  Drawable::Config{{wallThinkness, SCREEN_HEIGHT}, {SCREEN_WIDTH - wallThinkness, 0}, Wall::defaultColor}}},
		{Wall::Orientation::TOP, Wall{  Drawable::Config{{SCREEN_WIDTH, wallThinkness}, {0, 0}, Wall::defaultColor}}},
		{Wall::Orientation::BOTTOM, Wall{  Drawable::Config{{SCREEN_WIDTH, wallThinkness}, {0, SCREEN_HEIGHT - wallThinkness}, Wall::defaultColor}}}
	};

	bricks = Brick::GenerateBricks(brickSize, glm::vec2(wallThinkness, wallThinkness), glm::vec2(SCREEN_WIDTH - wallThinkness, SCREEN_HEIGHT / 2));
	ball = Ball{ Drawable::Config{{50.0f, 50.0f}, glm::vec2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, Ball::defaultColor}, {0, 100} };
}

bool Level::IsEnd() const
{
	return ball.IsEnd();
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
}

const Platform& Level::GetPlatform() const
{
	return platform;
}

const std::unordered_map<Wall::Orientation, Wall>& Level::GetWalls() const
{
	return walls;
}

std::vector<Brick>& Level::GetBricks()
{
	return bricks;
}
