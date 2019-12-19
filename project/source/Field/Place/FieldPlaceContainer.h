//=====================================
//
//PlaceContainer.h
//機能:プレイスコンテナ
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PLACECONTAINER_H_
#define _PLACECONTAINER_H_

#include "../../../main.h"
#include "PlaceConfig.h"
#include "../FieldConfig.h"

#include <vector>
#include <unordered_map>
#include <functional>

namespace Field::Model
{
	/**************************************
	前方宣言
	***************************************/
	class PlaceModel;
	class TownModel;
	class JunctionModel;

	using JunctionContainer = std::unordered_map<unsigned, JunctionModel*>;
	using TownContainer = std::unordered_map<unsigned, TownModel*>;
	using TownAction = std::function<void(const PlaceModel *start, const PlaceModel *goal, const PlaceModel* town)>;
	using MorphAction = std::function<void(const PlaceModel*, int current, int next)>;

	/**************************************
	クラス定義
	***************************************/
	class PlaceContainer
	{
	public:
		//コンストラクタ、デストラクタ
		PlaceContainer();
		~PlaceContainer();

		//更新処理、描画処理
		void Update();

		//クリア処理
		void Clear();

		//指定したマス目のPlaceModelを取得
		PlaceModel* GetPlace(int x, int z);
		PlaceModel* GetPlace(const FieldPosition& position);

		//全PlaceModel取得処理
		std::vector<PlaceModel*> GetAllPlaces() const;

		//CSVデータ読み込み
		void LoadCSV(const char* filePath);

		//プレイスの行と列の最大数取得
		FieldPosition GetPlaceBorder() const;

		//街が道と繋がったときに呼ばれる処理
		void OnConnectedTown(const PlaceModel* place, const PlaceModel *gate);

		//交差点が作られた際に呼ばれる処理
		void OnCreateJunction(const PlaceModel* place);

		//リンクレベルを計算
		void CalcLinkLevel();

		//AI発展レベル計算
		float CalcDevelopmentLevelAI(float bonus);

		//街全体のリンクレベルを加算
		void AddAllLinkLevel(int num);
		
		//一つの街のリンクレベルを加算
		void AddLinkLevel(int num);

		//混雑度増加バイアスを設定
		void SetTrafficjamBias(float bias);

		//破壊対象のプレイス取得
		const PlaceModel* GetDestroyTarget();

		//街を作れるプレイス取得
		const PlaceModel* GetNonePlace(std::vector<PlaceModel*>* ignoreList = nullptr);

		//街破壊処理
		void DestroyTown(const PlaceModel* target);

		//街作成処理
		void CreateTown(const PlaceModel* target);

		//アトランティス作成処理
		std::vector<const PlaceModel*> CreateAtlantis(const PlaceModel* target);

		//パッセンジャー出発ファンクタ設定
		void SetDepartPassengerFanctor(const TownAction& action);

		//モーフィングファンクタ設定
		void SetMorphingFantor(const MorphAction& action);

		//すべての町の発展レベルを取得する
		std::vector<PlaceData> GetAllTownLevel();

		//リンクレベル取得
		int GetLinkLevel();

		// 繋がった町の数を取得
		int GetTownNum(void) { return this->townContainer.size(); };

#ifdef DEBUG_PLACEMODEL
		void DrawDebug();
#endif

	private:
		const int PlaceMax = 10000;				//プレイスの最大数

		std::vector<PlaceModel*> placeVector;	//PlaceModelコンテナ
		TownContainer townContainer;			//TownModelコンテナ
		JunctionContainer junctionContainer;	//JunctionModelコンテナ

		int placeRowMax;						//1行あたりのプレイス最大数
		int placeColumMax;						//1列あたりのプレイス最大数

		int fieldLinkLevel;						//全Townのリンクレベルの合計

		bool initialized;						//初期化フラグ

		float trafficJamRate;					//混雑度
		float trafficJamBias;					//混雑度バイアス

		TownAction onDepartPassenger;			//街からパッセンジャーが出る時に呼ぶファンクタ
		MorphAction onStartMorph;				//モーフィング開始ファンクタ

		//隣接プレイス作成内部処理
		void MakeAdjacency();
	};
}

#endif