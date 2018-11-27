//[numthreads(1, 1, 1)]

struct Input
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR;
};

float4 main(Input input) : SV_Target
{ 
	return input.Color;
}
