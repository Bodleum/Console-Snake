#pragma once

#include <deque>

#include "sSnakeSegment.h"
#include "Food.h"
#include "Screen_Buffer.h"

class Snake
{
	std::deque<sSnakeSegment> Body;
	int Direction;
	int Speed;
	bool Dead;
	bool Shield;

public:
	Snake();

	int Get_Direction();
	int Get_Speed();
	bool Is_Alive();
	int Get_Length();
	bool Shield_Status();

	void Kill();
	void Move();
	void Undo_Move();
	void Set_Length(int);
	void Change_Direction(int);
	void Change_Speed(int);
	bool Collided(Screen_Buffer);
	bool On_Food(Food);
	void Grow(int);
	void Shrink(int);
	void Update_Tail();

	void Draw(Screen_Buffer);

	void Super_Speed();
	void Add_Shield();
	void Remove_Shield();

};
