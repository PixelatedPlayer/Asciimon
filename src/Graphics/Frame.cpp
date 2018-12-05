#include "Frame.h"

Frame::Frame(int width, int height) : width(width), height(height) {
    glyphs = new char[width * height];
    colors = new char[width * height];
}

void Frame::SetBit(int x, int y, char glyph, char col) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        glyphs[x + y * width] = glyph;
        colors[x + y * width] = col;
    }
}

void Frame::Fill(int x1, int y1, int x2, int y2, char glyph, char col) {
    if (x1 < 0)
        x1 = 0;
    else if (x1 > width)
        x1 = width;

    if (y1 < 0)
        y1 = 0;
    else if (y1 > height)
        y1 = height;

    if (x2 < 0)
        x2 = 0;
    else if (x2 > width)
        x2 = width;

    if (y2 < 0)
        y2 = 0;
    else if (y2 > height)
        y2 = height;

    for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++)
            SetBit(x, y, glyph, col);
    }
}

void Frame::DrawString(int x, int y, std::string str, char col) {
    for (unsigned int i = 0; i < str.size(); i++) {
        glyphs[x + i + y * width] = str[i];
        colors[x + i + y * width] = col;
    }
}

void Frame::DrawSprite(int x, int y, ConsoleSprite* sprite) {
    if (sprite == nullptr)
        return;

    for (int i = 0; i < sprite->GetWidth(); i++) {
        for (int j = 0; j < sprite->GetHeight(); j++) {
            if (sprite->GetGlyph(i, j) != ' ')
                SetBit(x + i, y + j, sprite->GetGlyph(i, j), sprite->GetColor(i, j));
        }
    }
}

void Frame::DrawBorder(char col) {
    for (int x = 0; x < width; x++) {
        SetBit(x, 0, ' ', col);
        SetBit(x, height - 1, ' ', col);
    }

    for (int y = 1; y < height - 1; y++) {
        SetBit(0, y, ' ', col);
        SetBit(width - 1, y, ' ', col);
    }
}

void Frame::DrawFrame(int x, int y, Frame* frame) {
    if (frame == nullptr)
        return;

    for (int i = 0; i < frame->width; i++) {
        for (int j = 0; j < frame->height; j++) {
            SetBit(x + i, y + j, frame->GetGlyph(i, j), frame->GetColor(i, j));
        }
    }
}

Frame::~Frame() {
    delete[] glyphs;
    delete[] colors;
}