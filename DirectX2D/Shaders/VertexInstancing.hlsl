//VertexInstancing
cbuffer WorldBuffer : register(b0)
{
	matrix world;
}

cbuffer ViewBuffer : register(b1)
{
	matrix view;
}

cbuffer ProjectionBuffer : register(b2)
{
	matrix projection;
}

struct VertexInput
{
	float4 pos : POSITION;
	float2 uv : UV;
	
	matrix transform : INSTANCE_TRANSFORM;
	float2 maxFrame : INSTANCE_MAX;
	float2 curFrame : INSTANCE_CUR;
};

struct VertexOutput
{
	float4 pos : SV_POSITION;
	float2 uv : UV;
	
	float2 maxFrame : INSTANCE_MAX;
	float2 curFrame : INSTANCE_CUR;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	
	output.pos = mul(input.pos, mul(input.transform, world));
	output.pos = mul(output.pos, view);
	output.pos = mul(output.pos, projection);
	output.uv = input.uv;
	
	output.maxFrame = input.maxFrame;
	output.curFrame = input.curFrame;
	
	return output;
}