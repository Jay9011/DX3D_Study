#pragma once

class ShootingScene : public Scene
{
public:
	ShootingScene();
	~ShootingScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;
	virtual void GUIRender() override;

private:
	Terrain* terrain;
	Player* player;


};