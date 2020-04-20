#include "DxLib.h"
#include "Player.h"
#include "DungeonMake.h"
#include <time.h>
#include <stdlib.h>

static const int MAP_SIZE = 32;

static int Key[256]; //�L�[��������Ă���t���[�������i�[����

static int count = 0;

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), SetDrawScreen(DX_SCREEN_BACK);	// Window���[�h�ɕύX ����ʐݒ�
	SetGraphMode(2048, 1536, 32);	//�SField�̑傫��
	SetWindowSize(1024, 768);	//Window�T�C�Y���傤�ǂ悭

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	Player_Initialize();		//Player�̏�����
	Field_Initialize();		//Field�̏�����

	srand((unsigned int)time(NULL));	//�����̏�����

	Sprite_Area(0);		//�G���A�̕���
	Generate_Field();


	//while(����ʂ�\��ʂɔ��f ���b�Z�[�W���� ��ʃN���A �L�[�̍X�V)
	while (!(ScreenFlip()) && !(ProcessMessage()) && !(ClearDrawScreen()) && !(gpUpdateKey(Key))) {

		DrawFormatString(100, 200, GetColor(255, 255, 255), "test");

		Player_Update(Key, MAP_SIZE);	//Player�X�V
		
		Display_Field();	//Field�`��


		Display_Area(Key);
		Player_Draw();		//Player�`��
		

		count++;

	}

	Player_Finalize();		

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}