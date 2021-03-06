#pragma once

#include <string>

#include "Colors.h"
#include "ConsoleSprite.h"

class Frame {
private:
	int width;
	int height;
	char* glyphs;
	char* colors;

public:
	//handleinput from world/player, ui, battle, etc.
	//	when a key is CHANGED, it sends THAT key to handleInput, instead of handleinput checking each key - makes more sense with bool
	Frame(int width, int height);

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	char GetGlyph(int x, int y) { return glyphs[x + y * width]; }
	char GetColor(int x, int y) { return colors[x + y * width]; }
	void SetBit(int x, int y, char glyph, char col = FG_WHITE + BG_BLACK);
	void Fill(int x1, int y1, int x2, int y2, char glyph = ' ', char col = FG_WHITE + BG_BLACK);
	void DrawString(int x, int y, std::string str, char col = FG_WHITE + BG_BLACK);
	void DrawSprite(int x, int y, ConsoleSprite* sprite);
	void DrawBorder(char col = FG_WHITE + BG_GRAY);
	void DrawFrame(int x, int y, Frame* frame);
	void Clear(char col = FG_WHITE + BG_BLACK) { Fill(0, 0, width, height, ' ', col); }

	~Frame();
};
