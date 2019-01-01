
cbuffer cb : register(b0)
{
	float4x4 mvp;	//ワールドビュープロジェクション行列
};

struct VS_INPUT
{
	float4 pos : SV_POSITION;
	float2 uv : TEXCOORD0;
	float alpha : TEXCOORD1;
};

struct VS_OUTPUT
{
	float4 pos : SV_POSITION;
	float4 worldPos : TEXCOORD0;
	float2 uv : TEXCOORD1;
	float alpha : TEXCOORD2;
};

Texture2D<float4> colorTexture : register(t0);
Texture2D<float4> depthTexture : register(t1);
sampler Sampler : register(s0);

VS_OUTPUT VSMain(VS_INPUT In)
{
	VS_OUTPUT Out;
	Out.pos = mul(mvp, In.pos);
	Out.worldPos = Out.pos;
	Out.uv = In.uv;
	Out.alpha = In.alpha;
	return Out;
}

float4 PSMain(VS_OUTPUT In) : SV_TARGET
{
	float4 color = colorTexture.Sample(Sampler, In.uv);
	In.worldPos /= In.worldPos.w;
	
	float2 uv = In.worldPos.xy;
	uv += 1.0f;
	uv *= 0.5f;
	uv.y = 1.0f - uv.y;
	float4 depthColor = depthTexture.Sample(Sampler, uv);
	depthColor = mul(mvp, depthColor);
	float depth = depthColor.z /  depthColor.w;
	clip(depth - In.worldPos.z);
	color.w *= In.alpha;
	return color;
}
