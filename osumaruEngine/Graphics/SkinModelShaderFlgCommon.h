#pragma once

struct SMaterialFlg
{
	int isShadowReceiver;
	int isNormalMap;
};

static const SMaterialFlg g_materialFlg = { 0b1, 0b10 };