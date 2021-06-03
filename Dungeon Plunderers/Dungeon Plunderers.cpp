#include "pch.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <windows.h>
#include <thread>
#include <future>
#include "Game.h"
#pragma comment(lib,"user32.lib") 

//temp
bool showHitboxes = true;

bool& getShowHitboxes()
{
	return showHitboxes;
}

int main()
{
	HWND okno = GetConsoleWindow();
	//ShowWindow(okno, SW_HIDE);
	ShowWindow(okno, SW_SHOW);

	Game game;
	game.run();	
	return 0;
}