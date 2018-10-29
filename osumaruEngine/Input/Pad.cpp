#include "engineStdafx.h"
#include "Pad.h"

const int triggerMax = 255;			//トリガーの入力値が0～255なので正規化するときに使う

const float inputDeadZone = 0.2f;	//入力量の誤差の範囲

struct SCorrespondencePad
{
	EnPadButton	padButton;
	DWORD		padCode;
	DWORD		keyCode;
};

const SCorrespondencePad correspondencePad[enButtonNum] =
{
	{ enButtonUp,			XINPUT_GAMEPAD_DPAD_UP,			'W' },
	{ enButtonDown,			XINPUT_GAMEPAD_DPAD_DOWN,		'S' },
	{ enButtonLeft,			XINPUT_GAMEPAD_DPAD_LEFT,		'A' },
	{ enButtonRight,		XINPUT_GAMEPAD_DPAD_RIGHT,		'D' },
	{ enButtonA,			XINPUT_GAMEPAD_A,				'J' },
	{ enButtonB,			XINPUT_GAMEPAD_B,				'K' },
	{ enButtonX,			XINPUT_GAMEPAD_X,				'I' },
	{ enButtonY,			XINPUT_GAMEPAD_Y,				'O' },
	{ enButtonStart,		XINPUT_GAMEPAD_START,			'B' },
	{ enButtonSelect,		XINPUT_GAMEPAD_BACK,			'V' },
	{ enButtonRB,			XINPUT_GAMEPAD_RIGHT_SHOULDER,	'2' },
	{ enButtonRStickPush,	XINPUT_GAMEPAD_RIGHT_THUMB,		'4' },
	{ enButtonLB,			XINPUT_GAMEPAD_LEFT_SHOULDER,	'7' },
	{ enButtonLStickPush,	XINPUT_GAMEPAD_LEFT_THUMB,		'9' },
	{ enButtonLeftTrigger,	-1,								'8' },
	{ enButtonRightTrigger,	-1,								'1' }
	
};
CPad::CPad() :
	m_padNum(0),
	m_rightStickX(0.0f),
	m_rightStickY(0.0f),
	m_leftStickX(0.0f),
	m_leftStickY(0.0f),
	m_rightTrigger(0.0f),
	m_leftTrigger(0.0f),
	m_isPadPress{0},
	m_isPadTrigger{0},
	m_state{}
{
}

CPad::~CPad()
{

}

void CPad::Update()
{
	DWORD result = XInputGetState(m_padNum, &m_state);
	
	if (result == ERROR_SUCCESS)
	{
		for (const SCorrespondencePad& pad : correspondencePad)
		{
			if (pad.padCode == (DWORD)-1)
			{
				continue;
			}
			if (m_state.Gamepad.wButtons & pad.padCode)
			{
				m_isPadTrigger[pad.padButton] = 1 ^ m_isPadPress[pad.padButton];
				m_isPadPress[pad.padButton] = 1;
				
			}
			else
			{
				m_isPadTrigger[pad.padButton] = 0;
				m_isPadPress[pad.padButton] = 0;
				
			}
		}
		float inputNormalize;
		inputNormalize = (float)triggerMax;
		//トリガーの押し込み量を0.0～1.0に正規化
		m_leftTrigger = (float)m_state.Gamepad.bLeftTrigger / inputNormalize;
		m_rightTrigger = (float)m_state.Gamepad.bRightTrigger / inputNormalize;

		if (m_state.Gamepad.bLeftTrigger != 0)
		{
			m_isPadTrigger[enButtonLeftTrigger] =1 ^ m_isPadPress[enButtonLeftTrigger];
			m_isPadPress[enButtonLeftTrigger] = 1;
		}
		else
		{
			m_isPadTrigger[enButtonLeftTrigger] = 0;
			m_isPadPress[enButtonLeftTrigger] = 0;
		}

		if (m_state.Gamepad.bRightTrigger != 0)
		{
			m_isPadTrigger[enButtonRightTrigger] = 1 ^ m_isPadPress[enButtonRightTrigger];
			m_isPadPress[enButtonRightTrigger] = 1;
		}
		else
		{
			m_isPadTrigger[enButtonRightTrigger] = 0;
			m_isPadPress[enButtonRightTrigger] = 0;
		}


		const int stickNum = 4;
		float padInput[stickNum] = 
		{
			m_state.Gamepad.sThumbLX,
			m_state.Gamepad.sThumbLY,
			m_state.Gamepad.sThumbRX,
			m_state.Gamepad.sThumbRY,
		};
		float* padOutput[stickNum] = 
		{
			&m_leftStickX,
			&m_leftStickY,
			&m_rightStickX,
			&m_rightStickY,
		};
		for (int i = 0; i < stickNum; i++)
		{
			if (0 < padInput)
			{
				inputNormalize = SHRT_MAX;
			}
			else
			{
				inputNormalize = -SHRT_MIN;
			}
			//スティックの入力量を-1.0～1.0に正規化
			*padOutput[i] = padInput[i] / inputNormalize;
			//入力量が小さい場合誤差とみなして値を0にする
			if (*padOutput[i] < inputDeadZone && -inputDeadZone < *padOutput[i])
			{
				*padOutput[i] = 0.0f;
			}
		}

	}
	else
	{
		//接続されてない場合キーボードで入力。
		for (const SCorrespondencePad& pad : correspondencePad)
		{
			if (GetAsyncKeyState(pad.keyCode))
			{
				m_isPadTrigger[pad.padButton] = 1 ^ m_isPadPress[pad.padButton];
				m_isPadPress[pad.padButton] = 1;
			}
			else
			{
				m_isPadTrigger[pad.padButton] = 0;
				m_isPadPress[pad.padButton] = 0;
			}
		}
		m_leftStickX = 0.0f;
		m_leftStickY = 0.0f;
		m_rightStickX = 0.0f;
		m_rightStickY = 0.0f;

		if (GetAsyncKeyState(VK_LEFT)) {
			m_rightStickX = -1.0f;
		}
		else if (GetAsyncKeyState(VK_RIGHT)) {
			m_rightStickX = 1.0f;
		}
		if (GetAsyncKeyState(VK_UP)) {
			m_rightStickY = 1.0f;
		}
		else if (GetAsyncKeyState(VK_DOWN)) {
			m_rightStickY = -1.0f;
		}

		if (GetAsyncKeyState('A')) {
			m_leftStickX = -1.0f;
		}
		else if (GetAsyncKeyState('D')) {
			m_leftStickX = 1.0f;
		}
		if (GetAsyncKeyState('W')) {
			m_leftStickY = 1.0f;
		}
		else if (GetAsyncKeyState('S')) {
			m_leftStickY = -1.0f;
		}
	}
}