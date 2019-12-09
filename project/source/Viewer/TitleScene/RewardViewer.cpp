//=============================================================================
//
// リワードビューアクラス [RewardViewer.cpp]
// Author : HAL東京 GP12B332 41 頼凱興
//
//=============================================================================
#include "../../../main.h"
#include "RewardViewer.h"
#include "../../Viewer/Framework/ViewerDrawer/TextureDrawer.h"
#include "../../Reward/RewardController.h"

#include "../../../Framework/Task/TaskManager.h"
#include "../../../Framework/Renderer2D/TextViewer.h"
#include "../../../Framework/Tool/DebugWindow.h"
#include "../../../Framework/Input/input.h"
#include <string>
using std::string;

// カーソル移動の間隔
const float MoveInterval = 218.0f;
const float CharInterval = 70.0f;
const int NameDigitalMax = 3;
const D3DXVECTOR3 DefaultCursorPos = D3DXVECTOR3(633.0f, 322.0f, 0.0f);
const D3DXVECTOR3 DefaultAchieverPos = D3DXVECTOR3(1400.0f, 1030.0f, 0.0f);
const string RewardText[10] =
{
	"防衛(連打)系イベント3回クリア",
	"山を20個破壊する",
	"橋を15本掛ける",
	"1つの町のリンクレベルが15に達した",
	"マイナスイベントを10回見る",
	"プラスイベントを20回見る",
	"道を250マス引く",
	"AIレベルが 1000000000000に達する",
	"マイナスイベントを全て見る",
	"プラスイベントを全て見る",
};


//=============================================================================
// コンストラクタ
//=============================================================================
RewardViewer::RewardViewer(void)
{
	isPlaying = false;

	TextureVec.push_back(Title = new TextureDrawer(D3DXVECTOR2(1024.0f, 171.0f)));
	Title->LoadTexture("data/TEXTURE/Title/RewardViewer/RewardTitle.png");
	Title->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, 100.0f, 0.0f));

	TextureVec.push_back(RewardIcon = new TextureDrawer(D3DXVECTOR2(872.0f, 654.0f)));
	RewardIcon->LoadTexture("data/TEXTURE/Title/RewardViewer/RewardIcon.png");
	RewardIcon->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, SCREEN_CENTER_Y, 0.0f));

	TextureVec.push_back(RewardFrame = new TextureDrawer(D3DXVECTOR2(1500.0f, 245.0f)));
	RewardFrame->LoadTexture("data/TEXTURE/Title/RewardViewer/RewardFrame.png");
	RewardFrame->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X, 960.0f, 0.0f));

	TextureVec.push_back(RewardName = new TextureDrawer(D3DXVECTOR2(768.0f, 720.0f), 1, 10));
	RewardName->LoadTexture("data/TEXTURE/Title/RewardViewer/RewardName.png");
	RewardName->SetPosition(D3DXVECTOR3(760.0f, 920.0f, 0.0f));

	TextureVec.push_back(FirstAchiever = new TextureDrawer(D3DXVECTOR2(512.0f, 128.0f)));
	FirstAchiever->LoadTexture("data/TEXTURE/Title/RewardViewer/FirstAchiever.png");
	FirstAchiever->SetPosition(D3DXVECTOR3(SCREEN_CENTER_X + 150.0f, 1040.0f, 0.0f));

	TextureVec.push_back(Unachieved = new TextureDrawer(D3DXVECTOR2(512.0f, 128.0f)));
	Unachieved->LoadTexture("data/TEXTURE/Title/RewardViewer/Unachieved.png");
	Unachieved->SetPosition(D3DXVECTOR3(1400.0f, 1040.0f, 0.0f));
	Unachieved->SetScale(0.8f);

	TextureVec.push_back(Cursor = new TextureDrawer(D3DXVECTOR2(218.0f, 218.0f)));
	Cursor->LoadTexture("data/TEXTURE/Title/RewardViewer/Cursor.png");
	Cursor->SetPosition(DefaultCursorPos);

	PlayerName = new TextureDrawer(D3DXVECTOR2(1536.0f, 1536.0f), 6, 6);
	PlayerName->LoadTexture("data/TEXTURE/Viewer/NameEntryViewer/NameEntryReelViewer/Character.png");
	PlayerName->SetPosition(DefaultAchieverPos);
	PlayerName->SetScale(0.5f);

	Text = new TextViewer("Makinas-4-Square", 60);
	Text->SetPos(480, 980);
	Text->SetText(RewardText[0]);

	PlayerNameInt.reserve(3);
}

//=============================================================================
// デストラクタ
//=============================================================================
RewardViewer::~RewardViewer()
{
	Utility::DeleteContainer(TextureVec);
	SAFE_DELETE(Text);
}

//=============================================================================
// 初期化
//=============================================================================
void RewardViewer::Init(void)
{
	isPlaying = true;

	//const int NameDigitalMax = 3;

	//int Num = 0;
	//for (auto &Name : PlayerNameInt)
	//{
	//	if (RewardController::Instance()->CheckFirstAchieved((RC::Type)Num))
	//	{
	//		// 最初の達成者の名前を取得
	//	}
	//	Num++;
	//}
}

//=============================================================================
// 更新
//=============================================================================
void RewardViewer::Update()
{
	if (!isPlaying)
		return;

	//Debug::Begin("RewardTexture");
	//static D3DXVECTOR3 AchieverPos = FirstAchiever->GetPosition();
	//static D3DXVECTOR3 UnachievedPos = Unachieved->GetPosition();
	//static D3DXVECTOR3 PlayerNamePos = PlayerName->GetPosition();
	//static D3DXVECTOR3 TitlePos = Title->GetPosition();
	//static D3DXVECTOR3 CursorPosTest = Cursor->GetPosition();
	//static D3DXVECTOR3 FramePos = RewardFrame->GetPosition();
	//static D3DXVECTOR3 NamePos = RewardName->GetPosition();
	//static D3DXVECTOR2 TextPos = D3DXVECTOR2(480, 980);
	//Debug::Input("TitlePos", TitlePos);
	//Debug::Input("CursorPos", CursorPosTest);
	//Debug::Input("FramePos", FramePos);
	//Debug::Input("NamePos", NamePos);
	//Debug::Input("TextPos", TextPos);
	//Debug::Input("AchieverPos", AchieverPos);
	//Debug::Input("UnachievedPos", UnachievedPos);
	//Debug::Input("PlayerNamePos", PlayerNamePos);
	//Title->SetPosition(TitlePos);
	//Cursor->SetPosition(CursorPosTest);
	//RewardFrame->SetPosition(FramePos);
	//RewardName->SetPosition(NamePos);
	//FirstAchiever->SetPosition(AchieverPos);
	//Unachieved->SetPosition(UnachievedPos);
	//PlayerName->SetPosition(PlayerNamePos);
	//Text->SetPos((int)TextPos.x, (int)TextPos.y);
	//Debug::End();

	CursorMove();

	// 終了
	if (Keyboard::GetTrigger(DIK_X) || GamePad::GetTrigger(0, BUTTON_X))
	{
		isPlaying = false;
	}
}

//=============================================================================
// 描画
//=============================================================================
void RewardViewer::Draw()
{
	if (!isPlaying)
		return;

	LPDIRECT3DDEVICE9 Device = GetDevice();
	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	// テクスチャ
	for (auto &Texture : TextureVec)
	{
		Texture->Draw();
	}

	if (!PlayerNameInt.empty())
	{
		for (int i = 0; i < NameDigitalMax; i++)
		{
			PlayerName->SetPosition(DefaultAchieverPos + D3DXVECTOR3(CharInterval * i, 0.0f, 0.0f));
			PlayerName->SetIndex(PlayerNameInt.at(i));
			PlayerName->Draw();
		}
	}

	Device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);

	// テキスト
	Text->Draw(true);
}

//=============================================================================
// カーソル移動の座標計算
//=============================================================================
void RewardViewer::CursorMove(void)
{
	static int DevideX = 0;
	static int DevideY = 0;

	// 左
	if (Keyboard::GetTrigger(DIK_LEFT) || GamePad::GetTriggerPOV(0, POV_LEFT))
	{
		DevideX--;

		if (DevideX < 0)
		{
			if (DevideY != 2)
			{
				DevideX = 3;
			}
			else
			{
				DevideX = 1;
			}
		}
	}
	// 右
	else if (Keyboard::GetTrigger(DIK_RIGHT) || GamePad::GetTriggerPOV(0, POV_RIGHT))
	{
		DevideX++;

		if (DevideY != 2)
		{
			DevideX %= 4;
		}
		else
		{
			DevideX %= 2;
		}
	}

	// 上
	if (Keyboard::GetTrigger(DIK_UP) || GamePad::GetTriggerPOV(0, POV_UP))
	{
		DevideY--;

		if (DevideY < 0)
		{
			if (DevideX > 1)
			{
				DevideY = 1;
			}
			else
			{
				DevideY = 2;
			}
		}
	}
	// 下
	else if (Keyboard::GetTrigger(DIK_DOWN) || GamePad::GetTriggerPOV(0, POV_DOWN))
	{
		DevideY++;

		if (DevideX > 1)
		{
			DevideY %= 2;
		}
		else
		{
			DevideY %= 3;
		}
	}

	// カーソル座標設定
	D3DXVECTOR3 CursorPos = DefaultCursorPos + D3DXVECTOR3(MoveInterval * DevideX, MoveInterval * DevideY, 0.0f);
	Cursor->SetPosition(CursorPos);

	int Index = DevideX + DevideY * 4;
	// テクスチャのインデックス設定
	RewardName->SetIndex(Index);
	// 説明のテキスト設定
	Text->SetText(RewardText[Index]);
	// 達成者の名前を設定
	ReceiveName((RC::Type)Index);
}

//=============================================================================
// 最初の達成者の名前を取得
//=============================================================================
void RewardViewer::ReceiveName(RewardConfig::Type rewardType)
{
	PlayerNameInt.clear();

	if (RewardController::Instance()->CheckFirstAchieved(rewardType))
	{
		FirstAchiever->SetVisible(true);
		PlayerName->SetVisible(true);
		Unachieved->SetVisible(false);

		// コントローラーから達成者の名前を取得
		//RewardController::Instance()->GetName();
	}
	else
	{
		FirstAchiever->SetVisible(false);
		PlayerName->SetVisible(false);
		Unachieved->SetVisible(true);
	}
}
