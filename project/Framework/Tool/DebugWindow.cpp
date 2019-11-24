//=====================================
//
//デバッグウィンドウ処理[DebugWindow.cpp]
//Author:GP12B332 21 立花雄太
//
//=====================================
#include "debugWindow.h"
#include "../../Library/imgui/imgui.h"
#include "../../Library/imgui/imgui_impl_win32.h"
#include "../../Library/imgui/imgui_impl_dx9.h"
#include "../Input/input.h"

/**************************************
マクロ定義
***************************************/
#define INTERBAL_GETTIMER		(20)

/**************************************
構造体定義
***************************************/

/**************************************
グローバル変数
***************************************/
LARGE_INTEGER timeCountBegin;
static unsigned int cntFrame = 0;
static bool enableDraw = true;
const unsigned Debug::MaxLog = 50;
std::deque<std::string> Debug::textLog;

/**************************************
プロトタイプ宣言
***************************************/
IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

/**************************************
デバッグウィンドウ用コールバック
***************************************/
LRESULT Debug::WindPrcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
#ifdef USE_DEBUGFUNC
	return ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);
#else
	return S_OK;
#endif
}

/**************************************
初期化処理
***************************************/
void Debug::Init(HWND hWnd, LPDIRECT3DDEVICE9 pDevice)
{
#ifdef USE_DEBUGFUNC
	ImGui::CreateContext();

	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(pDevice);

	ImGui::StyleColorsDark();
#endif
}

/**************************************
終了処理
***************************************/
void Debug::Uninit()
{
#ifdef USE_DEBUGFUNC
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
#endif
}

/**************************************
更新処理
***************************************/
void Debug::Update(void)
{
#ifdef USE_DEBUGFUNC
	if (Keyboard::GetTrigger(DIK_D) && Keyboard::GetPress(DIK_LCONTROL))
	{
		enableDraw = !enableDraw;
	}

	ImGui_ImplWin32_NewFrame();
	ImGui_ImplDX9_NewFrame();
	ImGui::NewFrame();

	cntFrame++;
#endif
}

/**************************************
描画処理
***************************************/
void Debug::Draw(void)
{
#ifdef USE_DEBUGFUNC
	if (!enableDraw)
	{
		ImGui::EndFrame();
		return;
	}

	Debug::Begin("Log");
	for(auto&& log : textLog)
	{
		Text(log.c_str());
	}
	Debug::End();
	
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
#endif
}

/*************************************
デバッグウィンドウ開始処理
***************************************/
void Debug::Begin(const char *label, bool menuBar)
{
#ifdef USE_DEBUGFUNC
	ImGuiWindowFlags flag = 0;

	if (menuBar) flag |= ImGuiWindowFlags_MenuBar;

	ImGui::Begin(label, nullptr, flag);
#endif
}

/*************************************
デバッグウィンドウ終了処理
***************************************/
void Debug::End()
{
#ifdef USE_DEBUGFUNC
	ImGui::End();
#endif
}

/*************************************
汎用デバッグテキスト表示
***************************************/
void Debug::Log(const char *str, ...)
{
#ifdef USE_DEBUGFUNC
	va_list list;			// 可変引数を処理する為に使用する変数
	char *pCur;
	char aBuf[256] = { "\0" };
	char aWk[32];

	// 可変引数にアクセスする前の初期処理
	va_start(list, str);

	pCur = (char *)str;
	for (; *pCur; ++pCur)
	{
		if (*pCur != '%')
		{
			sprintf(aWk, "%c", *pCur);
		}
		else
		{
			pCur++;

			switch (*pCur)
			{
			case 'd':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%d", va_arg(list, int));
				break;

			case 'f':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%.2f", va_arg(list, double));		// double型で指定
				break;

			case 's':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%s", va_arg(list, char*));
				break;

			case 'c':
				// 可変引数にアクセスしてその変数を取り出す処理
				sprintf(aWk, "%c", va_arg(list, char));
				break;

			default:
				sprintf(aWk, "%c", *pCur);
				break;
			}
		}
		strcat(aBuf, aWk);
	}

	// 可変引数にアクセスした後の終了処理
	va_end(list);
	
	//TextLogに格納
	if (textLog.size() == MaxLog)
		textLog.pop_front();
	textLog.push_back(std::string(aBuf));

#endif
}

/*************************************
デバッグテキスト表示処理
***************************************/
void Debug::Text(const char *str, ...)
{
#ifdef USE_DEBUGFUNC
	va_list ap;
	va_start(ap, str);
	ImGui::TextV(str, ap);
	//ImGui::Text(str, ap);
	va_end(ap);
#endif
}

/*************************************
デバッグテキスト表示処理
***************************************/
void Debug::Text(const D3DXVECTOR3& arg, const char* name)
{
#ifdef USE_DEBUGFUNC
	Text("%s : %f %f, %f", name, arg.x, arg.y, arg.z);
#endif
}

/*************************************
デバッグボタン表示処理
***************************************/
bool Debug::Button(const char *label)
{
#ifdef USE_DEBUGFUNC
	return ImGui::Button(label);
#else
	return false;
#endif
}

/*************************************
ラジオボタン処理
***************************************/
bool Debug::RadioButton(const char* label, int& output, int val)
{
#ifdef USE_DEBUGFUNC
	return ImGui::RadioButton(label, &output, val);
#else
	return false;
#endif
}

/*************************************
チェックボックス処理
***************************************/
bool Debug::CheckBox(const char* label, bool& val)
{
#ifdef USE_DEBUGFUNC
	return ImGui::Checkbox(label, &val);
#else
	return false;
#endif
}

/*************************************
入力処理
***************************************/
bool Debug::Input(const char* label, float& out)
{
#ifdef USE_DEBUGFUNC
	return ImGui::InputFloat(label, &out);
#else
	return false;
#endif
}

/*************************************
入力処理
***************************************/
bool Debug::Input(const char* label, int& out)
{
#ifdef USE_DEBUGFUNC
	return ImGui::InputInt(label, &out);
#else
	return false;
#endif
}

/*************************************
入力処理
***************************************/
bool Debug::Input(const char* label, char* out, size_t sizeBuff)
{
#ifdef USE_DEBUGFUNC
	return ImGui::InputText(label, out, sizeBuff);
#else
	return false;
#endif
}

/*************************************
入力処理
***************************************/
bool Debug::Input(const char* label, D3DXVECTOR3& out)
{
#ifdef USE_DEBUGFUNC
	return ImGui::InputFloat3(label, (float*)&out);
#else
	return false;
#endif
}

/*************************************
入力処理
***************************************/
bool Debug::Input(const char* label, D3DXVECTOR2& out)
{
#ifdef USE_DEBUGFUNC
	return ImGui::InputFloat2(label, (float*)&out);
#else
	return false;
#endif
}

/*************************************
入力処理
***************************************/
bool Debug::Input(const char* label, std::string& out)
{
#ifdef USE_DEBUGFUNC
	char tmp[128];
	strcpy(tmp, out.c_str());
	bool res = ImGui::InputText(label, tmp, 128);
	if (res)
	{
		out = std::string(tmp);
	}
	return res;
#else
	return false;
#endif
}

/*************************************
デバッグスライダー処理
***************************************/
bool Debug::Slider(const char *label, float& adr, float min, float max)
{
#ifdef USE_DEBUGFUNC
	return ImGui::SliderFloat(label, &adr, min, max);

#else
	return false;
#endif
}

/*************************************
デバッグスライダー処理
***************************************/
bool Debug::Slider(const char* label, int& out, int min, int max)
{
#ifdef USE_DEBUGFUNC
	return ImGui::SliderInt(label, &out, min, max);
#else
	return false;
#endif
}

/*************************************
デバッグスライダー処理
***************************************/
bool Debug::Slider(const char* label, D3DXVECTOR3& out, const D3DXVECTOR3& min, const D3DXVECTOR3& max)
{
#ifdef USE_DEBUGFUNC
	bool res = false;
	res |= ImGui::SliderFloat((std::string(label) + std::string(".x")).c_str(), &out.x, min.x, max.x);
	res |= ImGui::SliderFloat((std::string(label) + std::string(".y")).c_str(), &out.y, min.y, max.y);
	res |= ImGui::SliderFloat((std::string(label) + std::string(".z")).c_str(), &out.z, min.z, max.z);
	return res;
#else
	return false;
#endif
}

/*************************************
デバッグスライダー処理
***************************************/
bool Debug::Slider(const char* label, D3DXVECTOR2& out, const D3DXVECTOR2& min, const D3DXVECTOR2& max)
{
#ifdef USE_DEBUGFUNC
	bool res = false;
	res |= ImGui::SliderFloat((std::string(label) + std::string(".x")).c_str(), &out.x, min.x, max.x);
	res |= ImGui::SliderFloat((std::string(label) + std::string(".y")).c_str(), &out.y, min.x, max.y);
	return res;
#else
	return false;
#endif
}

/*************************************
デバッグカラーピッカー処理
***************************************/
bool Debug::ColorEdit(const char *label, D3DXCOLOR& out)
{
#ifdef USE_DEBUGFUNC
	return ImGui::ColorEdit4(label, (float*)&out);
#else
	return false;
#endif
}

/*************************************
テクスチャ表示処理
***************************************/
void Debug::DrawTexture(LPDIRECT3DTEXTURE9 texture, const D3DXVECTOR2& size)
{
#ifdef USE_DEBUGFUNC
	ImGui::Image((void*)texture, ImVec2(size.x, size.y));
#endif
}


/*************************************
プログレスバー処理
***************************************/
void Debug::ProgressBar(const char* label, float fraction, const D3DXVECTOR2& size)
{
#ifdef USE_DEBUGFUNC
	ImGui::ProgressBar(fraction, ImVec2(size.x, size.y), label);
#endif
}

/*************************************
デバッグウィンドウ改行処理
***************************************/
void Debug::NewLine(void)
{
#ifdef USE_DEBUGFUNC
	ImGui::NewLine();
#endif
}

/*************************************
デバッグウィンドウ連続行処理
***************************************/
void Debug::SameLine(void)
{
#ifdef USE_DEBUGFUNC
	ImGui::SameLine();
#endif
}

/*************************************
ツリー構造展開処理
***************************************/
void Debug::ExpandTree(bool isOpen)
{
#ifdef USE_DEBUGFUNC
	ImGui::SetNextTreeNodeOpen(isOpen, ImGuiSetCond_Once);
#endif
}

/*************************************
ツリー構造プッシュ処理
***************************************/
bool Debug::PushTree(const char *label)
{
#ifdef USE_DEBUGFUNC
	return ImGui::TreeNode(label);
#else
	return  false;
#endif
}

/*************************************
ツリー構造ポップ処理
***************************************/
void Debug::PopTree(void)
{
#ifdef USE_DEBUGFUNC
	ImGui::TreePop();
#endif
}

/*************************************
メニューバー設定開始処理
***************************************/
bool Debug::BeginMenu()
{
#ifdef USE_DEBUGFUNC
	return ImGui::BeginMenuBar();
#else
	return false;
#endif
}

/*************************************
メニューバー設定終了処理
***************************************/
void Debug::EndMenu()
{
#ifdef USE_DEBUGFUNC
	ImGui::EndMenuBar();
#endif
}

/*************************************
メニュー設定終了処理
***************************************/
bool Debug::BeginMenuItem(const char* label)
{
#ifdef USE_DEBUGFUNC
	return ImGui::BeginMenu(label);
#else
	return false;
#endif
}

/*************************************
メニュー設定終了処理
***************************************/
void Debug::EndMenuItem()
{
#ifdef  USE_DEBUGFUNC
	ImGui::EndMenu();
#endif //  USE_DEBUGFUNC

}

/*************************************
子供開始処理
***************************************/
bool Debug::BeginChild(const char* id)
{
#ifdef USE_DEBUGFUNC
	return ImGui::BeginChild(ImGui::GetID((void*)0));
#else
	return false;
#endif
}

/*************************************
子供終了処理
***************************************/
void Debug::EndChild()
{
#ifdef USE_DEBUGFUNC
	ImGui::EndChild();
#endif
}

///**************************************
//高解像度タイマーでの計測開始処理
//***************************************/
//void BeginTimerCount(void)
//{
//#ifdef USE_DEBUGFUNC
//	QueryPerformanceCounter(&timeCountBegin);
//#endif
//}
//
///**************************************
//計測開始からの経過時間[単位：msec]
//***************************************/
//double GetProgressTimerCount(void)
//{
//#ifdef USE_DEBUGFUNC
//	//タイマーの周波数を取得
//	LARGE_INTEGER frequencyTimer;
//	QueryPerformanceFrequency(&frequencyTimer);
//
//	//カウント取得
//	LARGE_INTEGER timeCurrent;
//	QueryPerformanceCounter(&timeCurrent);
//
//	//計測開始からの経過時間[msec]を計算
//	LONGLONG span = timeCurrent.QuadPart - timeCountBegin.QuadPart;
//	double msec = (double)span * 1000 / (double)frequencyTimer.QuadPart;
//
//	return msec;
//#else 
//	return 0.0f;
//#endif
//}
//
///**************************************
//タイマーカウント取得処理（20フレームおきに動作）
//***************************************/
//void GetTimerCount(LARGE_INTEGER *ptr)
//{
//#ifdef	USE_DEBUGFUNC
//	if (cntFrame % INTERBAL_GETTIMER != 0)
//		return;
//
//	QueryPerformanceCounter(ptr);
//#endif
//}
//
///**************************************
//経過時間取得処理[msec]
//***************************************/
//double CalcProgressTime(LARGE_INTEGER start, LARGE_INTEGER end)
//{
//#ifdef USE_DEBUGFUNC
//	//タイマーの周波数取得
//	LARGE_INTEGER frequency;
//	QueryPerformanceFrequency(&frequency);
//
//	//経過時間を計算
//	LONGLONG span = end.QuadPart - start.QuadPart;
//	double msec = (double)span * 1000.0f / (double)frequency.QuadPart;
//
//	return msec;
//#else
//	return 0.0f;
//#endif
//}
