#pragma once

struct SMaterialFlg
{
	int isShadowReceiver;
	int isNormalMap;
	int isDiffuse;
};

static const SMaterialFlg g_materialFlg = { 0b1, 0b10, 0b100 };