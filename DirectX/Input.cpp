#include "Input.h"
#include <cassert>

//���C�u�����̃����N
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")

//�V���O���g���p�^�[��
Input* Input::GetInstance()
{
	static Input instance;
	return &instance;
}

// �f�o�C�X�������Ɏ��s�����
BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE ipddi, LPVOID pvRef)
{
	return DIENUM_CONTINUE;
}

void Input::Initialize(WindowApp* winApp)
{
	HRESULT result;

	//DirectInput�̃C���X�^���X����
	result = DirectInput8Create(winApp->getWinInstance(), DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&dinput, nullptr);
	
	//�f�o�C�X�̗�
	result = dinput->EnumDevices(DI8DEVTYPE_JOYSTICK, DeviceFindCallBack,
		&parameter, DIEDFL_ATTACHEDONLY);

	//�L�[�{�[�h�f�o�C�X����
	result = dinput->CreateDevice(GUID_SysKeyboard, &devkeyboard, NULL);
	// �}�E�X�f�o�C�X�̐���	
	result = dinput->CreateDevice(GUID_SysMouse, &devMouse, NULL);
	//�W���C�X�e�b�N�̐���	
	result = dinput->CreateDevice(GUID_Joystick, &devStick, NULL);

	if (!FAILED(result))
	{
		isPad = true;
	}

	//���̓f�[�^�`���̃Z�b�g(�L�[)
	result = devkeyboard->SetDataFormat(&c_dfDIKeyboard);
	//�r�����䃌�x���̃Z�b�g(�L�[)
	result = devkeyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	// ���̓f�[�^�`���̃Z�b�g(�}�E�X)
	result = devMouse->SetDataFormat(&c_dfDIMouse2); // �W���`��
	// �r�����䃌�x���̃Z�b�g(�}�E�X)
	result = devMouse->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	
	//�X�e�B�b�N�����Ă��鎞
	if (isPad)
	{
		// ���̓f�[�^�`���̃Z�b�g(�W���C�X�e�b�N)
		result = devStick->SetDataFormat(&c_dfDIJoystick); // �W���`��

		//�����[�h���Βl���[�h�Ƃ��Đݒ�
		DIPROPDWORD diprop;
		ZeroMemory(&diprop, sizeof(diprop));
		diprop.diph.dwSize = sizeof(diprop);
		diprop.diph.dwHeaderSize = sizeof(diprop.diph);
		diprop.diph.dwHow = DIPH_DEVICE;
		diprop.diph.dwObj = 0;
		diprop.dwData = DIPROPAXISMODE_ABS;	// ��Βl���[�h�̎w��(DIPROPAXISMODE_REL�ɂ����瑊�Βl)

		devStick->SetProperty(DIPROP_AXISMODE, &diprop.diph);

		//�����[�h�̐ݒ�
		DIPROPRANGE diprg;
		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.diph.dwObj = DIJOFS_X;
		diprg.lMin = -1000;
		diprg.lMax = 1000;
		devStick->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y���̒l�͈̔͐ݒ�
		diprg.diph.dwObj = DIJOFS_Y;
		devStick->SetProperty(DIPROP_RANGE, &diprg.diph);
		// RX���̒l�͈̔͐ݒ�
		diprg.diph.dwObj = DIJOFS_RX;
		devStick->SetProperty(DIPROP_RANGE, &diprg.diph);
		// Y���̒l�͈̔͐ݒ�
		diprg.diph.dwObj = DIJOFS_RY;
		devStick->SetProperty(DIPROP_RANGE, &diprg.diph);

		// �r�����䃌�x���̃Z�b�g(�W���C�X�e�b�N)
		result = devStick->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	}
}

bool Input::PushKey(BYTE keyNumber)
{
	// �ُ�Ȉ��������o
	assert(0 <= keyNumber && keyNumber <= 256);

	//�w��L�[�������Ă��Ȃ����true��Ԃ�
	if (key[keyNumber]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	// �ُ�Ȉ��������o
	assert(0 <= keyNumber && keyNumber <= 256);

	//�w��L�[�������Ă��Ȃ����true��Ԃ�
	if (key[keyNumber]&& !keyPre[keyNumber]) {
		return true;
	}
	//�����łȂ����false��Ԃ�
	return false;
}

bool Input::PushMouseLeft()
{
	// 0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[0]) {
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool Input::PushMouseCenter()
{
	// 0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[1]) {
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool Input::PushMouseRight()
{
	// 0�łȂ���Ή����Ă���
	if (mouseState.rgbButtons[2]) {
		return true;
	}

	// �����Ă��Ȃ�
	return false;
}

bool Input::TriggerMouseLeft()
{
	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!mouseStatePre.rgbButtons[0] && mouseState.rgbButtons[0]) {
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}

bool Input::TriggerMouseCenter()
{
	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!mouseStatePre.rgbButtons[1] && mouseState.rgbButtons[1]) {
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}

bool Input::TriggerMouseRight()
{
	// �O��0�ŁA����0�łȂ���΃g���K�[
	if (!mouseStatePre.rgbButtons[2] && mouseState.rgbButtons[2]) {
		return true;
	}

	// �g���K�[�łȂ�
	return false;
}

char Input::LEFT_PadStickX()
{
	char point = 0;

	// �X�e�B�b�N�̕�������
	if (padData.lX <= -500)
	{
		//���ɌX����
		point = -1;
	} else if (padData.lX >= 500)
	{
		//�E�ɌX����
		point = +1;

	}

	return point;
}

char Input::LEFT_PadStickY()
{
	char point = 0;

	if (padData.lY <= -500)
	{
		//��ɌX����
		point = +1;
	} else if (padData.lY >= 500)
	{
		//���ɌX����
		point = -1;
	}

	return point;
}

char Input::RIGHT_PadStickX()
{
	char point = 0;

	// �X�e�B�b�N�̕�������
	if (padData.lRx <= -500)
	{
		//���ɌX����
		point = -1;
	} else if (padData.lRx >= 500)
	{
		//�E�ɌX����
		point = +1;

	}

	return point;
}

char Input::RIGHT_PadStickY()
{
	char point = 0;

	if (padData.lRy <= -500)
	{
		//��ɌX����
		point = +1;
	} else if (padData.lRy >= 500)
	{
		//���ɌX����
		point = -1;
	}

	return point;
}

bool Input::PushPadButtons(BYTE keyNumber)
{
	// �ُ�Ȉ��������o
	assert(0 <= keyNumber && keyNumber <= 31);

	if (keyNumber <= 9) {
		if (padData.rgbButtons[keyNumber] & 0x80)
		{
			return true;
		} 
	}
	else if (keyNumber >= 10 && keyNumber <= 13 && padData.rgdwPOV[0] != 0xFFFFFFFF) {
		const int Angle = 9000;
		const int maxButton = 10;
		if (keyNumber == 10 && padData.rgdwPOV[0] == Angle * (keyNumber - maxButton))
		{
			return true;
		} else if (keyNumber == 11 && padData.rgdwPOV[0] == Angle * (keyNumber - maxButton))
		{
			return true;
		} else if (keyNumber == 12 && padData.rgdwPOV[0] == Angle * (keyNumber - maxButton))
		{
			return true;
		} else if (keyNumber == 13 && padData.rgdwPOV[0] == Angle * (keyNumber - maxButton))
		{
			return true;
		}
	}

	return false;
}

bool Input::TriggerPadButtons(BYTE keyNumber)
{
	// �ُ�Ȉ��������o
	assert(0 <= keyNumber && keyNumber <= 31);

	if (keyNumber <= 9) {
		if (padData.rgbButtons[keyNumber] & 0x80 && !padDataPre.rgbButtons[keyNumber])
		{
			return true;
		}
	} else if (keyNumber >= 10 && keyNumber <= 13) {
		if (padData.rgdwPOV[keyNumber - 10] != 0xFFFFFFFF && !padDataPre.rgdwPOV[keyNumber - 10] != 0xFFFFFFFF)
		{
			return true;
		}
	}

	return false;
}

void Input::Update() {
	HRESULT result;

	//-----------�L�[--------------//
	//�L�[�{�[�h���̎擾�J�n
	result = devkeyboard->Acquire();

	//�O��L�[���͂�ۑ�
	memcpy(keyPre, key, sizeof(key));

	//�S�L�[�̓��͏�Ԃ��擾����
	result = devkeyboard->GetDeviceState(sizeof(key), key);

	//-----------�}�E�X--------------//
	// �}�E�X����J�n
	result = devMouse->Acquire();

	// �O��̓��͂�ۑ�
	mouseStatePre = mouseState;

	// �}�E�X�̓���
	result = devMouse->GetDeviceState(sizeof(mouseState), &mouseState);

	//-----------�X�e�B�b�N--------------//
	if (isPad)
	{
		// �X�e�B�b�N����J�n
		result = devStick->Acquire();

		// �O��̓��͂�ۑ�
		padDataPre = padData;

		// �X�e�B�b�N����
		result = devStick->GetDeviceState(sizeof(padData), &padData);
	}
}
