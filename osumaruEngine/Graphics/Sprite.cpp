#include "engineStdafx.h"
#include "Sprite.h"
#include "../Engine.h"
#include "Texture.h"

Sprite::Sprite() :
	m_pTexture(nullptr),
	m_vertexShader(),
	m_pixelShader(),
	m_primitive(),
	m_alpha(1.0f),
	m_position(0.0f, 0.0f),
	m_size(FRAME_BUFFER_WIDTH, FRAME_BUFFER_HEIGHT)
{

}
Sprite::~Sprite()
{
}


void Sprite::Init(Texture* texture)
{
	m_pTexture = texture;
	m_vertexShader.Load("Assets/shader/sprite.fx", "VSMain", Shader::enVS);
	m_pixelShader.Load("Assets/shader/sprite.fx", "PSMain", Shader::enPS);
	VSLayout vertexBufferLayout[4] = 
	{
		{ { -1.0f,  1.0f, 0.0f, 1.0f } , { 0.0f, 0.0f } },
		{ {  1.0f,  1.0f, 0.0f, 1.0f } , { 1.0f, 0.0f } },
		{ { -1.0f, -1.0f, 0.0f, 1.0f } , { 0.0f, 1.0f } },
		{ {  1.0f, -1.0f, 0.0f, 1.0f } , { 1.0f, 1.0f } },
	};
	DWORD indexBufferLayout[4] = {0, 2, 1, 3};
	SpriteCB cb;
	cb.worldMat = Matrix::Identity;
	cb.alpha = 1.0f;
	m_cb.Create(sizeof(SpriteCB), &cb);
	m_primitive.Create(vertexBufferLayout, sizeof(VSLayout), 4, indexBufferLayout, 4, Primitive::enIndex32, Primitive::enTypeTriangleStrip);

}

void Sprite::Draw()
{
	//座標のスケールを変換
	Vector3 position;
	position.x = m_position.x / (FRAME_BUFFER_WIDTH / 2.0f);
	position.y = m_position.y / (FRAME_BUFFER_HEIGHT / 2.0f);
	position.z = 0.0f;
	//拡大のスケールを変換
	Vector3 size;
	size.x = m_size.x / FRAME_BUFFER_WIDTH;
	size.y = m_size.y / FRAME_BUFFER_HEIGHT;
	size.z = 1.0f;

	//移動行列を作成
	Matrix transform;
	transform.MakeTranslation(position);
	//拡大行列を作成
	Matrix scale;
	scale.MakeScaling(size);
	//ワールド行列を作成
	SpriteCB cb;
	Matrix worldMatrix = Matrix::Identity;
	Quaternion quat = Quaternion::Identity;
	Matrix rot;
	rot.MakeRotationFromQuaternion(quat);
	worldMatrix.Mul(worldMatrix, scale);
	worldMatrix.Mul(worldMatrix, rot);
	worldMatrix.Mul(worldMatrix, transform);
	worldMatrix.Transpose();
	cb.worldMat = worldMatrix;
	cb.alpha = m_alpha;
	m_cb.Update(&cb);
	GetDeviceContext()->VSSetShader((ID3D11VertexShader*)m_vertexShader.GetBody(), nullptr, 0);
	GetDeviceContext()->PSSetShader((ID3D11PixelShader*)m_pixelShader.GetBody(), nullptr, 0);
	ID3D11Buffer* vertexBuffers[] = { m_primitive.GetVertexBuffer() };
	UINT strides[] = { m_primitive.GetVertexStride() };
	UINT offset = 0;
	GetDeviceContext()->IASetVertexBuffers(0, 1, vertexBuffers, strides, &offset);
	GetDeviceContext()->IASetPrimitiveTopology(m_primitive.GetPrimitiveType());
	GetDeviceContext()->IASetIndexBuffer(m_primitive.GetIndexBuffer(), m_primitive.GetIndexFormat(), 0);
	GetDeviceContext()->IASetInputLayout(m_vertexShader.GetInputlayOut());
	ID3D11Buffer* buffer = m_cb.GetBody();
	GetDeviceContext()->VSSetConstantBuffers(0, 1, &buffer);
	ID3D11ShaderResourceView* views[] = {m_pTexture->GetShaderResource()};
	GetDeviceContext()->PSSetShaderResources(0, 1, views);
	GetDeviceContext()->DrawIndexed(m_primitive.GetIndexNum(), 0, 0);
}