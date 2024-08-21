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
    // First triangle 
     0.5f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f,  0.5f, 0.0f,

    // Second Triangle
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

const char* fragmentShaderSource2 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main(){\n"
" FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);\n"
"}\0";


// OpenGL buffer objects: VAO, VBO, EBO and shaderProgram
// ------------------------------------------------------


unsigned int VAO1, VAO2, VBO1, VBO2, shaderProgram1, shaderProgram2;


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

    glGenVertexArrays(1, &VAO1);
    glGenVertexArrays(1, &VAO2);

    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &VBO2);
    
    // Store configuration for Triangle 1

    glBindVertexArray(VAO1);                            
        
        glBindBuffer(GL_ARRAY_BUFFER, VBO1);             
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);       // Unbind VBO
    
    glBindVertexArray(0);

    // Store the configuration for Triangle 2

    glBindVertexArray(VAO2);                           

        glBindBuffer(GL_ARRAY_BUFFER, VBO2);             
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);  

        // Set vertex attributes pointer for copied data related to the object position
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(9 * sizeof(float)));
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

    shaderProgram1 = glCreateProgram();
    glAttachShader(shaderProgram1, vertexShader);
    glAttachShader(shaderProgram1, fragmentShader);
    glLinkProgram(shaderProgram1);
    
    glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram1, BUFFER_SIZE, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM" << infoLog << std::endl;
    }

    //fragment shader for second triangle
    unsigned int fragmentShader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader2, 1, &fragmentShaderSource2, NULL);
    glCompileShader(fragmentShader2);

    glGetShaderiv(fragmentShader2, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader2, BUFFER_SIZE, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT" << infoLog << std::endl;
    }

    shaderProgram2 = glCreateProgram();
    glAttachShader(shaderProgram2, vertexShader);
    glAttachShader(shaderProgram2, fragmentShader2);
    glLinkProgram(shaderProgram2);

    glGetProgramiv(shaderProgram2, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shaderProgram2, BUFFER_SIZE, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM" << infoLog << std::endl;
    }

    // Delete unused shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(fragmentShader2);

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
    glDeleteVertexArrays(1, &VAO1);
    glDeleteVertexArrays(1, &VAO2);

    glDeleteBuffers(1, &VBO1);
    glDeleteBuffers(1, &VBO2);

    glDeleteProgram(shaderProgram1);
    glDeleteProgram(shaderProgram2);

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


    // Draw Triangle 1
    
    glUseProgram(shaderProgram1);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(VAO1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);

   
    // Draw Triangle 2

    glUseProgram(shaderProgram2);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(VAO2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
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