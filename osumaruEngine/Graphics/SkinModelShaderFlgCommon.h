#pragma once

struct SMaterialFlg
{
	int isShadowReceiver;
	int isNormalMap;
	int isDiffuse;
	int isSpecularmap;
};

static const SMaterialFlg g_materialFlg = { 0b1, 0b10, 0b100, 0b1000 };