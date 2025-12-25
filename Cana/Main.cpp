//
//  Main.cpp
//  Cana
//
//  Created by Stachu on 16.12.2025.
//

/*
    Possible optimizations:
 - implement timing to test solution speed
 - inline functions
 - change arguments to references
 
    TODO:
 - add float and double version of Vec2 and drawing functions
 - add conversions betweem local, global and unified dimensions
 - unify dimensions (float [-1, 1] by width)
 - add drawTriangle function
 - try making Cana handle everything
 - move enums to classes (one day)
 - create Cana_Event class (one day)
 
    DONE:
 - document functions (especially which format of dimensions)
*/

//  System Includes
#include <iostream>
#include <thread>

//  SDL Includes
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

//  Custom Includes
#include "Cana.h"

//  Defines
#define SCREEN_WIDTH 1440
#define SCREEN_HEIGHT 900
#define DRAW_WIDTH 120
#define DRAW_HEIGHT 90

//  Structs

//  Function declarations

//  Variable declarations

//  Main function
int main(int argc, char* argv[]) {
/* Startup */
    Cana cana("Cana Test", "0.1.2", "name.stachu.Cana");
    /* Screen and renderer */
    cana.createWindow("Cana Test", SCREEN_WIDTH, SCREEN_HEIGHT, WindowType_Fullscreen);
    Cana_Renderer renderer = cana.createRenderer(DRAW_WIDTH, DRAW_HEIGHT);
    
/* Game setup */
    /* Colors */
    Cana_Color color = cana.mapColors();
    
/* Game loop */
    while (cana.running) {
        /* Sleep in case of memory leaks lol */
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
    /* Events */
        cana.checkEvents();
        
    /* Rendering */
        /* Prepare for drawing */
        cana.drawingStart();
        
        /* Only draw here */
        renderer.clear(color.black);
        
        renderer.drawSquare(Cana_Vec2(0, 0), 70, color.blue);
//        renderer.drawTriangle(Cana_Vec2(-30, -30), Cana_Vec2(30, -30), Cana_Vec2(0, 30), color.green);
        renderer.drawLine(Cana_Vec2(20, 30), Cana_Vec2(100, 60), color.red, PixelAmount_LessPixels);
        
        /* Stop drawing */
        cana.drawingFinish();

    /* Swapping buffers */
        cana.scale();
        cana.swap();
    }
    
/* Shutdown */
    cana.quit();
}
