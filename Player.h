#pragma once
#include"Object3d.h"
#include"Model.h"
#include <DirectXMath.h>
#include <Input.h>
#include"CollisionPrimitive.h"
#include "Sprite.h"
class Player {
public:
	Player();

	void Initialize();
	void Update();
	void Draw();
private:
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public:
	/// <summary>
/// ���W�̎擾
/// </summary>
/// <returns>���W</returns>
	const XMFLOAT3& GetPosition() { return  object3d->GetPosition(); }

	const XMFLOAT3& GetRotation() { return object3d->GetRotation(); }

	/// <summary>
	/// ���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	void SetPosition(XMFLOAT3 position) { object3d->SetPosition(position); }

	void SetRotation(XMFLOAT3 rotation) { object3d->SetRotation(rotation); }

private:
	Object3d* shadowObj;
	Object3d* object3d;
	Model* model;
	XMFLOAT3 pos = { 0,0,0 };
	XMFLOAT3 shadowpos = { 0,0,0 };
	Sprite *Gauge=nullptr;

	char oldEW = 0;
	float chage = 0;
	bool Dash = false;
	float Dashframe = 0.0f;
	float lastradius = 0.0f;
	float lastspeed = 0.0f;
	float lastscale = 4.0f;// LaneNum�ƈꏏ�ɕς��邱��
	float LastPos_x = 0;
	float LastPos_y = 0;
	//���W��߂�
	bool undoPos = false;

	float rad = 0.4f;
	const float PI = 3.14f;

	float radius = 0.0f;
	float speed = 0.0f;
	float scale = 4.0f;// LaneNum�ƈꏏ�ɕς��邱��
	float circleX = 0.0f;
	float circleZ = 0.0f;

	//�c���֘A
	float frame = 0.0f;
	bool CheckCool = false;
	int coolCount = 0;
	bool  needCool = false;
	float posX = 256;

	XMFLOAT3 angle = { 0,0,0};
	bool shadowFlag = false;
	float shadowRadius = 0.0f;
	float shadowSpeed = 0.0f;
	float shadowScale = 4.0f;// LaneNum�ƈꏏ�ɕς��邱��
	float shadowCircleX = 0.0f;
	float shadowCircleZ = 0.0f;
public:
	Sphere collider;

};


