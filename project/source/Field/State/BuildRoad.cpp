//=====================================
//
//テンプレート処理[BuildRoad.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BuildRoad.h"
#include "../Controller/FieldInput.h"
#include "../Place/OperatePlaceContainer.h"
#include "../Place/FieldPlaceContainer.h"
#include "../Object/FieldCursor.h"
#include "../Controller/FieldDevelopper.h"

namespace Field
{
	/**************************************
	入場処理
	***************************************/
	void FieldController::BuildRoadState::OnStart(FieldController & entity)
	{
		//ルートの開始点を取得
		Model::PlaceModel* start = entity.GetPlace();

		//ルートの開始を試みる
		bool result = entity.operateContainer->BeginRoute(start);

		//開始できなかったらIdle状態へ遷移する
		if (!result)
		{
			entity.ChangeState(State::Idle);
		}
	}

	/**************************************
	入場処理
	***************************************/
	FieldController::State FieldController::BuildRoadState::OnUpdate(FieldController & entity)
	{
		//次のステート
		State next = State::Build;

		//カーソル位置のプレイスを操作対象として追加
		Model::PlaceModel* place = entity.GetPlace();
		entity.operateContainer->AddRoute(place);

		//Zキーが押されたら操作対象のプレイスを道に変える
		//TODO：キーボード以外の入力にも対応
		if (entity.input->GetBuildTrigger())
		{
			if (entity.operateContainer->EndRoute())
			{
				entity.developper->BuildRoad();
				entity.operateContainer->Clear();
				next = State::Idle;
			}
		}

		//Xキーが押されたらIdleステートへ遷移
		if (entity.input->GetBuildCancel())
		{
			entity.operateContainer->Clear();
			next = State::Idle;
		}

		return next;
	}

}