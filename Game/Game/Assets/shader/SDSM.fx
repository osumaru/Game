
#define SCATTER_BLOCK_DIM 32
#define SCATTER_BLOCK_SIZE (SCATTER_BLOCK_DIM * SCATTER_BLOCK_DIM)Bd

#define BINS 1024
#define PARTITIONS 4

cbuffer PerFrameConstants : register(b0)
{
	float4x4 mCameraWorldViewProj;
	float4x4 mCameraWorldView;
	float4x4 mCameraViewProj;
	float4x4 mCameraProj;
	float4x4 mLightWorldViewProj;
	float4x4 mCameraViewToLightProj;
	float4 mLightDir;
	float4 mBlurSizeLightSpace;
	float4 mCameraNearFar;
	float4 mShadowTextureDim;

	UIConstants mUI;
};

cbuffer SDSMPartion(b1)
{
	uint mScatterTileDim;		//64
}

struct BoundsUInt
{
	uint3 minCoord;
	uint3 maxCoord;
};

struct HistgramBin
{
	uint count;
	BoundsUInt bounds;
};

struct SurfaceData
{
	float3 positionView;
	float3 positionViewDX;
	float3 positionViewDY;
	float3 normal;
	float4 albedo;
	float3 lightTexCoord;
	float3 lightTexCoordDX;
	float3 lightTexCoordDY;
};

struct GeometryVSIn
{
	float3 position : position;
	float3 normal : normal;
	float2 texCoord : texCoord;
};

struct Partition
{
	float intervalBegin;
	float intervalEnd;

	float3 scale;
	float3 bias;
};

BoundsUInt EmptyBoundsUInt()
{
	BoundsUInt b;
	b.minCoord = uint(0x7F7FFFFF).xxx;
	b.maxCoord = uint(0).xxx;
	return b;
}

HistgramBin emptyBin()
{
	HistgramBin b;
	b.count = 0;
	b.bounds = EmptyBoundsUInt();
}

//カラーテクスチャと法線マップと深度テクスチャ
Texture2D GBufferTexture[3] : register(t0);

groupshared HistogramBin sLocalHistigram[BINS];
groupshared uint sMinBin;
groupshared uint sMaxBin;
groupshared uint sPartitionMaxBin[PARTITIONS];
groupshared BoundsUInt sPartitionBoundsUInt[PARTITIONS];

StructureBuffer<Partition> gPartitions : register(t4);
StructuredBuffer<HistogramBin> gHistogramReadOnly : register(t5);
RWStructuredBuffer<HistogramBin> gHistogram : register(u5);


/*
スクリーン座標系からビュー座標(カメラから見た座標)系に変換する
positionScreen	2次元のスクリーン座標
viewSpaceZ		ビュー座標系での深度値
*/
float3 ComputePositionViewFromZ(float2 positionScreen, float viewSpaceZ)
{
	float2 screenSpaceRay = float2(positionScreen.x / mCameraProj._11,
									positionScreen.y / mCameraProj.22);

	float3 positionView;
	positionView.z = viewSpace.z;
	positionView.xy = screenSpaceRay.xy * positionView.z;
	return positionView;
}

//何をする関数か半分わかってない
float3 DecodeSphereMap(float2 e)
{
	float2 tmp = e - e * e;
	float f = tmp.x + tmp.y;
	float m = sqrt(4.0f * f - 1.0f);

	float3 n;
	n.xy = m * (e * 4.0f - 2.0f);
	n.z = 3.0f - 8.0f * f;
	return n;
}

/*
ビュー座標系からライトのビュープロジェクション行列を使ってテクスチャ座標系に変換する
*/
float3 ProjectIntoLightTexCoord(float3 positionView)
{
	float4 positionLight = mul(float4(positionView, 1.0f), mCameraViewToLightProj);
	float3 texCoord = (positionLight.xyz / positionLight.w) * float3(0.5f, -0.5f, 1.0f) + float3(0.5f, 0.5f, 0.0f);
	return texCoord;
}

SurfaceData ComputeSurfaceDataFromGBuffer(uint2 coods)
{
	float4 normals = GBufferTexture[0][coords];
	float4 albedo = GBufferTexture[1][coords];
	float zBuffer = GBufferTexture[2][coords].x;
	float2 gbufferDim;
	GBufferTexture[0].GetDimensions(gbufferDim.x, gbufferDim.y);

	float2 screenPixelOffset = float2(2.0f, -2.0f) / gbufferDim;
	float2 positionScreen = (float2(coods.xy) + 0.5f) * screenPixelOffset.xy + float2(-1.0f, 1.0f);
	float2 positionScreenX = positionScreen + float2(screenPixelOffset.x, 0.0f);
	float2 positionScreenY = positionScreen + float2(0.0f, screenPixelOffset.y);

	
	float viewSpaceZ = mCameraProj._43 / (zBuffer - mCameraProj._33);

	data.positionView = ComputePositionViewFromZ(positionScreen, viewSpaceZ);
	data.positionViewDX = ComputePositionViewFromZ(positionScreenX, viewSpaceZ + normals.z) - data.positionView;
	data.positionViewDY = ComputePositionViewFromZ(positionScreenY, viewSpaceZ + normals.w) - data.positionView;

	data.normal = DecodeSphereMap(nowmalx.xy);
	data.albedo = albedo;
	
	float deltaPixels = 2.0f;
	data.lightTexCoord = (ProjectionIntoLightTexCoord(data.positionView));
	data.lightTexCoordDX = (ProjectionIntoLightTex(data.positionView + deltaPixels * data.positionViewDX) - data.lightTexCoord) / deltaPixels;
	data.lightTexCoordDY = (ProjectionIntoLightTex(data.positionView + deltaPixels * data.positionViewDY) - data.lightTexCoord) / deltaPixels;
	return data;
}

float ZToBin(float z)
{
	float near = mCameraNearFar.x;
	float far = mCameraNearFar.y;
	float depth = (z - near) / (far - near);
	return pow(depth, (1.0f / mUI.histogramResolutionPower));
}

float BinToZ(float bin)
{
	float z = bin / float(BINS);
	float near = mCameraNearFar.x;
	float far = mCameraNearFar.y;
	return pow(z, mUI.histogramResolutionPower) * (far - near) + near;
}

//分割した範囲毎の最大深度値を求める
float LogPartitionFromRange(uint partition, float minZ, float maxZ)
{
	float z = maxZ;
	if (partition < PARTITIONS)
	{
		float ratio = maxZ / minZ;
		float power = float(partition) * (1.0f / float(PARTITIONS));
		z = minZ * pow(ratio, power);
	}
	return z;
}

[numthreads(SCATTER_BLOCK_DIM, SCATTER_BLOCK_DIM, 1)]
void ScatterHistogram(	uint3 groupID : SV_GroupID,
						uint3 groupThreadID : SV_GroupThreadID,
						uint groupIndex : SV_GroupIndex)
{
	for (int i = groupIndex; i < BINS; i += SCATTER_BLOCK_SIZE)
	{
		sLocalHistogram[i] = emptyBin();
	}

	GroupMemoryBarrierWithGroupSync();

	uint2 tileStart = groupID.xy * mScatterTileDim.xx + groupThreadID.xy;
	for (uint tileY = 0; tileY < mScatterTileDim; tileY += SCATTER_BLOCK_DIM)
	{
		for (uint tileX = 0; tileX < mScatterTileDim; tileX += SCATTER_BLOCK_DIM)
		{
			uint2 globalCoods = tileStart + uint2(tileX, tileY);

			SurfaceData data = ComputeSurfaceDataFromGBuffer(globalCoods);

			int bin = int(ZToBin(data.positionView.z));

			uint texCoordX = asuint(data.lightTexCoord.x);
			uint texCoordY = asuint(data.lightTexCoord.y);
			uint lightSpaceZ = asuint(data.lightTexCoord.z);

			InterlockedAdd(sLocalHistogram[bin].count, 1);
			InterlockedMin(sLocalHistogram[bin].bounds.minCoord.x, texCoordX);
			InterlockedMin(sLocalHistogram[bin].bounds.minCoord.y, texCoordY);
			InterlockedMin(sLocalHistogram[bin].bounds.minCoord.z, lightSpaceZ);
			InterlockedMax(sLocalHistogram[bin].bounds.maxCoord.x, texCoordX);
			InterlockedMax(sLocalHistogram[bin].bounds.maxCoord.y, texCoordY);
			InterlockedMax(sLocalHistogram[bin].bounds.maxCoord.z, lightSpaceZ);
		}
	}


	GroupMemoryBarrierWithGroupSync();

	for (uint i = groupIndex; i < BINS; i += SCATTER_BLOCK_SIZE)
	{
		if (0 < sLocalHistogram[i].count)
		{
			InterlockedAdd(gHistogram[i].count, sLocalHistogram[i].count);
			InterlockedMin(gHistogram[i].bounds.minCoord.x, sLocalHistogram[i].bounds.minCoord.x);
			InterlockedMin(gHistogram[i].bounds.minCoord.y, sLocalHistogram[i].bounds.minCoord.y);
			InterlockedMin(gHistogram[i].bounds.minCoord.z, sLocalHistogram[i].bounds.minCoord.z);
			InterlockedMax(gHistogram[i].bounds.maxCoord.x, sLocalHistogram[i].bounds.maxCoord.x);
			InterlockedMax(gHistogram[i].bounds.maxCoord.y, sLocalHistogram[i].bounds.maxCoord.y);
			InterlockedMax(gHistogram[i].bounds.maxCoord.z, sLocalHistogram[i].bounds.maxCoord.z);
		}
	}
}

BoundsFloat BoundsUIntToFloat(BoundsUInt u)
{
	BoundsFloat f;
	f.minCoord.x = asfloat(u.minCoord.x);
	f.minCoord.y = asfloat(u.minCoord.y);
	f.minCoord.z = asfloat(u.minCoord.z);
	f.maxCoord.x = asfloat(u.maxCoord.x);
	f.maxCoord.y = asfloat(u.maxCoord.y);
	f.maxCoord.z = asfloat(u.maxCoord.z);
	return f;
}

void ComputePartitionDataFromBounds(BoundsFloat bounds, out float3 scale, out float3 bias)
{
	float3 minTexCoord = bounds.minCoord;
	float3 maxTexCoord = bounds.maxCoord;

	minTexCoord -= mLightSpaceBorder.xyz;
	maxTexCoord += mLightSpaceBorder.xyz;

	scale = 1.0f / (maxTexCoord - minTexCoord);
	bias = -minTexCoord * scale;

	float oneMinusTwoFactor = 1.0f - 2.0f * m_DilationFactor;
	scale *= oneMinusTwOFactor;
	bias = mDilationFactor + oneMinusTwoFactor * bias;

	float3 targetScale = min(scale, mMaxScale.xyz);

	if (mUI.quantizePartitions)
	{
		targetScale.xy = max(1.0f, exp2(floor(log2(targetScale.xy))));
	}

	float3 center = float3(0.5f, 0.5f, 0.5f);
	bias = (targetScale / scale) * (bias - center) + center;
	scale = targetScale;
	if (mUI.quantizePartitions)
	{
		float2 texelsInLightSpace = mShadowTextureDim.xy;
		bias.xy = floor(bias.xy * texelsInLightSpace) / texelsInLightSpace;
	}
	
	if (any(maxTexCoord < minTexCoord))
	{
		scale = asfloat(0x7F7FFFFF).xxx;
		bias = scale;
	}

}

void ComputePartitionDataFromHistogram(uint groupIndex)
{
	if (groupIndex < PARTITIONS)
	{
		sPartitionBoundsUInt[groupIndex] = EmptyBoundsUInt();
	}

	if (0 < gHistogramReadOnly[groupIndex].count)
	{
		uint partition = 0;
		for (uint i = 0; i < (PARTITIONS - 1); ++i)
		{
			partition += (groupIndex >= sPartitionMaxBin[i] ? 1U : 0U);
		}
		InterlockedMin(sPartitionBoundsUInt[partition].minCoord.x, gHistogramReadOnly[groupIndex].bounds.minCoord.x);
		InterlockedMin(sPartitionBoundsUInt[partition].minCoord.y, gHistogramReadOnly[groupIndex].bounds.minCoord.y);
		InterlockedMin(sPartitionBoundsUInt[partition].minCoord.z, gHistogramReadOnly[groupIndex].bounds.minCoord.z);
		InterlockedMax(sPartitionBoundsUInt[partition].maxCoord.x, gHistogramReadOnly[groupIndex].bounds.maxCoord.x);
		InterlockedMax(sPartitionBoundsUInt[partition].maxCoord.y, gHistogramReadOnly[groupIndex].bounds.maxCoord.y);
		InterlockedMax(sPartitionBoundsUInt[partition].maxCoord.z, gHistogramReadOnly[groupIndex].bounds.maxCoord.z);
	}

	GroupMemoryBrrierWithGroupSync();

	if (groupIndex < PARTITIONS)
	{
		uint minBin = 0;
		if (groupIndex > 0)
		{
			minBin = sPartitionMaxBin[groupIndex - 1];
		}
		uint maxBin = sPartitionMaxBin[groupIndex];
		float3 scale, bias;
		ComputePartitionDataFromBounds(BoundsUIntToFloat(sPartitionBoundsUInt[groupIndex]), scale, bias);

	}
}

[numthreads(BINS, 1, 1)]
void ComputeLogPartitionsFromHistogram(uint groupIndex : SV_GroupIndex)
{
	if (groupIndex == 0)
	{
		sMinBin = BINS;
		sMaxBin = 0;
	}

	GroupMemoryBarrierWithGroupSync();

	if (gHistogramReadOnly[groupIndex].count > 0)
	{
		InterLockedMin(sMinBin, groupIndex);
		InterLockedMax(sMaxBin, groupIndex + 1)
	}

	GroupMemoryBarrierWithGroupSync();

	if (groupIndex < PARTITIONS)
	{
		sPartitionMaxBin[groupIndex] = ZToBin(LogPartitionFromRange(groupIndex + 1, BinToZ(sMinBin), BinToZ(sMaxBin)););
	}

	GroupMemoryBarrierWithGroupSync();

	ComputePartitionDataFromHistogram(groupIndex);
}

float4 ShadowVS(GeometryVSIn input) : SV_POSITION
{
	float4 position mul(float4(input.position, 1.0f), mLightWorldViewProj);
	Partition partition = gPartitions[mRenderPartition];
	position.xy *= partition.scale.xy;
	position.x += (2.0f * partition.bias.x + partition.scale.x - 1.0f);
	position.y -= (2.0f * partition.bias.y + partition.scale.y - 1.0f);

	// Push the surface back ever-so-slightly
	// The only reason for this is because of interpolant and position reconstruction
	// precision issues on some GPUs/G-buffer layouts.
	position.z += 0.0001f;

	// Clamp to [0, 1] happens in the viewport transform
	// NOTE: Depth clipping is disabled in this pass (directional light)
	position.z = position.z * partition.scale.z + partition.bias.z;

	return position;
}