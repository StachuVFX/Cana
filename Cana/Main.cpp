//
//  Main.cpp
//  Cana
//
//  Created by Stachu on 16.12.2025.
//

/*
    Possible optimizations:
- inline functions
 
    TODO:
 - decide next steps (should Cana handle everything, or create screen and renderer objects in main function)
 - add drawTriangle function
 - maybe change functions arguments to references
 - implement timing
 - test if references and pointers are faster
 
    DONE:
 - move methods from Cana to Cana_Screen
 - moved methods from Cana to Cana_Renderer
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
    cana.createWindow("Cana Test", SCREEN_WIDTH, SCREEN_HEIGHT, WindowType_Fullscreen);
    
/* Game setup */
    cana.createDrawingSurface(DRAW_WIDTH, DRAW_HEIGHT);
    
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
        cana.clear(color.blue);
        
        cana.drawSquare(Cana_Point(0, 0), 70, color.green);
        cana.drawLine(Cana_Point(25, 30), Cana_Point(95, 60), color.red);
        
        /* Stop drawing */
        cana.drawingFinish();

    /* Swapping buffers */
        cana.scale();
        cana.swap();
    }
    
/* Shutdown */
    cana.quit();
}
