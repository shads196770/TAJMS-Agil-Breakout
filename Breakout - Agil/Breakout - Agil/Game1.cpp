#include "Game1.h"
#include "PhysicSystem.h"
#include "EntityManager.h"
#include "PhysicComponent.h"


Game1::Game1()
{
}


Game1::~Game1()
{
}

bool Game1::Initialize()
{
	PhysicSystem* tPhysics = new PhysicSystem();
	tPhysics->Initialize();
	mSystems.push_back(tPhysics);
	
	return true;
}

void Game1::Run()
{
	double tDeltaTimeMilli = 17; //global? or sent in func

	while (true)
	{
		for each (System* sys in mSystems)
		{
			sys->Update();
		}
	}
}

void Game1::Destroy()
{

}
