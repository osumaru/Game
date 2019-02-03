
cbuffer cb : register(b0)
{
	float4x4 mvp;	//ワールドビュープロジェクション行列
};

cbuffer cb1: register(b1)
{
	float alpha;
}

struct VS_INPUT
{
	float4 pos : SV_POSITION;
	float3 color : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float3 color : TEXCOORD0;
};

struct VS_INPUT_ERASE
{
	float4 pos : SV_POSITION;
	float3 color : TEXCOORD0;
	float dissolve: TEXCOORD1;
};

struct VS_OUTPUT_ERASE
{
	float4 pos : SV_POSITION;
	float3 color : TEXCOORD0;
	float dissolve : TEXCOORD1;
};


VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = mul(mvp, In.pos);
	Out.color = In.color;
	return Out;
}

float4 PSMain(VS_OUTPUT In) : SV_TARGET0
{
	float4 color = float4(In.color.xyz, 1.0f);
	return color;
}

VS_OUTPUT_ERASE VSEraseEffect(VS_INPUT_ERASE In)
{
	VS_OUTPUT_ERASE Out;
	Out.pos = mul(mvp, In.pos);
	Out.color = In.color;
	Out.dissolve = In.dissolve;
	return Out;
}

float4 PSEraseEffect(VS_OUTPUT_ERASE In) : SV_TARGET0
{
	float4 color = float4(In.color.xyz, 1.0f);
	clip(In.dissolve - alpha);
	return color;
}