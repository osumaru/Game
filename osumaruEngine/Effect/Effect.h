#pragma once
//エフェクトクラス

class CEffect
{
public:
	/*
	初期化関数
	filePath	ファイルのパス
	*/
	void Init(wchar_t* filepath);

	//再生関数
	void Play();

	//更新
	void Update();

	Effekseer::Effect* GetBody()
	{
		return m_effect;
	}

	//座標を取得
	const CVector3& GetPosition() const
	{
		return m_position;
	}

	//座標を設定
	void SetPosition(const CVector3& position)
	{
		m_position = position;
	}

	//回転を取得
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}

	//回転を設定
	void SetRotation(const CQuaternion& rotation)
	{
		m_rotation = rotation;
	}

	//拡大率を設定
	void SetScale(const CVector3& scale)
	{
		m_scale = scale;
	}

private:
	CVector3				m_scale = CVector3::One;
	CVector3				m_position = CVector3::Zero;		//座標
	CQuaternion				m_rotation = CQuaternion::Identity;	//回転
	Effekseer::Effect*		m_effect = nullptr;					//エフェクト
	Effekseer::Handle		m_handle = -1;						//エフェクトを識別するための番号
};