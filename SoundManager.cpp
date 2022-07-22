#include "SoundManager.h"
#include <cassert>
#include "Struct.h"

ComPtr<IXAudio2> SoundManager::xAudio2{};
IXAudio2MasteringVoice* SoundManager::masterVoice{};

//XAudio2VoiceCallback�̃C���X�^���X���O���[�o���ϐ��Ƃ��ăC���X�^���X�����
XAudio2VoiceCallback voiceCallback{};

void SoundManager::SettingSoundManager()
{
	//xaudio2�̃G���W���𐶐�
	HRESULT result = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
	//�}�X�^�[�{�C�X�𐶐�
	result = xAudio2->CreateMasteringVoice(&masterVoice);
}

SoundData SoundManager::SoundLoadWave(char* fileName)
{
	HRESULT result;

	//�t�@�C���I�[�v��
	//�t�@�C�����̓X�g���[���̃C���X�^���X
	ifstream file{};
	//.wav���o�C�i�����[�h�ŊJ��
	file.open(fileName, ios_base::binary);
	//�t�@�C���I�[�v���̎��s�����o����
	assert(file.is_open());

	//wav�̓ǂݍ��݂ƍĐ�
	//RIFF�w�b�_�[�̓ǂݍ���
	RiffHeader riff;
	file.read((char*)&riff, sizeof(riff));
	//�t�@�C����RIFF���`�F�b�N
	if (strncmp(riff.chunk.id, "RIFF", 4) != 0) {
		assert(0);
	}
	//�^�C�v��WAVE���`�F�b�N
	if (strncmp(riff.type, "WAVE", 4) != 0) {
		assert(0);
	}
	//Format�`�����N�̓ǂݍ���
	FormatChunk format{};
	file.read((char*)&format, sizeof(ChunkHeader));
	if (strncmp(format.chunk.id, "fmt ", 4) != 0) {
		assert(0);
	}
	//�`�����N�{�̂̓ǂݍ���
	assert(format.chunk.size <= sizeof(format.fmt));
	file.read((char*)&format.fmt, format.chunk.size);
	//Data�`�����N�̓ǂݍ���
	ChunkHeader data;
	file.read((char*)&data, sizeof(data));
	//JUNK�`�����N�����o�����ꍇ
	if (strncmp(data.id, "JUNK ", 4) == 0) {
		//�ǂݎ��ʒu��JUNK�`�����N�̏I���܂Ői�߂�
		file.seekg(data.size, std::ios_base::cur);
		//�ēǂݍ���
		file.read((char*)&data, sizeof(data));
	}
	if (strncmp(data.id, "LIST ", 4) == 0) {
		//�ǂݎ��ʒu��JUNK�`�����N�̏I���܂Ői�߂�
		file.seekg(data.size, std::ios_base::cur);
		//�ēǂݍ���
		file.read((char*)&data, sizeof(data));
	}
	if (strncmp(data.id, "data ", 4) != 0) {
		assert(0);
	}
	//Data�`�����N�̃f�[�^��(�g�`�f�[�^)�̓ǂݍ���
	char* pBuffer = new char[data.size];
	file.read(pBuffer, data.size);
	//Wave�t�@�C�������
	file.close();

	//return���邽�߂̉����f�[�^
	SoundData soundData = {};
	soundData.wfex = format.fmt;
	soundData.pBuffer = reinterpret_cast<BYTE*>(pBuffer);
	soundData.bufferSize = data.size;
	soundData.volume = 1.0f;

	return soundData;
}

void SoundManager::SoundUnload(SoundData* soundData)
{
	//�o�b�t�@�����������
	delete[]  soundData->pBuffer;

	soundData->pBuffer = 0;
	soundData->bufferSize = 0;
	soundData->wfex = {};
}

void SoundManager::SoundPlayerWave(SoundData& soundData, int loopCount)
{
	HRESULT result;

	//�g�`�t�H�[�}�b�g�����Ƃ�SourceVoice�̐���
	IXAudio2SourceVoice* pSourceVoice = nullptr;
	result = xAudio2->CreateSourceVoice(&pSourceVoice, &soundData.wfex);
	assert(SUCCEEDED(result));

	//�Đ�����g�`�f�[�^�̐ݒ�
	XAUDIO2_BUFFER buf{};
	buf.pAudioData = soundData.pBuffer;
	buf.AudioBytes = soundData.bufferSize;
	buf.Flags = XAUDIO2_END_OF_STREAM;
	buf.LoopCount = loopCount;

	pSourceVoice->SetVolume(soundData.volume);

	soundData.source = pSourceVoice;

	//�g�`�f�[�^�̍Đ�
	result = pSourceVoice->SubmitSourceBuffer(&buf);
	result = pSourceVoice->Start();
}
