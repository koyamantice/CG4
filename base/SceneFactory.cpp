#include "SceneFactory.h"
#include "GamePlayScene.h"
#include "TitleScene.h"


BaseScene* SceneFactory::CreateScene(const std::string& sceneName) {
	//次のシーンの作成
	BaseScene* newScene = nullptr;
	if (sceneName=="TITLE") {
		newScene=new TitleScene();
	}
	else if(sceneName == "GAMEPLAY"){
		newScene = new GamePlayScene();

	}
	return newScene;
}
