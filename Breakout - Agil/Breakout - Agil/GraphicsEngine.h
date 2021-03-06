#pragma once
#ifdef _WIN32
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include <windows.h>
#include <windowsx.h>
#include <d3d11_1.h>
#include <DirectXMath.h>
#include <dxgi.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>
#include <vector>
#include "DDSTextureLoader.h"
#include <iostream>
#include "GraphicsVirtual.h"
#include "Math.h"
#include "ObjLoader.h"
#include <string>
#ifdef DEBUG
	#include <iostream>
#endif // DEBUG

#define MAX_INSTANCES 100

using namespace DirectX;
using namespace std;



struct MatrixBufferType
{
	XMMATRIX world;
	XMMATRIX view;
	XMMATRIX projection;
};

struct MovementBufferType
{
	float time;
	XMFLOAT3 filler;
};

struct ObjectBufferType
{
	ID3D11Buffer* vertexDescription;
	unsigned int numberOfIndices;
	ObjectBufferType(ID3D11Buffer* _vertex, unsigned int _numberOfIndices)
	{
		vertexDescription = _vertex;
		numberOfIndices = _numberOfIndices;
		
	}
};

struct InstanceBufferType
{
	 XMFLOAT4X4 translationMatrices;
};

class GraphicsEngine
{
private:
	struct VertexShaderComponents
	{
		ID3D11VertexShader* ShaderHandle;
		ID3D11InputLayout * InputLayout;
	};
public:
	GraphicsEngine();
	~GraphicsEngine();
	// global declarations

	IDXGISwapChain *swapchain;           
	ID3D11Device *dev;                   
	ID3D11DeviceContext *devcon;         
	ID3D11RenderTargetView *backbuffer;  
	ID3D11Texture2D *mDepthBuffer;
	ID3D11DepthStencilView *mDepthView;


	XMMATRIX mTranslationMatrices[5];
	
	float time;

	void InitD3D();     // sets 
	void InitPipeline();
	void CleanD3D(void);         // close
	void InitGraphics(float pFoVAngleY, float pHeight, float pWidth, float pNear, float pFar, float pZPos);
	int CreateObject(string pMeshName);
	void GetTextureID(const char* pTetureName, int& pTextureGroup, int& pTextureID);
	void DrawObjects(int pMeshType, vector<InstanceBufferType> pInstanceBufferData, int pTextureBuffer);
	int CreateTexture(const wchar_t *pFileName);
	void EndDraw();

private:

	struct ConstantBufferType
	{
		int bufferID;
		int reg;
	};
	enum ShaderType { VertexShader, PixelShader };
	bool CreateShader(ShaderType pType, void* oShaderHandle, LPCWSTR pShaderFileName, LPCSTR pEntryPoint, ID3D11InputLayout** oInputLayout, D3D11_INPUT_ELEMENT_DESC pInputDescription[], int pArraySize);
	bool SetActiveShader(ShaderType pType, void* oShaderHandle);
	int CreateBuffer(D3D11_BUFFER_DESC pBufferDescription);
	bool PushToDevice(int pBufferID, void* pDataStart, unsigned int pSize);
	bool PushToDevice(int pBufferID, void* pDataStart, unsigned int pSize, unsigned int pRegister, ShaderType pType);
	bool PushToDevice(ID3D11Buffer* pBuffer, void* pDataStart, unsigned int pSize);
	int CreateObjectBuffer(D3D11_BUFFER_DESC pVertexBufferDescription, unsigned int pNumberOfVertices);

	//Variables
	ID3D11PixelShader* mPixelShader;
	VertexShaderComponents* mVertexShader = new VertexShaderComponents;
	vector< ObjectBufferType> mObjectBuffers;
	vector< ID3D11Buffer*> mBuffers;
	MatrixBufferType tBufferInfo;
	int mVertexBufferID;
	int mIndexBufferID;
	int mInstanceBufferID;

	ConstantBufferType mWVPBufferID;
	vector <InstanceBufferType> mInstanceBuffer;

	vector<ID3D11ShaderResourceView*> mTextureBuffers;
	ID3D11ShaderResourceView* mCubesTexture;
	ID3D11SamplerState* mCubesTexSamplerState;

	ObjLoader* mObjLoader;
};

#endif