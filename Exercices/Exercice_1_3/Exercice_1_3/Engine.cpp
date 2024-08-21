#include "Engine.h"
#include "Shader.h"
#include "Texture.h"

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include <iostream>

//=========== GLOBALES VARIABLES ===================//

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "Learn openGL - Exercise 1.3";

float vertices[] = {
    // Position            // Texture coordinates   
     0.5f,  0.5f, 0.0f,    1.0f, 1.0f,
     0.5f, -0.5f, 0.0f,    1.0f, 0.0f,
    -0.5f, -0.5f, 0.0f,    0.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,    0.0f, 1.0f
};

unsigned int indices[] = {
    0, 1, 3,
    1, 2, 3
};


//============ OpenGL BUFFER OBJECTS =================//

unsigned int VAO, VBO, EBO;


//============ SERVICES FUNCTIONS PROTOTYPES =========//

void framebufferSizeCb(GLFWwindow*, int, int);

//============ ENGINE CLASS DEFINTION ===============//

Engine::Engine() : 
    mWindow(nullptr), 
    mShader(nullptr), 
    mcontainerTex(nullptr),
    mFaceTex(nullptr),
    mixValue(0.0f)
{
}

Engine::~Engine()
{
    delete mShader; 
    delete mcontainerTex;
    delete mFaceTex;

    std::cout << "ENGINE::DESTRUCTOR::CALL" << std::endl;
}

bool Engine::Initialize()
{
     //glfw : Initialize glfw and set window Hint
    //--------------------------------------------

    if (!glfwInit())
    {
        std::cout << "ERROR::GLFW::Failed to initialize" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

     //glfw Window : Create a window
    //-------------------------------

    mWindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (mWindow == nullptr)
    {
        std::cout << "ERROR::GLFW::Failed to create window" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, framebufferSizeCb);


     // GLAD : Load openGL pointer functions
    //---------------------------------------

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERROR::GLAD::Failed loading opengl function" << std::endl;
        return false;
    }

     // Shader : Load shader program code source, compile and link them
    //-----------------------------------------------------------------

    mShader = new Shader("vShader.glsl", "fShader.glsl");

    if (mShader == nullptr)
    {
        std::cout << "ERROR::SHADER::Allocation failed" << std::endl;
    }

    // OpenGL Buffers objects
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        //EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Set position attributes pointer
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Set texture coordinates attributes pointer
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

     //load texture data
    //---------------------
    mcontainerTex = new Texture("./textures/container.jpg", "jpg");
    mFaceTex      = new Texture("./textures/awesomeface.png", "png");

    mShader->Use();

    // Assign texture units
    mShader->SetInt("containerTex", 0);
    mShader->SetInt("faceTex", 1);

    return true;
}

void Engine::Runloop()
{
    while (!glfwWindowShouldClose(mWindow))
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Engine::Shutdown()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void Engine::ProcessInput()
{
    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(mWindow, GL_TRUE);
    }

    if (glfwGetKey(mWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        mixValue -= 0.0001f;
        if (mixValue < 0.0f) { mixValue = 0.0f; }
    }

    if (glfwGetKey(mWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        mixValue += 0.0001f;
        if (mixValue > 1.0f) { mixValue = 1.0f; }
    }
}

void Engine::Update()
{
    // Matrice transformation happens from bottom to top
    glm::mat4 trans = glm::mat4(1.0f);
            
    float scaleAmount = static_cast<float>(sin(glfwGetTime()));
    trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
    trans = glm::rotate(trans, (float)glm::radians(glfwGetTime()), glm::vec3(0.0f, 0.0f, 1.0f));
    trans = glm::scale(trans, glm::vec3(scaleAmount, scaleAmount, scaleAmount));

    mShader->Use();

    mShader->SetMat4("transform", trans);
    mShader->SetFloat("mixValue", mixValue);
}

void Engine::Render()
{
    //Clear Color buffer with light grey color
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Rendering stuff
    mcontainerTex->Activate(GL_TEXTURE0);    
    mFaceTex->Activate(GL_TEXTURE1);

    mShader->Use();
    glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Swap and poll events
    glfwSwapBuffers(mWindow);
    glfwPollEvents();

}

//=================== SERVICES FUNCTIONS DEFINITIONS ==============//

void framebufferSizeCb(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
