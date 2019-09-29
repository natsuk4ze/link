//=====================================
//
//ポストエフェクトマネージャヘッダ[PostEffectManager.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _POSTEFFECTMANAGER_H_
#define _POSTEFFECTMANAGER_H_

#include "../../main.h"
#include "BaseEffectController.h"
#include "../Pattern/BaseSingleton.h"

#include <vector>

/**************************************
マクロ定義
***************************************/

/**************************************
クラス定義
***************************************/
class PostEffectManager : public BaseSingleton<PostEffectManager>
{
	friend class BaseSingleton<PostEffectManager>;
public:
	void Update();
	void Draw();

	void SetUse(unsigned flgUse);
	void PassDefaultTarget(LPDIRECT3DTEXTURE9 target);

	enum PostEffect
	{
		Bloom,
		CrossFilter,
		ShockBlur,
		SpeedBlur,
		SpikeNoiset,
		Max,
	};

private:
	unsigned flgUse;
	std::vector<BaseEffectController*> effectContainer;

	bool IsUse(unsigned flg);
	bool IsBrightEffect(UINT id);

	PostEffectManager();
	PostEffectManager(const PostEffectManager&){}
	~PostEffectManager() {}
};

#endif