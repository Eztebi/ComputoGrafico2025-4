#pragma once

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"
// Para obtener el HWND de la ventana de GLFW
#define GLFW_EXPOSE_NATIVE_WIN32
#include "GLFW/glfw3native.h"

#include <iostream>
#include <vector>
#include <windows.h>


// Librerías de DirectX 12
#include <DirectXMath.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h> // Para Microsoft::WRL::ComPtr
#include <d3dcompiler.h>


#include <map>
#include <string>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3dcompiler.lib")

struct Vertex {
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT3 normal;
};

struct Model {
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indicies;
};


typedef struct _SceneConstants
{
	DirectX::XMMATRIX model; //matriz de 4x4 y cada flotante es de 4 bytes = 64 bytes en total
	DirectX::XMMATRIX view;//matriz de 4x4 y cada flotante es de 4 bytes = 64 bytes en total
	DirectX::XMMATRIX projection;//matriz de 4x4 y cada flotante es de 4 bytes = 64 bytes en total

	//192 bytes
	
	//parametros de matriz de vista
	DirectX::XMVECTOR eye; //16 bytes
	DirectX::XMVECTOR center; //16 bytes
	DirectX::XMVECTOR up; //16 bytes
	//48 bytes
	UINT triangleAngle;//4 bytes
	//192+48+4
	float padding[3];
	
} SceneConstants;

class Application
{
private:
	void ThrowIfFailed(HRESULT hr, const std::string& msg);
	void ThrowIfFailed(HRESULT hr);
	void setupGeometry();
	void setupShaders();
	void setupDevice();
	void setupCommandQueue();
	void setupCommandAllocator();
	void setupCommandList();
	void setupSwapChain();
	void setupDescriptorHeap();
	void setupRenderTargetView();
	void setupSignature();
	void swapBuffers();
	void setUpConstantBuffer();
	void setBlendState(D3D12_BLEND_DESC& blend_desc);
	void setRasterizerState(D3D12_RASTERIZER_DESC& rasterizer_desc);
	void setDepthStencilState(D3D12_DEPTH_STENCIL_DESC& depth_stencil_desc);


	std::string readFile(const std::string& filename);

	// --- Configuración y Constantes ---
	static const UINT BUFFER_COUNT = 2; // Double buffering

	// --- Variables Globales de DX12 ---
	Microsoft::WRL::ComPtr<IDXGIFactory4> factory;

	Microsoft::WRL::ComPtr<ID3D12Device> device;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swapChain{};
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	Microsoft::WRL::ComPtr<ID3D12Resource> renderTargets[BUFFER_COUNT];
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvHeap;
	Microsoft::WRL::ComPtr<ID3D12Resource> constantBuffer;
	
	UINT frameIndex{0};
	UINT rtvIncrementSize;
	void *mappedMemory;
	SceneConstants sceneConstants;

	unsigned int triangle_angle =0;


public:
	const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 768;
	GLFWwindow* window;
	HWND GetWindowNativeHandler() const;
	void setup();
	void update();
	void draw();
	void keyCallback(int key, int scancode, int action, int mods);
};