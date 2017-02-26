#include "stdafx.h"
#include "ModelLoader.h"



Model* ModelLoader::LoadDebugCube(float aSize)
{
	Effect* newEffect = Engine::GetInstance()->GetEffectContainer().GetEffect(eEffectType::VertexColored3D);
	if (newEffect == nullptr)
	{
		return nullptr;
	}
	
	Model* newModel = new Model();
	newModel->myVertexFormat.Allocate(2);
	newModel->myVertexFormat.Add(VertexLayout_PositionColor[0]);
	newModel->myVertexFormat.Add(VertexLayout_PositionColor[1]);



	VertexPositionColor vertexes[24] =
	{
		VertexPositionColor({ -1.0f, 1.0f, -1.0f, 1.f },{ 0.f, 1.f, 0.f, 1.f }),
		VertexPositionColor({ 1.0f, 1.0f, -1.0f, 1.f },{ 0.f, 1.f, 0.f, 1.f }),
		VertexPositionColor({ 1.0f, 1.0f, 1.0f, 1.f },{ 0.f, 1.f, 0.f, 1.f }),
		VertexPositionColor({ -1.0f, 1.0f, 1.0f, 1.f },{ 0.f, 1.f, 0.f, 1.f }),

		VertexPositionColor({ -1.0f, -1.0f, -1.0f, 1.f },{ 0.f, 1.f, 1.f, 1.f }),
		VertexPositionColor({ 1.0f, -1.0f, -1.0f, 1.f },{ 0.f, 1.f, 1.f, 1.f }),
		VertexPositionColor({ 1.0f, -1.0f, 1.0f, 1.f },{ 0.f, 1.f, 1.f, 1.f }),
		VertexPositionColor({ -1.0f, -1.0f, 1.0f, 1.f },{ 0.f, 1.f, 1.f, 1.f }),

		VertexPositionColor({ -1.0f, -1.0f, 1.0f, 1.f },{ 1.f, 0.f, 0.f, 1.f }),
		VertexPositionColor({ -1.0f, -1.0f, -1.0f, 1.f },{ 1.f, 0.f, 0.f, 1.f }),
		VertexPositionColor({ -1.0f, 1.0f, -1.0f, 1.f },{ 1.f, 0.f, 0.f, 1.f }),
		VertexPositionColor({ -1.0f, 1.0f, 1.0f, 1.f },{ 1.f, 0.f, 0.f, 1.f }),

		VertexPositionColor({ 1.0f, -1.0f, 1.0f, 1.f },{ 1.f, 0.f, 0.f, 1.f }),
		VertexPositionColor({ 1.0f, -1.0f, -1.0f, 1.f },{ 1.f, 0.f, 0.f, 1.f }),
		VertexPositionColor({ 1.0f, 1.0f, -1.0f, 1.f },{ 1.f, 0.f, 0.f, 1.f }),
		VertexPositionColor({ 1.0f, 1.0f, 1.0f, 1.f },{ 1.f, 0.f, 0.f, 1.f }),

		VertexPositionColor({ -1.0f, -1.0f, -1.0f, 1.f },{ 0.f, 0.f, 1.f, 1.f }),
		VertexPositionColor({ 1.0f, -1.0f, -1.0f, 1.f },{ 0.f, 0.f, 1.f, 1.f }),
		VertexPositionColor({ 1.0f, 1.0f, -1.0f, 1.f },{ 0.f, 0.f, 1.f, 1.f }),
		VertexPositionColor({ -1.0f, 1.0f, -1.0f, 1.f },{ 0.f, 0.f, 1.f, 1.f }),

		VertexPositionColor({ -1.0f, -1.0f, 1.0f, 1.f },{ 0.f, 0.f, 1.f, 1.f }),
		VertexPositionColor({ 1.0f, -1.0f, 1.0f, 1.f },{ 0.f, 0.f, 1.f, 1.f }),
		VertexPositionColor({ 1.0f, 1.0f, 1.0f, 1.f },{ 0.f, 0.f, 1.f, 1.f }),
		VertexPositionColor({ -1.0f, 1.0f, 1.0f, 1.f },{ 0.f, 0.f, 1.f, 1.f })
	};

	newModel->myVertexData.numberOfOfVertexes = 24;
	newModel->myVertexData.stride = sizeof(VertexPositionColor);
	newModel->myVertexData.size = sizeof(VertexPositionColor) * 24;
	newModel->myVertexData.vertexType = eVertexType::Vertex_Position_Color;
	newModel->myVertexData.vertexData = new char[newModel->myVertexData.size];
	memcpy(newModel->myVertexData.vertexData, vertexes, newModel->myVertexData.size);



	int indexes[36] =
	{
		3, 1, 0,
		2, 1, 3,

		6, 4, 5,
		7, 4, 6,

		11, 9, 8,
		10, 9, 11,

		14, 12, 13,
		15, 12, 14,

		19, 17, 16,
		18, 17, 19,

		22, 20, 21,
		23, 20, 22
	};

	newModel->myIndexData.numberOfIndexes = 36;
	newModel->myIndexData.format = DXGI_FORMAT_R32_UINT;
	newModel->myIndexData.size = sizeof(int) * 36;
	newModel->myIndexData.indexData = new char[newModel->myIndexData.size];
	memcpy(newModel->myIndexData.indexData, indexes, newModel->myIndexData.size);

	newModel->SetEffect(newEffect);

	newModel->mySurfaces.Allocate(1);
	Surface newSurface;
	newSurface.SetEffect(newEffect);
	newSurface.SetPrimologyType(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	newModel->mySurfaces.Add(newSurface);

	newModel->InitVertexBuffer();
	newModel->InitIndexBuffer();

	newModel->myIsNullObject = false;
	return newModel;
}

Model* ModelLoader::LoadDebugTriangle(float aSize)
{
	Effect* newEffect = Engine::GetInstance()->GetEffectContainer().GetEffect(eEffectType::VertexColored3D);
	if (newEffect == nullptr)
	{
		return nullptr;
	}

	Model* newModel = new Model();
	newModel->myVertexFormat.Allocate(2);
	newModel->myVertexFormat.Add(VertexLayout_PositionColor[0]);
	newModel->myVertexFormat.Add(VertexLayout_PositionColor[1]);

	float halfSize = aSize * 0.5f;
	VertexPositionColor vertexes[3] =
	{
		VertexPositionColor({ -aSize, -halfSize, 0, 1.f },{ 1.f, 0.f, 0.f, 1.f }),
		VertexPositionColor({ 0, halfSize, 0, 1.f },   { 0.f, 1.f, 0.f, 1.f }),
		VertexPositionColor({ aSize, -halfSize, 0, 1.f }, { 0.f, 0.f, 1.f, 1.f }),
	};

	newModel->myVertexData.numberOfOfVertexes = 3;
	newModel->myVertexData.stride = sizeof(VertexPositionColor);
	newModel->myVertexData.size = sizeof(VertexPositionColor) * 3;
	newModel->myVertexData.vertexType = eVertexType::Vertex_Position_Color;
	newModel->myVertexData.vertexData = new char[newModel->myVertexData.size];
	memcpy(newModel->myVertexData.vertexData, vertexes, newModel->myVertexData.size);

	unsigned int indexes[3] =
	{
		0,1,2
	};

	newModel->myIndexData.numberOfIndexes = 3;
	newModel->myIndexData.format = DXGI_FORMAT_R32_UINT;
	newModel->myIndexData.size = sizeof(int) * 3;
	newModel->myIndexData.indexData = new char[newModel->myIndexData.size];
	memcpy(newModel->myIndexData.indexData, indexes, newModel->myIndexData.size);

	newModel->SetEffect(newEffect);

	newModel->mySurfaces.Allocate(1);
	Surface newSurface;
	newSurface.SetEffect(newEffect);
	newSurface.SetPrimologyType(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	newModel->mySurfaces.Add(newSurface);

	newModel->InitVertexBuffer();
	newModel->InitIndexBuffer();

	newModel->myIsNullObject = false;
	return newModel;
}

Model* ModelLoader::LoadRectangle(const Vector2<float>& aSize, eEffectType anEffectType, const string& aTextureFile, bool aDoubleSided)
{
	Effect* newEffect = Engine::GetInstance()->GetEffectContainer().GetEffect(anEffectType);
	if (newEffect == nullptr)
	{
		return nullptr;
	}

	Model* newModel = new Model();
	newModel->myVertexFormat.Allocate(2);
	newModel->myVertexFormat.Add(VertexLayout_PositionUV[0]);
	newModel->myVertexFormat.Add(VertexLayout_PositionUV[1]);

	float halfSizeX = aSize.x * 0.5f;
	float halfSizeY = aSize.y * 0.5f;

	if (aDoubleSided == true)
	{
		VertexPositionUV vertexes[8] =
		{
			//Frontside
			VertexPositionUV({ -halfSizeX, halfSizeY, 0, 1.f }, { 0, 0}),
			VertexPositionUV({ halfSizeX, halfSizeY, 0, 1.f },	{ 0.5f, 0 }),
			VertexPositionUV({ halfSizeX, -halfSizeY, 0, 1.f }, { 0.5f, 1.f }),
			VertexPositionUV({ -halfSizeX, -halfSizeY, 0, 1.f },{ 0, 1.f }),

			//Backside
			VertexPositionUV({ halfSizeX, halfSizeY, 0, 1.f },{ 0.5f, 0 }),
			VertexPositionUV({ -halfSizeX, halfSizeY, 0, 1.f },{ 1.f, 0 }),
			VertexPositionUV({ -halfSizeX, -halfSizeY, 0, 1.f },{ 1.f, 1.f }),
			VertexPositionUV({ halfSizeX, -halfSizeY, 0, 1.f },{ 0.5f, 1.f }),
		};

		newModel->myVertexData.numberOfOfVertexes = 8;
		newModel->myVertexData.stride = sizeof(VertexPositionUV);
		newModel->myVertexData.size = sizeof(VertexPositionUV) * 8;
		newModel->myVertexData.vertexType = eVertexType::Vertex_Position_UV;
		newModel->myVertexData.vertexData = new char[newModel->myVertexData.size];
		memcpy(newModel->myVertexData.vertexData, vertexes, newModel->myVertexData.size);

		int indexes[12] =
		{
			//Frontside
			0, 1, 2,
			2, 3, 0,

			//Backside
			4, 5, 6,
			6, 7, 4
		};

		newModel->myIndexData.numberOfIndexes = 12;
		newModel->myIndexData.format = DXGI_FORMAT_R32_UINT;
		newModel->myIndexData.size = sizeof(int) * 12;
		newModel->myIndexData.indexData = new char[newModel->myIndexData.size];
		memcpy(newModel->myIndexData.indexData, indexes, newModel->myIndexData.size);
	}
	else
	{
		VertexPositionUV vertexes[4] =
		{
			VertexPositionUV({ -halfSizeX, halfSizeY, 0, 1.f },{ 0, 0 }),
			VertexPositionUV({ halfSizeX, halfSizeY, 0, 1.f },{ 1.f, 0 }),
			VertexPositionUV({ halfSizeX, -halfSizeY, 0, 1.f },{ 1.f, 1.f }),
			VertexPositionUV({ -halfSizeX, -halfSizeY, 0, 1.f },{ 0, 1.f }),
		};

		newModel->myVertexData.numberOfOfVertexes = 4;
		newModel->myVertexData.stride = sizeof(VertexPositionUV);
		newModel->myVertexData.size = sizeof(VertexPositionUV) * 4;
		newModel->myVertexData.vertexType = eVertexType::Vertex_Position_UV;
		newModel->myVertexData.vertexData = new char[newModel->myVertexData.size];
		memcpy(newModel->myVertexData.vertexData, vertexes, newModel->myVertexData.size);

		int indexes[6] =
		{
			0, 1, 2,
			2, 3, 0,
		};

		newModel->myIndexData.numberOfIndexes = 6;
		newModel->myIndexData.format = DXGI_FORMAT_R32_UINT;
		newModel->myIndexData.size = sizeof(int) * 6;
		newModel->myIndexData.indexData = new char[newModel->myIndexData.size];
		memcpy(newModel->myIndexData.indexData, indexes, newModel->myIndexData.size);
	}


	newModel->SetEffect(newEffect);

	newModel->mySurfaces.Allocate(1);
	Surface newSurface;
	newSurface.SetEffect(newEffect);

	if (anEffectType != eEffectType::UnTextured)
	{
		newSurface.AddTexture("AlbedoTexture", aTextureFile);
	}
	newSurface.SetPrimologyType(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	newModel->mySurfaces.Add(newSurface);

	newModel->InitVertexBuffer();
	newModel->InitIndexBuffer();

	newModel->myIsNullObject = false;
	return newModel;
}





//Private methods

ModelLoader::ModelLoader()
{
}

ModelLoader::~ModelLoader()
{
}