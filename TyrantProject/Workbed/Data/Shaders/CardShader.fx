#include "Utilities/ShaderSamplerStates.fx"
#include "Utilities/ShaderVariables.fx"

Texture2D HighlightTexture;

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

	output.Pos = mul(input.Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.TexUV = input.TexUV;

	return output;
}


//--------------------------------------------------
//----------------PIXEL SHADERS---------------------
//--------------------------------------------------

float4 Bloodthirsty_Pixel_Shader(PS_INPUT input) : SV_Target
{
	float4 albedoColor = AlbedoTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 highlightColor = HighlightTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 factionColor = float4(1.f, 0, 0, 0);

	return albedoColor + factionColor * highlightColor;
}

float4 Imperial_Pixel_Shader(PS_INPUT input) : SV_Target
{
	float4 albedoColor = AlbedoTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 highlightColor = HighlightTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 factionColor = float4(0, 0, 1.f, 0);

	return albedoColor + factionColor * highlightColor;
}

float4 Raider_Pixel_Shader(PS_INPUT input) : SV_Target
{
	float4 albedoColor = AlbedoTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 highlightColor = HighlightTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 factionColor = float4(0.83f, 0.71f, 0.42f, 0);

	return albedoColor + factionColor * highlightColor;
}

float4 Righteous_Pixel_Shader(PS_INPUT input) : SV_Target
{
	float4 albedoColor = AlbedoTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 highlightColor = HighlightTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 factionColor = float4(0.2f, 0.2f, 0.2f, 0);

	return albedoColor + factionColor * highlightColor;
}

float4 Xeno_Pixel_Shader(PS_INPUT input) : SV_Target
{
	float4 albedoColor = AlbedoTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 highlightColor = HighlightTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 factionColor = float4(0, 0, 0, 0);

	return albedoColor + factionColor * highlightColor;
}



float4 Action_Pixel_Shader(PS_INPUT input) : SV_Target
{
	float4 albedoColor = AlbedoTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 highlightColor = HighlightTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float4 factionColor = float4(0.3f, 0.3f, 0.3f, 0.3f);

	return albedoColor + factionColor * highlightColor;
}


//--------------------------------------------------
//----------------RENDER PASSES---------------------
//--------------------------------------------------

technique11 Render
{
	pass P0 //Bloodthirsty
	{
		SetVertexShader(CompileShader(vs_5_0, Vertex_Shader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Bloodthirsty_Pixel_Shader()));
	}

	pass P1 //Imperial
	{
		SetVertexShader(CompileShader(vs_5_0, Vertex_Shader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Imperial_Pixel_Shader()));
	}

	pass P2 //Raider
	{
		SetVertexShader(CompileShader(vs_5_0, Vertex_Shader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Raider_Pixel_Shader()));
	}

	pass P3 //Righteous
	{
		SetVertexShader(CompileShader(vs_5_0, Vertex_Shader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Righteous_Pixel_Shader()));
	}

	pass P4 //Xeno
	{
		SetVertexShader(CompileShader(vs_5_0, Vertex_Shader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Xeno_Pixel_Shader()));
	}

	pass P5 //Action
	{
		SetVertexShader(CompileShader(vs_5_0, Vertex_Shader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Action_Pixel_Shader()));
	}
}