#pragma once

#include <Windows.h>
#include "Graphics/Frame.h"

class Game {
private: //implementation variables (consider inheritance)
    float pX, pY;
    bool showingLog;
	Frame* frmLog;
    ConsoleSprite player;
    
private:
	int screenWidth;
	int screenHeight;
	CHAR_INFO* screenBuffer;
	std::string name;
	HANDLE console;
	SMALL_RECT window;
	short keyOldState[256] = { 0 };
	short keyNewState[256] = { 0 };

	struct keyState {
		bool pressed;
		bool released;
		bool held;
	};

	keyState keys[256];
public:
	Game(int width, int height); //construct the console and initialize engine variables

	void Draw(int x, int y, char glyph = ' ', char col = FG_WHITE);
	void Fill(int x1, int y1, int x2, int y2, char glyph = ' ', char col = FG_WHITE);
	void DrawString(int x, int y, std::string str, char col = FG_WHITE);
	void DrawSprite(int x, int y, ConsoleSprite* sprite);
	void DrawFrame(int x, int y, Frame* frame);

	keyState GetKey(int key) { return keys[key]; }
	int GetWidth() { return screenWidth; }
	int GetHeight() { return screenHeight; }
	
	void Start(); // game loop

	bool Create(); //initialize implementation variables
	bool Update(float deltaTime);
	void Destroy(); //similar to destructor - free memory from implementation variables
};