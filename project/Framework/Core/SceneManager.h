//=====================================
//
//シーンマネージャヘッダ[SceneManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "../../main.h"
#include <unordered_map>

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class BaseScene;
class SceneManager
{
public:
	//コンストラクタ、デストラクタ
	SceneManager();
	~SceneManager();

	//シーン切り替え処理
	static void ChangeScene(const char* sceneName);

	//シーン追加処理
	void Add(const char* sceneName, BaseScene* scene);

	//更新処理、描画処理、終了処理
	void Update();
	void Draw();
	void Uninit();

	//シーン確認処理
	bool ExistsScene(const char* sceneName);

	//クリア処理
	void Clear();

private:
	//シーンコンテナ
	std::unordered_map<std::string, BaseScene*> sceneContainer;

	//現在のシーン、一つ前のシーン
	BaseScene *current, *prev;

	//シーン切り替え（内部処理）
	void _ChengeScene(std::string next);

	//staticインスタンス
	static SceneManager* mInstance;
};

#endif