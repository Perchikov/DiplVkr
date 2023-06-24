#pragma once
#include "TryOneConsts.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <list>
using namespace std;
const int SizeMap = SizeMapConst;
struct Room {
	int x1 = 0;
	int y1 = 0;
	int x2 = 0;
	int y2 = 0;
	int RoomId = 0;
	bool StoRasPos[4] = { true,true,true,true };
};

void CanStartExpand(Room& ro, int m[SizeMap][SizeMap]) {
	if (m[ro.x1][ro.y1 - 1] != 0 && m[ro.x2][ro.y1 - 1] != 0) ro.StoRasPos[0] = false;
	if (m[ro.x2 + 1][ro.y2] != 0 && m[ro.x2 + 1][ro.y1] != 0) ro.StoRasPos[1] = false;
	if (m[ro.x1][ro.y2 + 1] != 0 && m[ro.x2][ro.y2 + 1] != 0) ro.StoRasPos[2] = false;
	if (m[ro.x1 - 1][ro.y2] != 0 && m[ro.x1 - 1][ro.y1] != 0) ro.StoRasPos[3] = false;
}

void PrintCor(Room x) {
	cout << "Room " << x.RoomId << ": " << "(" << x.x1 << "," << x.y1 << ")" << "(" << x.x2 << "," << x.y2 << ")" << " Can Expand: " << x.StoRasPos[0] << ", " << x.StoRasPos[1] << ", " << x.StoRasPos[2] << ", " << x.StoRasPos[3] << ", " << endl;
};

void PrintMapASCII(int m[SizeMap][SizeMap]) {
	int i = 0;
	int j = 0;
	for (j = 0; j < SizeMap; j++) {
		for (i = 0; i < SizeMap; i++) {
			if (m[i][j] == 1)
				cout << (char)176 << " ";
			else if (m[i][j] == 0)
				cout << "  ";
			else if (m[i][j] == -3)
				cout << "- ";
			else
				cout << m[i][j] << " ";
		}
		cout << endl;
	}

}

bool RoomColi(Room a, Room b) {
	if ((a.x1 >= b.x1 &&
		a.x1 <= b.x2 &&
		a.y1 >= b.y1 &&
		a.y1 <= b.y2) ||

		(a.x2 >= b.x1 &&
			a.x2 <= b.x2 &&
			a.y1 >= b.y1 &&
			a.y1 <= b.y2) ||

		(a.x1 >= b.x1 &&
			a.x1 <= b.x2 &&
			a.y2 >= b.y1 &&
			a.y2 <= b.y2) ||

		(a.x2 >= b.x1 &&
			a.x2 <= b.x2 &&
			a.y2 >= b.y1 &&
			a.y2 <= b.y2) ||

		(b.x1 >= a.x1 &&
			b.x1 <= a.x2 &&
			b.y1 >= a.y1 &&
			b.y1 <= a.y2) ||

		(b.x2 >= a.x1 &&
			b.x2 <= a.x2 &&
			b.y1 >= a.y1 &&
			b.y1 <= a.y2) ||

		(b.x1 >= a.x1 &&
			b.x1 <= a.x2 &&
			b.y2 >= a.y1 &&
			b.y2 <= a.y2) ||

		(b.x2 >= a.x1 &&
			b.x2 <= a.x2 &&
			b.y2 >= a.y1 &&
			b.y2 <= a.y2)
		)
	{
		return true;
	}
	else return false;
}

bool NearBlock(int x, int y, int k, int m[SizeMap][SizeMap]) {
	int i = 0;
	int j = 0;
	bool f = false;
	for (i = x - 1; i <= x + 1; i++) {
		for (j = y - 1; j <= y + 1; j++) {
			if (m[i][j] == k) {
				f = true;
			}
		}
	}
	return f;
}

int MapGen(int m[SizeMap][SizeMap]) {
	int seed;
	int StorRand = 0;
	int i = 0;
	int j = 0;
	int k = 0;
	int x = 0;
	int y = 0;
	int x2 = 0;
	int y2 = 0;

	for (i = 0; i < SizeMap; i++)
		for (j = 0; j < SizeMap; j++)
			m[i][j] = 1;
	if (MapSeed == 0) {
		seed = time(0);
	}
	else {
		seed = MapSeed;
	}
	srand(seed);
	for (k = 1; k < 7; k++) {
		x = rand() % (SizeMap / 2) + 2;
		y = rand() % (SizeMap / 2) + 2;
		x2 = rand() % (SizeMap / 2) + (SizeMap / 2) - 2;
		y2 = rand() % (SizeMap / 2) + (SizeMap / 2) - 2;
		for (i = x; i < x2; i++) {
			for (j = y; j < y2; j++) {
				m[i][j] = 0;
			}
		}
	}
	list<Room> RoomList;
	list<Room>::iterator IterRoomList = RoomList.begin();
	list<Room>::iterator IterRoomListSravn = RoomList.begin();
	Room CurRoom;
	int roomCount = 0;
	while (roomCount != SizeMapConst/5) {
		for (int z = 0; z < 4; z++) {
			CurRoom.StoRasPos[z] = true;
		}
		x = rand() % SizeMap;
		y = rand() % SizeMap;
		if (m[x][y] == 0) {
			m[x][y] = roomCount + 2;
			CurRoom.x1 = x;
			CurRoom.y1 = y;
			CurRoom.x2 = x;
			CurRoom.y2 = y;
			CurRoom.RoomId = roomCount + 2;
			CanStartExpand(CurRoom, m);
			roomCount++;
			RoomList.push_back(CurRoom);
		}
	}

	/*for (IterRoomList = RoomList.begin(); IterRoomList != RoomList.end(); IterRoomList++) {
		PrintCor(*IterRoomList);
	}*/
	int iter = 0;
	Room ro;
	bool ExpandEnable = true;
	bool f = true;
	while (ExpandEnable) {

		iter++;
		//cout << "-------------------------------" << iter << endl;
		ExpandEnable = false;
		for (IterRoomList = RoomList.begin(); IterRoomList != RoomList.end(); IterRoomList++) {
			//PrintCor(*IterRoomList);
			f = true;
			while (f) {
				if ((*IterRoomList).StoRasPos[0] == true || (*IterRoomList).StoRasPos[1] == true || (*IterRoomList).StoRasPos[2] == true || (*IterRoomList).StoRasPos[3] == true) {

					ro = *IterRoomList;
					StorRand = rand() % 4; //0 - up, 1 - right, 2 - down, 3 - left
					//cout << StorRand << endl;

					if (StorRand == 0) {
						ro.y1 -= 1;
						if (m[ro.x1][ro.y1] == 0 && m[ro.x2][ro.y1] == 0) {
							for (IterRoomListSravn = RoomList.begin(); IterRoomListSravn != RoomList.end(); IterRoomListSravn++) {
								if (RoomColi(ro, (*IterRoomListSravn)) && ro.RoomId != (*IterRoomListSravn).RoomId) {
									(*IterRoomList).StoRasPos[StorRand] = false;
								}
							}
						}
						else {
							(*IterRoomList).StoRasPos[StorRand] = false;
						}
					}
					if (StorRand == 1) {
						ro.x2 += 1;
						if (m[ro.x2][ro.y2] == 0 && m[ro.x2][ro.y1] == 0) {
							for (IterRoomListSravn = RoomList.begin(); IterRoomListSravn != RoomList.end(); IterRoomListSravn++) {
								if (RoomColi(ro, (*IterRoomListSravn)) && ro.RoomId != (*IterRoomListSravn).RoomId) {
									(*IterRoomList).StoRasPos[StorRand] = false;
								}
							}
						}
						else {

							(*IterRoomList).StoRasPos[StorRand] = false;
						}
					}
					if (StorRand == 2) {
						ro.y2 += 1;
						if (m[ro.x1][ro.y2] == 0 && m[ro.x2][ro.y2] == 0) {
							for (IterRoomListSravn = RoomList.begin(); IterRoomListSravn != RoomList.end(); IterRoomListSravn++) {
								if (RoomColi(ro, (*IterRoomListSravn)) && ro.RoomId != (*IterRoomListSravn).RoomId) {
									(*IterRoomList).StoRasPos[StorRand] = false;
								}
							}
						}
						else {
							(*IterRoomList).StoRasPos[StorRand] = false;
						}
					}
					if (StorRand == 3) {
						ro.x1 -= 1;
						if (m[ro.x1][ro.y1] == 0 && m[ro.x1][ro.y2] == 0) {
							for (IterRoomListSravn = RoomList.begin(); IterRoomListSravn != RoomList.end(); IterRoomListSravn++) {
								if (RoomColi(ro, (*IterRoomListSravn)) && ro.RoomId != (*IterRoomListSravn).RoomId) {
									(*IterRoomList).StoRasPos[StorRand] = false;
								}
							}
						}
						else {
							(*IterRoomList).StoRasPos[StorRand] = false;
						}
					}

					if ((*IterRoomList).StoRasPos[StorRand] == true) {
						*IterRoomList = ro;
						f = false;
						ExpandEnable = true;
					}
				}
				else f = false;


			}

			//PrintCor(*IterRoomList);
		}
	}


	//___________________________________________________________________________________________________________________
	for (IterRoomList = RoomList.begin(); IterRoomList != RoomList.end(); IterRoomList++) {
		for (i = (*IterRoomList).x1; i <= (*IterRoomList).x2; i++) {
			for (j = (*IterRoomList).y1; j <= (*IterRoomList).y2; j++) {
				m[i][j] = (*IterRoomList).RoomId;
			}
		}
	}

	for (i = 0; i < SizeMap; i++)
		for (j = 0; j < SizeMap; j++)
			if (m[i][j] == 0)
				m[i][j] = 1;

	for (IterRoomList = RoomList.begin(); IterRoomList != RoomList.end(); IterRoomList++) {
		for (i = (*IterRoomList).x1; i <= (*IterRoomList).x2; i++) {
			m[i][(*IterRoomList).y1] = 1;
			m[i][(*IterRoomList).y2] = 1;
		}
		for (j = (*IterRoomList).y1; j <= (*IterRoomList).y2; j++) {
			m[(*IterRoomList).x1][j] = 1;
			m[(*IterRoomList).x2][j] = 1;

		}
	}

	int CenterX = 0;
	int CenterY = 0;
	int V = 0;
	for (IterRoomList = RoomList.begin(); IterRoomList != RoomList.end(); IterRoomList++) {
		V = ((*IterRoomList).x2 - (*IterRoomList).x1 - 1) * ((*IterRoomList).y2 - (*IterRoomList).y1 - 1);
		//cout << V << endl;
		//PrintCor(*IterRoomList);
		if (V > 0) {
			CenterX = ((*IterRoomList).x1 + (*IterRoomList).x2) / 2;
			CenterY = ((*IterRoomList).y1 + (*IterRoomList).y2) / 2;
			if (m[CenterX][(*IterRoomList).y1 - 2] != 1) {
				m[CenterX][(*IterRoomList).y1] = (*IterRoomList).RoomId;
				m[CenterX][(*IterRoomList).y1 - 1] = (*IterRoomList).RoomId;
			}
			if (m[CenterX][(*IterRoomList).y2 + 2] != 1) {
				m[CenterX][(*IterRoomList).y2] = (*IterRoomList).RoomId;
				m[CenterX][(*IterRoomList).y2 + 1] = (*IterRoomList).RoomId;
			}
			if (m[(*IterRoomList).x1 - 2][CenterY] != 1) {
				m[(*IterRoomList).x1][CenterY] = (*IterRoomList).RoomId;
				m[(*IterRoomList).x1 - 1][CenterY] = (*IterRoomList).RoomId;
			}
			if (m[(*IterRoomList).x2 + 2][CenterY] != 1) {
				m[(*IterRoomList).x2][CenterY] = (*IterRoomList).RoomId;
				m[(*IterRoomList).x2 + 1][CenterY] = (*IterRoomList).RoomId;
			}
		}
	}
	for (i = 0; i < SizeMap; i++)
		for (j = 0; j < SizeMap; j++)
			if (m[i][j] != 1)
				m[i][j] = 0;

	for (i = 1; i < SizeMap; i++)
		for (j = 1; j < SizeMap; j++)
			if (!NearBlock(i, j, 0, m)) {
				m[i][j] = -3;
			}
	for (i = 0; i < SizeMap; i++) {
		m[i][0] = -3;
		m[0][i] = -3;

	}
	return seed;
}