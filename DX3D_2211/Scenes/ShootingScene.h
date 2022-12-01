#pragma once

class ShootingScene : public Scene
{
private:
	enum END_TYPE
	{
		GAMEOVER,
		CLEAR
	};

public:
	ShootingScene();
	~ShootingScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

	void PrintTEXT();

private:
	Terrain* terrain;
	Player* player;

	bool isRunning = true;

	vector<Quad*> gameSet;
	END_TYPE endType = GAMEOVER;

	float textXPos = WIN_WIDTH * 0.5f;
	float textYPos = WIN_HEIGHT * 0.95f;
};