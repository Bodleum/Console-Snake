#pragma once

#include <list>
#include <utility>
#include <chrono>
#include <thread>

#include "sSnakeSegment.h"
#include "Screen_Buffer.h"

class Food
{
	int x, x_bound;
	int y, y_bound;

	bool Super = false;

	int Current_Type = 0;

public:

	Food(Screen_Buffer);

	std::pair<int, int> Get_Coords();
	int Get_Type();

	std::pair<int, int> New_Position();
	int Eaten();
	void Draw(Screen_Buffer);
	void New_Food(Screen_Buffer);
};

