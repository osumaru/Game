#pragma once
//定数バッファクラス

class CConstantBuffer
{
public:
	//コンストラクタ
	CConstantBuffer();

	//デストラクタ
	~CConstantBuffer();

	/*
	定数バッファを作成
	bufferSize	バッファのストライズ(サイズ)
	initData	初期化用のデータ
	*/
	void Create(int bufferSize, const void* initData);

	/*
	リソースの更新
	updateData	更新用のデータ
	*/
	void Update(void* updateData);

	//バッファを取得
	Microsoft::WRL::ComPtr<ID3D11Buffer>& GetBody()
	{
		return m_buffer;
	}

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer>				m_buffer;//バッファ
};

