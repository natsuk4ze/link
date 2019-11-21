//=====================================
//
// タイトルビュアー[TitleViewer.h]
// 機能：タイトル画面UI表示
// Author:GP12B332 19 染谷武志
//
//=====================================
#ifndef _TITLEVIEWER_H_
#define _TITLEVIEWER_H_

//**************************************
// クラス定義
//**************************************
class TitleViewer
{
private:
	bool isActive;

public:
	TitleViewer();
	~TitleViewer();

	void Update();
	void Draw();

	void SetActive();
};

#endif
