#include "DxLib.h"
#include "Player.h"

static const int MAP_SIZE = 32;

static int Key[256]; //�L�[��������Ă���t���[�������i�[����

static int count = 0;

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), SetDrawScreen(DX_SCREEN_BACK);	// Window���[�h�ɕύX ����ʐݒ�

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	Player_Initialize();		//Player�̏�����

	//while(����ʂ�\��ʂɔ��f ���b�Z�[�W���� ��ʃN���A �L�[�̍X�V
	while (!(ScreenFlip()) && !(ProcessMessage()) && !(ClearDrawScreen()) && !(gpUpdateKey(Key))) {

		DrawFormatString(100, 200, GetColor(255, 255, 255), "test");

		Player_Update(Key, MAP_SIZE);

		Player_Draw();		//Player�`��

		count++;

	}

	Player_Finalize();		

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}