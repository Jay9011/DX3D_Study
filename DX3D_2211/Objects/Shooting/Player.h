#pragma once

class Player
{
public:
	Player();
	~Player();

	void Update();
	void PostRender();

	void SetTerrain(Terrain* terrain) { this->terrain = terrain; }

private:
	void MoveControl();

private:
	float moveSpeed = 50.f;
	float rotSpeed = 10.f;
	float height = 3.f;

	Quad* crosshair;
	Terrain* terrain;
};