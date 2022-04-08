#include "Enemy.h"
#include "Input.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>
using namespace DirectX;

Enemy::Enemy() {
	model = Model::CreateFromOBJ("chr_knight");
	object3d = new Object3d();
}

void Enemy::Initialize() {
	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({ 1,1,1 });
	collider.radius=rad;
}

void Enemy::Update() {
	XMFLOAT3 pos = this->object3d->GetPosition();
	object3d->Update();
	collider.center = XMVectorSet(pos.x,pos.y,pos.z,1);
}

void Enemy::Draw() {
	Object3d::PreDraw();
	object3d->Draw();

}