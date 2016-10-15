#pragma once

struct IndexBufferWrapper
{
	IndexBufferWrapper() : indexBuffer(nullptr), byteOffset(0)
	{};

	DXGI_FORMAT indexBufferFormat;
	ID3D11Buffer* indexBuffer;
	int byteOffset;
};


struct VertexBufferWrapper
{
	VertexBufferWrapper() : vertexBuffer(nullptr), byteOffset(0), numberOfBuffers(0), startSlot(0), stride(0)
	{};

	unsigned int byteOffset;
	int numberOfBuffers;
	int startSlot;
	unsigned int stride;
	ID3D11Buffer* vertexBuffer;
};

struct VertexIndexWrapper
{
	VertexIndexWrapper() : indexData(nullptr), numberOfIndexes(0), size(0)
	{};

	DXGI_FORMAT format;
	char* indexData;
	int numberOfIndexes;
	int size;
};

struct VertexDataWrapper
{
	VertexDataWrapper() : vertexData(nullptr), numberOfOfVertexes(0), size(0), stride(0)
	{};

	int numberOfOfVertexes;
	int size;
	int stride;
	eVertexType vertexType;
	char* vertexData;
};