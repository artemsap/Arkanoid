#pragma once

#include <memory>
#include <unordered_map>

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
	bool IsWin() const;
	bool IsLose() const;

	virtual void Draw() const override;
	virtual void Act(float dt) override;

	const Platform& GetPlatform() const;
	const std::unordered_map<Wall::Orientation, Wall>& GetWalls() const;
	std::vector<Brick>& GetBricks();

private:
	Level();

	Platform platform;

	std::unordered_map<Wall::Orientation, Wall> walls;

	std::vector<Brick> bricks;
	std::vector<Ball> balls;
};
