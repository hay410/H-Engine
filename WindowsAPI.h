#pragma once
#include <Windows.h>

// �E�B���h�E�T�C�Y
const int window_width = 1280;  //����
const int window_height = 720;  //�c��

class WindowsAPI {
public:
	WNDCLASSEX windowClass;		//�E�B���h�E�N���X
	RECT wrc;					//�E�B���h�E�T�C�Y
	HWND hwnd;					//�E�B���h�E�I�u�W�F�N�g
	MSG msg;					//���b�Z�[�W
	LPCWSTR windowName = L"Engine";

	//�R���X�g���N�^
	WindowsAPI();
	//����������
	void Init();
};