#include "AttackWave.h"
#include "../../Player/Player.h"
#include "Maw.h"

void CAttackWave::Init(const CCamera* camera, const CVector3& position)
{
	//�V�F�[�_�[�����[�h
	m_vs.Load("Assets/shader/particle.fx", "VSMain", CShader::enVS);
	m_ps.Load("Assets/shader/particle.fx", "PSMain", CShader::enPS);
	//�J������ݒ�
	m_camera = camera;
	//�e�N�X�`����ݒ�
	m_texture = TextureResource().LoadTexture(L"Assets/sprite/aButton.png");
	//�T�C�Y
	m_size.x = 1.0f;
	m_size.y = 1.0f;

	//���_�o�b�t�@���쐬
	SLayout elements[4] =
	{
		{ { -1.0f,	1.0f,	1.0f,	1.0f }, { 0.0f ,	0.0f } },
		{ { 1.0f,	1.0f,	1.0f,	1.0f }, { 1.0f ,	0.0f } },
		{ { 1.0f,	-1.0f,	1.0f,	1.0f }, { 1.0f ,	1.0f } },
		{ { -1.0f,	-1.0f,	1.0f,	1.0f }, { 0.0f ,	1.0f } },
	};

	//�C���f�b�N�X�o�b�t�@�[���쐬
	WORD indexElements[4] = { 0, 3, 1, 2 };
	//�v���~�e�B�u���쐬
	m_primitive.Create(elements, sizeof(SLayout), 4, indexElements, 6, CPrimitive::enIndex16, CPrimitive::enTypeTriangleStrip);
	m_cb.Create(sizeof(SConstantBuffer), nullptr);
	//���W��ݒ�
	m_position = position;
	//��]��ݒ�
	m_rotation = CQuaternion::Identity;
	m_rotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	//������ݒ�
	m_lifeTimer = 2.0f;
}

void CAttackWave::Update()
{
	//�������c���Ă��邩
	if (m_lifeTimer > 0.0f)
	{
		const float WAVE_SPEED = 1.1f;	//�g�̃X�s�[�h
		const float	WAVE_WIDTH = 1.0f;	//�g�̕�
		//�T�C�Y��傫������
		m_size *= WAVE_SPEED;
		//���������炷
		m_lifeTimer -= GameTime().GetDeltaFrameTime();
		//�v���C���[�Ƃ̓����蔻����Ƃ�
		m_waveHitLength *= WAVE_SPEED;
		CVector3 distance = GetPlayer().GetPosition() - m_position;
		float length = distance.Length();
		if (length < m_waveHitLength)
		{
			if (length > m_waveHitLength - WAVE_WIDTH &&
				GetPlayer().GetCharacterController().IsOnGround())
			{
				//�v���C���[�ɓ�������
				GetPlayer().SetDamage(GetMaw().GetSmawStatus().Strength);
				GetPlayer().SetDamageEnemyPos(m_position);
			}
		}
	}
	//�������Ȃ��Ȃ��Ă��邩
	if (m_lifeTimer <= 0.0f)
	{
		Delete(this);
	}

	//���[���h�s����쐬
	CMatrix scaleMat;
	scaleMat.MakeScaling({ m_size.x, m_size.y, 0.0f });
	CMatrix rotationMat;
	rotationMat.MakeRotationFromQuaternion(m_rotation);
	CMatrix transMat;
	transMat.MakeTranslation({ m_position.x, m_position.y, m_position.z });
	m_worldMatrix = CMatrix::Identity;
	m_worldMatrix.Mul(m_worldMatrix, scaleMat);
	m_worldMatrix.Mul(m_worldMatrix, rotationMat);
	m_worldMatrix.Mul(m_worldMatrix, transMat);
}

void CAttackWave::AfterDraw()
{
	//���݂̐[�x�ݒ�̃o�b�N�A�b�v���Ƃ�
	EnDepthStencilState backupDepth = Engine().GetCurrentDepthStencilState();
	//�[�x�ݒ������
	Engine().SetDepthStencilState(enDepthStencilParticle);
	//�R���X�^���g�o�b�t�@���X�V
	SConstantBuffer constantBuffer;
	constantBuffer.worldViewProj = m_worldMatrix;
	constantBuffer.worldViewProj.Mul(constantBuffer.worldViewProj, m_camera->GetViewMatrix());
	constantBuffer.worldViewProj.Mul(constantBuffer.worldViewProj, m_camera->GetProjectionMatrix());
	constantBuffer.alpha = m_alpha;
	m_cb.Update(&constantBuffer);
	//���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[��ݒ�
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->IASetInputLayout(m_vs.GetInputlayOut().Get());
	//���_�V�F�[�_�[�ƃs�N�Z���V�F�[�_�[�ɃR���X�^���g�o�b�t�@��ݒ�
	GetDeviceContext()->VSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	GetDeviceContext()->PSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	//�V�F�[�_�[���\�[�X��ݒ�
	ID3D11ShaderResourceView* views[] = { m_texture->GetShaderResource().Get(), Engine().GetShaderResource(enRenderTargetDepth).Get() };
	GetDeviceContext()->PSSetShaderResources(0, 2, views);
	//�v���~�e�B�u��`��
	m_primitive.Draw(GetDeviceContext());
	//�[�x�ݒ�����ɖ߂�
	Engine().SetDepthStencilState(backupDepth);
}
