#ifndef ENGINE_H
#define ENGINE_H

#define GLFW_INCLUDE_NONE

#include "GLFW/glfw3.h"
#include "GLAD/glad.h"

class Engine
{
public:

	Engine();
	~Engine();

	bool Initialize();
	void Runloop();
	void Shutdown();

private:

	void ProcessInput();
	void Update();
	void Render();

	GLFWwindow* mWindow;
	class Shader* mShader;
	class Texture* mcontainerTex;
	class Texture* mFaceTex;

	//===== Uniform members variables =======//
	float mixValue;
};

#endif