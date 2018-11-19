#pragma once

int MakeHash(const wchar_t* str);
int MakeHash(const char* str);

static const int PRIORITY_PARTICLE = 10;
static const int PRIORITY_SKY = 10;

#include <d3d11.h>
#include <d3d11shader.h>
#include <windows.h>
#include <D3DCompiler.h>
#include <x3daudio.h>
#include <XAudio2.h>
#include <XAudio2fx.h>
#include <mmsystem.h>
#include <XInput.h>
#include <cstdlib>
#include <memory>
#include <vector>
#include <map>
#include <list>
#include <wincodec.h>
#include <wincodecsdk.h>
#include <string>
#include <typeinfo>
#include <stdio.h>
#include <string.h>

#pragma comment ( lib, "winmm.lib" )
//#include <wrl.h>
//#include <wrl/client.h>

#include "DirectXTK/Inc/CommonStates.h"
#include "DirectXTK\Inc\Effects.h"
#include "DirectXTK/Inc/Model.h"
#include "DirectXTK/Inc/Effects.h"
#include "DirectXTK/Inc/WICTextureLoader.h"
#include "DirectXTK/Inc/DDSTextureLoader.h"
#include "DirectXTK/Inc/SpriteFont.h"
#include "DirectXTK/Inc/SpriteBatch.h"


#include "../osumaruEngine/bulletPhysics/src/btBulletDynamicsCommon.h"

#include "Timer\GameTime.h"

#include "Uncopyable.h"
#include "Math\Math.h"
#include "Math/Matrix.h"
#include "Math\Vector.h"
#include "Engine.h"
#include "GameObject/GameObject.h"
#include "GameObject/GameObjectManager.h"
#include "Sound/SoundEngine.h"
#include "Graphics/ConstantBuffer.h"
#include "Graphics/Shader.h"


using namespace DirectX;
using namespace Microsoft::WRL;