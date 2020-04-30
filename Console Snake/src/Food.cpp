#include "Food.h"

Food::Food(Screen_Buffer screen)
{
	x_bound = screen.Get_Size().first;
	y_bound = screen.Get_Size().second;

	srand((unsigned int)time(NULL));

	New_Position();
}




std::pair<int, int> Food::Get_Coords()
{
	return std::make_pair(x, y);
}

int Food::Get_Type()
{
	return Current_Type;
}


std::pair<int, int> Food::New_Position()
{
	srand((unsigned int)time(NULL));

	std::pair<int, int> pos = std::make_pair(rand() % x_bound, (rand() % (y_bound - 3)) + 3);

	x = pos.first;
	y = pos.second;

	return pos;
}

int Food::Eaten()
{
	int modifier;

	switch (Current_Type)
	{
	case 1: // Super
		modifier = 5;
		break;
	case 2: // Speed
		modifier = 1;
		break;
	case 3: // Shield
		modifier = 1;
		break;
	case 4: // Chonk
		modifier = 1;
		break;
	case 5: // Magnet
		modifier = 1;
		break;
	default:  // Normal
		modifier = 1;
	};
	
	return modifier;
}

void Food::Draw(Screen_Buffer screen)
{
	wchar_t symbol;

	switch (Current_Type)
	{
	case 1: // Super
		symbol = L'#';
		break;
	case 2: // Speed
		symbol = L'F';
		break;
	case 3: // Shield
		symbol = L'S';
		break;
	case 4: // Chonk
		symbol = L'C';
		break;
	case 5: // Magnet
		symbol = L'U';
		break;
	default: // Normal
		symbol = L'%';
	};

	screen.Set_Element(x, y, symbol);
}

void Food::New_Food(Screen_Buffer screen)
{
	New_Position();

	while (screen.Element_At(x, y) != L' ')
		New_Position();

	if ((rand() % 3) == 0)
	{
		Current_Type = rand() % 6;
	}
	else Current_Type = -1;
}