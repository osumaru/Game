
cbuffer lightCB : register(b0)
{
	float4 ambientLight;
	float4 diffuseLight[4];
	float4 diffuseLightDir[4];
};

struct VS_INPUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
};

Texture2D<float4> colorTexture : register(t0);
Texture2D<float4> normalMapTexture : register(t1);
Texture2D<float4> normalTexture : register(t2);
Texture2D<float4> tangentTexture : register(t3);
Texture2D<float4> depthTexture : register(t4);
sampler Sampler : register(s0);

VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = In.pos;
	Out.uv = In.uv;
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
	return color;
}