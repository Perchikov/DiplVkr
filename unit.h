#pragma once
#include <iostream>
#include <iomanip>
#include <SFML/Graphics.hpp>
#include <mysql.h>
#include <math.h>
#include <string>
#include "fun.h"
#include <list>
using namespace std;

struct Point {
	int x;
	int y;
	Point() {
		x = 0;
		y = 0;
	}
	Point(int X, int Y) {
		x = X;
		y = Y;
	}
};

class Food {
	int HungerRestore;
	int Type = 0;//1 - fruit, 2 - meat, 3 - grass
	Point Position = Point(0, 0);
public:
	Food(int typ,int HungerResto,int x, int y) {
		Type = typ;
		HungerRestore = HungerResto;
		Position = Point(x, y);
		ItemMap[x][y] = 3;
	}
	Point GetPos() {
		return Position;
	}
	int GetType() {
		return Type;
	}
	int GetHunger() {
		return HungerRestore;
	}
};

class Units {
	int ID = 0;
	int Tier = 1;

	int Vision = 0;  //������
	int Flair = 0;  //���
	int Size = 0;  //������
	int Metabolism = 0;  //����������
	int Speed = 0;  //��������
	double Temperature = 0;  //���������� �����������

	double MinTemperature = 0;
	double MaxTemperature = 0;
	int LifeTime = 0;  //���� �����

	double Stamin = 0;
	double HungerPoints = 0;
	double MaxHungerPoints = 0;
	int Age = 0;

	Point Position = Point(0, 0);
	Point goalVis = Point(0, 0);
	Point goal = Point(0, 0);

	double WayMap[SizeMapConst][SizeMapConst];
	double PathMap[SizeMapConst][SizeMapConst];
	double MinFood = 99;
	string s;
public:

	Units(int Vis, int Fla, int Siz, int Met, int Spe, double Tem) {
		Vision = Vis;
		Flair = Fla;
		Size = Siz;
		Metabolism = Met;
		Speed = Spe;
		Temperature = Tem;

		LifeTime = 1000 / Metabolism;
		MinTemperature = Temperature - 1.5 * Metabolism;
		MaxTemperature = Temperature + 1.5 * Metabolism;
		MaxHungerPoints = 1000 / Metabolism;

		//ID = UnitId + 1;
		//UnitId++;
		//cout << endl << s << endl;
	}

	Units(int T, int Vis, int Fla, int Siz, int Met, int Spe, double Tem) {
		Tier = T;
		Vision = Vis;
		Flair = Fla;
		Size = Siz;
		Metabolism = Met;
		Speed = Spe;
		Temperature = Tem;

		LifeTime = 1000 / Metabolism;
		MinTemperature = Temperature - 1.5 * Metabolism;
		MaxTemperature = Temperature + 1.5 * Metabolism;
		MaxHungerPoints = 1000 / Metabolism;

		//ID = UnitId + 1;
		//UnitId++;
	}

	void SetStats(int T, int Vis, int Fla, int Siz, int Met, int Spe, double Tem, int X, int Y) {
		Tier = T;
		Vision = Vis;
		Flair = Fla;
		Size = Siz;
		Metabolism = Met;
		Speed = Spe;
		Temperature = Tem;

		if (Metabolism != 0) {
			LifeTime = 10000 / Metabolism;
			MinTemperature = Temperature - 1.5 * Metabolism;
			MaxTemperature = Temperature + 1.5 * Metabolism;
			MaxHungerPoints = 1000 / Metabolism;
			HungerPoints = MaxHungerPoints;
		}
		else {
			LifeTime = -1;
			MinTemperature = -1;
			MaxTemperature = -1;
			MaxHungerPoints = -1;
			HungerPoints = MaxHungerPoints;
		}

		ID = UnitId + 1;
		UnitId++;

		Position = Point(X, Y);
		ItemMap[X][Y] = 2;
		s = string("INSERT INTO `Units` VALUE (NULL,") + to_string(MapSeed) + string(",") + to_string(Tier) + string(",") + to_string(Vision) + string(",") + to_string(Flair) + string(",") + to_string(Size) + string(",") + to_string(Metabolism) + string(",") + to_string(Speed) + string(",") + to_string(Temperature) + string(")");
	}

	void SetPosition(int X, int Y) {
		Position = Point(X, Y);
		ItemMap[X][Y] = 2;
	}

	void ChangeHungerPoints(double k) {
		HungerPoints += k;
	}

	void ChangeAge(int x) {
		Age += x;
	}

	void ChangeStamin(double x) {
		Stamin += x;
	}

	void ReMap() {
		int i = 0, j = 0;
		for (i = 0; i <= SizeMapConst - 1; i++) {
			for (j = 0; j <= SizeMapConst - 1; j++) {
				if (ItemMap[i][j] == 0) {
					PathMap[i][j] = -1;
					WayMap[i][j] = -1;
				}
				else if (ItemMap[i][j] == 1) {
					PathMap[i][j] = -2;
					WayMap[i][j] = -2;
				}
				else if (ItemMap[i][j] == 2) {
					PathMap[i][j] = -2;
					WayMap[i][j] = -2;
				}
				else if (ItemMap[i][j] == 3) {
					PathMap[i][j] = -1;
					WayMap[i][j] = -1;
				}
				else {
					PathMap[i][j] = -3;
					WayMap[i][j] = -3;
				}
				if (Position.x == i && Position.y == j) {
					PathMap[i][j] = 0;
					WayMap[i][j] = 0;
				}
			}
		}
	}

	void PrintWayMapWay() {
		int i = 0;
		int j = 0;
		for (j = 0; j < SizeMapConst; j++) {
			for (i = 0; i < SizeMapConst; i++) {
				if (WayMap[i][j] == -2) {
					cout << setw(5) << (char)176;
				}
				else if (WayMap[i][j] == -1) {
					cout << setw(5) << " ";
				}
				else
					cout << setw(5) << WayMap[i][j];
			}
			cout << endl;
		}
	}

	void PrintPathMapWay() {
		int i = 0;
		int j = 0;
		for (j = 0; j < SizeMapConst; j++) {
			for (i = 0; i < SizeMapConst; i++) {
				if (PathMap[i][j] == -2) {
					cout << setw(5) << (char)176;
				}
				else if (PathMap[i][j] == -1) {
					cout << setw(5) << " ";
				}
				else
					cout << setw(5) << PathMap[i][j];
			}
			cout << endl;
		}
	}

	void FindFoodVision() {
		int i = 0, j = 0;
		double k = (double)Vision * 2, n = 0;
		int x1, x2, y1, y2;
		int ik = 0, jk = 0;
		double p = 0, u = -pi;
		double shp = 0.5,shu = 0.05;
		double dist;
		double distx, disty;
		MinFood = 99;
		goalVis = Point(0, 0);
		x1 = Position.x - k;
		x2 = Position.x + k;
		y1 = Position.y - k;
		y2 = Position.y + k;
		while (u<=pi) {
			u += shu;
			//cout << u << endl;
			ik = 0; jk = 0;
			n = 0;
			while (n <= k - 1.5 || WayMap[ik][jk] == -2)
			{
				n += shp;
				if (i >= Position.x)
					ik = Abou(n * cos(u)) + Position.x;
				else
					ik = -(Abou(n * cos(u))) + Position.x;

				jk = Abou(n * sin(u)) + Position.y;
				if (ik < 2) ik = 2;
				if (jk < 2) jk = 2;
				if (ik > SizeMapConst - 2) ik = SizeMapConst - 2;
				if (jk > SizeMapConst - 2) jk = SizeMapConst - 2;
				if (WayMap[ik][jk] != -2)
				{
					distx = abs((int)ik - Position.x);
					disty = abs((int)jk - Position.y);
					if (distx <= disty) {
						WayMap[ik][jk] = abs(distx - disty) + (distx * 1.4); 
						if (ItemMap[ik][jk] == 3) {
							if (WayMap[ik][jk] < MinFood) {
								MinFood = WayMap[ik][jk];
								goal = Point(ik, jk);
							}
						}
					}
					else {
						WayMap[ik][jk] = abs(distx - disty) + (disty * 1.4);
						if (ItemMap[ik][jk] == 3) {
							if (WayMap[ik][jk] < MinFood) {
								MinFood = WayMap[ik][jk];
								goal = Point(ik, jk);
							}
						}
					}
				}
				else break;
			}

		}
	}

	void FindFoodFlair() {
		ReMap();
		goal = Point(0, 0);
		goalVis = Point(0,0);
		FindFoodVision();
		int i = 0, j = 0, k = 0;
		int ik = 0, jk = 0;
		double MinWay = 99;
		MinFood = 99;
		Point FoodPoint;
		int Swi = 0;
		int x1, x2, y1, y2;
		if (goal.x == 0 && goal.y == 0){
			//goal = goalVis;
			for (k = 0; k <= Flair; k++) {
				x1 = Position.x - k;
				x2 = Position.x + k;
				y1 = Position.y - k;
				y2 = Position.y + k;
				if (x1 < 2) x1 = 2;
				if (x2 > (SizeMapConst - 2)) x2 = SizeMapConst - 2;
				if (y1 < 2) y1 = 2;
				if (y2 > (SizeMapConst - 2)) y2 = SizeMapConst - 2;
				for (i = x1; i <= x2; i++) {
					for (j = y1; j <= y2; j++) {
						if (WayMap[i][j] > -2) {
							MinWay = 99;
							for (ik = i - 1; ik <= i + 1; ik++) {
								for (jk = j - 1; jk <= j + 1; jk++) {
									if (WayMap[ik][jk] < MinWay && WayMap[ik][jk] >= 0) {
										MinWay = WayMap[ik][jk];
										if (ik == i || jk == j) {
											Swi = 0;
										}
										else {
											Swi = 1;
										}
									}
								}
							}
							if (MinWay != 99 && (MinWay + 1 + (0.4 * Swi) <= Flair) && ((MinWay + 1 + (0.4 * Swi) <= WayMap[i][j]) || WayMap[i][j] < 0)) {
								WayMap[i][j] = MinWay + 1 + (0.4 * Swi);
								if (ItemMap[i][j] == 3) {
									if (WayMap[i][j] < MinFood) {
										MinFood = WayMap[i][j];
										goal = Point(i, j);
										//cout << endl << MinFood << " " << WayMap[goalVis.x][goalVis.y] << " " << endl;
										//if ((WayMap[goalVis.x][goalVis.y] > MinFood)|| (WayMap[goalVis.x][goalVis.y] <= 0)) {
										//}
										//else if(WayMap[goalVis.x][goalVis.y] > 0){
											
										//	MinFood = WayMap[goalVis.x][goalVis.y];
										//	goal = goalVis;
										//}
									}
								}
							}
						}
					}
				}
			}
		}
		if (goal.x != 0 && goal.y != 0) {
			x1 = goal.x - 1;
			x2 = goal.x + 1;
			y1 = goal.y - 1;
			y2 = goal.y + 1;

			while (MinWay>0) {
				MinWay = 99;
				for (i = x1; i <= x2; i++) {
					for (j = y1; j <= y2; j++) {
						if (WayMap[i][j]<MinWay && WayMap[i][j]>-1) {
							MinWay = WayMap[i][j];
							FoodPoint = Point(i, j);
						}
					}
				}
				PathMap[FoodPoint.x][FoodPoint.y] = WayMap[FoodPoint.x][FoodPoint.y];
				x1 = FoodPoint.x - 1;
				x2 = FoodPoint.x + 1;
				y1 = FoodPoint.y - 1;
				y2 = FoodPoint.y + 1;
			}
		PathMap[goal.x][goal.y] = WayMap[goal.x][goal.y];
		}
	}

	void StepToGoal() {
		if (goal.x != 0 && goal.y != 0) {
			int i = 0, j = 0, k = 0;
			int x1, x2, y1, y2;
			x1 = Position.x - 1;
			x2 = Position.x + 1;
			y1 = Position.y - 1;
			y2 = Position.y + 1;
			Point StepPoint;
			for (i = x1; i <= x2; i++) {
				for (j = y1; j <= y2; j++) {
					if (PathMap[i][j] > PathMap[Position.x][Position.y] && WayMap[i][j] > -1) {
						StepPoint = Point(i, j);
					}
				}
			}
			ItemMap[Position.x][Position.y] = 0;
						//cout << Position.x << " " << Position.y <<" " << StepPoint.x << " " << StepPoint.y << endl;
						//if (StepPoint.x !=0 && StepPoint.y !=0)
			Position = StepPoint;
			//cout << HungerPoints << " " << HungerPoints - PathMap[Position.x][Position.y] << endl;
			HungerPoints -= PathMap[Position.x][Position.y] * (Speed * 0.1);
			if (Position.x==goal.x && Position.y == goal.y) {
				goal = Point(0, 0);
				goalVis = Point(0, 0);
			}
			ItemMap[Position.x][Position.y] = 2;
		}
	}

	void OnFood(list<Food> &f,int &food) {
		if (FoodMap[Position.x][Position.y] !=0) {
			list<Food>::iterator fi = f.begin();
			list<Food>::iterator fi2 = f.begin();
			for (fi = f.begin(); fi != f.end(); fi++) {
				if ((*fi).GetPos().x == Position.x && (*fi).GetPos().y == Position.y) {
					fi2 = fi;
				}
			}
			if ((*fi2).GetType() == 2) {
				FoodNum -= 1;
			}
			HungerPoints += (*fi2).GetHunger();
			f.erase(fi2);
			ItemMap[Position.x][Position.y] = 2; 
			FoodMap[Position.x][Position.y] = 0;
			food--;
			//cout << HungerPoints << " / " << MaxHungerPoints << endl;
		}
	}

	void AddUnit(Units& U, list<Units>& UnitsList, MYSQL* conn) {
		string str;
		const char* cstr;
		int v, f, s, m, sp;
		double t;
		if (Vision>1) v = Vision + rand() % 3 - 1; else v = Vision + rand() % 2;
		if (Flair > 1) f = Flair + rand() % 3 - 1; else f = Flair + rand() % 2;
		if (Size > 1) s = Size + rand() % 3 - 1; else s = Size + rand() % 2;
		if (Metabolism > 1) m = Metabolism + rand() % 3 - 1; else m = Metabolism + rand() % 2;
		if (Speed > 1) sp = Speed + rand() % 3 - 1; else sp = Speed + rand() % 2;
		if (Temperature > 1) t = Temperature + rand() % 3 - 1; else t = Temperature + rand() % 2;
		cout << Tier+1 << " " << v << " " << f << " " << s << " " << m << " " << sp << " " << t << endl;
		str = U.GetSQL();
		cstr = str.c_str();
		mysql_query(conn, cstr);
		U.SetStats(Tier+1, v, f, s, m, sp, t, Position.x, Position.y);
		UnitsList.push_back(U);
		UnitNum++;
	}

	string GetSQL() {
		return s;
	}

	double GetStamin() {
		return Stamin;
	}

	double GetHungerPoints() {
		return HungerPoints;
	}

	double GetMaxHungerPoints() {
		return MaxHungerPoints;
	}

	int GetLifeTime() {
		return LifeTime;
	}

	double GetAge() {
		return Age;
	}

	Point GetPoint() {
		return Position;
	}

	int GetMetabolism() {
		return Metabolism;
	}

	int GetSpeed() {
		return Speed;
	}

	double GetTemperature() {
		return Temperature;
	}
};


void FoodChek(list<Units>& UnitsList, Units& U, MYSQL* conn) {
	bool f = false;
	list<Units>::iterator UnitsListIter;
	list<Units>::iterator UnitsListIter2;
	for (UnitsListIter = UnitsList.begin(); UnitsListIter != UnitsList.end(); UnitsListIter++) {
		if ((*UnitsListIter).GetHungerPoints() < 0 || (*UnitsListIter).GetAge() > (*UnitsListIter).GetLifeTime() || ((*UnitsListIter).GetPoint().x <=1 && (*UnitsListIter).GetPoint().y <= 1)) {
			UnitsListIter2 = UnitsListIter;
			f = true;
		}
		if ((*UnitsListIter).GetHungerPoints() >= (*UnitsListIter).GetMaxHungerPoints()*2) {
			(*UnitsListIter).AddUnit(U, UnitsList, conn);
			(*UnitsListIter).ChangeHungerPoints(-(*UnitsListIter).GetMaxHungerPoints());
		}
	}
	if (f) {
		ItemMap[(*UnitsListIter2).GetPoint().x][(*UnitsListIter2).GetPoint().y] = 0;
		UnitsList.erase(UnitsListIter2);
		UnitNum--;
	}
}
