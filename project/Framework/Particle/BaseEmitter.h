//=====================================
//
//ベースエミッタヘッダ[BaseEmitter.h]
//Author:GP12B332 21 立花雄太
//
//=====================================
#ifndef _BASEEMITTER_H_
#define _BASEEMITTER_H_

#include "../../main.h"
#include "BaseParticle.h"

#include <vector>
#include <functional>

/**************************************
BaseEmitterクラス
***************************************/
class BaseParticle;
class ParticleRenderer;

class BaseEmitter : public GameObject
{
public:
	BaseEmitter();
	BaseEmitter(int emitNum);
	BaseEmitter(int emitNum, int duration);
	BaseEmitter(int emitNum, int durationMin, int durationMax);
	BaseEmitter(int emitNumMin, int emitNumMax, int durationMin, int durationMax);

	virtual ~BaseEmitter();

	virtual void Init(const std::function<void(void)>& callback);
	virtual void Update();
	virtual bool Emit();

	//virtual bool IsActive() const override;

	virtual void UseCulling(bool value);

	void PushRenderParameter(std::shared_ptr<ParticleRenderer> renderer);

	virtual void Stop();
	virtual void Loop(bool state);

	template<class T>
	void CreateParticleContainer(unsigned sizeContainer)
	{
		particleContainer.resize(sizeContainer, nullptr);
		for (auto&& particle : particleContainer)
		{
			particle = new T();
		}
	}

protected:
	int cntFrame;
	int duration;
	int emitNum;

	bool useCull;
	bool isFinished;
	bool enableEmit;
	bool flgLoop;

	std::vector<BaseParticle*> particleContainer;

	std::function<void(void)> callback;
};

#endif