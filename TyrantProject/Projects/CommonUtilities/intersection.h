#pragma once
#include "plane.h"

#pragma warning (push)
#pragma warning (disable: 4505)

namespace Collider
{
	class Sphere
	{
	public:
		Sphere(): radius(0),radiusSquared(0) {};

		Sphere(Vector3<float> aCenterposition, float aRadius): centerPosition(aCenterposition), radius(aRadius)
		{
			radiusSquared = aRadius * aRadius;
		}

		~Sphere() {};

		Vector3<float> centerPosition;

		inline float GetRadius() const { return radius; }
		inline float GetRadiusSquared() const { return radiusSquared; }

		void AddRadius(float aRadius)
		{
			radius += aRadius;
			radiusSquared = aRadius * aRadius;
		}
		void SetRadius(float aRadius)
		{
			radius = aRadius;
			radiusSquared = aRadius * aRadius;
		}

	private:
		float radius;
		float radiusSquared;
	};

	class AABB
	{
	public:
		AABB() {};

		AABB(const Vector3<float>& aCenterPosition, const Vector3<float>& aExtents) : centerPosition(aCenterPosition), extents(aExtents)
		{ };

		AABB(Vector3<float> aCenterPosition, Vector3<float> aExtents) : centerPosition(aCenterPosition), extents(aExtents)
		{ };

		~AABB() {};

		inline float GetWidth() { return extents.x * 2.f; }
		inline float GetHeight() { return extents.y * 2.f; }
		inline float GetDepth() { return extents.z * 2.f; }

		Vector3<float> centerPosition;
		Vector3<float> extents;
	private:
		Vector3<float> minPos;
		Vector3<float> maxPos;
	};

	class LineSegment3D
	{
	public:
		LineSegment3D() {};

		LineSegment3D(const Vector3<float>& aStartPosition, const Vector3<float>& anEndPosition) : startPosition(aStartPosition), endPosition(anEndPosition)
		{ };

		LineSegment3D(Vector3<float> aStartPosition, Vector3<float> anEndPosition) : startPosition(aStartPosition), endPosition(anEndPosition)
		{ };

		LineSegment3D(const Vector3<float>& aStartPosition, const Vector3<float>& aDirection, float aLength) : startPosition(aStartPosition)
		{
			endPosition = aStartPosition + aDirection.GetNormalized() * aLength;
		}

		LineSegment3D(Vector3<float> aStartPosition, Vector3<float> aDirection, float aLength) : startPosition(aStartPosition)
		{
			aDirection.Normalize();
			endPosition = aStartPosition + aDirection * aLength;
		}

		~LineSegment3D() {};

		Vector3<float> GetNormalizedDirection() const
		{
			Vector3<float> direction(endPosition - startPosition);
			direction.Normalize();

			return direction;
		}

		inline float GetLength() const
		{
			return (startPosition - endPosition).Length();
		}

		Vector3<float> startPosition;
		Vector3<float> endPosition;
	};

	class LineSegment2D
	{
	public:
		LineSegment2D() {};

		LineSegment2D(const Vector2<float>& aStartPoint, const Vector2<float>& anEndPoint) : startPoint(aStartPoint), endPoint(anEndPoint)
		{ };

		LineSegment2D(Vector2<float> aStartPoint, Vector2<float> anEndPoint) : startPoint(aStartPoint), endPoint(anEndPoint)
		{ };

		~LineSegment2D() {};

		Vector2<float> GetNormalizedDirection() const
		{
			Vector2<float> direction(endPoint - startPoint);
			direction.Normalize();
			return direction;
		}

		float GetLength() const
		{
			return (endPoint - startPoint).Length();
		}

		float GetLowestX() const
		{
			return (endPoint.x > startPoint.x ? startPoint.x : endPoint.x);
		}
		float GetLowestY() const
		{
			return (endPoint.y > startPoint.y ? startPoint.y : endPoint.y);
		}

		float GetHighestX() const
		{
			return (endPoint.x > startPoint.x ? endPoint.x : startPoint.x);
		}
		float GetHighestY() const
		{
			return (endPoint.y > startPoint.y ? endPoint.y : startPoint.y);
		}

		Vector2<float> startPoint;
		Vector2<float> endPoint;
	};

	class Fov90Frustrum
	{
	public:
		Fov90Frustrum(float aNearZ, float aFarZ)
		{
			myNearZ = aNearZ;
			myFarZ = aFarZ;

			myNearPlane.InitWithPointAndNormal(Vector3<float>(0, 0, myNearZ), Vector3<float>(0, 0, 1));
			myFarPlane.InitWithPointAndNormal(Vector3<float>(0, 0, myFarZ), Vector3<float>(0, 0, -1));

			myLeftPlane.InitWithPointAndNormal(Vector3<float>(-myNearZ, -myNearZ, myNearZ), Vector3<float>(1, 0, 1));
			myRightPlane.InitWithPointAndNormal(Vector3<float>(myNearZ, myNearZ, myNearZ), Vector3<float>(-1, 0, 1));

			myTopPlane.InitWithPointAndNormal(Vector3<float>(0, -myNearZ, myNearZ), Vector3<float>(0, 1, 1));
			myBottomPlane.InitWithPointAndNormal(Vector3<float>(0, -myNearZ, myNearZ), Vector3<float>(0, -1, 1));
		};
		~Fov90Frustrum() {};

		CommonUtilities::Plane<float> myNearPlane;
		CommonUtilities::Plane<float> myFarPlane;
		CommonUtilities::Plane<float> myLeftPlane;
		CommonUtilities::Plane<float> myRightPlane;
		CommonUtilities::Plane<float> myBottomPlane;
		CommonUtilities::Plane<float> myTopPlane;
		float myNearZ;
		float myFarZ;
	};

	class Hitbox2D
	{
		public:
			enum eHitbox2DCorner
			{
				Top_Left,
				Top_Right,
				Bottom_Left,
				Bottom_Right
			};

			Hitbox2D() : x(0), y(0), width(0), height(0)
			{};

			Hitbox2D(Vector2<float> aPosition, Vector2<float> aSize)
			{
				x = aPosition.x;
				y = aPosition.y;
				width = aSize.x;
				height = aSize.y;
			}

			Hitbox2D(float aX, float aY, float aWidth, float aHeight)
			{
				x = aX;
				y = aY;
				width = aWidth;
				height = aHeight;
			}

			Vector2<float> GetPosition() const
			{
				return Vector2<float>(x, y);
			}

			Vector2<float> GetSize() const
			{
				return Vector2<float>(width, height);
			}

			Vector2<float> GetCorner(eHitbox2DCorner aCorner) const
			{
				switch (aCorner)
				{
					case(Top_Left):
					{
						return Vector2<float>(x, y);
					}
					case(Top_Right) :
					{
						return Vector2<float>(x + width, y);
					}
					case(Bottom_Left) :
					{
						return Vector2<float>(x, y + height);
					}
					case(Bottom_Right) :
					{
						return Vector2<float>(x + width, y + height);
					}
					default:
					{
						return Vector2<float>(x, y);
					}
				}
			}

			Vector2<float> GetCenter()
			{
				return Vector2<float>(x + width * 0.5f, y + height * 0.5f);
			}

			void SetPosition(Vector2<float> aPosition)
			{
				x = aPosition.x;
				y = aPosition.y;
			}

			void SetPosition(float aX, float aY)
			{
				x = aX;
				y = aY;
			}

			void SetSize(Vector2<float> aSize)
			{
				width = aSize.x;
				height = aSize.y;
			}

			void SetSize(float aX, float aY)
			{
				width = aX;
				height = aY;
			}

			bool Inside(const Vector2<float>& aPoint) const
			{
				if (aPoint.x > x && aPoint.x < x + width)
				{
					return aPoint.y > y && aPoint.y < y + height;
				}
				return false;
			}

			bool Colliding(Hitbox2D aHitbox) const
			{
				if (aHitbox.x > x - width && aHitbox.x < x + width)
				{
					return aHitbox.y > y - height && aHitbox.y < y + height;
				}
				return false;
			}
			
			struct { float x, y, width, height; };
	};
}

using namespace Collider;

namespace Collision
{
	static bool PointInsideSphere(const Sphere& aSphere, Vector3<float> aPoint)
	{
		Vector3<float> DeltaPos(aPoint - aSphere.centerPosition);

		if (DeltaPos.Length2() <= aSphere.GetRadiusSquared())
		{
			return true;
		}
		return false;
	}

	static bool PointInsideAABB(const AABB& aBox, Vector3<float> aPoint)
	{
		Vector3<float> DeltaPos(aPoint - aBox.centerPosition);

		if (DeltaPos.x > -aBox.extents.x && DeltaPos.x < aBox.extents.x)
		{
			if (DeltaPos.y > -aBox.extents.y && DeltaPos.y < aBox.extents.y)
			{
				if (DeltaPos.z > -aBox.extents.z && DeltaPos.z < aBox.extents.z)
				{
					return true;
				}
			}
		}
		return false;
	}

	static bool LineVsSphere(const LineSegment3D& aLine, const Sphere& aSphere, Vector3<float>& aPoint)
	{
		Vector3<float> DeltaPos(aSphere.centerPosition - aLine.startPosition);

		Vector3<float> lineDirection = aLine.endPosition - aLine.startPosition;
		lineDirection.Normalize();
	
		float DotProduct = DeltaPos.Dot(lineDirection);
		float lineLength = aLine.GetLength();

		if (DotProduct > lineLength)
		{
			DotProduct = lineLength;
		}
		if (DotProduct < 0)
		{
			DotProduct = 0;
		}

		Vector3<float> closestPoint(aLine.startPosition + lineDirection * DotProduct);
		closestPoint -= aSphere.centerPosition;
		aPoint = closestPoint;

		if (closestPoint.Length2() <= aSphere.GetRadiusSquared())
		{
			return true;
		}
		return false;
	}

	static bool LineVsAABB(const LineSegment3D& aLine, const AABB& aBox, Vector3<float>& aPoint)
	{
		Vector3<float> DeltaPos(aBox.centerPosition - aLine.startPosition);

		Vector3<float> lineDirection = aLine.GetNormalizedDirection();
		float lineLength = aLine.GetLength();

		float DotProduct = DeltaPos.Dot(lineDirection);

		if (DotProduct > lineLength)
		{
			DotProduct = lineLength;
		}
		if (DotProduct < 0)
		{
			DotProduct = 0;
		}

		Vector3<float> closestPoint(aLine.startPosition + lineDirection * DotProduct);
		aPoint = closestPoint;

		return PointInsideAABB(aBox, closestPoint);
	}

	static bool SwepthSphereVsSphere(const LineSegment3D& aLine, float aRadius, Sphere aSphere)
	{
		aSphere.AddRadius(aRadius);

		return LineVsSphere(aLine, aSphere,Vector3<float>());
	}

	static bool SwepthSphereVsAABB(const LineSegment3D& aLine, float aRadius, const AABB& aBox)
	{
		Vector3<float> DeltaPos(aBox.centerPosition - aLine.startPosition);

		Vector3<float> lineDirection = aLine.GetNormalizedDirection();

		float lineLength = aLine.GetLength();
		float DotProduct = DeltaPos.Dot(lineDirection);

		if (DotProduct > lineLength)
		{
			DotProduct = lineLength;
		}
		if (DotProduct < 0)
		{
			DotProduct = 0;
		}

		Vector3<float> closestPoint(aLine.startPosition + lineDirection * DotProduct);
		closestPoint -= aBox.centerPosition;

		if ((closestPoint.x - aRadius) < aBox.extents.x 
			&& (closestPoint.x + aRadius) > -aBox.extents.x)
		{
			if ((closestPoint.y - aRadius) < aBox.extents.y
				&& (closestPoint.y + aRadius) > -aBox.extents.y)
			{ 
				if ((closestPoint.z - aRadius) < aBox.extents.z
					&& (closestPoint.z + aRadius) > -aBox.extents.z)
				{
					return true;
				}
			}
		}
		return false;
	}

	static bool SphereVsFrustrum(const Sphere& aSphere, const Fov90Frustrum& aFrustum)
	{
		Vector3<float> sphereCenter = aSphere.centerPosition;
		float sphereRadius = aSphere.GetRadius();

		if (aFrustum.myLeftPlane.Inside(Vector3<float>(sphereCenter.x + sphereRadius, sphereCenter.y, sphereCenter.z))
	     && aFrustum.myRightPlane.Inside(Vector3<float>(sphereCenter.x - sphereRadius, sphereCenter.y, sphereCenter.z)))
		{
			if (aFrustum.myTopPlane.Inside(Vector3<float>(sphereCenter.x, sphereCenter.y + sphereRadius, sphereCenter.z))
		     && aFrustum.myBottomPlane.Inside(Vector3<float>(sphereCenter.x, sphereCenter.y - sphereRadius, sphereCenter.z)))
			{
				if (aFrustum.myNearPlane.Inside(Vector3<float>(sphereCenter.x, sphereCenter.y, sphereCenter.z + sphereRadius))
				 && aFrustum.myFarPlane.Inside(Vector3<float>(sphereCenter.x, sphereCenter.y, sphereCenter.z - sphereRadius)))
				{
					return true;
				}
			}
		}

		return false;
	}

	static bool LineVsLine(const LineSegment2D& aFirstLine, const LineSegment2D& aSecondLine, Vector3<float>& aIntersectionPoint)
	{
		aIntersectionPoint; //Calculate intersection point sometime in the future

		Vector2<float> firstLineDelta(aFirstLine.endPoint - aFirstLine.startPoint);
		Vector2<float> secondLineDelta(aSecondLine.endPoint - aSecondLine.startPoint);

		float denom = (secondLineDelta.y * firstLineDelta.x) - (secondLineDelta.x * firstLineDelta.y);

		if (denom < 0.001f)
		{
			if (aSecondLine.GetHighestX() >= aFirstLine.GetLowestX() && aSecondLine.GetLowestX() <= aFirstLine.GetHighestX())
			{
				if (aSecondLine.GetHighestY() >= aFirstLine.GetHighestY() && aSecondLine.GetLowestY() <= aFirstLine.GetHighestY())
				{
					return true;
				}
			}
			return false;
		}
		else
		{
			float denom_A = secondLineDelta.x * (aFirstLine.startPoint.y - aSecondLine.startPoint.y) -
							secondLineDelta.y * (aFirstLine.startPoint.x - aSecondLine.startPoint.x);

			float denom_B = firstLineDelta.x * (aFirstLine.startPoint.y - aSecondLine.startPoint.y) -
							firstLineDelta.y * (aFirstLine.startPoint.y - aSecondLine.startPoint.y);

			if (denom_A >= 0 && denom_A <= 1 && denom_B >= 0 && denom_B <= 1)
			{
				return true;
			}
		}

		return false;
	}

	static bool PointVsAABB(Vector2<float>& aPoint, Vector4<float> aRectangle)
	{
		/*if (aPoint.x < aRectangle.x + aRectangle.z &&
			aPoint.x > aRectangle.x &&
			aPoint.y < aRectangle.y + aRectangle.w &&
			aPoint.y > aRectangle.y)
		{
			return true;
		}

		return false;*/

		if (aPoint.x < aRectangle.x) return false;
		if (aPoint.y < aRectangle.y) return false;
		if (aPoint.x >= aRectangle.x + aRectangle.z) return false;
		if (aPoint.y >= aRectangle.y + aRectangle.w) return false;

		return true;
	}
}

#pragma warning (pop)