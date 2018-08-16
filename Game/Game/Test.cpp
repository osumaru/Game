#include "stdafx.h"
#include "Test.h"



void Test::Init()
{
	texture.Load(L"Assets/sprite/CLEAR.png");

	sprite.Init(&texture);
	view.MakeLookAt({ 0.0f, 0.0f, -200.0f }, { 0.0f, 0.0f, 0.0f }, {0.0f, 1.0f, 0.0f});
	proj.MakeProjectionMatrix(Math::DegToRad(60.0f), (float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT, 1.0f, 500.0f);
	camera.Init();
	camera.SetViewMatrix(view);
	camera.SetProjectionMatrix(proj);
	camera.SetFar(500.0f);
	camera.SetNear(1.0f);
	camera.SetAspect((float)FRAME_BUFFER_WIDTH / (float)FRAME_BUFFER_HEIGHT);
	camera.SetAngle(Math::DegToRad(60.0f));
	camera.SetPosition({ 0.0f, 0.0f, -200.0f });
	camera.SetTarget({ 0.0f, 0.0f, 0.0f });
	camera.SetUp({ 0.0f, 1.0f, 0.0f });
	
	std::unique_ptr<AnimationClip[]> animClip;
	animClip.reset(new AnimationClip[2]);
	animClip[0].Load(L"Assets/modelData/unity3.tka");
	animClip[1].Load(L"Assets/modelData/unity2.tka");
	model.Load(L"Assets/modelData/Unitychan.cmo");
	//capsule.Create(100.0f, 1.0f);
	capsule.CreateCollider(&model);
	RigidBodyInfo info;
	info.pos = Vector3::Zero;
	info.rot = Quaternion::Identity;
	info.collider = &capsule;
	rigidbody.Create(info);
	GetPhysicsWorld().SetCamera(&camera);
	animation.Init(std::move(animClip), model.GetSkelton());
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
	animation.Update();
	rigidbody.SetRotation(def);
	if (GetPad().IsTriggerButton(enButtonA))
	{
		animation.Play(0);
	}
	if (GetPad().IsTriggerButton(enButtonB))
	{
		animation.Play(1);
	}
}

void Test::Draw()
{
	//GetPhysicsWorld().DebugDraw(rigidbody.GetBody()->getWorldTransform(), rigidbody.GetBody()->getCollisionShape());
	model.Draw(view, proj);
	//sprite.Draw();
}