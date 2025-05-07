#include "graphics.h"   //"graphics" is a namespace.
#include "game.h"
#include "config.h"



void resize(int w, int h)
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->setWindowDimensions((unsigned int)w, (unsigned int)h);
}

void update(float ms)
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->update();
}

// The window content drawing function.
void draw()
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    game->draw();
}

int main()
{

    Game mygame;

    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Game");

    graphics::setUserData(&mygame);

    graphics::setDrawFunction(draw);        //The graphics::startMessageLoop() calls the two "call-backs" functions. Not us.
    graphics::setUpdateFunction(update);    //(We don't know when they are called.)

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    mygame.init();  						//init(): kaleitai prin mpo sto messageloop.
    mygame.setDebugMode(false);
    graphics::startMessageLoop(); 
      
    //graphics::destroyWindow();
    //otan pataei exit

    return 0;
}
