#pragma once
class CWeekPoint :
	public IGameObject
{
public:
	//������
	void Init();
	//�X�V
	void Update() override;
	//�`��
	void Draw() override;

	void PostAfterDraw() override;
private:
	CSprite						m_weekSprite;		//��_�̃X�v���C�g
	CTexture*					m_weekTexture;		//��_�̃e�N�X�`��
};

