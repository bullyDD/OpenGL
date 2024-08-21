#include "Renderer.h"
#include <iostream>


  //---------------------------//
 //  GLOABLES VARIABLES       //
//---------------------------//

const int WIDTH = 800;
const int HEIGHT = 600;
const char* TITLE = "Learn OpenGL : Exercice 1";
const int BUFFER_SIZE = 512;

float vertices[] = {
    // T1
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,

    // T2
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f
};

// Shader: vertex and fragment shaders sources code
//--------------------------------------------------

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main(){\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
" FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
"}\0";


// OpenGL buffer objects: VAO, VBO, EBO and shaderProgram
// ------------------------------------------------------


unsigned int VAO, VBO, EBO, shaderProgram;


// PROTOTYPES : SERVICES FUNCTIONS
//---------------------------------


void frameBufferSizeCb(GLFWwindow*, int, int);

Renderer::Renderer() : mWindow(nullptr)
{
}

Renderer::Renderer(Renderer& r)
{
    r.mWindow = mWindow;
}

Renderer::~Renderer()
{
    std::cout << "RENDERER::DESTRUCTOR::CALL" << std::endl;
}

bool Renderer::Initialize()
{
    // GLFW : Initialize glfw set window hints
    //-----------------------------------------

    if (!glfwInit())
    {
        std::cout << "ERROR::GLFW:Initialization failed" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // GLFW Window: Create glfw window, check for errors and attach it to openGL.
    //---------------------------------------------------------------------------

    mWindow = glfwCreateWindow(WIDTH, HEIGHT, TITLE, NULL, NULL);
    if (mWindow == nullptr)
    {
        std::cout << "ERROR::GLFW:Failed to create a window" << std::endl;
        return false;
    }

    glfwMakeContextCurrent(mWindow);
    glfwSetFramebufferSizeCallback(mWindow, frameBufferSizeCb);

    // GLAD: Load opengl function pointers
    //-------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "ERRROR:GLAD:Failed to load" << std::endl;
        return false;
    }

    // OpenGL Data : Generate buffers object, bind configuration and copy data to the GPU
    //------------------------------------------------------------------------------------

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);         // Bind for storing configuration when rendering this object
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO);             // Allocate memory on GPU for object data
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  // Copy data on GPU memory

        // Set vertex attributes pointer for copied data related to the object position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);       // Unbind VBO
    
    glBindVertexArray(0);


    // Shader programs
    // ----------------

    int success;
    char infoLog[BUFFER_SIZE];

    // Vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, BUFFER_SIZE, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX" << infoLog << std::endl;
    }

    //fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, BUFFER_SIZE, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT" << infoLog << std::endl;
    }

    // Shader program : Through the graphic pipeline, shader program is responsible of
    // the link each input of one stage to output of anothe stage.
    //----------------------------------------------------------------------------------

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram, BUFFER_SIZE, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM" << infoLog << std::endl;
    }

    // Delete unused shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return true;
}

void Renderer::Runloop()
{
    // Keep running the renderer until user press ESC Key on keyboard
    while (!glfwWindowShouldClose(mWindow))
    {
        ProcessInput();
        Update();
        GenerateOutput();
    }
}

void Renderer::Shutdown()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glfwDestroyWindow(mWindow);
    glfwTerminate();
}

void Renderer::ProcessInput()
{
    if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(mWindow, GL_TRUE);
    }
}

void Renderer::Update()
{
}

void Renderer::GenerateOutput()
{
    // Clear color buffer
    glClearColor(0.6f, 0.6f, 0.6f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    // Render stuff
    //--------------

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);

    //GLFW swap buffers (front and back) and poll events such as keyboard action, sound etc..
    //---------------------------------------------------------------------------------------

    glfwSwapBuffers(mWindow);
    glfwPollEvents();

}


// DEFINITIONS: SERVICES 

void frameBufferSizeCb(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}