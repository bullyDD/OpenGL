#include "Scene.h"
#include "Shader.h"
#include "Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


float vertices[] = {
    // Position            // Color            // Texture
     0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,    0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,    1.0f, 0.0f, 1.0f,   0.0f, 1.0f
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
    mTexture1 = 0;
    mTexture2 = 0;

    // Ajoute la scene actuelle si son etat courant est actif
    mRenderer->Add(this);
}

Scene::~Scene()
{
    std::cout << "SCENE::DESTRUCTOR::CALL" << std::endl;
    delete mShader;
    //glDeleteVertexArrays(1, &mVAO);
    //glDeleteBuffers(1, &mVBO);
    //glDeleteBuffers(1, &mEBO);
    //glDeleteTextures(1, &mTexture);
    
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
            4. Activer le programme shader.

    */

    const char* vertex   = "vShaderSource.glsl";
    const char* fragment = "fShaderSource.glsl";

    mShader = new Shader(vertex, fragment);

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

        // Set vertex attributes pointer for position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Set vertex attributes pointer for color
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        // Set vertex attributes pointer for texture coordinates
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        // Unbind VBO
        glBindBuffer(GL_ARRAY_BUFFER, mVBO);

    glBindVertexArray(mVAO); 

     // Container Textures : Generate, bind and load image
    //----------------------------------------------------

    glGenTextures(1, &mTexture1);
    glBindTexture(GL_TEXTURE_2D, mTexture1);
    
     // Texture parameters : Set wrapping and filtering params
    //-------------------------------------------------------

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

     // stb_image : load image data and tell OpenGL to generate mipmaps 
    //-----------------------------------------------------------------
    
    int width, height, nrChannels;
    unsigned char* data = stbi_load("../../../textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }


    // Face Textures : Generate, bind and load image
   //----------------------------------------------------

    glGenTextures(1, &mTexture2);
    glBindTexture(GL_TEXTURE_2D, mTexture2);

    // Texture parameters : Set wrapping and filtering params
   //-------------------------------------------------------

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // stb_image : load image data and tell OpenGL to generate mipmaps 
   //-----------------------------------------------------------------

    stbi_set_flip_vertically_on_load(true);

    data = stbi_load("../../../textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);

    mShader->Use();
    this->mSate = EState::EACTIVE;

    std::string container = "containerTex";
    std::string face = "faceTex";

    mShader->SetInt(container, 0);
    mShader->SetInt(face, 1);


    return true;
}

void Scene::Update(float dt)
{
    /*
        Si @mState est EACTIVE alors :
            Update values that has to be send to the GPU
    */

    std::cout << "Dt from Scene = " << dt <<std::endl;
    std::string name = "mixValue";

    mShader->Use();
    mShader->SetFloat(name, dt);
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
   
    mShader->Use();

    // Active texture unit 0 and then bind it configuration
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mTexture1);
   
    // Again active texture unit 1 then bind its configuration before
    // drawing
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, mTexture2);
    

    glBindVertexArray(mVAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
}
