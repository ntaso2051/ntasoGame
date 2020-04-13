#pragma once

#define DEF_PLAYER_H

//初期化する
void Player_Initialize();

//動きを計算する
void Player_Update(int Key[256], int MAP_SIZE);

//描画する
void Player_Draw();

//終了処理をする
void Player_Finalize();

//すべてのキー入力状態を把握
int gpUpdateKey(int Key[256]);

