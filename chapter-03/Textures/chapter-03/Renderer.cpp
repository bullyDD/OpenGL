#include "Renderer.h"
#include "Scene.h"

Renderer::Renderer() : mWindow(nullptr)
{
}

Renderer::Renderer(Renderer& r)
{
	r.mWindow = mWindow;
	r.mScenes = mScenes;
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize()
{
	return true;
}

void Renderer::Runloop()
{
}

void Renderer::Shutdown()
{
}

void Renderer::Add(Scene* s)
{
}

void Renderer::ProcessInput()
{
}

void Renderer::Update(float)
{
}

void Renderer::Render()
{
}


