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
	Platform platform{ {100, 10}, 100, {SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT * 0.8f} };

	int wallThinkness = 20;
	Wall wallLeft{ {SCREEN_HEIGHT, wallThinkness}, {0, 0} };
	Wall wallRight{ {SCREEN_HEIGHT, wallThinkness}, {SCREEN_WIDTH - wallThinkness, 0} };
	Wall wallUp{ {wallThinkness, SCREEN_WIDTH}, {0,0} };
	Wall wallDown{ {wallThinkness, SCREEN_WIDTH}, {0,SCREEN_HEIGHT - wallThinkness} };

	std::vector<Brick> bricks;

	Ball ball{ 50.0f, {0, 100}, &platform, &wallLeft, &wallRight, &wallUp, &wallDown, &bricks };
};

