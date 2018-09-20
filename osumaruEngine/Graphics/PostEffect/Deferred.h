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
	Deferred();

	void Init();

	void Draw();

	void Start();

	void End();
	
private:
	static const int						RENDER_TARGET_NUM = 4;
	CRenderTarget							m_renderTarget[RENDER_TARGET_NUM];
	CTexture								m_renderTargetTexture[RENDER_TARGET_NUM];
	CTexture								m_depthStencilTextures[RENDER_TARGET_NUM];
	CPrimitive								m_primitive;
	CShader									m_vertexShader;		//���_�V�F�[�_�[
	CShader									m_pixelShader;		//�s�N�Z���V�F�[�_�[
	CConstantBuffer							m_lightCB;
};