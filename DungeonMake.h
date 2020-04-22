#pragma once

#define DEF_FIELD_H

typedef struct {
	int field[48][64];
}FIELD;

typedef struct {
	int x, y, h, w;
} ROOM;

typedef struct {
	int x, y, h, w;
	ROOM room;
}AREA;


FIELD Return_Field();
AREA* Return_Areas();
int Return_areaCount();

void Field_Initialize();

void Display_Field();

void Display_Area(int Key[256]);

void Sprite_Area(int areaIndex);

void Generate_Field();