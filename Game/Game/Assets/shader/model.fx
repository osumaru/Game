cbuffer cb : register(b0)
{
	float4x4 mvp;	//ワールドビュープロジェクション行列
	float4x4 viewProj;
	int isNormalMap;
};

cbuffer lightCB : register(b1)
{
	float4 ambientLight;
	float4 diffuseLight[4];
	float4 diffuseLightDir[4];
};

StructuredBuffer<float4x4> boneMatrix : register(t100);

struct VS_INPUT
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 uv : TEXCOORD0;
};

struct VS_SKIN_INPUT
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float2 uv : TEXCOORD0;
	uint4 boneIndex : BLENDINDICES;
	float4 blendWeight : BLENDWEIGHT;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 normal : NORMAL;
	float3 tangent : TANGENT;
	float3 binormal : BINORMAL;
	float2 uv : TEXCOORD0;
};

struct PS_OUTPUT
{
	float4 color		: SV_TARGET0;
	float4 normalMap	: SV_TARGET1;
	float4 normal		: SV_TARGET2;
	float4 tangent		: SV_TARGET3;
};

Texture2D<float4> colorTexture : register(t10);
Texture2D<float4> normalTexture : register(t11);
sampler Sampler : register(s0);


VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = mul(mvp, In.pos);
	Out.pos = mul(viewProj, Out.pos);
	Out.normal = mul(mvp, In.normal);
	Out.normal = normalize(Out.normal);
	Out.tangent = mul(mvp, In.tangent);
	Out.tangent = normalize(Out.tangent);
	Out.binormal = cross(Out.normal, Out.tangent);
	Out.binormal = normalize(Out.binormal);
	Out.uv = In.uv;
	return Out;
}

VS_OUTPUT VSSkinMain(VS_SKIN_INPUT In)
{
	VS_OUTPUT Out;
	float4x4 pos = 0;
	float4 blendWeight;
	for (int i = 0;i < 4;i++)
	{
		pos += boneMatrix[In.boneIndex[i]] * In.blendWeight[i];
	}
	Out.pos = mul(pos, In.pos);
	Out.pos = mul(viewProj, Out.pos);
	Out.normal = mul(pos, In.normal);
	Out.normal = normalize(Out.normal);
	Out.tangent = mul(pos, In.tangent);
	Out.tangent = normalize(Out.tangent);
	Out.binormal = cross(Out.normal, Out.tangent);
	Out.binormal = normalize(Out.binormal);
	Out.uv = In.uv;
	return Out;
}

PS_OUTPUT PSMain(VS_OUTPUT In)
{
	PS_OUTPUT Out;
	Out.color = float4(colorTexture.Sample(Sampler, In.uv).xyz, 1.0f);
	Out.normal = float4(In.normal, 1.0f);
	Out.tangent = float4(In.tangent, 1.0f);
	float3 normalColor = normalTexture.Sample(Sampler, In.uv) * isNormalMap + float3(0.0f, 0.0f, 1.0f) * (1 - isNormalMap);
	Out.normalMap = float4(normalColor, 1.0f);
	return Out;
}


