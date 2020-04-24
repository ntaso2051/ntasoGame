#pragma once

#define DEF_PLAYER_H

typedef struct {
	int image;
	int x;
	int y;
	bool isMoving[4];
}CHARACTER;

CHARACTER Return_Player();

void Player_Initialize();

void Player_Update(int Key[256], int MAP_SIZE);

void Player_Draw();

void Player_Draw_Debug();

void Player_Finalize();

int gpUpdateKey(int Key[256]);

void Debug();

