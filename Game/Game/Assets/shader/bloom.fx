

cbuffer cb : register(b0)
{
	float4 g_sceneTextureSize;
	float4 g_offset;
	float4 g_weight1;
	float4 g_weight2;
};


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

struct BLUR_OUTPUT
{
	float4 pos	: SV_POSITION;
	float2 uv0	: TEXCOORD0; 
	float2 uv1	: TEXCOORD1; 
	float2 uv2	: TEXCOORD2;
	float2 uv3	: TEXCOORD3;
	float2 uv4	: TEXCOORD4;
	float2 uv5	: TEXCOORD5;
	float2 uv6	: TEXCOORD6;
	float2 uv7	: TEXCOORD7;
};

Texture2D<float4> downTexture0 : register(t0);
Texture2D<float4> downTexture1 : register(t1);
Texture2D<float4> downTexture2 : register(t2);
Texture2D<float4> downTexture3 : register(t3);
Texture2D<float4> downTexture4 : register(t4);
Texture2D<float4> sceneTexture : register(t5);
sampler Sampler : register(s1);


VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = In.pos;
	Out.uv = In.uv;
	return Out;
}

float4 PSMain(VS_OUTPUT In) : SV_Target0
{
	float4 color = sceneTexture.Sample(Sampler, In.uv);
	float t = dot(color.xyz, float3(0.2125f, 0.7154f, 0.0721f));
	clip(t - 1.001f);
	color.xyz *= (t - 1.0f);
	color.a = 1.0f;
	return color;
}

float4 CombinePS(VS_OUTPUT In) : SV_Target0
{
	float4 color;
	color = downTexture0.Sample(Sampler, In.uv);
	color += downTexture1.Sample(Sampler, In.uv);
	color += downTexture2.Sample(Sampler, In.uv);
	color += downTexture3.Sample(Sampler, In.uv);
	color += downTexture4.Sample(Sampler, In.uv);
	color *= 0.2f;
	return color;
}


float4 FinalPS(VS_OUTPUT In) : SV_Target0
{
	float4 color = sceneTexture.Sample(Sampler, In.uv);
	return clamp(color.x, color.y, color.z);
}

BLUR_OUTPUT XBlurVS(VS_INPUT In)
{
	BLUR_OUTPUT Out;
	Out.pos = In.pos;
	float2 uv = In.uv;
	Out.uv0 = uv + float2(-1.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv1 = uv + float2(-3.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv2 = uv + float2(-5.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv3 = uv + float2(-7.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv4 = uv + float2(-9.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv5 = uv + float2(-11.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv6 = uv + float2(-13.0f / g_sceneTextureSize.x, 0.0f);
	Out.uv7 = uv + float2(-15.0f / g_sceneTextureSize.x, 0.0f);
	return Out;
}

BLUR_OUTPUT YBlurVS(VS_INPUT In)
{
	BLUR_OUTPUT Out;
	Out.pos = In.pos;
	float2 uv = In.uv;
	Out.uv0 = uv + float2(0.0f, -1.0f / g_sceneTextureSize.y);
	Out.uv1 = uv + float2(0.0f, -3.0f / g_sceneTextureSize.y);
	Out.uv2 = uv + float2(0.0f, -5.0f / g_sceneTextureSize.y);
	Out.uv3 = uv + float2(0.0f, -7.0f / g_sceneTextureSize.y);
	Out.uv4 = uv + float2(0.0f, -9.0f / g_sceneTextureSize.y);
	Out.uv5 = uv + float2(0.0f, -11.0f / g_sceneTextureSize.y);
	Out.uv6 = uv + float2(0.0f, -13.0f / g_sceneTextureSize.y);
	Out.uv7 = uv + float2(0.0f, -15.0f / g_sceneTextureSize.y);
	return Out;
}

float4 BlurPS(BLUR_OUTPUT In) : SV_Target0
{
	float4 color;
	
	color = g_weight1.x * (sceneTexture.Sample(Sampler, In.uv0) + sceneTexture.Sample(Sampler, In.uv7 + g_offset.xy));
	color += g_weight1.y * (sceneTexture.Sample(Sampler, In.uv1) + sceneTexture.Sample(Sampler, In.uv6 + g_offset.xy));
	color += g_weight1.z * (sceneTexture.Sample(Sampler, In.uv2) + sceneTexture.Sample(Sampler, In.uv5 + g_offset.xy));
	color += g_weight1.w * (sceneTexture.Sample(Sampler, In.uv3) + sceneTexture.Sample(Sampler, In.uv4 + g_offset.xy));
	color += g_weight2.x * (sceneTexture.Sample(Sampler, In.uv4) + sceneTexture.Sample(Sampler, In.uv3 + g_offset.xy));
	color += g_weight2.y * (sceneTexture.Sample(Sampler, In.uv5) + sceneTexture.Sample(Sampler, In.uv2 + g_offset.xy));
	color += g_weight2.z * (sceneTexture.Sample(Sampler, In.uv6) + sceneTexture.Sample(Sampler, In.uv1 + g_offset.xy));
	color += g_weight2.w * (sceneTexture.Sample(Sampler, In.uv7) + sceneTexture.Sample(Sampler, In.uv0 + g_offset.xy));
	return color;
}