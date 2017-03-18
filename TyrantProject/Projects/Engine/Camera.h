#pragma once
#include "../CommonUtilities/Matrix44.h"

class Camera
{
public:
	Camera();
	~Camera();

	void Init(const Vector3<float>& aPosition, int aScreenWidth, int aScreenHeight, float aFarPlane = 1000.f, float aNearPlane = 0.01f);
	void Init(const Vector4<float>& aPosition, int aScreenWidth, int aScreenHeight, float aFarPlane = 1000.f, float aNearPlane = 0.01f);

	void SetScreenSize(int aScreenWidth, int aScreenHeight);

	void MoveForward(const float aSpeed, const float aDeltatime);
	void MoveBack(const float aSpeed, const float aDeltatime);
	void MoveRight(const float aSpeed, const float aDeltatime);
	void MoveLeft(const float aSpeed, const float aDeltatime);
	void MoveUp(const float aSpeed, const float aDeltatime); 
	void MoveDown(const float aSpeed, const float aDeltatime);
	void RotateX(const float anAngle);
	void RotateY(const float anAngle);
	void RotateZ(const float anAngle);

	void SetPosition(const Vector4<float>& aPosition);
	void SetPosition(const Vector3<float>& aPosition);

	Vector2<float> ToScreenPosition(const Vector3<float>& aPosition);

	inline const CU::Matrix44<float>& GetOrientation() const;
	inline const CU::Matrix44<float>& GetProjection() const;
	inline const CU::Matrix44<float> GetInverse() const;

private:
	void CreateProjectionMatrix(const float aNearPlaneZ, const float aFarPlaneZ, const float anAspectRatio, const float aFOVAngle);

	CU::Matrix44<float> myProjection;
	CU::Matrix44<float> myOrientation;
	float myNearPlane;
	float myFarPlane;
};


inline const CU::Matrix44<float>& Camera::GetOrientation() const
{
	return myOrientation;
}

inline const CU::Matrix44<float>& Camera::GetProjection() const
{
	return myProjection;
}

inline const CU::Matrix44<float> Camera::GetInverse() const
{
	return myOrientation.GetInverse();
}