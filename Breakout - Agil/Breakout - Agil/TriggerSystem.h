#pragma once
#include "System.h"

class TriggerSystem : public System
{
public:
	TriggerSystem();
	TriggerSystem(string pName);
	~TriggerSystem();
	virtual void Initialize();
	virtual void Start();
	virtual void Update(double pDeltaTime);
	virtual void Pause();
	virtual void Stop();
	virtual void OnEvent(Event* pEvent);

private:
	int mNumOfBallsActive;
	int mNumOfGoalBlocksActive;
	bool mCreateNextLevel;
	int mCurrentLevel;
	vector<string> mMapNames;
};

