#pragma once

#include<memory>
#include<unordered_map>

#include "Interfaces/Drawable.h"
#include "Interfaces/Actable.h"

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

	void InitLevel();
	bool IsEnd() const;

	virtual void Draw() const override;
	virtual void Act(float dt) override;

	const Platform& GetPlatform() const;
	const std::unordered_map<Wall::Orientation, Wall>& GetWalls() const;
	std::vector<Brick>& GetBricks();

private:
	Level();

	Platform platform;

	int wallThinkness = 20;
	std::unordered_map<Wall::Orientation, Wall> walls;

	glm::vec2 brickSize{ 100, 70 };
	std::vector<Brick> bricks;

	Ball ball;
};
