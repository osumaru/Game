#include "AttackWave.h"
#include "../../Player/Player.h"
#include "Maw.h"

void CAttackWave::Init(const CCamera* camera, const CVector3& position)
{
	//シェーダーをロード
	m_vs.Load("Assets/shader/particle.fx", "VSMain", CShader::enVS);
	m_ps.Load("Assets/shader/particle.fx", "PSMain", CShader::enPS);
	//カメラを設定
	m_camera = camera;
	//テクスチャを設定
	m_texture = TextureResource().LoadTexture(L"Assets/sprite/aButton.png");
	//サイズ
	m_size.x = 1.0f;
	m_size.y = 1.0f;

	//頂点バッファを作成
	SLayout elements[4] =
	{
		{ { -1.0f,	1.0f,	1.0f,	1.0f }, { 0.0f ,	0.0f } },
		{ { 1.0f,	1.0f,	1.0f,	1.0f }, { 1.0f ,	0.0f } },
		{ { 1.0f,	-1.0f,	1.0f,	1.0f }, { 1.0f ,	1.0f } },
		{ { -1.0f,	-1.0f,	1.0f,	1.0f }, { 0.0f ,	1.0f } },
	};

	//インデックスバッファーを作成
	WORD indexElements[4] = { 0, 3, 1, 2 };
	//プリミティブを作成
	m_primitive.Create(elements, sizeof(SLayout), 4, indexElements, 6, CPrimitive::enIndex16, CPrimitive::enTypeTriangleStrip);
	m_cb.Create(sizeof(SConstantBuffer), nullptr);
	//座標を設定
	m_position = position;
	//回転を設定
	m_rotation = CQuaternion::Identity;
	m_rotation.SetRotationDeg(CVector3::AxisX, 90.0f);
	//寿命を設定
	m_lifeTimer = 2.0f;
}

void CAttackWave::Update()
{
	//寿命が残っているか
	if (m_lifeTimer > 0.0f)
	{
		const float WAVE_SPEED = 1.1f;	//波のスピード
		const float	WAVE_WIDTH = 1.0f;	//波の幅
		//サイズを大きくする
		m_size *= WAVE_SPEED;
		//寿命を減らす
		m_lifeTimer -= GameTime().GetDeltaFrameTime();
		//プレイヤーとの当たり判定をとる
		m_waveHitLength *= WAVE_SPEED;
		CVector3 distance = GetPlayer().GetPosition() - m_position;
		float length = distance.Length();
		if (length < m_waveHitLength)
		{
			if (length > m_waveHitLength - WAVE_WIDTH &&
				GetPlayer().GetCharacterController().IsOnGround())
			{
				//プレイヤーに当たった
				GetPlayer().SetDamage(GetMaw().GetSmawStatus().Strength);
				GetPlayer().SetDamageEnemyPos(m_position);
			}
		}
	}
	//寿命がなくなっているか
	if (m_lifeTimer <= 0.0f)
	{
		Delete(this);
	}

	//ワールド行列を作成
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
	//現在の深度設定のバックアップをとる
	EnDepthStencilState backupDepth = Engine().GetCurrentDepthStencilState();
	//深度設定をする
	Engine().SetDepthStencilState(enDepthStencilParticle);
	//コンスタントバッファを更新
	SConstantBuffer constantBuffer;
	constantBuffer.worldViewProj = m_worldMatrix;
	constantBuffer.worldViewProj.Mul(constantBuffer.worldViewProj, m_camera->GetViewMatrix());
	constantBuffer.worldViewProj.Mul(constantBuffer.worldViewProj, m_camera->GetProjectionMatrix());
	constantBuffer.alpha = m_alpha;
	m_cb.Update(&constantBuffer);
	//頂点シェーダーとピクセルシェーダーを設定
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vs.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_ps.GetBody().Get(), nullptr, 0);
	GetDeviceContext()->IASetInputLayout(m_vs.GetInputlayOut().Get());
	//頂点シェーダーとピクセルシェーダーにコンスタントバッファを設定
	GetDeviceContext()->VSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	GetDeviceContext()->PSSetConstantBuffers(0, 1, m_cb.GetBody().GetAddressOf());
	//シェーダーリソースを設定
	ID3D11ShaderResourceView* views[] = { m_texture->GetShaderResource().Get(), Engine().GetShaderResource(enRenderTargetDepth).Get() };
	GetDeviceContext()->PSSetShaderResources(0, 2, views);
	//プリミティブを描画
	m_primitive.Draw(GetDeviceContext());
	//深度設定を元に戻す
	Engine().SetDepthStencilState(backupDepth);
}
