#pragma once

#include "assetmanager.h"

namespace XEngine
{
    using namespace Assets;
    class Resources
    {
    public:
        
        Resources() 
        {
            initModels();
            initTextures();
        }


        ~Resources()
        {
            delete plane;
            delete secondmodel;
            delete cube;
            delete sphere;
            delete dragon;
   
        }

        void initModels()
        {       
            plane = new Model("src/models/simple/plane.obj", false);
            secondmodel = new Model("src/models/nano/nanosuit.obj", false);

            cube = new Model("src/models/simple/cube.obj", false);
            sphere = new Model("src/models/simple/sphere.obj", false);

            //dragon = new Model("src/models/dragon.obj", false);
            //sportCar = new Model("src/models/sportsCar.obj" , false);

            AssetManager::addModel("First", plane);
            AssetManager::addModel("Second", secondmodel);
            AssetManager::addModel("Third", cube);
            AssetManager::addModel("Fourth", sphere);
            //AssetManager::addModel("Dragon", dragon);
            
        }

        void initTextures()
        {

        }

    private:

        Model *plane;
        Model *secondmodel; 
        Model *cube;
        Model *sphere;
        Model *dragon;

    };
}
