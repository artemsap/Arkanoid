#pragma once

#include "Drawable.h"
#include "Actable.h"

#include "Ball.h"
#include "Platform.h"
#include "Wall.h"
#include "Brick.h"

class Level : public Drawable, public Actable
{
public:
	void Init();
	virtual void Draw() override;
	virtual void Act(float dt) override;
private:
	Platform platform{ {100, 10}, 100, {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT * 0.8f}, Platform::defaultColor };

	int wallThinkness = 20;
	Wall wallLeft{ {wallThinkness, SCREEN_HEIGHT}, {0, 0}, Wall::defaultColor };
	Wall wallRight{ {wallThinkness, SCREEN_HEIGHT}, {SCREEN_WIDTH - wallThinkness, 0}, Wall::defaultColor };
	Wall wallUp{ {SCREEN_WIDTH, wallThinkness}, {0, 0}, Wall::defaultColor };
	Wall wallDown{ {SCREEN_WIDTH, wallThinkness}, {0, SCREEN_HEIGHT - wallThinkness}, Wall::defaultColor };

	std::vector<Brick> bricks;

	Ball ball{ 50.0f, {0, 100}, &platform, &wallLeft, &wallRight, &wallUp, &wallDown, &bricks };
};

