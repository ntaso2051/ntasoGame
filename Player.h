#pragma once

#define DEF_PLAYER_H

//����������
void Player_Initialize();

//�������v�Z����
void Player_Update(int Key[256], int MAP_SIZE);

//�`�悷��
void Player_Draw();

//�I������������
void Player_Finalize();

//���ׂẴL�[���͏�Ԃ�c��
int gpUpdateKey(int Key[256]);

