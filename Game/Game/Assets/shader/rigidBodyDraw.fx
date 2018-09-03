
cbuffer cb : register(b0)
{
	float4x4 mvp;	//���[���h�r���[�v���W�F�N�V�����s��
};

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