#ifndef SCENE_H
#define SCENE_H

class Scene
{
public:

	enum class EState {
		EACTIVE,
		EDISABLE
	};

	Scene(class Renderer*);
	~Scene();

	bool Initialize();
	void Update(float);
	void Draw();
	//void SetShader(class Shader*);

	// Getter/Setter
	inline EState GetSceneState() const { return mSate; }

private:

	unsigned int mVAO, mVBO, mEBO, mTexture1, mTexture2;

	EState mSate;
	class Renderer* mRenderer;
	class Shader* mShader;
};

#endif

