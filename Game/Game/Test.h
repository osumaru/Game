#pragma once

class Test : public GameObject
{
public:
	Test()
	{

	}
	void Init();

	void Update()override;

	void Draw()override;
private:
	SkinModel model;
	Sprite sprite;
	Texture texture;
	Matrix	view;
	Matrix	proj;
};