#include "Utilities/ShaderSamplerStates.fx"
#include "Utilities/ShaderVariables.fx"

float2 FrameSize;
float2 FrameUV;
bool FlipX;
bool FlipY;

struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 TexUV : TEXCOORD;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 TexUV : TEXCOORD;
};


PS_INPUT Vertex_Shader(VS_INPUT input)
{
	PS_INPUT output = (PS_INPUT)0;

	output.Pos = mul(input.Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);

	output.TexUV = FrameUV;

	float x = FlipX + ((input.Pos.x / abs(input.Pos.x)) + 1) / (2 - 4 * FlipX);
	float y = ((input.Pos.y / abs(input.Pos.y)) + 1) / (2 - 4 * FlipY);
	output.TexUV.x += FrameSize.x * x;
	output.TexUV.y += FrameSize.y * ((1 - FlipY) - y);

	return output;
}

float4 Pixel_Shader(PS_INPUT input) : SV_Target
{
	float4 albedoColor = AlbedoTexture.Sample(sampleLinear_Wrap, input.TexUV);

	return albedoColor;
}


technique11 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, Vertex_Shader()));
		SetGeometryShader(NULL);
		SetPixelShader(CompileShader(ps_5_0, Pixel_Shader()));
	}
}