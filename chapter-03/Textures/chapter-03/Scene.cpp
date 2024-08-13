#include "Scene.h"
#include "Shader.h"

Scene::Scene() : mShader(nullptr), mSate(EState::EDISABLE)
{
    mVAO = 0;
    mVBO = 0;
    mEBO = 0;
}

Scene::~Scene()
{
    delete mShader;
    delete[] vertices;
    delete[] indices;

}

bool Scene::Initialize()
{
    /*
        Comme dans le moteur de jeu Godot, une scene est un GameObject.
        Une scene est constitu�e de Nodes qui repr�sente des GameObject.

        Initialiser une scene revient pour l'instant � :
            1. Generer les buffers objects
            2. Cr�er des zones m�moires dans le GPU
            3. Envoyer les donn�es dans la m�moire du GPU.
            4. Activer le programme shader
    */

    return true;
}

void Scene::Update(float dt)
{
    /*
        Si @mState est EACTIVE alors :
            Update values that has to be send to the GPU
    */
}

void Scene::Draw()
{
    /*
        Si @mState est EACTIVE alors :

            1. Activate program
            2. Bind vertex array object
            3. glDrawElements
            4. Unbind vertex array
    */
}
