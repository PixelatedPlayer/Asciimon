#include <chrono>
#include <cstdio>

#include "Game.h"
#include "Log.h"

bool Game::Create() {
    pX = 5;
    pY = 5;
    showingLog = false;
    player.Load("res/Spider.spr");
    frmLog = new Frame(GetWidth(), GetHeight() / 2);
    return true;
}

bool Game::Update(float deltaTime) {
    Fill(0, 0, GetWidth(), GetHeight());
    
    DrawSprite(pX, pY, &player);
    if (showingLog) {
        frmLog->Clear();
        frmLog->DrawBorder();
        Log::Display(frmLog, logINFO, 1, 1);
        DrawFrame(0, GetHeight() / 2, frmLog);
    }
    
    if (GetKey('W').held){
        pY -= 5.0f * deltaTime;
    } else if (GetKey('S').held){
        pY += 5.0f * deltaTime;
    }
    
    if (GetKey('A').held){
        pX -= 5.0f * deltaTime;
    } else if (GetKey('D').held){
        pX += 5.0f * deltaTime;
    }
    
    if (GetKey('L').pressed){
        showingLog = !showingLog;
        if (showingLog)
            Log::ToFile("Log.txt");
    }
    return true;
}

void Game::Destroy() {
    delete frmLog;
}

Game::Game(int width, int height){
    screenWidth = width;
    screenHeight = height;
    
    console = GetStdHandle(STD_OUTPUT_HANDLE);

    // initialize key data
    for (int i = 0; i < 256; i++) {
        keyNewState[i] = 0;
        keyOldState[i] = 0;
        keys[i].pressed = false;
        keys[i].released = false;
        keys[i].held = false;
    }

    name = "Asciimon";
    
    // CONSTRUCT CONSOLE
    
    if (console == INVALID_HANDLE_VALUE) {
        Log::Critical("CORE: Invalid Handle");
        return;
    }
    
    window = {0, 0, 1, 1};
    SetConsoleWindowInfo(console, TRUE, &window);

    //Set Window Style
    HWND hwnd = GetConsoleWindow();
    if (!SetWindowPos(hwnd, 0, 20, 20, 0, 0, SWP_NOSIZE | SWP_NOZORDER))
        Log::Warn("CORE: Could not set console position");
    long dwStyle = GetWindowLong(hwnd, GWL_STYLE);
    //SET STYLES - ^ is exclusive or (bit), so it reverses the bit
    dwStyle ^= WS_MAXIMIZEBOX; //disable maximize button
    dwStyle ^= WS_SIZEBOX; //disable border size change

    SetWindowLong(hwnd, GWL_STYLE, dwStyle);
	
    // set size of screen buffer
    COORD coord = {(short)screenWidth, (short)screenHeight};
    if (!SetConsoleScreenBufferSize(console, coord))
        Log::Error("CORE: SetConsoleScreenBufferSize");

    if (!SetConsoleActiveScreenBuffer(console)) {
        Log::Critical("CORE: SetConsoleActiveScreenBuffer");
        return;
    }

    // is desired window size within max?
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(console, &csbi)) {
        Log::Critical("CORE: GetConsoleScreenBufferInfo");
        return;
    }
    if (screenHeight > csbi.dwMaximumWindowSize.Y) {
        Log::Critical("CORE: Height too large");
        return;
    }
    if (screenWidth > csbi.dwMaximumWindowSize.X) {
        Log::Critical("CORE: Width too large");
        return;
    }

    // set window size
    window = {0, 0, (short)(screenWidth - 1), (short)(screenHeight - 1)};
    if (!SetConsoleWindowInfo(console, TRUE, &window)){
        Log::Critical("CORE: SetConsoleWindowInfo");
        return;
    }

    // create screen buffer
    screenBuffer = new CHAR_INFO[screenWidth * screenHeight];
    for (int i = 0; i < screenWidth * screenHeight; i++) {
        screenBuffer[i].Char.AsciiChar = 0;
        screenBuffer[i].Attributes = 0;
    }

    // disable cursor (blinking) - consider having a toggle function for implementation control
    CONSOLE_CURSOR_INFO cursor;
    GetConsoleCursorInfo(console, &cursor);
    cursor.bVisible = false;
    SetConsoleCursorInfo(console, &cursor);
    //SetConsoleCtrlHandler? if we want ctrl control
}

void Game::Draw(int x, int y, char glyph, char col) {
    if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
        screenBuffer[x + y * screenWidth].Char.AsciiChar = glyph;
        screenBuffer[x + y * screenWidth].Attributes = col;
    }
}

void Game::Fill(int x1, int y1, int x2, int y2, char glyph, char col) {
    if (x1 < 0)
        x1 = 0;
    else if (x1 > screenWidth)
        x1 = screenWidth;

    if (y1 < 0)
        y1 = 0;
    else if (y1 > screenHeight)
        y1 = screenHeight;

    if (x2 < 0)
        x2 = 0;
    else if (x2 > screenWidth)
        x2 = screenWidth;

    if (y2 < 0)
        y2 = 0;
    else if (y2 > screenHeight)
        y2 = screenHeight;

    for (int x = x1; x < x2; x++) {
        for (int y = y1; y < y2; y++)
            Draw(x, y, glyph, col);
    }
}

void Game::DrawString(int x, int y, std::string str, char col) {
    //consider word wrap - will automatically letter wrap
    for (unsigned int i = 0; i < str.size(); i++) {
        screenBuffer[x + i + y * screenWidth].Char.AsciiChar = str[i];
        screenBuffer[x + i + y * screenWidth].Attributes = col;
    }
}

void Game::DrawSprite(int x, int y, ConsoleSprite* sprite) {
    if (sprite == nullptr){
        Log::Error("Attempted to draw invalid sprite");
        return;
    }

    for (int i = 0; i < sprite->GetWidth(); i++) {
        for (int j = 0; j < sprite->GetHeight(); j++) {
            if (sprite->GetGlyph(i, j) != ' ')
                Draw(x + i, y + j, sprite->GetGlyph(i, j), sprite->GetColor(i, j));
        }
    }
}

void Game::DrawFrame(int x, int y, Frame* frame) {
    if (frame == nullptr){
        Log::Error("Attempted to draw invalid frame");
        return;
    }

    for (int i = 0; i < frame->GetWidth(); i++) {
        for (int j = 0; j < frame->GetHeight(); j++) {
            Draw(x + i, y + j, frame->GetGlyph(i, j), frame->GetColor(i, j));
        }
    }
}

void Game::Start() {
    bool running = true;
    if (!Create())
        running = false;

    auto tp1 = std::chrono::system_clock::now(); // time point 1
    auto tp2 = std::chrono::system_clock::now(); // time point 2
    float perSec = 1; //1 so is set in first frame
    
    while (running) {
        //TIMING
        tp2 = std::chrono::system_clock::now();
        std::chrono::duration<float> duration = tp2 - tp1;
        tp1 = tp2;
        float deltaTime = duration.count();
        perSec += duration.count();

        //KEYBOARD INPUT
        //TODO event style? when one is CHANGED, send it to handleInput?
        //OR just have a redundant check in update - with a keystate enum?
        //	keystate has none, pressed, held, released and checks all 256 for changes, then sends change to appropriate input handlers?
        //option 1 faster, option 2 more versatile
        for (int i = 0; i < 256; i++) {
            keyNewState[i] = GetAsyncKeyState(i);

            keys[i].pressed = false;
            keys[i].released = false;

            if (keyNewState[i] != keyOldState[i]) {
                //TODO remove & 0x8000?
                if (keyNewState[i]) {
                    keys[i].pressed = !keys[i].held;
                    keys[i].held = true;
                } else {
                    keys[i].released = true;
                    keys[i].held = false;
                }
            }

            keyOldState[i] = keyNewState[i];
        }

        // Update
		if (!Update(deltaTime))
			running = false;

        //Title
        if (perSec >= 1){
            char s[256];
            snprintf(s, 256, "%s - FPS: %4.0f", name.c_str(), 1.0f / deltaTime);
            SetConsoleTitle(s);
            perSec = 0;
       }
        
        //Screen buffer
        WriteConsoleOutput(console, screenBuffer,{ (short)screenWidth, (short)screenHeight }, { 0, 0 }, &window); }

    //implementation deconstruct
    Destroy();
    
    //only heap memory in core
    delete[] screenBuffer;
}