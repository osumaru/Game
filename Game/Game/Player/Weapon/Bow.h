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

	/*
	������X�g����폜����֐�
	it	��̃C�e���[�^�[
	*/
	void ArrowDelete(std::list<CPlayerArrow*>::iterator it);
private:
	std::list<CPlayerArrow*>			m_arrowList;							//�|��̃��X�g
	CSprite								m_tag;									//�T�[�N���̃X�v���C�g
	CTexture							m_texture;								//�T�[�N���̃e�N�X�`��
	bool								m_isZoom;								//�|�p�̎��_�ɐ؂�ւ��邩�̔��������ϐ�

};