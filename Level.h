#pragma once

#include<memory>
#include<unordered_map>

#include "Drawable.h"
#include "Actable.h"

#include "Ball.h"
#include "Platform.h"
#include "Wall.h"
#include "Brick.h"

class Level : public Drawable, public Actable
{
public:
	static std::shared_ptr<Level> Get();

	Level(const Level&) = delete;
	Level(Level&&) = delete;
	Level& operator=(const Level&) = delete;
	Level& operator=(Level&&) = delete;

	virtual void Draw() const override;
	virtual void Act(float dt) override;

	const Platform& GetPlatform() const;
	const Wall& GetWall(Wall::Orientation orient) const;
	std::vector<Brick>& GetBricks();

private:
	Level();

	Platform platform{ {100, 10}, {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT * 0.8f}, Platform::defaultColor, 100 };

	int wallThinkness = 20;
	std::unordered_map<Wall::Orientation, Wall> walls =
	{
		{Wall::Orientation::LEFT, Wall{ {wallThinkness, SCREEN_HEIGHT}, {0, 0}, Wall::defaultColor }},
		{Wall::Orientation::RIGHT, Wall{ {wallThinkness, SCREEN_HEIGHT}, {SCREEN_WIDTH - wallThinkness, 0}, Wall::defaultColor}},
		{Wall::Orientation::TOP, Wall{ {SCREEN_WIDTH, wallThinkness}, {0, 0}, Wall::defaultColor} },
		{Wall::Orientation::BOTTOM, Wall{ {SCREEN_WIDTH, wallThinkness}, {0, SCREEN_HEIGHT - wallThinkness}, Wall::defaultColor }}
	};

	std::vector<Brick> bricks;

	Ball ball{ {50.0f, 50.0f}, glm::vec2{ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 }, Ball::defaultColor, {0, 100}};
};

