#include "stdafx.h"
#include "Effect.h"


#if defined( DEBUG ) || defined( _DEBUG )
#pragma comment (lib, "../LibraryFiles/DirectX/Effects11_debug.lib")
#else
#pragma comment (lib, "../LibraryFiles/DirectX/Effects11_release.lib")
#endif


Effect::Effect() : myTechnique(nullptr), myEffect(nullptr), myProjectionMatrixVariable(nullptr),
myViewMatrixVariable(nullptr), myWorldMatrixVariable(nullptr)
{
}

Effect::~Effect()
{
	if (myEffect != nullptr)
	{
		myEffect->Release();
	}
}

bool Effect::Init(const string& anEffectFile)
{
	myFileName = anEffectFile;
	HRESULT hr;
	unsigned int dwShaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;

#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3D10_SHADER_DEBUG;
	dwShaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
	dwShaderFlags |= D3D10_SHADER_NO_PRESHADER;
#endif

	ID3D10Blob* compiledShader = 0;
	ID3D10Blob* compilationMsgs = 0;
	
	hr = D3DX11CompileFromFile(anEffectFile.c_str(), 0, 0, 0, "fx_5_0", dwShaderFlags, 0, 0, &compiledShader, &compilationMsgs, 0);
	if (FAILED(hr))
	{
		stringLong error = "Failed to compile Effect file: '";
		error += anEffectFile.c_str();
		error += "'";
		PRINT_HRES_ERROR(hr, error.c_str());
		if (compilationMsgs != 0)
		{
			OutputDebugStringA(static_cast<char*>(compilationMsgs->GetBufferPointer()));
		}
		else
		{
			OutputDebugStringA("No info on compilation errors!\n");
		}
		DEBUG_ASSERT(false, error.c_str());
		return false;
	}
	if (compilationMsgs != nullptr)
	{
		compilationMsgs->Release();
	}

	ID3D11Device* device = Engine::GetInstance()->GetDirectX().GetDevice();

	if (device == nullptr)
	{
		DEBUG_ASSERT(false, "Failed to get device from engine");
	}

	hr = D3DX11CreateEffectFromMemory(compiledShader->GetBufferPointer(),
		compiledShader->GetBufferSize(),
		NULL,
		device,
		&myEffect);

	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to create effect from memory.");
		DEBUG_ASSERT(false, "Failed to create effect from memory.");
		return false;
	}

	// Obtain the technique
	myTechnique = myEffect->GetTechniqueByName("Render");
	if (myTechnique->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Technique in effect is not valid");
	}
	

	// Obtain the variables
	myWorldMatrixVariable = myEffect->GetVariableByName("World")->AsMatrix();
	if (myWorldMatrixVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "World matrix in effect is not valid");
	}

	myViewMatrixVariable = myEffect->GetVariableByName("View")->AsMatrix();
	if (myViewMatrixVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "View matrix in effect is not valid");
	}

	myProjectionMatrixVariable = myEffect->GetVariableByName("Projection")->AsMatrix();
	if (myProjectionMatrixVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Projection matrix in effect is not valid");
	}

	myAlphaVariable = myEffect->GetVariableByName("Alpha")->AsScalar();
	if (myAlphaVariable->IsValid() == false)
	{
		DEBUG_ASSERT(false, "Alpha in effect is not valid");
	}

	return true;
}

void Effect::Update()
{
	HRESULT hr;

	hr = myWorldMatrixVariable->SetMatrix(static_cast<float*>(&EffectData::worldMatrix.matrix[0]));
	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to set world matrix for shader");
	}

	hr = myViewMatrixVariable->SetMatrix(static_cast<float*>(&EffectData::viewMatrix.matrix[0]));
	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to set view matrix for shader");
	}

	hr = myProjectionMatrixVariable->SetMatrix(static_cast<float*>(&EffectData::projectionMatrix.matrix[0]));
	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to set projection matrix for shader");
	}

	hr = myAlphaVariable->SetFloat(EffectData::alpha);
	if (FAILED(hr))
	{
		PRINT_HRES_ERROR(hr, "Failed to set alpha for shader");
	}
}

