#pragma once
#include "IWeapon.h"
class CPlayerArrow;
//������|�N���X

class CBow : public IWeapon
{
public:

	~CBow();

	void Init()override;

	void Update()override;

	void AfterDraw()override;

	//������֐�
	void ArrowCreate();

	void Release();

	/*
	������X�g����폜����֐�
	it	��̃C�e���[�^�[
	*/
	void ArrowDelete(std::list<CPlayerArrow*>::iterator it);

	//�c�e�����擾
	int GetRemainNum()
	{
		return m_remainNum;
	}

private:
	std::list<CPlayerArrow*>			m_arrowList;							//�|��̃��X�g
	CSprite								m_tag;									//�T�[�N���̃X�v���C�g
	CTexture*							m_texture;								//�T�[�N���̃e�N�X�`��
	bool								m_isZoom;								//�|�p�̎��_�ɐ؂�ւ��邩�̔��������ϐ�
	float								m_timer = 0.0f;					//�^�C�}�[
	float								RECOVERY_TIME = 10.0f;			//�e���񕜂��鎞��
	int									ARROW_LIMIT_NUM = 5;			//�e���̌��E
	int									m_remainNum = ARROW_LIMIT_NUM;	//�c�e��
};