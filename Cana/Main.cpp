//
//  Main.cpp
//  Cana
//
//  Created by Stachu on 16.12.2025.
//

/*
    Conventions:
 - dimensions:
    * unified (signed float, [-1, 1], relative to screen center)
    * direct (unsinged float or int, relative to top-left corner)
 
    Possible optimizations:
 - implement timing to test solution speed
 - inline functions
 - change arguments to references
 
    TODO:
 - add drawTriangle function
 - add float (blured/sampled) versions of drawing functions
 - try making Cana handle everything
 - move enums to classes (one day)
 - create Cana_Event class (one day)
 
    DONE:
 - add float version of Vec2
 - fixed a minor bug in drawSquare()
 - modified specific screen functions to use their buffer versions
 - added conversion from unified to direct dimensions
 - added unified version of drawLine()
 - added out of bounds protection
 - change square size from pixels to unified
 - unify dimensions (float [-1, 1] by width) - all done
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
        renderer.clear(color.gray);
        
        renderer.drawSquare(Cana_Vec2(0, 0), 1.2, color.blue);
//        renderer.drawTriangle(Cana_Vec2(-30, -30), Cana_Vec2(30, -30), Cana_Vec2(0, 30), color.green);
        renderer.drawLine_unified(Cana_Vec2(-0.68, 0.25), Cana_Vec2(0.68, -0.25), color.red, PixelAmount_LessPixels);
        
        /* Stop drawing */
        cana.drawingFinish();

    /* Swapping buffers */
        cana.scale();
        cana.swap();
    }
    
/* Shutdown */
    cana.quit();
}
