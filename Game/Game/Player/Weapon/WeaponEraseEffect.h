#pragma once
#include "WeaponCommon.h"

class CWeaponEraseEffect : Uncopyable
{
public:
	/*
	������
	skinmodel�@����̃��f���̔z��
	*/
	void Init(const CSkinModel* skinmodel[enWeaponNum]);

	//�`�悷�邩�̃t���O��ݒ�
	void SetIsDraw(bool isDraw)
	{
		m_isDraw = isDraw;
	}

	/*
	���[���h�s����g���ăv���~�e�B�u�̈ʒu���X�V
	mat			���[���h�s��
	weaponNum	����̎��
	*/
	void SetWorldMatrix(const CMatrix& mat, EnPlayerWeapon weaponNum);

	//�`��֐�
	void Draw();

	//Clip����l��ݒ�
	void SetDissolve(float dissolve)
	{
		m_dissolve = dissolve;
	}


	struct SVSLayout
	{
		CVector4 position;//���W
		CVector3 color;	//�J���[
		float dissolve;	//Clip����l
	};
public:
	bool						m_isDraw = true;					//�`��t���O
	std::vector<SVSLayout>		m_vertexBuffer;						//���_�o�b�t�@
	std::vector<unsigned short> m_indexBuffer;						//�C���f�b�N�X�o�b�t�@
	std::vector<CVector3>		m_weaponVertexBuffer[enWeaponNum];	//���했�̒��_�o�b�t�@
	std::vector<unsigned short> m_weaponIndexBuffer[enWeaponNum];	//���했�̒��_�o�b�t�@
	CVector3					m_color;							//�F(x,y,z) = (r,g,b)
	CPrimitive					m_primitive;						//�v���~�e�B�u
	CShader						m_ps;								//�s�N�Z���V�F�[�_�[
	CShader						m_vs;								//���_�V�F�[�_�[
	CConstantBuffer				m_cb;								//�萔�o�b�t�@
	CConstantBuffer				m_alphaCB;							//
	float						m_dissolve = 1.0f;					//�����
};