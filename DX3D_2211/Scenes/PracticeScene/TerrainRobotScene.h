#pragma once

class TerrainRobotScene : public Scene
{
public:
	TerrainRobotScene();
	~TerrainRobotScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void GUIRender() override;

private:
	Terrain* terrain;
	Robot* robot;
};