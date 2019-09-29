//=====================================
//
//パーティクルJSONパーサヘッダ[ParticleJsonParser.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _PARTICLEJSONPARSER_H_
#define _PARTICLEJSONPARSER_H_

#include "../../main.h"
#include <string>

/**************************************
マクロ定義
***************************************/

/**************************************
前方宣言
***************************************/

/**************************************
クラス定義
***************************************/
class ParticleJsonParser
{
public:
	ParticleJsonParser(const char* fileName);

	std::string GetTexturePath() const;
	int GetParticleMax() const;
	int GetEmitterMax() const;
	int GetEmitNum() const;
	int GetDuration() const;
	D3DXVECTOR2 GetSize() const;
	D3DXVECTOR2 GetTexDiv() const;
	
private:
	std::string texturePath;
	int particleMax;
	int emitterMax;
	int emitNumMin, emitNumMax;
	int durationMin, durationMax;
	D3DXVECTOR2 size;
	D3DXVECTOR2 texDiv;
};

#endif