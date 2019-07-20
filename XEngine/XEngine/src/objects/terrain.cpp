#include "terrain.h"

#include "../core/rendering/scenes/sceneObjects.h"
#include "../core/rendering/pipeline/shader.h"

XEngine::Terrain::Terrain::Terrain(int grid)
{
 
    
    glm::mat4 id;
    glm::mat4 scaleMatrix = glm::scale(id, glm::vec3(1.0, 0.0, 1.0));
    glm::mat4 positionMatrix = glm::translate(id, glm::vec3(0., 0.0, 0.));
    modelMatrix = positionMatrix;

    octaves = 13;
    frequency = 0.01;
    grassCoverage = 0.65;
    tessMultiplier = 1.0;
    dispFactor = 20.0;
    fogFalloff = 1.5;
    posBuffer = 0;

    /*shad = new Shader("src/shaders/terrain.vs", "src/shaders/terrain.fs");
    shad->addShader("src/shaders/terrain.tcs")
        ->addShader("src/shaders/terrain.tes")
        ->linkPrograms();
*/
    this->gridLength = grid + (grid + 1) % 2; //ensure gridLength is odd


    res = 4;
    initializePlaneVAO();

    this->textures = new Texture2D[6];
    textures[0].loadFromFile("src/textures/terrain/terrain/sand.jpg", COLOR);
    textures[1].loadFromFile("src/textures/terrain/terrain/grass.jpg", COLOR);
    textures[2].loadFromFile("src/textures/terrain/terrain/rdiffuse.jpg", COLOR);
    textures[3].loadFromFile("src/textures/terrain/terrain/snow2.jpg", COLOR);
    textures[4].loadFromFile("src/textures/terrain/terrain/rnormal.jpg", COLOR);
    textures[5].loadFromFile("src/textures/terrain/terrain/terrainTexture.jpg", COLOR);

    positionVec.resize(gridLength*gridLength);
    generateTileGrid(glm::vec2(0.0, 0.0));

    setPositionsArray(positionVec);

    rockColor = glm::vec4(120, 105, 75, 255)*1.5f / 255.f;
    power = 3.0;
}

XEngine::Terrain::Terrain::~Terrain()
{
}

void XEngine::Terrain::Terrain::render(Rendering::ForwardRender *forwardRender)
{
    SceneObjects &sceneSetup = SceneObjects::getInstance();

    //drawFog = !sceneSetup.wireframe;

    if (up != 0.0f) {
        glEnable(GL_CLIP_DISTANCE0);
    }
    glm::mat4 gWorld = modelMatrix;
    glm::mat4 gVP = sceneSetup.projMatrix * forwardRender->getActiveCamera()->getViewMatrix();

    shad->enableShader();
    shad->setVec3("gEyeWorldPos", forwardRender->getActiveCamera()->camPos);
    shad->setMat4("gWorld", gWorld);
    shad->setMat4("gVP", gVP);
    shad->setFloat("gDispFactor", dispFactor);

   // float waterHeight = (waterPtr ? waterPtr->getModelMatrix()[3][1] : 100.0);
    glm::vec4 clipPlane(0.0, 1.0, 0.0, -10.0f);
    shad->setVec4("clipPlane", clipPlane*up);
   // shad->setVec3("u_LightColor", light.getColor());
    //shad->setVec3("u_LightPosition", light.getPos());
    shad->setVec3("u_ViewPosition", forwardRender->getActiveCamera()->camPos);
    shad->setVec3("fogColor", sceneSetup.fogColor);
    shad->setVec3("rockColor", rockColor);
   // shad->setVec3("seed", sceneSetup.seed);

    shad->setInt("octaves", octaves);
    shad->setFloat("freq", frequency);
    shad->setFloat("u_grassCoverage", grassCoverage);
    shad->setFloat("waterHeight", 10.0f);
    shad->setFloat("tessMultiplier", tessMultiplier);
    shad->setFloat("fogFalloff", fogFalloff*1.e-6);
    shad->setFloat("power", power);

    shad->setBool("normals", true);
    //shad->setBool("drawFog", Terrain::drawFog);

    textures[0].bind(1);
    shad->setInt("sand", 1);

    textures[1].bind(2);
    shad->setInt("grass", 2);

    textures[2].bind(3);
    shad->setInt("rock", 3);

    textures[3].bind(4);
    shad->setInt("snow", 4);

    textures[4].bind(5);
    shad->setInt("grass1", 5);

    textures[4].bind(6);
    shad->setInt("rockNormal", 6);

    int nIstances = positionVec.size();

    drawVertices(nIstances);

    glDisable(GL_CLIP_DISTANCE0);
    up = 0.0;
}

void XEngine::Terrain::Terrain::updateTilesPositions(Rendering::ForwardRender *forwardRender)
{
    SceneObjects &sceneSetup = SceneObjects::getInstance();

    glm::vec2 camPosition(forwardRender->getActiveCamera()->camPos.x, forwardRender->getActiveCamera()->camPos.z);
    int whichTile = -1;
    int howManyTiles = 0;

    glm::vec2 currentTile;
    if (getWhichTileCameraIs(currentTile)) {
        glm::vec2 center = getPos(gridLength / 2, gridLength / 2);
        for (glm::vec2& p : positionVec) {
            p += currentTile - center;
        }
        setPositionsArray(positionVec);

        /*if (waterPtr) {
            glm::vec2 center = getPos(gridLength / 2, gridLength / 2);
            waterPtr->setPosition(center, 1.0*gridLength, waterPtr->getHeight());
        }*/
    }
}

void XEngine::Terrain::Terrain::setPositionsArray(std::vector<glm::vec2>& pos)
{
    if (posBuffer) {
        this->deleteBuffer();
    }

    // vertex Buffer Object
    glGenBuffers(1, &posBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, posBuffer);
    glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec2), &pos[0], GL_STATIC_DRAW);

    glBindVertexArray(planeVAO);
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

    glVertexAttribDivisor(3, 1);
    glBindVertexArray(0);

}

void XEngine::Terrain::Terrain::initializePlaneVAO()
{
    //const int res = 3;
    const int nPoints = res * res;
    const int size = nPoints * 3 + nPoints * 3 + nPoints * 2;
    float * vertices = new float[size];
    for (int i = 0; i < res; i++) {
        for (int j = 0; j < res; j++) {
            //add position
            float x = j * (float)tileW / (res - 1) - tileW / 2.0;
            float y = 0.0;
            float z = -i * (float)tileW / (res - 1) + tileW / 2.0;

            vertices[(i + j * res) * 8] = x; //8 = 3 + 3 + 2, float per point
            vertices[(i + j * res) * 8 + 1] = y;
            vertices[(i + j * res) * 8 + 2] = z;

            //add normal
            float x_n = 0.0;
            float y_n = 1.0;
            float z_n = 0.0;

            vertices[(i + j * res) * 8 + 3] = x_n;
            vertices[(i + j * res) * 8 + 4] = y_n;
            vertices[(i + j * res) * 8 + 5] = z_n;

            //add texcoords
            vertices[(i + j * res) * 8 + 6] = (float)j / (res - 1);
            vertices[(i + j * res) * 8 + 7] = (float)(res - i - 1) / (res - 1);
        }
    }

    const int nTris = (res - 1)*(res - 1) * 2;
    int * trisIndices = new int[nTris * 3];

    for (int i = 0; i < nTris; i++) {
        int trisPerRow = 2 * (res - 1);
        for (int j = 0; j < trisPerRow; j++) {
            if (!(i % 2)) { //upper triangle
                int k = i * 3;
                int triIndex = i % trisPerRow;

                int row = i / trisPerRow;
                int col = triIndex / 2;
                trisIndices[k] = row * res + col;
                trisIndices[k + 1] = ++row*res + col;
                trisIndices[k + 2] = --row* res + ++col;
            }
            else {
                int k = i * 3;
                int triIndex = i % trisPerRow;

                int row = i / trisPerRow;
                int col = triIndex / 2;
                trisIndices[k] = row * res + ++col;
                trisIndices[k + 1] = ++row * res + --col;
                trisIndices[k + 2] = row * res + ++col;
            }
        }
    }

    glGenVertexArrays(1, &planeVAO);
    glGenBuffers(1, &planeVBO);
    glGenBuffers(1, &planeEBO);

    glBindVertexArray(planeVAO);

    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, planeEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, nTris * 3 * sizeof(unsigned int), trisIndices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
    glBindVertexArray(0);

    delete[] vertices;
}

void XEngine::Terrain::Terrain::deleteBuffer()
{
    glDeleteBuffers(1, &posBuffer);
    posBuffer = 0;
}

void XEngine::Terrain::Terrain::drawVertices(int nInstances)
{
    glBindVertexArray(planeVAO);
    shad->enableShader();
    glDrawElementsInstanced(GL_PATCHES, (res - 1)*(res - 1) * 2 * 3, GL_UNSIGNED_INT, 0, nInstances);
    glBindVertexArray(0);
}

void XEngine::Terrain::Terrain::generateTileGrid(glm::vec2 offset)
{
    float sc = tileW;

    glm::vec2 I = glm::vec2(1, 0)*sc;
    glm::vec2 J = glm::vec2(0, 1)*sc;

    for (int i = 0; i < gridLength; i++) {
        for (int j = 0; j < gridLength; j++) {
            glm::vec2 pos = (float)(j - gridLength / 2)*glm::vec2(I) + (float)(i - gridLength / 2)*glm::vec2(J);
            setPos(i, j, pos + offset);
        }
    }
}

bool XEngine::Terrain::Terrain::getWhichTileCameraIs(glm::vec2 & result)
{
    return false;
}

void XEngine::Terrain::Terrain::reset()
{
}
