
cbuffer lightCB : register(b0)
{
	float4 ambientLight;
	float4 diffuseLight[4];
	float4 diffuseLightDir[4];
};

cbuffer shadowConB : register(b1)
{
	float4x4 gameViewProj;
};

cbuffer shadowCB : register(b2)
{
	float4x4 lightViewProj;
};
cbuffer materialCB : register(b3)
{
	int isShadowReceiver;
	int isNormalMapFlg;
};


cbuffer framesizeCB : register(b4)
{
	int frameBufferWidth;
	int frameBufferHeight;
};
struct SPointLight
{
	float4 pos;
	float4 color;
};

StructuredBuffer<SPointLight> pointLightList : register(t10);


struct VS_INPUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 screenPos : TEXCOORD1;
	float2 uv : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);
Texture2D<float4> normalMapTexture : register(t1);
Texture2D<float4> normalTexture : register(t2);
Texture2D<float4> tangentTexture : register(t3);
Texture2D<float4> depthTexture : register(t4);
Texture2D<int4> materialTexture : register(t5);
Texture2D<float4> shadowTexture : register(t6);
sampler Sampler : register(s0);
sampler shadowSampler : register(s1);
VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = In.pos;
	Out.uv = In.uv;
	Out.screenPos = In.pos;
	return Out;
}

float4 PSMain(VS_OUTPUT In) : SV_TARGET0
{
	float4 color = colorTexture.Sample(Sampler, In.uv);
	float3 normal = normalTexture.Sample(Sampler, In.uv).xyz;
	float3 tangent = tangentTexture.Sample(Sampler, In.uv).xyz;
	float3 binormal = cross(normal, tangent).xyz;
	normal = normalize(normal);
	tangent = normalize(tangent);
	binormal = normalize(binormal);
	float3 normalColor = normalMapTexture.Sample(Sampler, In.uv);
	normalColor = normalize(normalColor);
	float4x4 mat = {
		float4(tangent, 0.0f),
		float4(binormal, 0.0f),
		float4(normal, 0.0f),
		float4(0.0f, 0.0f, 0.0f, 1.0f)
	};
	normalColor = mul(normalColor, mat);
	float3 normalLight[4] =
	{
		normalize(diffuseLightDir[0].xyz),
		normalize(diffuseLightDir[1].xyz),
		normalize(diffuseLightDir[2].xyz),
		normalize(diffuseLightDir[3].xyz)
	};
	float4 lig = float4(0.0f, 0.0f, 0.0f, 1.0f);
	for (int i = 0; i < 4; i++)
	{
		lig.xyz += diffuseLight[i].xyz * max(-dot(normal, normalLight[i]), 0.0f) * max(-dot(normalColor, normalLight[i]), 0.0f);
	}
	lig.xyz += ambientLight;
	color *= lig;
	
	In.screenPos = depthTexture.Sample(Sampler, In.uv);
	float4 shadowMapPos = depthTexture.Sample(Sampler, In.uv);
	float4 worldPos = depthTexture.Sample(Sampler, In.uv);
	shadowMapPos = mul(lightViewProj, shadowMapPos);
	shadowMapPos /= shadowMapPos.w;
	shadowMapPos.xy += 1.0f;
	shadowMapPos.xy /= 2.0f;
	shadowMapPos.y = 1.0f - shadowMapPos.y;
	int3 uv;
	uv.xy = (int2)(shadowMapPos.xy * 1024);
	uv.z = 0;
	float depth = shadowMapPos.z;
	float shadowDepth;
	//shadowDepth = shadowTexture.Sample(shadowSampler, shadowMapPos.xy).z;
	shadowDepth = shadowTexture.Load(uv, int2(0, 0)).x;
	float shadowValue = 1.0f;
	if (shadowMapPos.x <= 1.0f && 0.0f <= shadowMapPos.x
		&&	shadowMapPos.y <= 1.0f && 0.0f <= shadowMapPos.y)
	{
		int3 uv;
		uv.z = 0;
		uv.x = (int)(In.uv.x * 1280.0f);
		uv.y = (int)(In.uv.y * 720.0f);
		float d = depth - 0.01 - shadowDepth;
		shadowValue *= step(depth, shadowDepth + 0.001f);// - materialTexture.Load(uv, int2(0, 0)).x & isShadowReceiver;
	}
	color.xyz *= shadowValue;
	return color;
}

