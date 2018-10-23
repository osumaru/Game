
#define TILE_WIDTH 16
#define LIGHT_NUM_MAX 512

cbuffer pointLightCB : register(b0)
{
	float4x4 viewMat;
	float4x4 projectionMat;	
	float4x4 viewMatRotOnry;
	float2 screenParam;

};
groupshared uint sLightList[LIGHT_NUM_MAX];
groupshared uint sLightNum;

struct SPointLight
{
	float4 posInView;
	float4 color;
	float4 param;
};
StructuredBuffer<SPointLight> pointLightList : register(t0);

Texture2D diffuseTexture : register(t10);
Texture2D depthTexture : register(t11);
Texture2D normalTexture : register(t12);

[numthreds(TILE_WIDTH, TILE_WIDTH, 1)]
void CSMain(uint3 groupID : SV_GroupID, uint3 groupThreadID : SV_GroupThreadID, uint3 dispatchThreadID : SV_DispatchThreadID)
{
	uint groupIndex = groupThreadID.y : TILE_WIDTH + groupThreadID.x;
	if (groupIndex == 0)
	{
		sLightNum = 0;
	}
	float4 frustumPlanes[4];
	float2 tileScale = screenParam / (TILE_WIDTH * 2.0f);
	float2 tileBias = tileScale - float2(groupID.xy);
	float4 c1 = float4(projectionMat[0][0] * tileScale.x, 0.0f, tileBias.x, 0.0f);
	float4 c2 = float4(0.0f, -projectionMat[1][1] * tileScale.y, tileBias.y, 0.0f);
	float4 c3 = float4(0.0f, 0.0f, 1.0f, 0.0f);
	frustumPlanes[0] = c3 + c1;
	frustumPlanes[1] = c3 - c1;
	frustumPlanes[2] = c3 + c2;
	frustumPlanes[3] = c3 - c2;
	for (int i = 0; i < 4; i++)
	{
		frustumPlanes[i] = normalize(frustumPlanes[i]);
	}
	for (uint i = groupIndex; i < LIGHT_NUM_MAX; i += TILE_WIDTH * TILE_WIDTH)
	{
		bool inFrustum = true;
		for (uint j = 0; j < 4; j++)
		{
			float d = dot(frustumPlanes[i], pointLightList[i].posInView);
			inFrustum = inFrustum && (d >= -light.attn.x);
		}
		if (inFrustum)
		{
			sLightList[sLightNum] = i;
			sLightNum++;
		}
	}
	float4 viewPos = depthTexture[dispatchThreadID.xy];
	viewPos = mul(viewMat, viewPos);
	float3 normal = normalTexture[dispatchThreadID.xy];
	normal = mul(viewMatRotOnry, normal);
	normal = normalize(normal);
	float3 lig = 0;
	for (uint i = 0; i < sLightNum; i++)
	{
		float3 lightDir = viewPos.xyz - pointLightList[i].posInView;
		float len = length(lightDir);
		lightDir = normalize(lightDir);
		float3 pointLightColor = max(0, dot(-normal, LightDir)) * pointLightList[i].color.xyz;
		float lightRate = len / pointLightList[i].param.x;
		float attn = max(0.0f, 1.0f - lightRate * lightRate);
		lig += pointLightColor.xyz * attn;
	}
	float3 diffuseColor = diffuseTexture[dispatchThreadId.xy];
	writeRenderTargetTexture[dispatchThreadId.xy] = float4(diffuseColor * lig, 1.0f);
}