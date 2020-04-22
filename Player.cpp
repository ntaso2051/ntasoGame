#include "DxLib.h"
#include "Player.h"
#include "DungeonMake.h"

//このファイル内でしか使えないグローバル変数
static int m_Image;		//描画ハンドル
static int m_x;		//x座標
static int m_y;		//y座標
static bool isMoving[4]; //4方向でどの方向に動いているか
static int count;

void Debug() {
	DrawFormatString(100, 100, GetColor(0, 255, 255), "(%d)", Return_Field().field[0][0]);
	DrawFormatString(100, 200, GetColor(0, 255, 255), "(%d)", Return_Areas()[0].x);
}

//初期化をする
void Player_Initialize() {
	m_Image = LoadGraph("source/image/testPlayer.png");
	m_x = 32 * (Return_Areas()[rand() % Return_areaCount()].room.x + rand()%2);
	m_y = 32 * (Return_Areas()[rand() % Return_areaCount()].room.y + rand()%3);
	for (int i = 0; i < 4; i++) {
		isMoving[i] = false;
	}
	count = 0;
}

//動きを計算する
void Player_Update(int Key[256],int MAP_SIZE) {
	
	if (!(isMoving[0] || isMoving[1] || isMoving[2] || isMoving[3])) {
		if (Key[KEY_INPUT_RIGHT] == 1) {
			isMoving[0] = true;
		}
		if (Key[KEY_INPUT_LEFT] == 1) {
			isMoving[1] = true;
		}
		if (Key[KEY_INPUT_UP] == 1) {
			isMoving[2] = true;
		}
		if (Key[KEY_INPUT_DOWN] == 1) {
			isMoving[3] = true;
		}
	}
	else {
		if (isMoving[0] && !isMoving[1] && !isMoving[2] && !isMoving[3]) {
			m_x += MAP_SIZE / 16;
			count++;
		}
		if (isMoving[1] && !isMoving[0] && !isMoving[2] && !isMoving[3]) {
			m_x -= MAP_SIZE / 16;
			count++;
		}
		if (isMoving[2] && !isMoving[1] && !isMoving[0] && !isMoving[3]) {
			m_y -= MAP_SIZE / 16;
			count++;
		}
		if (isMoving[3] && !isMoving[1] && !isMoving[2] && !isMoving[0]) {
			m_y += MAP_SIZE / 16;
			count++;
		}
		if (count % (MAP_SIZE / 2) == 0) {
			for (int i = 0; i < 4; i++) {
				isMoving[i] = false;
			}
			count = 0;
		}
	}

}

//描画する
void Player_Draw() {
	DrawGraph(m_x, m_y, m_Image, TRUE);
	DrawFormatString(m_x, m_y, GetColor(255, 255, 255), "(%d,%d)", m_x, m_y);
}

//終了処理をする
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