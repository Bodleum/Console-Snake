#pragma once

#include <utility>
#include <Windows.h>

class Screen_Buffer
{
	int width, height;
	wchar_t* buffer;

public:

	Screen_Buffer(int, int);

	std::pair<int, int> Get_Size();
	wchar_t* Get_Buffer();
	wchar_t Element_At(int, int);

	void Clear();
	void Set_Element(int, int, wchar_t);
	void Print(int, int, const wchar_t*, int format = 0);
};

