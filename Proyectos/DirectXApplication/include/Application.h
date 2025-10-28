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
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h> // Para Microsoft::WRL::ComPtr
#include <d3dcompiler.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

#include <map>
#include <string>


class Application
{
private:
	void ThrowIfFailed(HRESULT hr, const std::string& msg);
	void ThrowIfFailed(HRESULT hr);
	void setupGeometry();
	void setupShaders();
	void setupDevice();
	void setupCommandQueue();
	void setupSwapChain();
	void setupDescriptorHeap();
	void setupRenderTargetView();
	void setupCommandAllocator();
	void setupCommandList();
	void swapBuffers();

	std::string readFile(const std::string& filename);

	// --- Configuración y Constantes ---
	static const UINT BUFFER_COUNT = 2; // Double buffering
	const int WINDOW_WIDTH = 1024;
	const int WINDOW_HEIGHT = 768;

	// --- Variables Globales de DX12 ---
	Microsoft::WRL::ComPtr<IDXGIFactory4> factory;

	Microsoft::WRL::ComPtr<ID3D12Device> device = nullptr;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> command_queue;
	Microsoft::WRL::ComPtr<IDXGISwapChain4> swap_chain_desc = {};
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtv_heap;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> g_commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_lists;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> command_list = nullptr;
	Microsoft::WRL::ComPtr<ID3D12Resource> render_targets[2];
	Microsoft::WRL::ComPtr<D3D12_CPU_DESCRIPTOR_HANDLE> rtv_handle;
	Microsoft::WRL::ComPtr<ID3D12RootSignature> root_signature = nullptr;
	Microsoft::WRL::ComPtr<UINT> rtv_increment_size;// = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	Microsoft::WRL::ComPtr<HRESULT> hr;// = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_2, IID_PPV_ARGS(&device));
	Microsoft::WRL::ComPtr <UINT> back_buffer_index;
	Microsoft::WRL::ComPtr <D3D12_RESOURCE_BARRIER> barrier = {};
	Microsoft::WRL::ComPtr < D3D12_ROOT_SIGNATURE_DESC> root_signature_desc = {};
	;


	Microsoft::WRL::ComPtr<ID3D12Resource> g_renderTargets[BUFFER_COUNT];
	UINT g_frameIndex;
	UINT g_rtvDescriptorSize;



public:
	HWND hwnd;
	const int width{ 1280 };
	const int height{ 1024 };
	GLFWwindow* window;
	HWND GetWindowNativeHandler() const;
	void setup();
	void update();
	void draw();
	void clearColorBuffer(const float& r, const float& g, const float& b, const float& a);
	void keyCallback(int key, int scancode, int action, int mods);
	void setupSignature();
	void setBlendState(D3D12_BLEND_DESC& blend_desc);
	void setRasterizerState(D3D12_RASTERIZER_DESC& rasterizer_desc);
	void setDepthStencilState(D3D12_DEPTH_STENCIL_DESC& depth_stencil_desc);
};
