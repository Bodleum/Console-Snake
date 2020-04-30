#include "Screen_Buffer.h"

Screen_Buffer::Screen_Buffer(int w, int h)
{
	width = w;
	height = h;

	buffer = new wchar_t[(unsigned long long)width * (unsigned long long)height];

	for (int i = 0; i < width * height; i++)
	{
		buffer[i] = L' ';
	}
}


std::pair<int, int> Screen_Buffer::Get_Size()
{
	return std::make_pair(width, height);
}

wchar_t* Screen_Buffer::Get_Buffer()
{
	return buffer;
}

wchar_t Screen_Buffer::Element_At(int x, int y)
{
	return buffer[y * width + x];
}



void Screen_Buffer::Clear()
{
	for (int i = 0; i < width * height; i++)
	{
		buffer[i] = L' ';
	}

}


void Screen_Buffer::Set_Element(int x, int y, wchar_t element)
{
	buffer[y * width + x] = element;
}

void Screen_Buffer::Print(int x, int y, const wchar_t *message, int format)
{
	wsprintf(&buffer[y * width + x], message, format);
}