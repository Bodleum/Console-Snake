#include <iostream>
#include <list>
#include <thread>
#include <chrono>

#include <Windows.h>

#include "Food.h"
#include "sSnakeSegment.h"
#include "Snake.h"
#include "Screen_Buffer.h"

int main()
{
	srand((unsigned int)time(NULL));

	// Create screen buffer
	Screen_Buffer screen(120, 40);

	HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(hConsole);
	DWORD dwBytesWritten = 0;

	int snake_init_length = 10;

	while (true)
	{

		Snake snake;
		snake.Set_Length(10);
		Snake *snake_ptr;
		snake_ptr = &snake;

		bool bWin = false;

		bool bKeyLeft = false, bKeyLeftOld = false;
		bool bKeyRight = false, bKeyRightOld = false;
		bool bKeyUp = false, bKeyUpOld = false;
		bool bKeyDown = false, bKeyDownOld = false;

		Food food(screen);

		while (snake.Is_Alive() && !bWin)
		{
			// Timing and input
			auto t1 = std::chrono::system_clock::now();
			while ((std::chrono::system_clock::now() - t1) < ((snake.Get_Direction() % 2 == 1) ? std::chrono::milliseconds(200 / snake.Get_Speed()) : std::chrono::milliseconds(275 / snake.Get_Speed())))
			{
				// Get input
				bKeyRight = (0x8000 & GetAsyncKeyState((unsigned char)('D'))) != 0;
				bKeyLeft = (0x8000 & GetAsyncKeyState((unsigned char)('A'))) != 0;
				bKeyUp = (0x8000 & GetAsyncKeyState((unsigned char)('W'))) != 0;
				bKeyDown = (0x8000 & GetAsyncKeyState((unsigned char)('S'))) != 0;

				if (bKeyRight && !bKeyRightOld && snake.Get_Direction() != 3) snake.Change_Direction(1);
				if (bKeyLeft && !bKeyLeftOld && snake.Get_Direction() != 1) snake.Change_Direction(3);
				if (bKeyUp && !bKeyUpOld && snake.Get_Direction() != 2) snake.Change_Direction(0);
				if (bKeyDown && !bKeyDownOld && snake.Get_Direction() != 0) snake.Change_Direction(2);

				bKeyRightOld = bKeyRight;
				bKeyLeftOld = bKeyLeft;
				bKeyUpOld = bKeyUp;
				bKeyDownOld = bKeyDown;
			}

			// Game Logic
			// Test move
 			std::pair<int, int> snake_test_pos = snake.Test_Move();

			// Collision
			 
			if (snake.Test_Collision(screen, snake_test_pos))
			{
				// Snake vs food
				if (snake.Test_On_Food(food, snake_test_pos))
				{
					snake.Grow(food.Eaten());

					switch (food.Get_Type())
					{
					case 2:
						std::thread(&Snake::Super_Speed, snake_ptr).detach();
						break;
					case 3:
						snake.Add_Shield();
						break;
					case 4:
						std::thread(&Snake::Chonk, snake_ptr).detach();
						break;
					default:
						break;
					}

					food.New_Food(screen);

					// Update snake position
					snake.Move();

					// Update snake's tail
					snake.Update_Tail();
				}
				else if (snake.Shield_Status())
				{
					snake.Remove_Shield();
					snake.Undo_Move();
					snake.Shrink(1);
					if (snake.Get_Direction() == 0 || snake.Get_Direction() == 2)
						snake.Change_Direction(1);
					else
						snake.Change_Direction(0);
				}
				else
				{
					snake.Kill();
				}
			}
			else
			{
				// Update snake position
				snake.Move();

				// Update snake's tail
				snake.Update_Tail();
			}

			// Display to player
			// Clear screen
			screen.Clear();

			// Draw snake
			snake.Draw(screen);

			// Draw stats and border
			for (int i = 0; i < screen.Get_Size().first; i++)
			{
				screen.Set_Element(i, 0, L'=');
				screen.Set_Element(i, 2, L'=');
			}

			screen.Print(2, 1, L"S N A K E  G A M E ! !");
			screen.Print(55, 1, L"SCORE: %d", snake.Get_Length() - 10);

			// Draw food
			food.Draw(screen);

			if (!snake.Is_Alive())
				screen.Print(45, 20, L"PRESS 'SPACE' TO START AGAIN");

			// Display frame
			WriteConsoleOutputCharacter(hConsole, screen.Get_Buffer(), screen.Get_Size().first * screen.Get_Size().second, { 0, 0 }, &dwBytesWritten);
		}

		// Wait for spacebar
		while ((0x8000 & GetAsyncKeyState((unsigned char)('\x20'))) == 0);
	}

	return 0;
}
