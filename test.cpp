#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(TRUE), SetDrawScreen(DX_SCREEN_BACK);	// Window���[�h�ɕύX ����ʐݒ�

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//while(����ʂ�\��ʂɔ��f ���b�Z�[�W���� ��ʃN���A �L�[�̍X�V
	while (!(ScreenFlip()) && !(ProcessMessage()) && !(ClearDrawScreen())) {

		DrawFormatString(100, 200, GetColor(255, 255, 255), "test");

	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}