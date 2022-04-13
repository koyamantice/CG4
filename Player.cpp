#include "Player.h"
#include "Input.h"
#include"Collision.h"
#include"Easing.h"
#include "DebugText.h"
#include<sstream>
#include<iomanip>
using namespace DirectX;

Player::Player() {
	model = Model::CreateFromOBJ("chr_knight");
	object3d = new Object3d();
	shadowObj = new Object3d();
	Sprite::LoadTexture(3, L"Resources/2d/gage.png");
}

void Player::Initialize() {
	Sprite::LoadTexture(3, L"Resources/2d/gage.png");
	//�w�i�X�v���C�g����
	Gauge = Sprite::Create(3, { 0.0f,0.0f });

	//�v���C���[
	radius = speed * PI / 180.0f;
	circleX = cosf(radius) * scale;
	circleZ = sinf(radius) * scale;
	pos.x = circleX;
	pos.y = circleZ;

	//�v���C���[(���z)
	shadowRadius = shadowSpeed * PI / 180.0f;
	shadowCircleX = cosf(shadowRadius) * shadowScale;
	shadowCircleZ = sinf(shadowRadius) * shadowScale;
	shadowpos.x = shadowCircleX;
	shadowpos.y = shadowCircleZ;

	object3d = Object3d::Create();
	object3d->SetModel(model);
	object3d->SetPosition(pos);
	object3d->SetScale({ 1,1,1 });

	shadowObj = Object3d::Create();
	shadowObj->SetModel(model);
	shadowObj->SetPosition(shadowpos);
	shadowObj->SetScale({ 1,1,1 });

	collider.radius = rad;
}

void Player::Update() {
	Input* input = Input::GetInstance();
	XMFLOAT3 pos = this->object3d->GetPosition();
	object3d->Update();
	shadowObj->Update();
	collider.center = XMVectorSet(pos.x, pos.y, pos.z, 1);
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN)) {
		if (!undoPos && !Dash) {
			if (input->PushKey(DIK_UP)) {
				speed += 2.0f;
				oldEW = 1;
			}
			if (input->PushKey(DIK_DOWN)) {
				speed -= 2.0f;
				oldEW = 2;
			}
			//�v���C���[
			radius = speed * PI / 180.0f;
			circleX = cosf(radius) * scale;
			circleZ = sinf(radius) * scale;
			pos.x = circleX;
			pos.y = circleZ;
			object3d->SetPosition(pos);
		}
	}
	if (!Dash) {
		if (chage >= 0.5f) {
			DebugText::GetInstance()->Print("OK", 0, 110, 5.0f);
		if (input->ReleaseKey(DIK_Z)) {
			if (chage < 1.0f) {
				chage = 0.5f;
			}
				Dashframe = 0.0f;
				if (oldEW != 2) {
					lastspeed = speed + (90.0f * chage);
				} else {
					lastspeed = speed - (90.0f * chage);
				}
				Dash = true;
			}
		}
		if (input->PushKey(DIK_Z)) {
			chage += 0.0166f;
			if (chage >= 1.0f) {
				DebugText::GetInstance()->Print("MAX", 0, 50, 5.0f);
				chage = 1.0f;
			}
		} else {
			chage = 0;
		}
	}else {
		if (Dashframe <= 1.0f) {
			Dashframe += 0.04f;
		} else {
			Dashframe = 1.0f;
			Dash = false;
		}
		speed = Ease(InOut, Sine, Dashframe, speed, lastspeed);
		radius = speed * PI / 180.0f;
		circleX = cosf(radius) * scale;
		circleZ = sinf(radius) * scale;
		pos.x = circleX;
		pos.y = circleZ;
		object3d->SetPosition(pos);
	}
	if (input->TriggerKey(DIK_SPACE)) {
		if (!shadowFlag) {
			shadowSpeed = speed;
			shadowFlag = true;
			if (coolCount <= 90 && CheckCool) {
				coolCount = 0;
				needCool = true;
			}
		} else {
			if (!undoPos) {
				frame = 0;
				undoPos = true;
			}
		}
	}
	if (shadowFlag) {
		if (needCool) {
			posX *= 0.989f;
		} else {
			posX *= 0.999f;
		}
		Gauge->SetSize({ posX,64});
		if (posX <= 2) {
			if (!undoPos) {
				frame = 0;
				undoPos = true;
			}
			posX = 1;
		}
	} else {
		if (posX < 256) {
			posX *= 1.01f;
			Gauge->SetSize({ posX,64 });
		} else {
			posX = 256;
			Gauge->SetSize({ posX,64 });

		}
		if (posX<1) {
			posX = 1;
		}
	}
	//Gauge�֘A
	if (CheckCool&&!needCool) {
		Gauge->SetColor({255,0,0,255});
		coolCount++;
		if (coolCount>90) {
			CheckCool = false;
			needCool = false;
			coolCount = 0;
		}
	} else {
		Gauge->SetColor({ 255,255,255,255 });
		coolCount = 0;
	}
	if (needCool) {
		Gauge->SetColor({ 0,0,255,255 });
	} else if (posX == 256) {
		Gauge->SetColor({ 0,255,0,255 });

	}
	if (!shadowFlag) {
		shadowSpeed = speed;
	}
	//�v���C���[(���z)
	shadowRadius = shadowSpeed * PI / 180.0f;
	shadowCircleX = cosf(shadowRadius) * shadowScale;
	shadowCircleZ = sinf(shadowRadius) * shadowScale;
	shadowpos.x = shadowCircleX;
	shadowpos.y = shadowCircleZ;
	shadowObj->SetPosition(shadowpos);
	if (undoPos) {
		if (frame <= 1.0f) {
			frame += 0.04f;
		} else {
			frame = 1.0f;
			speed = shadowSpeed;
			shadowFlag = false;
			undoPos = false;
			needCool = false;
			if (!CheckCool) {
				CheckCool = true;
			}
		}
		pos.x = Ease(In, Exp, frame, pos.x, shadowpos.x);
		pos.y = Ease(In, Exp, frame, pos.y, shadowpos.y);
		object3d->SetPosition(pos);
	}
}

void Player::Draw() {
	Sprite::PreDraw();
	//�w�i�p
	Gauge->Draw();

	Object3d::PreDraw();
	object3d->Draw();
	if (shadowFlag) {
		shadowObj->Draw();
	}
}

