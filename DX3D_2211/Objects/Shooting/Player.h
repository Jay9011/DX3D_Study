#pragma once

class Player
{
private:
	const float HPBAR_WIDTH = 500.0f;
	const float HPBAR_HEIGHT = 30.0f;

public:
	Player();
	~Player();

	void Update();
	void Render();
	void PostRender();

	void SetTerrain(Terrain* terrain) { this->terrain = terrain; }

	float GetHP() { return curHp; }
	float GetScore() { return score; }

private:
	void MoveControl();
	void FireControl();
	void CollisionTarget();
	void CollisionBullet();

	void SetHpBar();

private:
	float moveSpeed = 50.f;
	float rotSpeed = 10.f;
	float height = 3.f;

	float maxHp = 10.0f;
	float curHp = 10.0f;

	float score = 0.0f;

	Quad* crosshair;
	Terrain* terrain;

	Quad* hpBar;
	FloatValueBuffer* valueBuffer;
	Texture* hpBarBackImg;

	Collider* collider;
};