#pragma once


class DiabloScene : public Scene
{
public:
	DiabloScene();
	~DiabloScene();

	virtual void Update() override;
	virtual void Render() override;
	virtual void PostRender() override;

	void CreateSound();

private :
	void SetFont();

private :
	Character* player;
	vector<Diablo*> diablos;
	//Diablo* diablo;
	Map* map;
	AStar* aStar;
};