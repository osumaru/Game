#pragma once
//�g���C����`�悷��N���X

class CWeaponTraceDraw
{
public:

	//������
	void Init();

	/*
	�g���C����`�悷���o�^
	swordRootPosition	���{�̍��W
	swordPointPosition	�������̍��W
	*/
	void Add(const CVector3& swordRootPosition, const CVector3& swordPointPosition);
	
	/*
	�g���C�����n�߂�n�_��o�^
	swordRootPosition	���{�̍��W
	swordPointPosition	�������̍��W
	*/
	void Start(const CVector3& swordRootPosition, const CVector3& swordPointPosition);

	//�`��
	void Draw();

private:
	//���_���C�A�E�g
	struct SVSLayout
	{
		CVector4 position;	//���W
		CVector2	uv;		//UV
		float alpha;		//�����x
	}; 

	CVector4						m_rootPos;				//���̍��{�̍��W
	CVector4						m_pointPos;				//���̐������̍��W
	static const int				VERTEX_STRIDE_NUM = 4;	//�|���ꖇ�̒��_�̐�
	static const int				INDEX_STRIDE_NUM = 6;	//�|���ꖇ�̃C���f�b�N�X�o�b�t�@�̐�
	static const int				POLIGON_NUM = 5;		//�|���̐�
	DWORD							m_indexBuffer[INDEX_STRIDE_NUM * POLIGON_NUM];
	SVSLayout						m_vertexBuffer[VERTEX_STRIDE_NUM * POLIGON_NUM];
	CTexture*						m_pTexture;			//�e�N�X�`��
	CShader							m_vertexShader;		//���_�V�F�[�_�[
	CShader							m_pixelShader;		//�s�N�Z���V�F�[�_�[
	CPrimitive						m_primitive;		//�v���~�e�B�u
	CConstantBuffer					m_cb;				//�萔�o�b�t�@
	CMatrix							m_viewProj;			//�r���[�v���W�F�N�V�����s��

};