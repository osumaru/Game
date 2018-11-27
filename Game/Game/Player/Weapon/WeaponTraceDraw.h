#pragma once

class CWeaponTraceDraw
{
public:

	void Init();

	void Add(const CVector3& swordRootPosition, const CVector3& swordPointPosition);

	void Start();

	void Draw();

private:
	//���_���C�A�E�g
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	}; 
	CVector4						m_rootPos;
	CVector4						m_pointPos;
	DWORD							m_indexCount = 0;
	int								m_vertexCount = 0;;
	static const int				INDEX_BUFFER_NUM = 1500;
	static const int				VERTEX_BUFFER_NUM = 1000;
	DWORD							m_indexBuffer[INDEX_BUFFER_NUM];
	SVSLayout						m_vertexBuffer[VERTEX_BUFFER_NUM];
	CTexture*						m_pTexture;			//�e�N�X�`��
	CShader							m_vertexShader;		//���_�V�F�[�_�[
	CShader							m_pixelShader;		//�s�N�Z���V�F�[�_�[
	CPrimitive						m_primitive;		//�v���~�e�B�u
	CConstantBuffer					m_cb;
	CMatrix							m_viewProj;

};