#pragma once

static const int PRIORITY_PLAYER = 1;
static const int PRIORITY_NPC = 0;
static const int PRIORITY_ENEMY = 1;
static const int PRIORITY_MAPCHIP = 1;
static const int PRIORITY_UI = 0;
static const int PRIORITY_CAMERA = 0;
static const int PRIORITY_ITEM = 0;
static const int PRIORITY_ARROW = 0;
static const int PRIORITY_SCENE = 0;


#include "../../osumaruEngine/engineStdafx.h"
#include "../../osumaruEngine/GameObject/GameObject.h"
#include "../../osumaruEngine/GameObject/GameObjectManager.h"
#include "../../osumaruEngine/Engine.h"
#include "../../osumaruEngine/Graphics/Texture.h"
#include "../../osumaruEngine/Graphics/Sprite.h"
#include "../../osumaruEngine/Graphics/SkinModel.h"
#include "../../osumaruEngine/Graphics/Skelton.h"
#include "../../osumaruEngine/Graphics/Animation.h"
#include "../../osumaruEngine/Camera/Camera.h"
#include "../../osumaruEngine/Camera/SpringCamera.h"
#include "../../osumaruEngine/Physics/Physics.h"
#include "../../osumaruEngine/Physics/RigidBody.h"
#include "../../osumaruEngine/Physics/Collider/CapsuleCollider.h"
#include "../../osumaruEngine/Physics/Collider/MeshCollider.h"
#include "../../osumaruEngine/Physics/Collider/BoxCollider.h"
#include "../../osumaruEngine/Physics/Collider/SphereCollider.h"
#include "../../osumaruEngine/Physics/Collider/ICollider.h"
#include "../../osumaruEngine/Physics/CharacterController.h"
#include "../../osumaruEngine/Physics/CollisionAttr.h"
#include "../../osumaruEngine/Input/Pad.h"
#include "../../osumaruEngine/Sound/SoundEngine.h"
#include "../../osumaruEngine/Sound/SoundSource.h"
#include "../../osumaruEngine/Graphics/Particle/Particle.h"
#include "../../osumaruEngine/Graphics/Particle/ParticleEmitter.h"
#include "../../osumaruEngine/Graphics/Font/Font.h"
#include "../../osumaruEngine/Random/Random.h"
#include "../../osumaruEngine/Physics/RayTest.h"
#include "../../osumaruEngine/Sky.h"
#include "../../osumaruEngine/NavigationMesh.h"
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <algorithm>


#ifdef _DEBUG 
#define _CRTDBG_MAP_ALLOC
#include <new>
#include <memory>
#include <cstdlib>
#include <crtdbg.h> 
//#define new new( _NORMAL_BLOCK , __FILE__ , __LINE__ ) 
#endif  // _DEBUG