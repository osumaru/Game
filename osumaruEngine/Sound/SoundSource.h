#pragma once
#include "WaveFileOpen.h"
#include "SoundEngine.h"

class CSoundSource : public IGameObject
{
public:
	//コンストラクタ
	CSoundSource();

	//デストラクタ
	~CSoundSource();

	/*
	初期化
	filePath		読み込みたいWaveファイルのパス
	*/
	void Init(char* filePath, bool is3DSound = false);

	//更新
	void Update()override;

	//座標を設定(3Dサウンドの時に使う
	void SetPosition(CVector3 position)
	{
		m_position = position;
	}

	/*
	再生
	isLoop		ループさせるか？trueならループ、falseならループしない
	isBegin		途中から再生開始するときに使うフラグ、trueなら最初から、falseなら前回停止いたところの続きから
	*/
	void Play(bool isLoop, bool isBegin = false);

	//一時停止
	void Stop();

	//ソースボイスを取得
	IXAudio2SourceVoice* GetBody()
	{
		return m_sourceVoice;
	}

	//座標を取得
	CVector3& GetPosition()
	{
		return m_position;
	}

	//ボリュームを設定
	void SetVolume(float volume)
	{
		m_sourceVoice->SetVolume(volume, XAUDIO2_COMMIT_NOW);
	}

	

	int GetInputChannelNum()
	{
		return m_waveFile.GetFormat()->nChannels;
	}

	X3DAUDIO_DSP_SETTINGS* GetDSPSettings()
	{
		return &m_dspSettings;
	}

	FLOAT32* GetEmitterAzimuths()
	{
		return m_emitterAzimuths;
	}

	FLOAT32* GetCoefficients()
	{
		return m_coefficients;
	}

private:
	CVector3				m_position;			//座標
	FLOAT32					m_coefficients[INPUTCHANNELS * OUTPUTCHANNELS];
	FLOAT32					m_emitterAzimuths[INPUTCHANNELS];
	X3DAUDIO_DSP_SETTINGS	m_dspSettings;
	IXAudio2SourceVoice*	m_sourceVoice;		//ソースボイス
	WaveFileOpen			m_waveFile;			//WAVEファイルのデータ
	bool					m_isLoop;			//ループフラグ
	bool					m_isPlaying;		//再生中か？
	bool					m_is3DSound;		//3Dサウンドか？
};