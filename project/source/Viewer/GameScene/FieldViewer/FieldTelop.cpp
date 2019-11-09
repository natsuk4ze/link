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

//アニメーションの数
static const int animMax = 4;

//テキストアニメーション開始位置
static const float textStartPositionY[animMax] = {
	SCREEN_CENTER_Y/1.9f,
	SCREEN_CENTER_Y/1.9f,
	SCREEN_CENTER_Y/2.7,
	SCREEN_CENTER_Y/2.7
};

//テキストアニメーション終了位置
static const float textEndPositionY[animMax] = {
	SCREEN_CENTER_Y/1.9f,
	SCREEN_CENTER_Y/2.7,
	SCREEN_CENTER_Y/2.7,
	SCREEN_CENTER_Y/2.7 
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
	10,
	80
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
	text->LoadTexture("data/TEXTURE/Viewer/FieldViewer/FieldTelop/TextCity.png");
	text->size = D3DXVECTOR3(512, 128.0f, 0.0f);
	text->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	text->position = D3DXVECTOR3(SCREEN_CENTER_X, textStartPositionY[0], 0.0f);
	text->MakeVertex();

	//ライン
	line = new BaseViewerDrawer();
	line->LoadTexture("data/TEXTURE/Viewer/FieldViewer/FieldTelop/Line.png");
	line->size = D3DXVECTOR3(0.0f, 32.0f, 0.0f);
	line->rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	line->position = D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y/2, 0.0f);
	line->MakeVertex();
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
	DrawTelopText();
}

//=============================================================================
// テロップ再生処理
//=============================================================================
void FieldTelop::Play()
{
	//再生中なら実行
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
// テキスト描画処理
//=============================================================================
void FieldTelop::DrawTelopText(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	float percant;
	float t;
	float y;

	t = line->position.y - textEndPositionY[Text_Raise];

	//テキストの座標がラインの座標より高い位置にきた時から描画開始
	if (text->position.y <= line->position.y)
	{
		y = text->position.y - textEndPositionY[Text_Raise];
		percant = 1.0f - (y / t);
	}
	else
	{
		percant = 0.0f;
	}

	// テクスチャ座標の設定
	text->vertexWk[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	text->vertexWk[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	text->vertexWk[2].tex = D3DXVECTOR2(0.0f, 1.0f*percant);
	text->vertexWk[3].tex = D3DXVECTOR2(1.0f, 1.0f*percant);

	// 頂点座標の設定
	text->vertexWk[0].vtx = text->position + D3DXVECTOR3(-text->size.x / 2, -text->size.y / 2, 0.0f);
	text->vertexWk[1].vtx = text->position + D3DXVECTOR3(text->size.x / 2, -text->size.y / 2, 0.0f);
	text->vertexWk[2].vtx = text->position + D3DXVECTOR3(-text->size.x / 2, text->size.y / 2*percant, 0.0f);
	text->vertexWk[3].vtx = text->position + D3DXVECTOR3(text->size.x / 2, text->size.y / 2*percant, 0.0f);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	pDevice->SetTexture(0, text->texture);

	// ポリゴンの描画
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, text->vertexWk, sizeof(VERTEX_2D));
}

//=============================================================================
// テロップセット処理
//=============================================================================
void FieldTelop::Set(TelopID id, std::function<void(void)> Callback)
{
	//再生状態にする
	isPlaying = true;

	//テロップ再生終了通知
	this->Callback = Callback;
}
