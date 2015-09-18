#include "LevelManager.h"
#include "StorageShelf.h"
#include "TransformComponent.h"
#include "MeshComponent.h"
#include "LabelComponent.h"
#include "PhysicComponent.h"
#include "VelocityComponent.h"
#include "TextFileReader.h"
#include "ComponentTable.h"
#include <iostream>
using namespace std;



LevelManager* LevelManager::mSingleton = nullptr;

LevelManager* LevelManager::GetInstance()
{
	if (mSingleton == nullptr)
	{
		mSingleton = new LevelManager();
	}

	return mSingleton;
}

LevelManager::LevelManager()
{
	mEntityFactory = mEntityFactory->GetInstance();
}


LevelManager::~LevelManager()
{
}

void LevelManager::Initialize()
{
	//TODO: TEST remove this when we load maps in a good way
	EntityFactory::EntityBlueprint tBlueprint;

	TransformComponent* tTrans = new TransformComponent();
	MeshComponent* tMesh = new MeshComponent();
	LabelComponent* tLabel = new LabelComponent();
	PhysicComponent* tPhysic = new PhysicComponent();
	VelocityComponent* tVelocity = new VelocityComponent();

	//set component values
	//we ignore this and use the initialization values for test
	//WARNINIG: We should call the graphic engine for loading a texture then
	//return the ID To meshComponent
	tLabel->mLabel = Label::Pad;

	//add to blueprint
	tBlueprint[TransformType] = tTrans;
	tBlueprint[MeshType] = tMesh;
	tBlueprint[LabelType] = tLabel;

	mEntityFactory->RegisterEntityTemplate("Padda", tBlueprint);

	//add block to blueprint
	EntityFactory::EntityBlueprint tBlockBlueprint;

	//Component values might be silly and have to be altered later
	tTrans = new TransformComponent();
	tMesh = new MeshComponent();
	tVelocity = new VelocityComponent();
	tBlockBlueprint[TransformType] = tTrans;
	tBlockBlueprint[MeshType] = tMesh;
	tBlockBlueprint[VelocityType] = tVelocity;


	mEntityFactory->RegisterEntityTemplate("Block", tBlockBlueprint);

	//add ball to blueprint
	EntityFactory::EntityBlueprint tBallBlueprint;

	//Component values might be silly and have to be altered later
	tTrans = new TransformComponent();
	tMesh = new MeshComponent();
	tLabel = new LabelComponent();

	//We set the label here since it never changes
	tLabel->mLabel = Label::Ball;

	tBallBlueprint[TransformType] = tTrans;
	tBallBlueprint[MeshType] = tMesh;
	tBallBlueprint[LabelType] = tLabel;

	mEntityFactory->RegisterEntityTemplate("Ball", tBallBlueprint);

}

void LevelManager::GenerateWorld(string pWorldName)
{
	
	/////Creating a Pad for the game
	EntityID tNewID = mEntityFactory->CreateEntity("Padda");
	TransformComponent* tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition[0] = 1.0f;
	GetComponent<VelocityComponent>(tNewID)->mSpeed = 0.001f;
	
	//Reading The level from textfile
	vector<string> mLevelTextVector;
	mLevelTextVector = TextFileReader::ReadTextFile(pWorldName);


	//Create blocks

	
	int blockX = 10;
	int blockY = 5;

	//Space between blocks. Should probably be expanded to account for block sizes
	//Hard-coded until we can read from proper level file
	float margin = 2;

	for (int i = 0; i > blockX; i++)
		for (int j = 0; j < blockY; j++)
		{
			tNewID = mEntityFactory->CreateEntity("Block");
			tTrans = GetComponent<TransformComponent>(tNewID);
			tTrans->mPosition.x = margin*i;
			tTrans->mPosition.y = margin*j;
		}

	//Create the ball
	float tStartPositionX = 0;
	float tStartPositionY = 0;

	tNewID = mEntityFactory->CreateEntity("Ball");
	tTrans = GetComponent<TransformComponent>(tNewID);
	tTrans->mPosition.x = tStartPositionX;
	tTrans->mPosition.y = tStartPositionY;

	VelocityComponent* tVel = GetComponent<VelocityComponent>(tNewID);
	tVel->mSpeed = 0.001f;
	vec3 tStartDirection = vec3(1.0f, 1.0f, 0.0f);
	tVel->mDirection.x = tStartDirection.x;
	tVel->mDirection.y = tStartDirection.y;
	tVel->mDirection.z = tStartDirection.z;

	//Create the goal block
	tNewID = mEntityFactory->CreateEntity("Block");
	ComponentTable::GetInstance()->AddComponent(tNewID, LabelType);
	GetComponent<LabelComponent>(tNewID)->mLabel = Label::Goal;


}
