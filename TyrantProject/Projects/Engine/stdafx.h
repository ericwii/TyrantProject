#pragma once

#include "../CommonUtilities/GrowingArray.h"
#include "../CommonUtilities/StaticArray.h"
#include "../CommonUtilities/Matrix44.h"
#include "../CommonUtilities/Assert.h"
#include "../CommonUtilities/String.h"
#include "../CommonUtilities/Macro.h"

#include "Engine.h"
#include "EffectData.h"

#pragma warning (push,0)
#include <D3DX11async.h>
#include <d3dx11effect.h>
#pragma warning (pop)

#include  <comdef.h>

#if defined(DEBUG) || defined (_DEBUG)
#define PRINT_HRES_ERROR(hres, msg)			\
	_com_error err(hres);					\
	OutputDebugStringA("\n");				\
	OutputDebugStringA(msg);				\
	OutputDebugStringA("\n");				\
	OutputDebugStringA(err.ErrorMessage()); \
	OutputDebugStringA("\n");			
#else
#define PRINT_HRES_ERROR(hres, msg) (void(0))
#endif


#define GET_DIRECTX Engine::GetInstance()->GetDirectX