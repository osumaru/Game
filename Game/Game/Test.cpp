#include "stdafx.h"
#include "Test.h"



void Test::Init()
{
	texture.Load(L"Assets/sprite/CLEAR.png");

	sprite.Init(&texture);

	
	wchar_t* animClip[2];
	animClip[0] = L"Assets/modelData/unity3.tka";
	animClip[1] = L"Assets/modelData/unity2.tka";
	model.Load(L"Assets/modelData/Unitychan.cmo", &animation);
	//capsule.Create(100.0f, 1.0f);
	capsule.CreateCollider(&model);
	RigidBodyInfo info;
	info.pos = Vector3::Zero;
	info.rot = Quaternion::Identity;
	info.collider = &capsule;
	rigidbody.Create(info);
	GetPhysicsWorld().SetCamera(&camera);
	animation.Init(animClip, 2);
}

void Test::Update()
{
	static float angle = 0.0f;
	angle += 0.2f;
	Quaternion rot;
	rot.SetRotationDeg(Vector3::AxisZ, 180.0f);
	Quaternion def;
	def.SetRotationDeg(Vector3::AxisX, -90.0f);
	def.Multiply(rot);
	rot.SetRotationDeg(Vector3::AxisY, angle);
	model.Update({ 0.0f, 0.0f, 0.0f }, def, { 1.0f, 1.0f, 1.0f });
	rigidbody.SetRotation(def);

}

void Test::Draw()
{
	//GetPhysicsWorld().DebugDraw(rigidbody.GetBody()->getWorldTransform(), rigidbody.GetBody()->getCollisionShape());
	//model.Draw(view, proj);
	//sprite.Draw();
}