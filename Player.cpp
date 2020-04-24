#include "DxLib.h"
#include "Player.h"
#include "DungeonMake.h"

CHARACTER player;


static int count;


CHARACTER Return_Player() {
	return player;
}

int Return_Count() {
	return count;
}

void Debug() {
	DrawFormatString(100, 100, GetColor(0, 255, 255), "(%d)", Return_Field().field[0][0]);
	DrawFormatString(100, 200, GetColor(0, 255, 255), "(%d)", Return_Areas()[0].x);
}

void Player_Initialize() {
	player.image = LoadGraph("source/image/testPlayer.png");
	player.x = 32 * (Return_Areas()[rand() % Return_areaCount()].room.x + 2);
	player.y = 32 * (Return_Areas()[rand() % Return_areaCount()].room.y + 2);
	player.scrollX = 0;
	player.scrollY = 0;
	for (int i = 0; i < 4; i++) {
		player.isMoving[i] = false;
	}
	count = 0;
}

void Player_Update(int Key[256],int MAP_SIZE) {
	
	if (!(player.isMoving[0] || player.isMoving[1] || player.isMoving[2] || player.isMoving[3])) {
		if (Key[KEY_INPUT_RIGHT] == 1) {
			player.isMoving[0] = true;
		}
		if (Key[KEY_INPUT_LEFT] == 1) {
			player.isMoving[1] = true;
		}
		if (Key[KEY_INPUT_UP] == 1) {
			player.isMoving[2] = true;
		}
		if (Key[KEY_INPUT_DOWN] == 1) {
			player.isMoving[3] = true;
		}
	}
	else {
		if (player.isMoving[0] && !player.isMoving[1] && !player.isMoving[2] && !player.isMoving[3]) {
			player.scrollX += MAP_SIZE / 16;
			count++;
		}
		if (player.isMoving[1] && !player.isMoving[0] && !player.isMoving[2] && !player.isMoving[3]) {
			player.scrollX -= MAP_SIZE / 16;
			count++;
		}
		if (player.isMoving[2] && !player.isMoving[1] && !player.isMoving[0] && !player.isMoving[3]) {
			player.scrollY -= MAP_SIZE / 16;
			count++;
		}
		if (player.isMoving[3] && !player.isMoving[1] && !player.isMoving[2] && !player.isMoving[0]) {
			player.scrollY += MAP_SIZE / 16;
			count++;
		}
		if (count % (MAP_SIZE / 2) == 0) {
			player.scrollX = 0;
			player.scrollY = 0;
			if (player.isMoving[0] && !player.isMoving[1] && !player.isMoving[2] && !player.isMoving[3]) {
				player.x += 32;
			}
			if (player.isMoving[1] && !player.isMoving[0] && !player.isMoving[2] && !player.isMoving[3]) {
				player.x -= 32;
			}
			if (player.isMoving[2] && !player.isMoving[1] && !player.isMoving[0] && !player.isMoving[3]) {
				player.y -= 32;
			}
			if (player.isMoving[3] && !player.isMoving[1] && !player.isMoving[2] && !player.isMoving[0]) {
				player.y += 32;
			}
			count = 0;
			for (int i = 0; i < 4; i++) {
				player.isMoving[i] = false;
			}
		}
	}

}

void Player_Draw() {
	DrawGraph(192, 128, player.image, TRUE);
	DrawFormatString(192, 160, GetColor(255, 255, 255), "(%d,%d)", player.x, player.y);
}

void Player_Draw_Debug() {
	DrawGraph(player.x + player.scrollX, player.y + player.scrollY, player.image, TRUE);
	DrawFormatString(192, 128, GetColor(255, 255, 255), "(%d,%d)", player.x, player.y);
}

void Player_Finalize() {
	DeleteGraph(player.image);
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