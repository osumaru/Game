#pragma once

class CWeaponTraceDraw
{
public:

	void Init();

	void Add(const CVector3& swordRootPosition, const CVector3& swordPointPosition);

	void Start(const CVector3& swordRootPosition, const CVector3& swordPointPosition);

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
	static const int				VERTEX_STRIDE_NUM = 4;
	static const int				INDEX_STRIDE_NUM = 6;
	static const int				POLIGON_NUM = 12;
	DWORD							m_indexBuffer[INDEX_STRIDE_NUM * POLIGON_NUM];
	SVSLayout						m_vertexBuffer[VERTEX_STRIDE_NUM * POLIGON_NUM];
	CTexture*						m_pTexture;			//�e�N�X�`��
	CShader							m_vertexShader;		//���_�V�F�[�_�[
	CShader							m_pixelShader;		//�s�N�Z���V�F�[�_�[
	CPrimitive						m_primitive;		//�v���~�e�B�u
	CConstantBuffer					m_cb;
	CMatrix							m_viewProj;

};