#pragma once
static int startUnits = 30;
const int SizeMapConst = 80;
static int MapSeed = 0;

static double GameSpeed = 32;
static double soil = 0.025;
static int TemperatuteM = 16;


static int FoodNum = 20;
static int UnitNum = 0;
static int ItemMap[SizeMapConst][SizeMapConst];//0 - Free, 1 - Wall, 2 - Unit, 3 - Food,
static int FoodMap[SizeMapConst][SizeMapConst];
static int StartUnitStats[6] = { 10, 15, 10, 5, 10, 21 };
static int UnitId = 0;
const double pi = 3.14159265358979323846;