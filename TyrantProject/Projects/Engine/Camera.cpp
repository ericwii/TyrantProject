#include "stdafx.h"
#include "Camera.h"


Camera::Camera() : myNearPlane(0.001f), myFarPlane(1000.f)
{
}

Camera::~Camera()
{
}



void Camera::Init(const Vector3<float>& aPosition, int aScreenWidth, int aScreenHeight, float aFarPlane, float aNearPlane)
{
	myNearPlane = aNearPlane;
	myFarPlane = aFarPlane;
	float ratio = static_cast<float>(aScreenWidth) / aScreenHeight;
	CreateProjectionMatrix(aNearPlane, aFarPlane, ratio, PI_2);

	myOrientation.SetPosition(aPosition);
}

void Camera::Init(const Vector4<float>& aPosition, int aScreenWidth, int aScreenHeight, float aFarPlane, float aNearPlane)
{
	myNearPlane = aNearPlane;
	myFarPlane = aFarPlane;
	float ratio = static_cast<float>(aScreenWidth) / aScreenHeight;
	CreateProjectionMatrix(aNearPlane, aFarPlane, ratio, PI_2);

	myOrientation.SetTranslation(aPosition);
}

void Camera::SetScreenSize(int aScreenWidth, int aScreenHeight)
{
	float ratio = static_cast<float>(aScreenWidth) / aScreenHeight;
	CreateProjectionMatrix(myNearPlane, myFarPlane, ratio, PI_2);
}

void Camera::MoveForward(const float aSpeed, const float aDeltatime)
{
	Vector4<float> move(myOrientation.GetTranslation());

	move += (myOrientation.GetForward() * aSpeed) * aDeltatime;
	myOrientation.matrix[12] = move.x;
	myOrientation.matrix[13] = move.y;
	myOrientation.matrix[14] = move.z;
}

void Camera::MoveBack(const float aSpeed, const float aDeltatime)
{
	Vector4<float> move(myOrientation.GetTranslation());

	move -= (myOrientation.GetForward() * aSpeed) * aDeltatime;
	myOrientation.matrix[12] = move.x;
	myOrientation.matrix[13] = move.y;
	myOrientation.matrix[14] = move.z;
}

void Camera::MoveRight(const float aSpeed, const float aDeltatime)
{
	Vector4<float> move(myOrientation.GetTranslation());

	move -= (myOrientation.GetRight() * aSpeed) * aDeltatime;
	myOrientation.matrix[12] = move.x;
	myOrientation.matrix[13] = move.y;
	myOrientation.matrix[14] = move.z;
}

void Camera::MoveLeft(const float aSpeed, const float aDeltatime)
{
	Vector4<float> move(myOrientation.GetTranslation());

	move += (myOrientation.GetRight() * aSpeed) * aDeltatime;
	myOrientation.matrix[12] = move.x;
	myOrientation.matrix[13] = move.y;
	myOrientation.matrix[14] = move.z;
}

void Camera::MoveUp(const float aSpeed, const float aDeltatime)
{
	Vector4<float> move(myOrientation.GetTranslation());

	move += (myOrientation.GetUp() * aSpeed) * aDeltatime;
	myOrientation.matrix[12] = move.x;
	myOrientation.matrix[13] = move.y;
	myOrientation.matrix[14] = move.z;
}

void Camera::MoveDown(const float aSpeed, const float aDeltatime)
{
	Vector4<float> move(myOrientation.GetTranslation());

	move -= (myOrientation.GetUp() * aSpeed) * aDeltatime;
	myOrientation.matrix[12] = move.x;
	myOrientation.matrix[13] = move.y;
	myOrientation.matrix[14] = move.z;
}

void Camera::RotateX(const float anAngle)
{
	Vector4<float> oldPos = myOrientation.GetTranslation();
	myOrientation.SetTranslation(Vector4<float>(0, 0, 0, 1.f));
	myOrientation = CU::Matrix44<float>::CreateRotateAroundX(anAngle) * myOrientation;
	myOrientation.SetTranslation(oldPos);
}

void Camera::RotateY(const float anAngle)
{
	Vector4<float> oldPos = myOrientation.GetTranslation();
	myOrientation.SetTranslation(Vector4<float>(0, 0, 0, 1.f));
	myOrientation = CU::Matrix44<float>::CreateRotateAroundY(anAngle) * myOrientation;
	myOrientation.SetTranslation(oldPos);
}

void Camera::RotateZ(const float anAngle)
{
	Vector4<float> oldPos = myOrientation.GetTranslation();
	myOrientation.SetTranslation(Vector4<float>(0, 0, 0, 1.f));
	myOrientation = CU::Matrix44<float>::CreateRotateAroundZ(anAngle) * myOrientation;
	myOrientation.SetTranslation(oldPos);
}

void Camera::SetPosition(const Vector4<float>& aPosition)
{
	myOrientation.SetTranslation(aPosition);
}

void Camera::SetPosition(const Vector3<float>& aPosition)
{
	myOrientation.SetPosition(aPosition);
}

Vector2<float> Camera::ToScreenPosition(const Vector3<float>& aPosition)
{
	Vector4<float> finalPosition = Vector4<float>(aPosition, 1.f) * myOrientation.GetInverse();
	finalPosition *= myProjection;
	finalPosition /= finalPosition.w;

	return finalPosition;
}

//Private methods

void Camera::CreateProjectionMatrix(const float aNearPlaneZ, const float aFarPlaneZ, const float anAspectRatio, const float aFOVAngle)
{
	float sinFov = sin(aFOVAngle * 0.5f);
	float cosFov = cos(aFOVAngle * 0.5f);
	
	float height = cosFov / sinFov;
	float width = height / anAspectRatio;

	float scaling = aFarPlaneZ / (aFarPlaneZ - aNearPlaneZ);

	myProjection.matrix[0] = width;
	myProjection.matrix[1] = 0;
	myProjection.matrix[2] = 0;
	myProjection.matrix[3] = 0;

	myProjection.matrix[4] = 0;
	myProjection.matrix[5] = height;
	myProjection.matrix[6] = 0;
	myProjection.matrix[7] = 0;

	myProjection.matrix[8] = 0;
	myProjection.matrix[9] = 0;
	myProjection.matrix[10] = scaling;
	myProjection.matrix[11] = 1.f;

	myProjection.matrix[12] = 0;
	myProjection.matrix[13] = 0;
	myProjection.matrix[14] = -scaling * aNearPlaneZ;
	myProjection.matrix[15] = 0;
}