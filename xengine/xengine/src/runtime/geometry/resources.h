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
            
        }

        // @Refactor!!!
        void initModels()
        {       
            //plane = new Model("src/models/simple/plane.obj", false);
            //secondmodel = new Model("src/models/nano/nanosuit.obj", false);

            //cube = new Model("src/models/simple/cube.obj", false);
            //sphere = new Model("src/models/simple/sphere.obj", false);

            //erato = new Model("src/models/erato/erato-1.obj", false);
            //sportCar = new Model("src/models/sportsCar.obj" , false);

            //AssetManager::addModel("Plane", plane);
            //AssetManager::addModel("Second", secondmodel);
            //AssetManager::addModel("Cube", cube);
            //AssetManager::addModel("Sphere", sphere);
            //AssetManager::addModel("Erato", erato);            
        }

        void initTextures()
        {

        }

    private:

        //Model *plane;
        //Model *secondmodel; 
        //Model *cube;
        //Model *sphere;
        //Model *erato;
    };
}
