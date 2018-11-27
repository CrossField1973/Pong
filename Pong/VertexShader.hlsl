cbuffer cbBat
{
	float4x4 Transformation;
}


struct Input
{
	float4 Pos : POSITION;
	float4 Color : COLOR;
};

struct Output
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

Output main(Input input)
{
	Output output;
	output.Pos = mul(input.Pos, Transformation);
	output.Color = input.Color;

	return output;
}