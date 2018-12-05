#include "Engine/Game.h"
#include "Engine/Log.h"
#include <iostream>

/* TODO
 * consider engine inheritance for cleaner implementation?
 * asciimon
 * battle scene
 * player
 * map (player movement - init battle scene)
 * catching asciimon
 * 
 * OPTIONAL
 * towns?
 *  resources (asciiballs)
 *  healing
 *  items? (potions)
 */

using namespace std;

int main() {
    COORD size;
    int w;
    int h;
    int dec = 0;

    size = GetLargestConsoleWindowSize(GetStdHandle(STD_OUTPUT_HANDLE));

    //can handle this all differently for different resolutions
    //can change ratio from 2:1 to 16:9
    //or have an array of predetermined options, cycling through until valid

    do {
        w = int(size.X / 10 - dec) * 10;
        h = w / 2;
        dec++;
    } while (h > size.Y);

    Log::Info("Console Size Determined: %d, %d", w, h);

    if (w > 0 && h > 0) {
        Game game(w, h);
        game.Start();
    } else {
        cout << "Game cannot run on your maximum console size. Please reduce your console font size or play on a greater resolution monitor.";
    }
    return 0;
}