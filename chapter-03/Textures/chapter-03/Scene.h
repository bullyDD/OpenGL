#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:

	enum class EState {
		EACTIVE,
		EDISABLE
	};

	Scene();
	~Scene();

	bool Initialize();
	void Update(float);
	void Draw();
	//void SetShader(class Shader*);

private:

	unsigned int mVAO, mVBO, mEBO;

	float *vertices = new float[
		 0.5f,  0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	];

	int *indices = new int[
		0, 1, 3,
		1, 2, 3
	];

	EState mSate;
	class Shader* mShader;
};

#endif

