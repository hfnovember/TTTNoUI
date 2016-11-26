#ifndef __COLOR__
#define __COLOR__ 
#include <Windows.h>
#include <iostream>
#include <string>
using namespace std;
/**************************************************/
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
/**************************************************/
WORD GetConsoleTextAttribute(HANDLE hCon) {
	CONSOLE_SCREEN_BUFFER_INFO con_info;
	GetConsoleScreenBufferInfo(hCon, &con_info);
	return con_info.wAttributes;
}//end GetConsoleTextAttribute
/**************************************************/
const int white = 15;
const int red = 12;
const int yellow = 14;
const int green = 10;
const int blue = 11;
const int pink = 13;
/**************************************************/
void PrintColored(int color, string text) {
	const int savedColor = GetConsoleTextAttribute(hConsole);
	SetConsoleTextAttribute(hConsole, color);
	cout << text;
	SetConsoleTextAttribute(hConsole, savedColor);
}//end PrintColored()
/**************************************************/
void PrintColored(int color, char text) {
	const int savedColor = GetConsoleTextAttribute(hConsole);
	SetConsoleTextAttribute(hConsole, color);
	cout << text;
	SetConsoleTextAttribute(hConsole, savedColor);
}//end PrintColored()
/**************************************************/
void SetColor(int color) {
	SetConsoleTextAttribute(hConsole, color);
}//end SetColor()
/**************************************************/
#endif 