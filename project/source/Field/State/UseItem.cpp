//=====================================
//
//アイテム使用処理[UseItem.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "UseItem.h"
#include "../../../Framework/Input/input.h"
#include "../Place/OperatePlaceContainer.h"
#include "../Place/FieldPlaceContainer.h"
#include "../FieldCursor.h"

namespace Field
{
	/**************************************
	入場処理
	***************************************/
	void FieldController::UseItemState::OnStart(FieldController & entity)
	{
		//ルートの開始点を取得
		Model::PlaceModel* start = entity.GetPlace();

		//ルートの開始を試みる
		bool result = entity.operateContainer->Begin(start);

		//開始できなかったらIdle状態へ遷移する
		if (!result)
		{
			entity.ChangeState(State::Idle);
		}
	}

	/**************************************
	更新処理
	***************************************/
	FieldController::State FieldController::UseItemState::OnUpdate(FieldController & entity)
	{
		//次のステート
		State next = State::Build;

		//カーソル位置のプレイスを操作対象として追加
		Model::PlaceModel* place = entity.GetPlace();
		entity.operateContainer->Add(place);

		//Xキーが押されたら操作対象のプレイスを道に変える
		//TODO：キーボード以外の入力にも対応
		if (Keyboard::GetTrigger(DIK_X))
		{
			if (entity.operateContainer->End())
			{
				PlaceVector vector = entity.operateContainer->GetPlaces();
				entity.DevelopPlace(vector, vector.begin());
			}

			entity.operateContainer->Clear();

			next = State::Idle;
		}

		//Zキーが押されたらIdleステートへ遷移
		if (Keyboard::GetTrigger(DIK_Z))
		{
			next = State::Idle;
		}

		return next;
	}
}