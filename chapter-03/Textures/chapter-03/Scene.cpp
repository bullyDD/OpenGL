#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"


float vertices[] = {
     0.5,  0.5, 0.0,
     0.5, -0.5, 0.0,
    -0.5, -0.5, 0.0,
    -0.5,  0.5, 0.0
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};

Scene::Scene(class Renderer* renderer) : mShader(nullptr), mSate(EState::EACTIVE), mRenderer(renderer)
{
    mVAO = 0;
    mVBO = 0;
    mEBO = 0;

    // Ajoute la scene actuelle si son etat courant est actif
    mRenderer->Add(this);
}

Scene::~Scene()
{
    std::cout << "SCENE::DESTRUCTOR::CALL" << std::endl;
    delete mShader;
    //glDeleteBuffers(1, &mVBO);
    //glDeleteBuffers(1, &mEBO);
    //glDeleteVertexArrays(1, &mVAO);
}

bool Scene::Initialize()
{
    /*
        Comme dans le moteur de jeu Godot, une scene est un GameObject.
        Une scene est constituée de Nodes qui représente des GameObject.

        Initialiser une scene revient pour l'instant à :
            1. Generer les buffers objects
            2. Créer des zones mémoires dans le GPU
            3. Envoyer les données dans la mémoire du GPU.
            4. Activer le programme shader
    */
    const char* vertex = "vShaderSource.glsl";
    const char* fragment = "fShaderSource.glsl";

    //Shader shader(vertex, fragment);
    mShader = new Shader(vertex, fragment);

    std::cout << "shader = " << mShader->ID << std::endl;

    if (mShader == nullptr)
    {
        this->mSate = EState::EDISABLE;
        std::cout << "SCENE::SHADER::ALLOCATION_FAILED" << std::endl;
        return false;
    }
   
    // 1. Generer les buffers objects
    glGenVertexArrays(1, &mVAO);
    glGenBuffers(1, &mVBO);
    glGenBuffers(1, &mEBO);

    std::cout << "VAO= " << mVAO << std::endl;
    std::cout << "VBO= " << mVBO << std::endl;
    std::cout << "EBO= " << mEBO << std::endl;

    // 2. Créer des zones mémoires dans le GPU
    glBindVertexArray(mVAO);

        // 3. Envoyer les données dans la mémoire du GPU.
        // 
        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Set pointer attributes for vertex position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBindVertexArray(mVAO); 

    this->mSate = EState::EACTIVE;
    mShader->Use();
    
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
   
    //mShader->Use();
    
    glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
}
