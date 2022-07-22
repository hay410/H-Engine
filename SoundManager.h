#pragma once
#include <fstream>
#include "DirectXBase.h"
#include "Singleton.h"
#include "Struct.h"

class SoundManager : public Singleton<SoundManager> {
private:
	friend Singleton<SoundManager>;
	SoundManager() {};

public:
	static ComPtr<IXAudio2> xAudio2;
	static IXAudio2MasteringVoice* masterVoice;

	void SettingSoundManager();
	//�T�E���h�Đ�
	SoundData SoundLoadWave(char* fileName);
	//�����f�[�^�̍Đ�
	void SoundUnload(SoundData* soundData);
	//�����Đ�
	void SoundPlayerWave(SoundData& soundData, int loopCount);
};

//�R�[���o�b�N�p
class XAudio2VoiceCallback : public IXAudio2VoiceCallback {
public:
	//�{�C�X�����p�X�̊J�n��
	STDMETHOD_(void, OnVoiceProcessingPassStart)(THIS_ UINT32 BytesRequired) {};
	//�{�C�X�����p�X�̏I����
	STDMETHOD_(void, OnVoiceProcessingPassEnd)(THIS) {};
	//�o�b�t�@�X�g���[���̍Đ����I��������
	STDMETHOD_(void, OnStreamEnd)(THIS) {};
	//�o�b�t�@�̎g�p�J�n��
	STDMETHOD_(void, OnBufferStart)(THIS_ void* pBufferContext) {};
	//�o�b�t�@�̖����ɒB������
	STDMETHOD_(void, OnBufferEnd)(THIS_ void* pBUfferContext) {
		//�o�b�t�@���J������
		delete[] pBUfferContext;
	};
	//�Đ������[�v�ʒu�ɒB������
	STDMETHOD_(void, OnLoopEnd)(THIS_ void* pBUfferContext) {};
	//�{�C�X�̎��s�G���[��
	STDMETHOD_(void, OnVoiceError)(THIS_ void* pBufferContext, HRESULT Error) {};
};