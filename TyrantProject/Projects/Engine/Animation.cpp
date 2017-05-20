#include "stdafx.h"
#include "Animation.h"
#include "Texture.h"
#include "ModelLoader.h"
#include "../Time/Time.h"


Animation::Animation() : myShouldRender(false), myFlipX(false), myFlipY(false)
{
}

Animation::~Animation()
{
}

//Public Methods

void Animation::Init(const AnimationData& someData, const Vector2<float> aSize)
{
	Model* model = ModelLoader::LoadRectangle(aSize, eEffectType::Animated, someData.textureFileName);

	myInstance.Init(model);
	myTexture = model->GetTexture("AlbedoTexture");

	DEBUG_ASSERT(myTexture != nullptr, "Failed to get texture from model");

	InitAnimation(someData.amountOfFrames, someData.amountOfRows, someData.framesPerSecond, someData.loop);
}

void Animation::Init(const AnimationData& someData, const Vector3<float>& aPosition, const Vector2<float> aSize)
{
	Model* model = ModelLoader::LoadRectangle(aSize, eEffectType::Animated, someData.textureFileName);

	CU::Matrix44<float> orientation;
	orientation.SetPosition(aPosition);
	myInstance.Init(model, orientation);

	myTexture = model->GetTexture("AlbedoTexture");

	DEBUG_ASSERT(myTexture != nullptr, "Failed to get texture from model");

	InitAnimation(someData.amountOfFrames, someData.amountOfRows, someData.framesPerSecond, someData.loop);
}

void Animation::SetPosition(Vector3<float>& aPosition)
{
	myInstance.SetPosition(aPosition);
}

void Animation::SetRotation(float someRadians)
{
	Vector3<float> position = myInstance.GetPosition();
	myInstance.SetOrientation(CU::Matrix44<float>::CreateRotateAroundZ(someRadians));
	myInstance.SetPosition(position);
}

void Animation::Update(float aDeltaTime)
{
	if (myShouldRender == false) return;

	myCurrentFrameDelay += aDeltaTime;

	if (myCurrentFrameDelay >= myFrameDelay)
	{
		myCurrentFrameDelay = 0;
		++myCurrentFrame_X;

		if (myCurrentFrame_X >= myRowLength)
		{
			myCurrentFrame_X = 0;
			++myCurrentFrame_Y;

			if (myCurrentFrame_Y >= myAmountOfRows || (myCurrentFrame_Y * myRowLength + myCurrentFrame_X) >= myAmountOfFrames)
			{
				myCurrentFrame_Y = 0;
				myShouldRender = myLoop;
			}
		}
	}
}

void Animation::Render()
{
	if (myShouldRender == true)
	{
		EffectData::animationFrameSize = myNormalizedFrameSize;
		EffectData::animationUV = Vector2<float>(myCurrentFrame_X * myNormalizedFrameSize.x, myCurrentFrame_Y * myNormalizedFrameSize.y);
		EffectData::flipX = myFlipX;
		EffectData::flipY = myFlipY;
		myInstance.Render();
	}
}



//Private Methods

void Animation::InitAnimation(int amountOfFrames, int amountOfRows, float framesPerSecond, bool loop)
{
	DEBUG_ASSERT(amountOfFrames > 0, "Amount of frames must be more than 0");
	DEBUG_ASSERT(amountOfRows > 0, "Amount of rows must be more than 0");
	DEBUG_ASSERT(framesPerSecond > 0, "Frames per second must be more than 0");
	DEBUG_ASSERT(myTexture != nullptr, "Texture must be loaded before initializing animation");

	myAmountOfFrames = amountOfFrames;
	myAmountOfRows = amountOfRows;
	myLoop = loop;
	myFrameDelay = 1.f / framesPerSecond;
	myCurrentFrameDelay = 0;
	myCurrentFrame_X = 0;
	myCurrentFrame_Y = 0;

	myRowLength = static_cast<int>(ceil(myAmountOfFrames / (float)myAmountOfRows) + 0.5f);

	if (myTexture != nullptr)
	{
		float frameWidth = myTexture->GetWidth() / myRowLength;
		float frameHeight = myTexture->GetHeight() / myAmountOfRows;

		myNormalizedFrameSize.x = frameWidth / myTexture->GetWidth();
		myNormalizedFrameSize.y = frameHeight / myTexture->GetHeight();

		EffectData::animationFrameSize = myNormalizedFrameSize;
	}

	EffectData::animationUV = Vector2<float>(myCurrentFrame_X * myNormalizedFrameSize.x, myCurrentFrame_Y * myNormalizedFrameSize.y);
}