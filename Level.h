#pragma once

#include<memory>

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

	virtual void Draw() override;
	virtual void Act(float dt) override;
private:
	Level();

	Platform platform{ {100, 10}, {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT * 0.8f}, Platform::defaultColor, 100 };

	int wallThinkness = 20;
	Wall wallLeft{ {wallThinkness, SCREEN_HEIGHT}, {0, 0}, Wall::defaultColor };
	Wall wallRight{ {wallThinkness, SCREEN_HEIGHT}, {SCREEN_WIDTH - wallThinkness, 0}, Wall::defaultColor };
	Wall wallUp{ {SCREEN_WIDTH, wallThinkness}, {0, 0}, Wall::defaultColor };
	Wall wallDown{ {SCREEN_WIDTH, wallThinkness}, {0, SCREEN_HEIGHT - wallThinkness}, Wall::defaultColor };

	std::vector<Brick> bricks;

	Ball ball{ 50.0f, {0, 100}, &platform, &wallLeft, &wallRight, &wallUp, &wallDown, &bricks };
};

