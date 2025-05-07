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
    graphics::setUpdateFunction(update);    

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    mygame.init();  				
    mygame.setDebugMode(false);
    graphics::startMessageLoop(); 
    return 0;
}
