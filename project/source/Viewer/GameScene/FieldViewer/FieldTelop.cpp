//=============================================================================
//
// フィールドテロップ処理 [FieldTelop.cpp]
// Author : Yu Oohama (bnban987@gmail.com)
//
//=============================================================================
#include "../../../../main.h"
#include"../../../../Framework/Math/Easing.h"
#include "../../../../Framework/Math/TMath.h"
#include "../../Framework/ViewerDrawer/BaseViewerDrawer.h"
#include "FieldTelop.h"

#ifdef _DEBUG

#include "../../../../Framework/Input/input.h"
#include "../../../../Framework/Tool/DebugWindow.h"

#endif

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//テキストのテクスチャパス
static const char *textTexPath[FieldTelop::Max]
{
	"data/TEXTURE/Viewer/FieldViewer/FieldTelop/TextCity.png",
};

//アニメーションの数
static const int animMax = 4;

//テキストアニメーション開始位置
static const float textStartPositionY[animMax] = {
	SCREEN_CENTER_Y,
	SCREEN_CENTER_Y,
	SCREEN_CENTER_Y/3,
	SCREEN_CENTER_Y/3
};

//テキストアニメーション終了位置
static const float textEndPositionY[animMax] = {
	SCREEN_CENTER_Y,
	SCREEN_CENTER_Y/3,
	SCREEN_CENTER_Y/3,
	SCREEN_CENTER_Y/3 
};

//テキストアニメーション種類
static const EaseType animType[animMax] = {
	OutCirc,
	OutCirc,
	InOutCubic,
	InOutCubic
};

//テキストアニメーション間隔(ここを変更するとアニメーションの速さを調整できる)
//*注意(0を入れると無限大になるからアニメーションそのものを削除すること)
static const float animDuration[animMax] = {
	30,
	50,
	20,
	100
};

//アニメーションシーン
enum TelopAnimScene
{
	Line_Draw,
	Text_Raise,
	Wait,
	Telop_FadeOut,
};

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
FieldTelop::FieldTelop()
{
	//テキスト
	text = new BaseViewerDrawer();
	text->size = D3DXVECTOR3(512, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f);
	text->MakeVertex();

	//ライン
	line = new BaseViewerDrawer();
	line->LoadTexture("data/TEXTURE/Viewer/FieldViewer/FieldTelop/Line.png");
	line->size = D3DXVECTOR3(0.0f, 32.0f, 0.0f);
	line->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	line->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y/2, 0.0f);
	line->MakeVertex();

	//コンテナにテクスチャ情報をロードする
	for (int i = 0; i < Max; i++)
	{
		LPDIRECT3DDEVICE9 pDevice = GetDevice();

		LPDIRECT3DTEXTURE9 tTex;

		D3DXCreateTextureFromFile(pDevice,
			textTexPath[i],
			&tTex);

		textTexContainer.push_back(tTex);
	}
}

//*****************************************************************************
// デストラクタ
//*****************************************************************************
FieldTelop::~FieldTelop()
{
	SAFE_DELETE(text);
	SAFE_DELETE(line);
}

//=============================================================================
// 更新処理
//=============================================================================
void FieldTelop::Update()
{
	//テロップ再生処理
	Play();

#ifdef _DEBUG

	Debug::Text("currentAnim:%d", currentAnim);
	Debug::Text("α値:%d", alpha);

#endif

}

//=============================================================================
// 描画処理
//=============================================================================
void FieldTelop::Draw(void)
{
	//再生中なら描画
	if (!isPlaying) return;

	//背景を先に描画
	line->Draw();

	//テキスト
	text->Draw();
}

//=============================================================================
// テロップ再生処理
//=============================================================================
void FieldTelop::Play()
{
	//再生中なら描画
	if (!isPlaying) return;

	//フレーム更新
	countFrame++;

	//時間更新
	animTime = countFrame / animDuration[currentAnim];

	//アニメーションシーンがLine_Drawの間線を引く
	if (currentAnim == Line_Draw)
	{
		DrawLine();
	}

	//アニメーションシーンがTelop_FadeOutの間フェードアウトを実行
	if (currentAnim == Telop_FadeOut)
	{
		FadeOut();
	}

	//ポジションを更新
	text->position.y = Easing::EaseValue(animTime,
		textStartPositionY[currentAnim],
		textEndPositionY[currentAnim],
		animType[currentAnim]);

	//アニメーション更新
	if (countFrame == animDuration[currentAnim])
	{
		countFrame = 0;
		currentAnim++;
	}

	//アニメーション終了
	if (currentAnim >= animMax)
	{
		countFrame = 0;
		currentAnim = 0;
		alpha = 1.0f;
		text->SetAlpha(alpha);
		line->SetAlpha(alpha);
		line->size.x = 0.0f;
		text->position.y = textStartPositionY[0];
		isPlaying = false;

		//ヌルチェック
		if (Callback != nullptr)
		{
			//再生終了の通知
			Callback();
		}
	}
}

//=============================================================================
// ラインを引く処理
//=============================================================================
void FieldTelop::DrawLine(void)
{
	//イージングのスタートとゴールを設定
	float lineEasingStart = 0.0f;
	float lineEasingGoal = 512.0f;

	//線のXサイズを更新
	line->size.x = Easing::EaseValue(animTime, lineEasingStart, lineEasingGoal, animType[Line_Draw]);

	//line->size.xの最大をlineEasingGoalに設定
	Math::WrapAround(line->size.x, lineEasingGoal, line->size.x);
}

//=============================================================================
// フェードアウト処理
//=============================================================================
void FieldTelop::FadeOut(void)
{
	//イージングのスタートとゴールを設定
	float alphaEasingStart = 1.0f;
	float alphaEasingGoal = 0.0f;

	//α値を更新
	alpha = Easing::EaseValue(animTime, alphaEasingStart, alphaEasingGoal, animType[Telop_FadeOut]);

	//alpha->size.xの最大をalphaEasingGoalに設定
	Math::WrapAround(alpha, alphaEasingGoal, alpha);

	text->SetAlpha(alpha);
	line->SetAlpha(alpha);
}

//=============================================================================
// テクスチャ情報受け渡し処理
//=============================================================================
void FieldTelop::PassTexture(TelopID id)
{
	text->texture = textTexContainer[id];
}

//=============================================================================
// テロップセット処理
//=============================================================================
void FieldTelop::Set(TelopID id, std::function<void(void)> Callback)
{
	//テクスチャ情報受け渡し
	PassTexture(id);

	//再生状態にする
	isPlaying = true;

	//テロップ再生終了通知
	this->Callback = Callback;
}
