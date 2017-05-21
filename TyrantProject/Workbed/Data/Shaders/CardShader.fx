#include "Utilities/ShaderSamplerStates.fx"
#include "Utilities/ShaderVariables.fx"


struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 TexUV : TEXCOORD;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 TexUV : TEXTURE;
};


PS_INPUT Vertex_Shader(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = input.Pos;
	output.Pos.xy *= float2(1 - World._m32, 1 - World._m32);
	output.Pos = mul(output.Pos, World);
	output.Pos.z = 0;

	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.TexUV = input.TexUV;

	return output;
}


//--------------------------------------------------
//----------------PIXEL SHADERS---------------------
//--------------------------------------------------

float4 Normal_Pixel_Shader(PS_INPUT input) : SV_Target
{
	float4 albedoColor = AlbedoTexture.Sample(sampleLinear_Wrap, input.TexUV);
	albedoColor.w = Alpha;

	return albedoColor;
}

float4 Foil_Pixel_Shader(PS_INPUT input) : SV_Target
{
	float4 albedoColor = AlbedoTexture.Sample(sampleLinear_Wrap, input.TexUV);
	albedoColor.w = Alpha;

	return albedoColor;
}


//--------------------------------------------------
//----------------RENDER PASSES---------------------
//--------------------------------------------------

technique11 Render
{
	pass P0 //Normal
	{
		SetVertexShader(CompileShader(vs_5_0, Vertex_Shader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Normal_Pixel_Shader()));
	}

	pass P1 //Foil
	{
		SetVertexShader(CompileShader(vs_5_0, Vertex_Shader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Foil_Pixel_Shader()));
	}

}