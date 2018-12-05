#pragma once
#include <string>

class ConsoleSprite {
private:
	char* glyphs;
	char* colors;
	int width;
	int height;

private:
    void Create(int w, int h);

public:
    void SetGlyph(int x, int y, char glyph) { glyphs[x + y * width] = glyph; }
    void SetColor(int x, int y, char col) { colors[x + y * width] = col; }
    char GetGlyph(int x, int y) { return glyphs[x + y * width]; }
    char GetColor(int x, int y) { return colors[x + y * width]; }
    int GetWidth() { return width; }
    int GetHeight() { return height; }

    bool Save(std::string file);
    bool Load(std::string file);
    bool LoadFromRaw(std::string file); //simple text - used only to create a file to load from Load()
};