#include "DxLib.h"
#include "Player.h"

//���̃t�@�C�����ł����g���Ȃ��O���[�o���ϐ�
static int m_Image;		//�`��n���h��
static int m_x;		//x���W
static int m_y;		//y���W

//������������
void Player_Initialize() {
	m_Image = LoadGraph("source/image/testPlayer.png");
	m_x = 0;
	m_y = 0;
}

//�������v�Z����
void Player_Update(int Key[256],int MAP_SIZE) {

	if (Key[KEY_INPUT_RIGHT] == 1) {
		m_x += MAP_SIZE;
	}
	if (Key[KEY_INPUT_LEFT] == 1) {
		m_x -= MAP_SIZE;
	}
	if (Key[KEY_INPUT_UP] == 1) {
		m_y -= MAP_SIZE;
	}
	if (Key[KEY_INPUT_DOWN] == 1) {
		m_y += MAP_SIZE;
	}

}

//�`�悷��
void Player_Draw() {
	DrawGraph(m_x, m_y, m_Image, TRUE);
}

//�I������������
void Player_Finalize() {
	DeleteGraph(m_Image);
}

int gpUpdateKey(int Key[256]) {
	char tmpKey[256];
	GetHitKeyStateAll(tmpKey);
	for (int i = 0; i < 256; i++) {
		if (tmpKey[i] != 0) {
			Key[i]++;
		}
		else {
			Key[i] = 0;
		}
	}
	return 0;
}