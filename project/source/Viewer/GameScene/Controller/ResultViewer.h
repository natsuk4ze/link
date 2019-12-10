//=============================================================================
//
// 結果ビュアーコントロール処理 [ResultViewer.h]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#ifndef _RESULT_VIEWER_H_
#define _RESULT_VIEWER_H_

#include <vector>
#include <functional>

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class ResultScoreViewer;
class ResultAchieveViewer;
class ResultViewerParam;
class BaseViewer;
class GuideActor;
class SubScreen;
class Camera;

namespace RewardConfig
{
	enum Type : int;
}

//*****************************************************************************
// クラス定義
//*****************************************************************************
class ResultViewer
{
public:
	enum ResultAnimation
	{
		PlayingIn,
		Idle,
		PlayingOut
	};

	ResultViewer();
	~ResultViewer();

	void Update(void);
	void Draw(void);

	//アクティブ状態をセット
	void SetActive(bool flag);

	//パラメータの受け取り処理
	void ReceiveParam(int cityScore,int worldScore,int spaceScore);

	//スコアビューアのアニメーション再生中判定
	ResultAnimation IsPlayingAnimation() const;

	//実績ビューワセット
	void SetAchiveViewer(std::vector<RewardConfig::Type>& rewardContainer, std::function<void()> callback = nullptr);

	//スコアビューワをスライドインさせる
	void SlideScoreViewer(bool isIn);

private:
	std::vector <BaseViewer*> resultViewer;
	ResultScoreViewer * scoreViewer;
	ResultAchieveViewer *achieveViewer;
	ResultViewerParam *viewerParam;

	bool isActive;

	//画面右に表示するロボ
	GuideActor* actor;

	//ロボを描画するレンダリングターゲット
	SubScreen* screen;

	//ロボ描画用のカメラ
	Camera *camera;
};

#endif

