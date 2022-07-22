#pragma once

#include "Singleton.h"

#include <dinput.h>
#include <Xinput.h>
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"xinput.lib")

static const int ALL_KEYS = 256;

static const int XINPUT_THUMB_LEFTVERT = 0;
static const int XINPUT_THUMB_LEFTSIDE = 1;
static const int XINPUT_THUMB_RIGHTVERT = 2;
static const int XINPUT_THUMB_RIGHTSIDE = 3;

static const int XINPUT_TRIGGER_LEFT = 0;
static const int XINPUT_TRIGGER_RIGHT = 1;

class Input : public Singleton<Input>
{
public:
	BYTE keys[ALL_KEYS];					//���݂̃t���[���̃L�[���
	BYTE oldkeys[ALL_KEYS];				//�O�̃t���[���̃L�[���
	DIMOUSESTATE mouse;					//���݂̃t���[���̃}�E�X���
	DIMOUSESTATE oldmouse;				//�O�̃t���[���̃}�E�X���
	XINPUT_STATE state;					//���݂̃t���[���̃Q�[���p�b�h���
	XINPUT_STATE oldstate;				//�O�̃t���[���̃Q�[���p�b�h���
	XINPUT_VIBRATION vibration;			//�U���p

	//�X�V����
	void Update(IDirectInputDevice8* devKeyboard, IDirectInputDevice8* devmouse) {
		for (int i = 0; i < ALL_KEYS; ++i) {
			//�O�̃t���[���̃L�[����ۑ�
			oldkeys[i] = keys[i];
		}
		//���݂̃t���[���̃L�[�����擾
		devKeyboard->Acquire();
		devKeyboard->GetDeviceState(sizeof(keys), keys);
		//�O�̃t���[���̃}�E�X����ۑ�
		oldmouse = mouse;
		//���݂̃t���[���̃}�E�X�����擾
		devmouse->Acquire();
		devmouse->GetDeviceState(sizeof(DIMOUSESTATE), &mouse);
		//�O�̃t���[���̃Q�[���p�b�h����ۑ�
		oldstate = state;
		//���݂̃t���[���̃}�E�X�����擾
		ZeroMemory(&state, sizeof(XINPUT_STATE));
		XInputGetState(0, &state);

		//�U�����̎擾
		XInputSetState(0, &vibration);
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

		//�֐����Ă΂�ĂȂ��Ƃ��͐U�����~�܂�悤�ɂ���
		vibration.wLeftMotorSpeed = 0;
		vibration.wRightMotorSpeed = 0;

	}

	bool isKey(int keyIndex) {
		if (keyIndex < 0 || keyIndex > 255)return false;
		return keys[keyIndex];
	}

	bool isKeyTrigger(int keyIndex) {
		if (keyIndex < 0 || keyIndex > 255)return false;
		return keys[keyIndex] && !oldkeys[keyIndex];
	}

	bool isKeyRelease(int keyIndex) {
		if (keyIndex < 0 || keyIndex > 255)return false;
		return !keys[keyIndex] && oldkeys[keyIndex];
	}

	bool isMouse(int mouseIndex) {
		if (mouseIndex < 0 || mouseIndex > 255)return false;
		return mouse.rgbButtons[mouseIndex];
	}

	bool isMouseTrigger(int mouseIndex) {
		if (mouseIndex < 0 || mouseIndex > 255)return false;
		return mouse.rgbButtons[mouseIndex] && !oldmouse.rgbButtons[mouseIndex];
	}

	bool isMouseRelease(int mouseIndex) {
		if (mouseIndex < 0 || mouseIndex > 255)return false;
		return !mouse.rgbButtons[mouseIndex] && oldmouse.rgbButtons[mouseIndex];
	}

	bool isPad(int pad)//�����@�����{�^���̎��
	{

		return state.Gamepad.wButtons & pad;
	}

	//XINPUT_GAMEPAD_DPAD_UP          0x0001		�f�W�^�������{�^����
	//XINPUT_GAMEPAD_DPAD_DOWN        0x0002		�f�W�^�������{�^����
	//XINPUT_GAMEPAD_DPAD_LEFT        0x0004		�f�W�^�������{�^����
	//XINPUT_GAMEPAD_DPAD_RIGHT       0x0008		�f�W�^�������{�^���E
	//XINPUT_GAMEPAD_START            0x0010		START�{�^��
	//XINPUT_GAMEPAD_BACK             0x0020		BACK�{�^��
	//XINPUT_GAMEPAD_LEFT_THUMB       0x0040		LT�{�^��(����̂�)
	//XINPUT_GAMEPAD_RIGHT_THUMB      0x0080		RT�{�^��(����̂�)
	//XINPUT_GAMEPAD_LEFT_SHOULDER    0x0100		LB�{�^��
	//XINPUT_GAMEPAD_RIGHT_SHOULDER   0x0200		RB�{�^��
	//XINPUT_GAMEPAD_A                0x1000		A�{�^��
	//XINPUT_GAMEPAD_B                0x2000		B�{�^��
	//XINPUT_GAMEPAD_X                0x4000		X�{�^��
	//XINPUT_GAMEPAD_Y                0x8000		Y�{�^��



	bool isPadTrigger(int pad)
	{
		return (state.Gamepad.wButtons & pad) && !(oldstate.Gamepad.wButtons & pad);
	}

	bool isPadEnd(int pad)
	{
		return !(state.Gamepad.wButtons & pad) && (oldstate.Gamepad.wButtons & pad);
	}

	//�����@�X����X�e�B�b�N�̍��E�ƌ���
	float isPadThumb(int pad)
	{
		switch (pad)
		{
		case XINPUT_THUMB_LEFTVERT:
			return (float)state.Gamepad.sThumbLY / (32767.0f);
		case XINPUT_THUMB_LEFTSIDE:
			return (float)state.Gamepad.sThumbLX / 32767.0f;
		case XINPUT_THUMB_RIGHTVERT:
			return (float)state.Gamepad.sThumbRY / 32767.0f;
		case XINPUT_THUMB_RIGHTSIDE:
			return (float)state.Gamepad.sThumbRX / 32767.0f;
		default: return 0;
		}
	}

	float isOldPadThumb(int pad)
	{
		switch (pad)
		{
		case XINPUT_THUMB_LEFTVERT:
			return (float)oldstate.Gamepad.sThumbLY / (32767.0f);
		case XINPUT_THUMB_LEFTSIDE:
			return (float)oldstate.Gamepad.sThumbLX / 32767.0f;
		case XINPUT_THUMB_RIGHTVERT:
			return (float)oldstate.Gamepad.sThumbRY / 32767.0f;
		case XINPUT_THUMB_RIGHTSIDE:
			return (float)oldstate.Gamepad.sThumbRX / 32767.0f;
		default: return 0;
		}
	}

	//XINPUT_THUMB_LEFTVERT		���X�e�B�b�N�̏c����
	//XINPUT_THUMB_LEFTSIDE		���X�e�B�b�N�̉�����
	//XINPUT_THUMB_RIGHTVERT	�E�X�e�B�b�N�̏c����
	//XINPUT_THUMB_RIGHTSIDE	�E�X�e�B�b�N�̉�����

	//���g������
	//�������͂��Ă�Ƃ��ړ����������ꍇ
	//�E�ɓ|���Ă�Ƃ����A���ɓ|���Ă�Ƃ����̒l���Ԃ�̂Ŗ߂�l�̐�����if���������΂悢

	//���͂̕��ɂ���Ĉړ��ʂ�ς������ꍇ
	//�֐��̖߂�l���ړ��ʂɂ����A�v���C���[�̍��W�ɑ����΂���
	//�v���C���[�̍��W += �֐��̖߂�l * �ړ���;

	float isPadThumbTrigger(int pad)
	{
		switch (pad)
		{
		case XINPUT_THUMB_LEFTVERT:
			return ((float)state.Gamepad.sThumbLY / 32767) && !((float)oldstate.Gamepad.sThumbLY / 32767);
		case XINPUT_THUMB_LEFTSIDE:
			return ((float)state.Gamepad.sThumbLX / 32767) && !((float)oldstate.Gamepad.sThumbLX / 32767);
		case XINPUT_THUMB_RIGHTVERT:
			return ((float)state.Gamepad.sThumbRY / 32767) && !((float)oldstate.Gamepad.sThumbRY / 32767);
		case XINPUT_THUMB_RIGHTSIDE:
			return ((float)state.Gamepad.sThumbRX / 32767) && !((float)oldstate.Gamepad.sThumbRX / 32767);
		default: return 0;
		}
	}

	float isPadTri(int pad)
	{
		switch (pad)
		{
		case XINPUT_TRIGGER_LEFT:
			return static_cast<float>(state.Gamepad.bLeftTrigger) / 255.0f;
		case XINPUT_TRIGGER_RIGHT:
			return static_cast<float>(state.Gamepad.bRightTrigger) / 255.0f;
		default: return 0;
		}
	}

	//XINPUT_TRIGGER_LEFT		���̃g���K�[
	//XINPUT_TRIGGER_RIGHT		�E�̃g���K�[

	//���g������
	//��{�I��isPadThumb�ƕς��Ȃ�
	//�����Ă�Ƃ����̒l���Ԃ�


	float isPadTriTrigger(int pad)
	{
		switch (pad)
		{
		case XINPUT_TRIGGER_LEFT:
			return ((float)state.Gamepad.bLeftTrigger / 255) && !((float)oldstate.Gamepad.bLeftTrigger / 255);
		case XINPUT_TRIGGER_RIGHT:
			return ((float)state.Gamepad.bRightTrigger / 255) && !((float)oldstate.Gamepad.bRightTrigger / 255);
		default: return 0;
		}
	}

	float isPadTriEnd(int pad)
	{
		switch (pad)
		{
		case XINPUT_TRIGGER_LEFT:
			return !((float)state.Gamepad.bLeftTrigger / 255) && ((float)oldstate.Gamepad.bLeftTrigger / 255);
		case XINPUT_TRIGGER_RIGHT:
			return !((float)state.Gamepad.bRightTrigger / 255) && ((float)oldstate.Gamepad.bRightTrigger / 255);
		default: return 0;
		}
	}

	//�l�w���
	float isPadTriEndDefValue(int pad, float value)
	{
		switch (pad)
		{
		case XINPUT_TRIGGER_LEFT:
			return !((float)state.Gamepad.bLeftTrigger / 255 > value) && ((float)oldstate.Gamepad.bLeftTrigger / 255 > value);
		case XINPUT_TRIGGER_RIGHT:
			return !((float)state.Gamepad.bRightTrigger / 255 > value) && ((float)oldstate.Gamepad.bRightTrigger / 255 > value);
		default: return 0;
		}
	}

	void StartVibration(int LeftMotorRate, int RightMotorRate)
	{
		if (LeftMotorRate < 0 || LeftMotorRate > 100 || RightMotorRate < 0 || RightMotorRate > 100) {
			return;
		}

		vibration.wLeftMotorSpeed = static_cast<WORD>(655.35 * LeftMotorRate);
		vibration.wRightMotorSpeed = static_cast<WORD>(655.35 * RightMotorRate);
		//0�`100�͈̔͂Ŏw��
	}
};

enum InputMouseButton {
	DIM_LEFT,
	DIM_RIGHT,
	DIM_CENTER
};