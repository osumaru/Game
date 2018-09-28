#pragma once
#include "../RenderTarget.h"
#include "../Texture.h"
#include "../Primitive.h"
#include "../Shader.h"
#include "../ConstantBuffer.h"

class Deferred : Uncopyable
{
public:
	//���_���C�A�E�g
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};
	//�R���X�g���N�^
	Deferred();

	//�������֐�
	void Init();

	//�f�B�t�@�[�h�p�̃����_�����O�^�[�Q�b�g�ɐ؂�ւ���
	void Start();

	//�`��֐�
	void Draw();
	
private:
	static const int						RENDER_TARGET_NUM = 4;				//G�o�b�t�@�[�̐�
	CRenderTarget							m_renderTarget[RENDER_TARGET_NUM];	//G�o�b�t�@�[
	CPrimitive								m_primitive;						//�v���~�e�B�u
	CShader									m_vertexShader;						//���_�V�F�[�_�[
	CShader									m_pixelShader;						//�s�N�Z���V�F�[�_�[
	CConstantBuffer							m_lightCB;							//���C�g�̒萔�o�b�t�@
};