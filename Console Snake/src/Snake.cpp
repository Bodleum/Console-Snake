#include "Snake.h"

Snake::Snake()
{
	Direction = 3;
	Speed = 2;
	Width = 0;

	Dead = false;
	Shield = false;
}


int Snake::Get_Direction()
{
	return Direction;
}

int Snake::Get_Speed()
{
	return Speed;
}

bool Snake::Is_Alive()
{
	return !Dead;
}

int Snake::Get_Length()
{
	return Body.size();
}

bool Snake::Shield_Status()
{
	return Shield;
}







void Snake::Kill()
{
	Dead = true;
}

void Snake::Move()
{
	switch (Direction)
	{
	case 0: // UP
		Body.push_front({ Body.front().x, Body.front().y - 1 });
		break;
	case 1: // RIGHT
		Body.push_front({ Body.front().x + 1, Body.front().y });
		break;
	case 2: // Down
		Body.push_front({ Body.front().x, Body.front().y + 1 });
		break;
	case 3: // LEFT
		Body.push_front({ Body.front().x - 1, Body.front().y });
		break;
	}
}

void Snake::Undo_Move()
{
	Body.pop_front();
	Grow(1);
}

void Snake::Set_Length(int length)
{
	for (int i = 0; i < length; i++)
		Body.push_back({ 60 + i, 15 });
}

void Snake::Change_Direction(int new_dir)
{
	Direction = new_dir;
}

void Snake::Change_Speed(int new_speed)
{
	Speed = new_speed;
}



bool Snake::Collided(Screen_Buffer screen)
{
	// Snake vs snake
	for (std::deque<sSnakeSegment>::iterator it = Body.begin(); it != Body.end(); it++)
		if (it != Body.begin() && it->x == Body.front().x && it->y == Body.front().y)
			return true;

	// Snake vs world
	if (Body.front().x < 0 || Body.front().x >= screen.Get_Size().first)
		return true;
	if (Body.front().y < 3 || Body.front().y >= screen.Get_Size().second)
		return true;

	return false;
}

bool Snake::On_Food(Food food)
{
	return Body.front().x == food.Get_Coords().first && Body.front().y == food.Get_Coords().second;
}


void Snake::Grow(int length)
{
	for (int i = 0; i < length; i++) Body.push_back({ Body.back().x, Body.back().y });
}

void Snake::Shrink(int length)
{
	for (int i = 0; i < length; i++) Body.pop_back();
}

void Snake::Update_Tail()
{
	Body.pop_back();
}



void Snake::Draw(Screen_Buffer screen)
{
	for (int i = -1 * Width; i < Width + 1; i++)
	{
		if (Direction % 2 == 0)
		{
			// Draw snake body
			for (auto s : Body) screen.Set_Element(s.x + i, s.y, Dead ? L'+' : L'O');

			// Draw snake head
			screen.Set_Element(Body.front().x + i, Body.front().y, Dead ? L'X' : L'@');
			if (Shield) screen.Set_Element(Body[1].x + i, Body[1].y, L'@');
		}
		else if (Direction % 2 == 1)
		{
			// Draw snake body
			for (auto s : Body) screen.Set_Element(s.x, s.y + i, Dead ? L'+' : L'O');

			// Draw snake head
			screen.Set_Element(Body.front().x, Body.front().y + i, Dead ? L'X' : L'@');
			if (Shield) screen.Set_Element(Body[1].x, Body[1].y + i, L'@');
		}
	}
}




void Snake::Super_Speed()
{
	Speed += 3;
	std::this_thread::sleep_for(std::chrono::seconds(20));
	Speed -= 3;
}

void Snake::Add_Shield()
{
	Shield = true;
}

void Snake::Remove_Shield()
{
	Shield = false;
}

void Snake::Chonk()
{
	Width++;
	std::this_thread::sleep_for(std::chrono::seconds(10));
	Width--;
}