//=====================================
//
// パッセンジャーコントローラ[PassengerController.cpp]
// 機能：パッセンジャー管理クラス
// Author:GP12B332 19 染谷武志
//
//=====================================
#include "PassengerController.h"
#include <algorithm>
#include <fstream>
#include <string>
#include "../../Framework/String/String.h"
#include "../../Framework/Resource/ResourceManager.h"

//**************************************
// クラスのメンバ変数初期化
//**************************************
const int PassengerController::PassengerReserve = 1000;

//=====================================
// コンストラクタ
//=====================================
PassengerController::PassengerController(Field::FieldLevel level) :
	callback(nullptr), currentLevel(level)
{
	modelVector.reserve(PassengerReserve);
}

//=====================================
// デストラクタ
//=====================================
PassengerController::~PassengerController()
{
	for (auto& vec : modelVector)
	{
		SAFE_DELETE(vec);
	}
	modelVector.clear();
}

//=====================================
// 更新
//=====================================
void PassengerController::Update()
{
	for (auto& actor : modelVector)
	{
		actor->Update();
	}

	if (currentLevel == Field::World)
	{
		// メッシュ切り替えの確認
		CheckPassengerMesh();
	}
}

//=====================================
// 描画
//=====================================
void PassengerController::Draw()
{
	for (auto& actor : modelVector)
	{
		actor->Draw();
	}
}

//=====================================
// パッセンジャーのセット
//=====================================
void PassengerController::SetPassenger(std::deque<D3DXVECTOR3>& root)
{
	bool check = false;
	int sub = 0;
	// vectorの内部に未使用のものがあるか確認
	for (auto& vec : modelVector)
	{
		if (!vec->IsActive())
		{
			check = true;
			break;
		}
		sub++;
	}

	if (check)
	{
		modelVector[sub]->SetActor(root, currentLevel);
	}
	else
	{
		PassengerModel *model = new PassengerModel(root, currentLevel, &callback);
		modelVector.push_back(model);
	}
}

//=====================================
// コールバック設定処理
//=====================================
void PassengerController::SetCallbackOnReach(const std::function<void(const D3DXVECTOR3&)>& callback)
{
	this->callback = callback;
}

//=====================================
// PlaceActorに合わせてパッセンジャーの種類を切り替え（FieldLevel = Worldでのみ使用）
//=====================================
void PassengerController::CheckPassengerMesh()
{
	for (auto& model : modelVector)
	{
		// PlaceActorから足元のフィールドの種類を取得
		int type = continentMap[model->GetFieldPosition()];

		// フィールドのタイプが陸、アクターのタイプが舟の場合
		if (type == 0 && model->GetType() == PassengerActor::Ship)
		{
			model->ChangeMesh("Train");
			model->SetType(PassengerActor::Train);
		}
		// フィールドのタイプが海、アクターのタイプが電車の場合
		else if (type == -1 && model->GetType() == PassengerActor::Train)
		{
			model->ChangeMesh("Ship");
			model->SetType(PassengerActor::Ship);
		}
	}
}

//=====================================
// CSV読み込み
//=====================================
void PassengerController::LoadCSV(const char* path)
{
	if (initializedMap)
		return;

	std::fstream stream(path);

	std::string line;		// 行
	const char Delim = ',';	// 区切り文字
	int x = 0;
	int z = 0;

	// 終わりまで読み込み続ける
	while (std::getline(stream, line))
	{
		// 1行分読み込んだデータを区切り文字で分割する
		std::vector<std::string> subStr;
		String::Split(subStr, line, Delim);

		x = 0;

		// 分割したデータごとにmapを作成
		for (auto&& str : subStr)
		{
			int sub = std::stoi(str);
			continentMap.emplace(Field::FieldPosition(x, z), sub);

			x++;
		}
		z++;
	}

	// 行数と列数を保存
	mapRowMax = x;
	mapColumMax = z;

	initializedMap = true;
}

//=====================================
// リソース読み込み
//=====================================
void PassengerController::LoadResource()
{
	ResourceManager::Instance()->LoadMesh("Car", "data/MODEL/PassengerActor/ToonCar.x");
	ResourceManager::Instance()->LoadMesh("Train", "data/MODEL/PassengerActor/PassengerTrain.x");
	ResourceManager::Instance()->LoadMesh("Ship", "data/MODEL/PassengerActor/Boat.x");
	ResourceManager::Instance()->LoadMesh("Rocket", "data/MODEL/PassengerActor/PassengerSpace.x");
}

//=====================================
// 陸or海のデータが書き換わった場合こちらを呼び出す
//=====================================
void PassengerController::RewriteMap(const Field::FieldPosition& pos, const Geography& data)
{
	continentMap[pos] = data;
}