#include"SceneManager.h"

//Windows�A�v���ł̃G���g���[�|�C���g(main�֐�)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	while (true) //�Q�[�����[�v
	{
		//�X�V
		SceneManager::Instance()->Update();
	
		//�`��
		SceneManager::Instance()->Draw();
	}

	SceneManager::Instance()->Finalize();
	return 0;
}