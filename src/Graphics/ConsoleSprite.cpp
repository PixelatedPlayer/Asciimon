#include "ConsoleSprite.h"
#include "Colors.h"
#include "../Engine/Log.h"

#include <vector>
#include <fstream>

void ConsoleSprite::Create(int w, int h) {
	width = w;
	height = h;
	glyphs = new char[w*h];
	colors = new char[w*h];
	for (int i = 0; i < w*h; i++) {
		glyphs[i] = ' ';
		colors[i] = FG_BLACK;
	}
}

bool ConsoleSprite::Save(std::string file) {
	FILE* f = nullptr;
	f = fopen(file.c_str(), "wb");
	if (f == nullptr) {
		Log::Error("Error saving sprite \"" + file + "\"");
		return false;
	}

	fwrite(&width, sizeof(int), 1, f);
	fwrite(&height, sizeof(int), 1, f);
	fwrite(glyphs, sizeof(char), width * height, f);
	fwrite(colors, sizeof(char), width * height, f);

	fclose(f);

	return true;
}

bool ConsoleSprite::Load(std::string file) {
	delete[] glyphs;
	delete[] colors;
	width = 0;
	height = 0;

	FILE* f = nullptr;
	f = fopen(file.c_str(), "rb");
	if (f == nullptr) {
		Log::Error("Error loading sprite \"" + file + "\"");
		return false;
	}

	fread(&width, sizeof(int), 1, f);
	fread(&height, sizeof(int), 1, f);

	Create(width, height);
	fread(glyphs, sizeof(char), width * height, f);
	fread(colors, sizeof(char), width * height, f);

	fclose(f);

	return true;
}

bool ConsoleSprite::LoadFromRaw(std::string file) {
	delete[] glyphs;
	delete[] colors;

	std::ifstream f;
	std::vector<std::string> vecLines;
	f.open(file);
	if (f.fail()) {
		Log::Error("Error loading from raw: \"" + file + "\"");
		return false;
	}

	int w = 0;
	int h = 0;
	std::string line;
	while (getline(f, line)) {
		h++;
		if (line.length() > w)
			w = line.length();

		vecLines.push_back(line);
	}

	Create(w, h);

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			if (j < vecLines[i].length())
				glyphs[j + i * w] = vecLines[i][j];
			else
				glyphs[j + i * w] = ' ';
		}
	}

	for (int i = 0; i < w * h; i++) {
		colors[i] = FG_WHITE + BG_BLACK;
	}

	f.close();
	return true;
}
