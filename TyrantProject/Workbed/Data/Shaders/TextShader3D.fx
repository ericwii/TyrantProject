#include "Utilities/ShaderSamplerStates.fx"
#include "Utilities/ShaderVariables.fx"


float2 CharacterSize;

struct VS_INPUT
{
	float4 Pos : POSITION;
	float2 TexUV : TEXCOORD;
};

struct GS_INPUT
{
	float4 Pos : POSITION;
	float2 TexUV : TEXCOORD;
};

struct PS_INPUT
{
	float4 Pos : SV_POSITION;
	float2 TexUV : TEXCOORD;
};


GS_INPUT Vertex_Shader(VS_INPUT input)
{
	GS_INPUT output = (GS_INPUT)0;


	output.Pos = mul(input.Pos, World);
	output.TexUV = input.TexUV;

	return output;
}

[maxvertexcount(4)]
void Geometry_Shader(point GS_INPUT input[1], inout TriangleStream<PS_INPUT> triangleStream)
{
	float4 right = float4(World._m10, World._m11, World._m12, World._m13);
	float4 up = float4(World._m00, World._m01, World._m02, World._m03);

	float4 sidePos = right * CharacterSize.x * Scale.x;
	float4 upPos = up * CharacterSize.y * Scale.y;

	const float4 offset[4] =
	{
		{ -sidePos + upPos }, 
		{ -sidePos - upPos }, 
		{ sidePos + upPos }, 
		{ sidePos - upPos },  
	};

	const float2 uv_coordinates[4] =
	{
		{ input[0].TexUV.x + CharacterSize.x, input[0].TexUV.y + CharacterSize.y },
		{ input[0].TexUV.x, input[0].TexUV.y + CharacterSize.y },
		{ input[0].TexUV.x + CharacterSize.x, input[0].TexUV.y },
		{ input[0].TexUV.x, input[0].TexUV.y }
	};

	PS_INPUT vertex = (PS_INPUT)0;
	for (int i = 0; i < 4; ++i)
	{
		vertex.Pos = input[0].Pos + offset[i];

		vertex.Pos = mul(vertex.Pos, View);
		vertex.Pos = mul(vertex.Pos, Projection);
		vertex.TexUV = uv_coordinates[i];

		triangleStream.Append(vertex);
	}

	triangleStream.RestartStrip();
}

float4 Pixel_Shader(PS_INPUT input) : SV_Target
{
	float4 albedoColor = AlbedoTexture.Sample(sampleLinear_Wrap, input.TexUV);
	float albedoSum = saturate(albedoColor.x + albedoColor.y + albedoColor.z);
	albedoColor = Color * albedoSum;
	albedoColor.w *= Color.w;
	
	return albedoColor;
}


technique11 Render
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, Vertex_Shader()));
		SetGeometryShader(CompileShader(gs_5_0, Geometry_Shader()));
		SetPixelShader(CompileShader(ps_5_0, Pixel_Shader()));
	}
}