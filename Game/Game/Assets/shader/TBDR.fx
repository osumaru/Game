
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
StructuredBuffer<SPointLight> pointLightList : register(t5);

Texture2D<float4> diffuseTexture : register(t0);
Texture2D<float4> depthTexture : register(t1);
Texture2D<float4> normalTexture : register(t2);
RWTexture2D<float4>  finalTexture : register(u3);

[numthreads(TILE_WIDTH, TILE_WIDTH, 1)]
void CSMain(uint3 groupID : SV_GroupID, uint3 groupThreadID : SV_GroupThreadID, uint3 dispatchThreadID : SV_DispatchThreadID)
{
	uint lightNum;
	uint dummy;
	pointLightList.GetDimensions(lightNum, dummy);
	uint groupIndex = groupThreadID.y * TILE_WIDTH + groupThreadID.x;
	if (groupIndex == 0)
	{
		sLightNum = 0;
	}
	GroupMemoryBarrierWithGroupSync();
	float4 frustumPlanes[4];
	float2 tileScale = screenParam / (TILE_WIDTH * 2.0f);
	float2 tileBias = tileScale - float2(groupID.xy);
	float4 c1 = float4(projectionMat._11 * tileScale.x, 0.0f, tileBias.x, 0.0f);
	float4 c2 = float4(0.0f, -projectionMat._22 * tileScale.y, tileBias.y, 0.0f);
	float4 c3 = float4(0.0f, 0.0f, 1.0f, 0.0f);
	frustumPlanes[0] = c3 - c1;
	frustumPlanes[1] = c3 + c1;
	frustumPlanes[2] = c3 - c2;
	frustumPlanes[3] = c3 + c2;
	for (int i = 0; i < 4; i++)
	{
		frustumPlanes[i].xyz *= rcp(length(frustumPlanes[i].xyz));
	}
	for (uint i = groupIndex; i < lightNum; i += TILE_WIDTH * TILE_WIDTH)
	{
		bool inFrustum = true;
		for (uint j = 0; j < 4; j++)
		{
			float d = dot(frustumPlanes[j].xyz, pointLightList[i].posInView.xyz);
			inFrustum = inFrustum && (d >= -pointLightList[i].param.x);
		}
		if (inFrustum)
		{
			uint listIndex;
			InterlockedAdd( sLightNum, 1, listIndex);
			sLightList[listIndex] = i;
		}
	}
	
	float4 viewPos = depthTexture[dispatchThreadID.xy];
	viewPos = mul(viewMat, viewPos);
	float3 normal = normalTexture[dispatchThreadID.xy];
	normal = mul(viewMatRotOnry, normal);
	normal = normalize(normal);
	float3 lig = float3(1.0f ,1.0f, 1.0f);
	GroupMemoryBarrierWithGroupSync();
	for (uint i = 0; i < sLightNum; i++)
	{
		uint lightIndex = sLightList[i];
		float3 lightDir = pointLightList[lightIndex].posInView.xyz - viewPos.xyz;
		float len = length(lightDir);
		lightDir = normalize(lightDir);
		float3 pointLightColor = pointLightList[lightIndex].color.xyz;// * max(0.0f, dot(normal, lightDir));
		float lightRate = len / pointLightList[lightIndex].param.x;
		float attn = max(0.0f, 1.0f - lightRate * lightRate);
		lig += pointLightColor.xyz * attn;
	}
	float3 diffuseColor = diffuseTexture[dispatchThreadID.xy] * lig;
	finalTexture[dispatchThreadID.xy] = float4(diffuseColor, 1.0f);
}