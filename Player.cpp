#include "DxLib.h"
#include "Player.h"
#include "DungeonMake.h"

CHARACTER player;
CHARACTER enemy;


static int count;
static int countE;


CHARACTER Return_Player() {
	return player;
}

CHARACTER Return_Enemy() {
	return enemy;
}

int Return_Count() {
	return count;
}

int Return_CountE() {
	return countE;
}

void Debug() {
	DrawFormatString(100, 100, GetColor(0, 255, 255), "(%d)", Return_Field().field[0][0]);
	DrawFormatString(100, 200, GetColor(0, 255, 255), "(%d)", Return_Areas()[0].x);
}

void Enemy_Initialize() {
	enemy.isLiving = true;
	enemy.isAttack = false;
	enemy.hp = 6 + rand() % Return_stairsCount();
	enemy.maxHp = enemy.hp;
	enemy.attack = 3 + 2 * (rand() % Return_stairsCount());
	enemy.image = LoadGraph("source/image/enemy.png");
	enemy.x = 32 * (Return_Areas()[rand() * rand() % Return_areaCount()].room.x + rand() % 3);
	enemy.y = 32 * (Return_Areas()[rand() * rand() % Return_areaCount()].room.y + rand() % 3);
	enemy.scrollX = 0;
	enemy.scrollY = 0;
	for (int i = 0; i < 4; i++) {
		enemy.isMoving[i] = false;
	}
	countE = 0;
}

void Player_Initialize() {
	player.isLiving = true;
	player.isAttack = false;
	player.isClear = false;
	player.hp = 15;
	player.maxHp = 15;
	player.attack = 3;
	player.image = LoadGraph("source/image/player.png");
	player.x = 32 * (Return_Areas()[rand() % Return_areaCount()].room.x + 2);
	player.y = 32 * (Return_Areas()[rand() % Return_areaCount()].room.y + 2);
	player.scrollX = 0;
	player.scrollY = 0;
	for (int i = 0; i < 4; i++) {
		player.isMoving[i] = false;
	}
	count = 0;
}

void Character_Die() {
	if (player.hp <= 0) {
		player.isLiving = false;
	}
	if (enemy.hp <= 0) {
		enemy.isLiving = false;
		enemy.x = -200;
		enemy.y = -200;
		countE = 0;
		count = 0;
		for (int i = 0; i < 4; i++) {
			player.isMoving[i] = false;
			enemy.isMoving[i] = false;
		}
	}
}

void Player_Attack() {
	if ((player.x + 32 == enemy.x && player.y == enemy.y) || (player.x - 32 == enemy.x && player.y == enemy.y)
		|| (player.x == enemy.x && player.y + 32 == enemy.y) || (player.x == enemy.x && player.y - 32 == enemy.y)) {
		enemy.hp -= player.attack;
	}
}

void Enemy_Attack() {
	player.hp -= enemy.attack;
}
void Clear() {
	if (Return_Field().field[player.y / 32][player.x / 32] == CELL_TYPE_AMULET) {
		player.isClear = true;
	}
}

void Player_Update(int Key[256],int MAP_SIZE) {
	int x = player.x;
	int y = player.y;
	bool ok = true;

	Clear();

	if (enemy.isLiving) {
		Character_Die();
	}

	if (Key[KEY_INPUT_SPACE] == 1) {
		player.isAttack = true;
		Player_Attack();
	}

	if ((!player.isMoving[0] && !player.isMoving[1] && !player.isMoving[2] && !player.isMoving[3])
		&& (!enemy.isMoving[0] && !enemy.isMoving[1] && !enemy.isMoving[2] && !enemy.isMoving[3])) {
		if (Key[KEY_INPUT_RIGHT] == 1 && Key[KEY_INPUT_LEFT] != 1 && Key[KEY_INPUT_UP] != 1 && Key[KEY_INPUT_DOWN] != 1) {
			if (Return_Field().field[player.y / 32][(player.x + 32) / 32] != CELL_TYPE_WALL /*&& (enemy.x != player.x + 32 && enemy.y != player.y)*/)
				player.isMoving[0] = true;
		}
		if (Key[KEY_INPUT_RIGHT] != 1 && Key[KEY_INPUT_LEFT] == 1 && Key[KEY_INPUT_UP] != 1 && Key[KEY_INPUT_DOWN] != 1) {
			if(Return_Field().field[player.y / 32][(player.x - 32) / 32] != CELL_TYPE_WALL /*&& (enemy.x != player.x - 32 && enemy.y != player.y)*/)
				player.isMoving[1] = true;
		}
		if (Key[KEY_INPUT_RIGHT] != 1 && Key[KEY_INPUT_LEFT] != 1 && Key[KEY_INPUT_UP] == 1 && Key[KEY_INPUT_DOWN] != 1) {
			if (Return_Field().field[(player.y - 32) / 32][player.x / 32] != CELL_TYPE_WALL /*&& (enemy.x != player.x && enemy.y != player.y - 32)*/)
				player.isMoving[2] = true;
		}
		if (Key[KEY_INPUT_RIGHT] != 1 && Key[KEY_INPUT_LEFT] != 1 && Key[KEY_INPUT_UP] != 1 && Key[KEY_INPUT_DOWN] == 1) {
			if (Return_Field().field[(player.y + 32) / 32][player.x / 32] != CELL_TYPE_WALL /*&& (enemy.x != player.x && enemy.y != player.y + 32)*/)
				player.isMoving[3] = true;
		}

		if ((Key[KEY_INPUT_RIGHT] == 1 && Key[KEY_INPUT_LEFT] != 1 && Key[KEY_INPUT_UP] != 1 && Key[KEY_INPUT_DOWN] != 1 && Key[KEY_INPUT_SPACE] != 1)
			|| (Key[KEY_INPUT_RIGHT] != 1 && Key[KEY_INPUT_LEFT] == 1 && Key[KEY_INPUT_UP] != 1 && Key[KEY_INPUT_DOWN] != 1 && Key[KEY_INPUT_SPACE] != 1)
			|| (Key[KEY_INPUT_RIGHT] != 1 && Key[KEY_INPUT_LEFT] != 1 && Key[KEY_INPUT_UP] == 1 && Key[KEY_INPUT_DOWN] != 1 && Key[KEY_INPUT_SPACE] != 1)
			|| (Key[KEY_INPUT_RIGHT] != 1 && Key[KEY_INPUT_LEFT] != 1 && Key[KEY_INPUT_UP] != 1 && Key[KEY_INPUT_DOWN] == 1 && Key[KEY_INPUT_SPACE] != 1)
			|| (Key[KEY_INPUT_RIGHT] != 1 && Key[KEY_INPUT_LEFT] != 1 && Key[KEY_INPUT_UP] != 1 && Key[KEY_INPUT_DOWN] != 1 && Key[KEY_INPUT_SPACE] == 1)) {
			if (player.isMoving[0] || player.isMoving[1] || player.isMoving[2] || player.isMoving[3] || player.isAttack) {
				if ((Get_Room(enemy.x, enemy.y) == Get_Room(player.x, player.y))) {
					if (abs(player.x - enemy.x) >= abs(player.y - enemy.y)) {
						if (enemy.x < player.x && Return_Field().field[(enemy.y) / 32][(enemy.x + 32) / 32] != CELL_TYPE_WALL
							/*&& !(enemy.x + 32 == player.x && enemy.y == player.y)*/) {
							enemy.isMoving[0] = true;
						}
						else if (enemy.x >= player.x && Return_Field().field[(enemy.y) / 32][(enemy.x - 32) / 32] != CELL_TYPE_WALL
							/*&& !(enemy.x - 32 == player.x && enemy.y == player.y)*/) {
							enemy.isMoving[1] = true;
						}
					}
					else {
						if (enemy.y > player.y && Return_Field().field[(enemy.y - 32) / 32][(enemy.x) / 32] != CELL_TYPE_WALL
							/*&& !(enemy.x == player.x && enemy.y - 32 == player.y)*/) {
							enemy.isMoving[2] = true;
						}
						else if (enemy.y <= player.y && Return_Field().field[(enemy.y + 32) / 32][(enemy.x) / 32] != CELL_TYPE_WALL
							/*&& !(enemy.x == player.x && enemy.y + 32 == player.y)*/) {
							enemy.isMoving[3] = true;
						}
					}
				}
				player.isAttack = false;
			}
		}
	}
	else {
		if (countE == 0) {
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
		}
		if (count % (MAP_SIZE / 2) == 0) {
			if (countE == 0) {
				player.scrollX = 0;
				player.scrollY = 0;
				if (player.isMoving[0] && !player.isMoving[1] && !player.isMoving[2] && !player.isMoving[3]) {
					player.x += 32;
					if (player.hp < player.maxHp)
						player.hp++;
					countE++;
				}
				if (player.isMoving[1] && !player.isMoving[0] && !player.isMoving[2] && !player.isMoving[3]) {
					player.x -= 32;
					if (player.hp < player.maxHp)
						player.hp++;
					countE++;
				}
				if (player.isMoving[2] && !player.isMoving[1] && !player.isMoving[0] && !player.isMoving[3]) {
					player.y -= 32;
					if (player.hp < player.maxHp)
						player.hp++;
					countE++;
				}
				if (player.isMoving[3] && !player.isMoving[1] && !player.isMoving[2] && !player.isMoving[0]) {
					player.y += 32;
					if (player.hp < player.maxHp)
						player.hp++;
					countE++;
				}
				if (!enemy.isMoving[0] && !enemy.isMoving[1] && !enemy.isMoving[2] && !enemy.isMoving[3]) {
					countE = 0;
					count = 0;
					for (int i = 0; i < 4; i++) {
						player.isMoving[i] = false;
					}
				}
				if (enemy.isMoving[0] || enemy.isMoving[1] || enemy.isMoving[2] || enemy.isMoving[3])
					countE++;
			}
			else {
				if (enemy.isLiving) {
					//‚±‚±‚©‚ç“G‚Ìˆ—
					if ((enemy.x + 32 == player.x && enemy.y == player.y) || (enemy.x - 32 == player.x && enemy.y == player.y)
						|| (enemy.x == player.x && enemy.y - 32 == player.y) || (enemy.x == player.x && enemy.y + 32 == player.y)) {
						Enemy_Attack();
						countE = 0;
						count = 0;
						for (int i = 0; i < 4; i++) {
							player.isMoving[i] = false;
							enemy.isMoving[i] = false;
						}
					}
					else {
						if (enemy.isMoving[0] && !enemy.isMoving[1] && !enemy.isMoving[2] && !enemy.isMoving[3]) {
							enemy.scrollX += MAP_SIZE / 16;
							countE++;
							if (enemy.x + 32 == player.x && enemy.y == player.y) {
								count = 0;
								countE = 0;
								enemy.scrollX = 0;
								enemy.scrollY = 0;
								for (int i = 0; i < 4; i++) {
									player.isMoving[i] = false;
									enemy.isMoving[i] = false;
								}
							}
						}
						if (enemy.isMoving[1] && !enemy.isMoving[0] && !enemy.isMoving[2] && !enemy.isMoving[3]) {
							enemy.scrollX -= MAP_SIZE / 16;
							countE++;
							if (enemy.x - 32 == player.x && enemy.y == player.y) {
								count = 0;
								countE = 0;
								enemy.scrollX = 0;
								enemy.scrollY = 0;
								for (int i = 0; i < 4; i++) {
									player.isMoving[i] = false;
									enemy.isMoving[i] = false;
								}
							}
						}
						if (enemy.isMoving[2] && !enemy.isMoving[1] && !enemy.isMoving[0] && !enemy.isMoving[3]) {
							enemy.scrollY -= MAP_SIZE / 16;
							countE++;
							if (enemy.x == player.x && enemy.y - 32 == player.y) {
								count = 0;
								countE = 0;
								enemy.scrollX = 0;
								enemy.scrollY = 0;
								for (int i = 0; i < 4; i++) {
									player.isMoving[i] = false;
									enemy.isMoving[i] = false;
								}
							}
						}
						if (enemy.isMoving[3] && !enemy.isMoving[1] && !enemy.isMoving[2] && !enemy.isMoving[0]) {
							enemy.scrollY += MAP_SIZE / 16;
							countE++;
							if (enemy.x == player.x && enemy.y + 32 == player.y) {
								count = 0;
								countE = 0;
								enemy.scrollX = 0;
								enemy.scrollY = 0;
								for (int i = 0; i < 4; i++) {
									player.isMoving[i] = false;
									enemy.isMoving[i] = false;
								}
							}
						}
						if (countE % (MAP_SIZE / 2) == 0) {
							enemy.scrollX = 0;
							enemy.scrollY = 0;
							if (enemy.isMoving[0] && !enemy.isMoving[1] && !enemy.isMoving[2] && !enemy.isMoving[3]) {
								enemy.x += 32;
							}
							if (enemy.isMoving[1] && !enemy.isMoving[0] && !enemy.isMoving[2] && !enemy.isMoving[3]) {
								enemy.x -= 32;
							}
							if (enemy.isMoving[2] && !enemy.isMoving[1] && !enemy.isMoving[0] && !enemy.isMoving[3]) {
								enemy.y -= 32;
							}
							if (enemy.isMoving[3] && !enemy.isMoving[1] && !enemy.isMoving[2] && !enemy.isMoving[0]) {
								enemy.y += 32;
							}

							countE = 0;
							count = 0;
							for (int i = 0; i < 4; i++) {
								player.isMoving[i] = false;
								enemy.isMoving[i] = false;
							}
							//player.isAttack = false;
						}
					}
				}
			}
		}
	}

}

void Player_Draw() {
	DrawGraph(256, 192, player.image, TRUE);
	//DrawFormatString(192, 160, GetColor(255, 255, 255), "(%d,%d)", player.x, player.y);
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