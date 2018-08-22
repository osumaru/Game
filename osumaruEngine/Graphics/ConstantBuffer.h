#pragma once
//定数バッファクラス

class ConstantBuffer
{
public:
	//コンストラクタ
	ConstantBuffer();

	//デストラクタ
	~ConstantBuffer();

	/*
	定数バッファを作成
	bufferSize	バッファのストライズ(サイズ)
	initData	初期化用のデータ
	*/
	void Create(int bufferSize, void* initData);

	/*
	リソースの更新
	updateData	更新用のデータ
	*/
	void Update(void* updateData);

	//バッファを取得
	ID3D11Buffer* GetBody()
	{
		return m_buffer;
	}
private:
	ID3D11Buffer*					m_buffer;//バッファ
};

