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
 - drawTriangle versions:
    * 1. Lines from one vertex to all points on the opposite side - missing points towards the side edge
    * 2. Lines between two sides, simultanous (starting from one vertex, ending at the other vertices at the same time) - inefficient
    * 3. Only horizontal lines, phased (starting from top vertex, ending at bottom vertex, 2 phases divided by the middle vertex) - efficient
    * 4. Using straight line relative equations and comparisons - probably inefficient
 
    Possible optimizations:
 - implement timing to test solution speed
 - inline functions
 - change arguments to references
 
    TODO:
 - add blured/sampled versions of screen functions
 - add float (blured/sampled) versions of drawing functions
 - try making Cana handle everything
 - move enums to classes (one day)
 - create Cana_Event class (one day)
 
    DONE:
 - moved line pixelAmount from unified function args to a define
    * only left pixelAmount changable in drawLine_direct
 - add drawTriangle function (version 2 not 3 because I'm lazy)
    * decided to use less pixels on triangle sides, but more on the lines between
 - updated documentation
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
#define DRAW_WIDTH 800
#define DRAW_HEIGHT 600

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
        renderer.drawTriangle_unified(Cana_Vec2(-0.7, -0.50), Cana_Vec2(0.7, -0.50), Cana_Vec2(0, 0.7), color.green);
        renderer.drawLine_unified(Cana_Vec2(-0.68, 0.25), Cana_Vec2(0.68, -0.25), color.red);
        
        /* Stop drawing */
        cana.drawingFinish();

    /* Swapping buffers */
        cana.scale();
        cana.swap();
    }
    
/* Shutdown */
    cana.quit();
}
