#pragma once
#include "Instance.h"

class Animation
{
public:
	Animation();
	~Animation();

	void InitModel(const string& aTextureFileName, const Vector3<float>& aPosition, const Vector2<float> aSize);
	void InitAnimation(int amountOfFrames, int amountOfRows, float framesPerSecond = 1.f, bool loop = false);

	void Update();
	void Render();

	inline void Play();
	inline void Stop();
	inline const Instance& GetInstance();

private:
	Instance myInstance;
	Texture* myTexture;
	Vector2<float> myNormalizedFrameSize;
	float myCurrentFrameDelay;
	float myFrameDelay;
	int myAmountOfFrames;
	int myCurrentFrame_X;
	int myCurrentFrame_Y;
	int myAmountOfRows;
	int myRowLength;
	bool myShouldRender;
	bool myLoop;
};

inline void Animation::Play()
{
	myShouldRender = true;
}

inline void Animation::Stop()
{
	myShouldRender = false;
	myCurrentFrame_X = 0;
	myCurrentFrame_Y = 0;
	myCurrentFrameDelay = 0;
}

inline const Instance& Animation::GetInstance()
{
	return myInstance;
}