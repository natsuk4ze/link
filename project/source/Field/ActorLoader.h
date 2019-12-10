//=====================================
//
// ActorLoader.h
// 機能:アクターのモデルローダ
// Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _ACTORLOADER_H_
#define _ACTORLOADER_H_

#include "../../main.h"

#include <map>

namespace Field::Actor
{
	/**************************************
	前方宣言
	***************************************/

	/**************************************
	クラス定義
	***************************************/
	class ActorLoader
	{
	public:
		const static std::string CityTag[];			//街モデルのリソースタグ
		const static std::string StraightTag[];		//直線道のリソースタグ
		const static std::string CurveTag[];		//カーブ道のリソースタグ
		const static std::string TJunctionTag[];	//T字路のリソースタグ
		const static std::string CrossTag[];		//十字路のリソースタグ
		const static std::string BridgeTag[];		//橋のリソースタグ
		const static std::string MountainTag[];		//山のリソースタグ

		const static std::string WaterStraight;		//水上の直線道
		const static std::string WaterCurve;		//水上のカーブ
		const static std::string WaterT;			//水上のT字路
		const static std::string WaterCross;		//水上の十字路

		const static std::string WhirlPoolTag;		//渦潮のリソースタグ

		const static std::string GroundTag;			//地面のリソースタグ
		const static std::string RiverTag;			//川のリソースタグ

		const static std::string CityTownTag[];		//町レベルの町モデルリソースタグ
		const static std::string WorldTownTag[];	//世界レベルの町モデルリソースタグ

		//コンストラクタ、デストラクタ
		ActorLoader();
		~ActorLoader();

		//設定ファイルの読み込み
		void LoadConfig();

		//リソースの読み込み
		void LoadResource();

	private:
		std::map<std::string, std::string> modelFileName;	//タグとファイル名の対応マップ

	};
}



#endif