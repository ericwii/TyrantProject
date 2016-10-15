SamplerState sampleLinear_Wrap
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = WRAP;
	AddressV = WRAP;
};

SamplerState sampleLinear_Clamp
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = CLAMP;
	AddressV = CLAMP;
};

SamplerState sampleLinear_Mirror
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = MIRROR;
	AddressV = MIRROR;
};