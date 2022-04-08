#include "GamePlayScene.h"
#include "Audio.h"
#include "input.h"
#include "DebugText.h"
#include "TitleScene.h"
#include"Collision.h"
#include<sstream>
#include<iomanip>

void GamePlayScene::Initialize() {
	//�I�u�W�F�N�g������
	// �e�N�X�`���ǂݍ���
	Sprite::LoadTexture(2, L"Resources/2d/gameplay.png");

	//�w�i�X�v���C�g����
	sprite = Sprite::Create(2, { 0.0f,0.0f });
	//�X�v���C�g����

	// ���f���ǂݍ���
	Audio::GetInstance()->LoadSound(1, "Resources/BGM/NewWorld.wav");
	player = new Player();
	player->Initialize();
	for (int i = 0; i < PlayerMax; i++) {
		enemy[i] = new Enemy();
		enemy[i]->Initialize();
		enemy[i]->SetPosition({ (float)-13.0f + i * 5.0f,(float)0,(float)0 });
	}
	enemy[0]->SetPosition({ (float)0.0f,(float)-3.0f,(float)0 });
	srand(NULL);
}

void GamePlayScene::Finalize() {
	//�R���̃��f���̃f���[�g
}

void GamePlayScene::Update() {
	Input* input = Input::GetInstance();

}

void GamePlayScene::Draw() {
	{
		ImGui::Begin("test");
		if (ImGui::TreeNode("Debug")) 	{
			if (ImGui::Button("")) {
				printf("Button\n");
			}
			if (ImGui::TreeNode("Field")) 		{
				//ImGui::SliderFloat("Position.x", &s, 50, -50);
				ImGui::Unindent();
				ImGui::TreePop();
			}
			ImGui::TreePop();
		}
		ImGui::End();
		ImGui::Render();
	}
	Sprite::PreDraw();
	sprite->Draw();


	Object3d::PreDraw();
	player->Draw();

	//�O�ʗp

}

