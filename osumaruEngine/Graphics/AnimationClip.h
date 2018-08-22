#pragma once
class Skelton;
class Keyframe;


/*!
*@brief	アニメーションクリップのヘッダー。
*/
struct AnimClipHeader {
	std::uint32_t numKey;				//!<キーフレームの数。
	std::uint32_t numAnimationEvent;	//!<アニメーションイベントの数。
};
/*!
*@brief	アニメーションイベント
*/
struct AnimationEvent {
	float	invokeTime;					//!<アニメーションイベントが発生する時間(単位:秒)
	std::uint32_t eventNameLength;		//!<イベント名の長さ。
};
/*!
*@brief	キーフレーム。
*/
struct Keyframe {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	Matrix transform;			//!<トランスフォーム。
};
/*!
*@brief	キーフレーム。
*/
struct KeyframeRow {
	std::uint32_t boneIndex;	//!<ボーンインデックス。
	float time;					//!<時間。
	Vector3 transform[4];		//!<トランスフォーム。
};

//アニメーションクリップ(一つのアニメーションを管理するクラス)

class AnimationClip : Uncopyable
{
public:
	/*
	アニメーションを読み込む関数。
	filePath	アニメーションファイルのパス
	*/
	void Load(wchar_t* filePath);


	//更新関数。
	void Update(float deltaTime);

	//ボーンの行列を取得。
	const std::vector<Matrix>& GetLocalMatrix() const
	{
		return m_localMatrix;
	}

	//アニメーションを再生。
	void Play();
	
	//ループフラグを設定。
	void SetIsLoop(bool isLoop)
	{
		m_isLoop = isLoop;
	}

	//ループフラグを取得。
	bool IsLoop() const
	{
		return m_isLoop;
	}

	//再生中かのフラグを取得。
	bool IsPlay() const
	{
		return m_isPlay;
	}

private:
	bool									m_isPlay;					//再生中か？
	bool									m_isLoop;					//ループしてるか？
	std::wstring							m_clipName;					//アニメーションクリップの名前。
	std::vector<std::unique_ptr<Keyframe>>	m_keyframes;				//キーフレーム。
	std::vector<std::vector<Keyframe*>>		m_keyFramePtrListArray;		//ボーン毎のキーフレームのリスト
	std::vector<Keyframe*>*					m_topBoneKeyFrameList;		//一番最初のキーフレーム
	std::vector<Matrix>						m_localMatrix;				//ボーンの行列を保存するためのもの
	float									m_frameTime;				//フレームを進めるためのタイマー
	int										m_currentFrameNo;			//現在のフレームナンバー
};