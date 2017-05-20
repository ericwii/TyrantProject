#pragma once
#include "Instance.h"

struct AnimationData
{
	AnimationData(const string& aTextureFile, int anAmountOfFrames, int anAmountOfRows)
	{
		textureFileName = aTextureFile;
		amountOfFrames = anAmountOfFrames;
		amountOfRows = anAmountOfRows;
	}

	AnimationData(const string& aTextureFile, int anAmountOfFrames, int anAmountOfRows, float aframesPerSecond)
	{
		textureFileName = aTextureFile;
		amountOfFrames = anAmountOfFrames;
		amountOfRows = anAmountOfRows;
		framesPerSecond = aframesPerSecond;
	}

	AnimationData(const string& aTextureFile, int anAmountOfFrames, int anAmountOfRows, float aframesPerSecond, bool aLoop)
	{
		textureFileName = aTextureFile;
		amountOfFrames = anAmountOfFrames;
		amountOfRows = anAmountOfRows;
		framesPerSecond = aframesPerSecond;
		loop = aLoop;
	}

	string textureFileName;
	float framesPerSecond = 30.f;
	int amountOfFrames;
	int amountOfRows;
	bool loop = false;
};

class Animation
{
public:
	Animation();
	~Animation();

	void Init(const AnimationData& someData, const Vector2<float> aSize);
	void Init(const AnimationData& someData, const Vector3<float>& aPosition, const Vector2<float> aSize);
	void SetRotation(float someRadians);
	void SetPosition(Vector3<float>& aPosition);

	void Update(float aDeltaTime);
	void Render();

	inline void Play();
	inline void Stop();
	inline const Instance& GetInstance();
	inline bool IsPlaying();

	inline void SetFlip(bool aFlipX, bool aFlipY = false);

private:
	void InitAnimation(int amountOfFrames, int amountOfRows, float framesPerSecond, bool loop);

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
	bool myFlipX;
	bool myFlipY;
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

inline void Animation::SetFlip(bool aFlipX, bool aFlipY)
{
	myFlipX = aFlipX;
	myFlipY = aFlipY;
}

inline const Instance& Animation::GetInstance()
{
	return myInstance;
}

inline bool Animation::IsPlaying()
{
	return myShouldRender;
}