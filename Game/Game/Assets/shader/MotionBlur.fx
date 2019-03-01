

struct VS_INPUT
{
	float4 pos	: SV_POSITION;
	float2 uv	: TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos	: SV_POSITION;
	float2 uv	: TEXCOORD0;
};

Texture2D<float4> mainTexture : register(t0);
Texture2D<float4> velocityTexture : register(t1);
sampler Sampler : register(s0);
sampler clampSampler : register(s1);

VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = In.pos;
	Out.uv = In.uv;
	return Out;
}

float4 PSMain(VS_OUTPUT In) : SV_Target0
{
	float4 color = 0;
	float4 velocity = velocityTexture.Sample(Sampler, In.uv);
	for(int i = 0;i < 5;i++)
	{
		float2 fuv = In.uv;
		fuv += -velocity.xy * i * 0.06f;
		int3 uv;
		uv.z = 0;
		uv.x = fuv.x * 1280;
		uv.y = fuv.y * 720;
		color.xyz += mainTexture.Load(uv, int2(0, 0)).xyz;
	}
	color.xyz /= 5.0f;
	color.w = 1.0f;
	return color;
}