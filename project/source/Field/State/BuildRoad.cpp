//=====================================
//
//フィールドの道建設ステート処理[BuildRoad.cpp]
//Author:GP12A332 21 立花雄太
//
//=====================================
#include "BuildRoad.h"
#include "../Controller/FieldInput.h"
#include "../Place/OperatePlaceContainer.h"
#include "../Place/FieldPlaceContainer.h"
#include "../Object/FieldCursor.h"
#include "../Controller/FieldDevelopper.h"
#include "../Place/FieldPlaceModel.h"
#include "../../Viewer/GameScene/FieldViewer/OperationExplanationViewer.h"
#include "../../Viewer/GameScene/Controller/FieldViewer.h"
#include "../PlaceActorController.h"

namespace Field
{
	/**************************************
	入場処理
	***************************************/
	void FieldController::BuildRoadState::OnStart(FieldController & entity)
	{
		//ルートの開始点を取得
		Model::PlaceModel* start = entity.GetPlace();
		bool isSea = entity.placeActController->IsOnSea(start->GetPosition());

		//ルートの開始を試みる
		bool result = entity.operateContainer->BeginRoute(start, isSea);

		//開始できなかったらIdle状態へ遷移する
		if (!result)
		{
			entity.ChangeState(State::Idle);
		}
	}

	/**************************************
	更新処理
	***************************************/
	FieldController::State FieldController::BuildRoadState::OnUpdate(FieldController & entity)
	{
		//次のステート
		State next = State::Build;

		//カーソル位置のプレイスを操作対象として追加
		Model::PlaceModel* place = entity.GetPlace();
		bool isSea = entity.placeActController->IsOnSea(place->GetPosition());
		entity.operateContainer->AddRoute(place, isSea);

		//操作説明を更新
		entity.operationZ = entity.operateContainer->EndRoute() ?
			OperationExplanationViewer::OperationID::Z_Build :
			OperationExplanationViewer::OperationID::Z_None;

		entity.operationX = OperationExplanationViewer::OperationID::X_Cancel;

		entity.operationSpace = OperationExplanationViewer::OperationID::Space_Change;

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
			else
			{
				//エラーメッセージの表示
				entity.viewer->SetFieldErroMessage(FieldErrorMessage::ErroID::NotConnection);
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