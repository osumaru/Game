cbuffer cb : register(b0)
{
	float4x4 mvp;	//ワールドビュープロジェクション行列
	float4x4 view;
	float4x4 proj;
};

StructuredBuffer<float4x4> boneMatrix : register(t0);

struct VS_INPUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_SKIN_INPUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	uint4 boneIndex : BLENDINDICES;
	float4 blendWeight : BLENDWEIGHT;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);
sampler Sampler : register(s0);


VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = mul(mvp, In.pos);
	Out.pos = mul(view, Out.pos);
	Out.pos = mul(proj, Out.pos);
	Out.uv = In.uv;
	return Out;
}

VS_OUTPUT VSSkinMain(VS_SKIN_INPUT In)
{
	VS_OUTPUT Out;
	float4 pos = 0;
	for (int i = 0;i < 4;i++)
	{
		pos += mul(boneMatrix[In.boneIndex[i]], In.pos) * In.blendWeight[i];
	}
	Out.pos = pos;
	//Out.pos = mul(mvp, Out.pos);
	Out.pos = mul(view, Out.pos);
	Out.pos = mul(proj, Out.pos);
	Out.uv = In.uv;
	return Out;
}

float4 PSMain(VS_OUTPUT In) : SV_TARGET
{
	float4 color = colorTexture.Sample(Sampler, In.uv);
	return color;
}