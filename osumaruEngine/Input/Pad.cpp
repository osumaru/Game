#include "engineStdafx.h"
#include "Pad.h"

const int triggerMax = 255;			//�g���K�[�̓��͒l��0�`255�Ȃ̂Ő��K������Ƃ��Ɏg��

const float inputDeadZone = 0.2f;	//���͗ʂ̌덷�͈̔�

struct CorrespondencePad
{
	EnPadButton	padButton;
	DWORD		padCode;
	DWORD		keyCode;
};

const CorrespondencePad correspondencePad[enButtonNum] = 
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
	{ enButtonLStickPush,	XINPUT_GAMEPAD_LEFT_THUMB,		'9' }
};
Pad::Pad() :
	m_padNum(0),
	m_rightStickX(0.0f),
	m_rightStickY(0.0f),
	m_leftStickX(0.0f),
	m_leftStickY(0.0f),
	m_rightTrigger(0.0f),
	m_leftTrigger(0.0f),
	m_isPadPress{},
	m_isPadTrigger{},
	m_state{}
{
}

Pad::~Pad()
{

}

void Pad::Update()
{
	DWORD result = XInputGetState(m_padNum, &m_state);

	if (result == ERROR_SUCCESS)
	{
		for (const CorrespondencePad& pad : correspondencePad)
		{
			if (m_state.Gamepad.wButtons & pad.padCode)
			{
				if (!m_isPadPress[pad.padButton])
				{
					m_isPadTrigger[pad.padButton] = true;
				}
				else
				{
					m_isPadTrigger[pad.padButton] = false;
				}
				m_isPadPress[pad.padButton] = true;
			}
			else
			{
				m_isPadTrigger[pad.padButton] = false;
				m_isPadPress[pad.padButton] = false;
			}
		}
		float inputNormalize;
		inputNormalize = (float)triggerMax;
		//�g���K�[�̉������ݗʂ�0.0�`1.0�ɐ��K��
		m_leftTrigger = (float)m_state.Gamepad.bLeftTrigger / inputNormalize;
		m_rightTrigger = (float)m_state.Gamepad.bRightTrigger / inputNormalize;

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
			//�X�e�B�b�N�̓��͗ʂ�-1.0�`1.0�ɐ��K��
			*padOutput[i] = padInput[i] / inputNormalize;
			//���͗ʂ��������ꍇ�덷�Ƃ݂Ȃ��Ēl��0�ɂ���
			if (*padOutput[i] < inputDeadZone && -inputDeadZone < *padOutput[i])
			{
				*padOutput[i] = 0.0f;
			}
		}

	}
	else
	{
		//�ڑ�����ĂȂ��ꍇ�L�[�{�[�h�œ��́B
		for (const CorrespondencePad& pad : correspondencePad)
		{
			if (GetAsyncKeyState(pad.keyCode))
			{
				if (!m_isPadPress[pad.padButton])
				{
					m_isPadTrigger[pad.padButton] = true;
				}
				else
				{
					m_isPadTrigger[pad.padButton] = false;
				}
				m_isPadPress[pad.padButton] = true;
			}
			else
			{
				m_isPadTrigger[pad.padButton] = false;
				m_isPadPress[pad.padButton] = false;
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