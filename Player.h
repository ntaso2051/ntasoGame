#pragma once

#define DEF_PLAYER_H

typedef struct {
	int hp;
	int attack;
	int maxHp;
	int image;
	int x;
	int y;
	int scrollX;
	int scrollY;
	bool isMoving[4];
	bool isAttack;
	bool isLiving;
	bool isClear;
}CHARACTER;

CHARACTER Return_Player();

void Enemy_Initialize();

CHARACTER Return_Enemy();

void Player_Attack();

void Character_Die();

void Enemy_Attack();

int Return_Count();

int Return_CountE();

void Main_Camera();

void Player_Initialize();

void Player_Update(int Key[256], int MAP_SIZE);

void Player_Draw();

void Player_Draw_Debug();

void Player_Finalize();

int gpUpdateKey(int Key[256]);

void Debug();

