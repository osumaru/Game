#pragma once
#include "../RenderTarget.h"
#include "../Texture.h"
#include "../Primitive.h"
#include "../Shader.h"
#include "../ConstantBuffer.h"

class CCamera;

enum EnRenderTarget 
{
	enRenderTargetColor,		//�J���[
	enRenderTargetNormalMap,	//�@���}�b�v
	enRenderTargetNormal,		//�@��
	enRenderTargetTangent,		//�ڃx�N�g��
	enRenderTargetDepth,		//�[�x�l(���̓��[���h���W
	enRenderTargetMaterial,		//�}�e���A�����
	enRenderTargetNum
};

class CDeferred : Uncopyable
{
public:
	//���_���C�A�E�g
	struct SVSLayout
	{
		CVector4 position;
		CVector2	uv;
	};

	//�R���X�g���N�^
	CDeferred();

	//�������֐�
	void Init();

	//�f�B�t�@�[�h�p�̃����_�����O�^�[�Q�b�g�ɐ؂�ւ���
	void Start();

	//�`��֐�
	void Draw();

	/*
	�V�F�[�_�[���\�[�X�r���[���擾
	numRenderTarget	�����_�����O�^�[�Q�b�g�̔ԍ�
	*/
	ID3D11ShaderResourceView* GetShaderResource(EnRenderTarget numRenderTarget)
	{
		return m_renderTarget[numRenderTarget].GetRenderTargetTexture().GetShaderResource();
	}

	/*
	�J�����̃Z�b�^�[
	camera	�Q�[���J����
	*/
	void SetCamera(const CCamera* camera);

private:
	struct SFrameSizeCB
	{
		int frameBufferWidth;
		int frameBufferHeight;
	};
	struct SPointLightCB
	{
		CMatrix viewMat;
		CMatrix projectionMat;
		CMatrix viewMatRotOnry;
		CVector2 screenParam;
	};
	CShader									m_cs;
	CConstantBuffer							m_pointLightCB;
	CRenderTarget							m_renderTarget[enRenderTargetNum];	//G�o�b�t�@�[
	CPrimitive								m_primitive;						//�v���~�e�B�u
	CShader									m_vertexShader;						//���_�V�F�[�_�[
	CShader									m_pixelShader;						//�s�N�Z���V�F�[�_�[
	CConstantBuffer							m_lightCB;							//���C�g�̒萔�o�b�t�@
	CConstantBuffer							m_gameCameraCB;						//�Q�[���J�����̒萔�o�b�t�@
	CConstantBuffer							m_materialCB;						//�}�e���A�����
	CConstantBuffer							m_frameSizeCB;						//�t���[�����
	const CCamera*								m_camera = nullptr;					//�萔�o�b�t�@�̍X�V�Ɏg���Q�[���J����
};