#pragma once
#include "../RenderTarget.h"
#include "../Texture.h"
#include "../Primitive.h"
#include "../Shader.h"
#include "../ConstantBuffer.h"

class CCamera;

enum EnRenderTarget
{
	enRenderTargetColor,
	enRenderTargetNormalMap,
	enRenderTargetNormal,
	enRenderTargetTangent,
	enRenderTargetDepth,
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

	void SetViewMatrix(CMatrix& viewMatrix)
	{
		m_viewMatrix = viewMatrix;
	}

	void SetProjectionMatrix(CMatrix& projectionMatrix)
	{
		m_projectionMatrix = projectionMatrix;
	}

	CMatrix& GetViewMatrix()
	{
		return m_viewMatrix;
	}

	CMatrix& GetProjMatrix()
	{
		return m_projectionMatrix;
	}

	void SetConstantBuffer();

	void SetCamera(CCamera* camera);

private:
	CRenderTarget							m_renderTarget[enRenderTargetNum];	//G�o�b�t�@�[
	CPrimitive								m_primitive;						//�v���~�e�B�u
	CShader									m_vertexShader;						//���_�V�F�[�_�[
	CShader									m_pixelShader;						//�s�N�Z���V�F�[�_�[
	CConstantBuffer							m_lightCB;							//���C�g�̒萔�o�b�t�@
	CMatrix									m_viewMatrix;						
	CMatrix									m_projectionMatrix;
	CConstantBuffer							m_shadowCB;
	CConstantBuffer							m_gameCameraCB;
	CCamera*								m_camera = nullptr;
};