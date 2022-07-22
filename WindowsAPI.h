#pragma once
#include <Windows.h>

// ウィンドウサイズ
const int window_width = 1280;  //横幅
const int window_height = 720;  //縦幅

class WindowsAPI {
public:
	WNDCLASSEX windowClass;		//ウィンドウクラス
	RECT wrc;					//ウィンドウサイズ
	HWND hwnd;					//ウィンドウオブジェクト
	MSG msg;					//メッセージ
	LPCWSTR windowName = L"Engine";

	//コンストラクタ
	WindowsAPI();
	//初期化処理
	void Init();
};