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
	glm::vec2 platformSize{ 150,15 };
	platform = Platform{ Drawable::Config{platformSize, {SCREEN_WIDTH / 2 - platformSize.x / 2, SCREEN_HEIGHT * 0.8f}, Platform::defaultColor}, 100 };
	
	int wallThinkness = 20;
	walls = 
	{
		{Wall::Orientation::LEFT, Wall{ Drawable::Config{{wallThinkness, SCREEN_HEIGHT}, {0, 0}, Wall::defaultColor}}},
		{Wall::Orientation::RIGHT, Wall{  Drawable::Config{{wallThinkness, SCREEN_HEIGHT}, {SCREEN_WIDTH - wallThinkness, 0}, Wall::defaultColor}}},
		{Wall::Orientation::TOP, Wall{  Drawable::Config{{SCREEN_WIDTH, wallThinkness}, {0, 0}, Wall::defaultColor}}},
		{Wall::Orientation::BOTTOM, Wall{  Drawable::Config{{SCREEN_WIDTH, wallThinkness}, {0, SCREEN_HEIGHT - wallThinkness}, Wall::defaultColor}}}
	};

	bricks = Brick::GenerateBricks({ 100, 70 }, glm::vec2(wallThinkness, wallThinkness), glm::vec2(SCREEN_WIDTH - wallThinkness, SCREEN_HEIGHT / 2));

	float ballSize = 50.0f;
	balls.push_back(Ball{ Drawable::Config{{ballSize, ballSize}, glm::vec2{ SCREEN_WIDTH / 2 - ballSize / 2, SCREEN_HEIGHT / 2 }, Ball::defaultColor}, {0, 100} });
}

bool Level::IsWin() const
{
	return bricks.empty();
}

bool Level::IsLose() const
{
	return balls.empty();
}

void Level::Draw() const
{
	for (const auto& ball : balls)
	{
		ball.Draw();
	}
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
	for (auto iter = balls.begin(); iter != balls.end();)
	{
		(*iter).Act(dt);
		if ((*iter).IsDestroid())
		{
			iter = balls.erase(iter);
		}
		else
		{
			++iter;
		}
	}

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
