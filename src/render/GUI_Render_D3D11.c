/*********************************************************
* Copyright (C) VERTVER, 2019. All rights reserved.
* OMCIDE - Open Micro-controller IDE
* License: GPLv3
**********************************************************
* Module Name: GUI Render
*********************************************************/
#include "GUI_Render.h"
#include "base/Window.h"
#include <d3d11.h>

#include "../demo/style.c"
#include "../demo/calculator.c"
#include "../demo/overview.c"
#include "../demo/node_editor.c"

PFN_D3D11_CREATE_DEVICE_AND_SWAP_CHAIN         pD3D11CreateDevice = NULL;

static IDXGISwapChain *pSwapChain;
static ID3D11Device *pDevice;
static ID3D11DeviceContext *pContext;
static ID3D11RenderTargetView* pRTView;
extern struct nk_context *ctx;
extern struct nk_colorf bg;

boolean
OMCRenderInitD3D11()
{
	D3D_FEATURE_LEVEL feature_level;
	DXGI_SWAP_CHAIN_DESC swap_chain_desc;
	HRESULT hr = 0;

	if (!pD3D11CreateDevice)
	{
		void* hLib = OMCLoadLibrary("d3d11.dll");
		pD3D11CreateDevice = OMCGetProc(hLib, "D3D11CreateDeviceAndSwapChain");
	}

	void* hWnd = OMCWindowCreate();

	/* D3D11 setup */
	memset(&swap_chain_desc, 0, sizeof(swap_chain_desc));
	swap_chain_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swap_chain_desc.BufferDesc.RefreshRate.Numerator = 60;
	swap_chain_desc.BufferDesc.RefreshRate.Denominator = 1;
	swap_chain_desc.SampleDesc.Count = 1;
	swap_chain_desc.SampleDesc.Quality = 0;
	swap_chain_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swap_chain_desc.BufferCount = 1;
	swap_chain_desc.OutputWindow = hWnd;
	swap_chain_desc.Windowed = TRUE;
	swap_chain_desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swap_chain_desc.Flags = 0;

	if (FAILED(pD3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &swap_chain_desc, &pSwapChain, &pDevice, &feature_level, &pContext)))
	{
		/* if hardware device fails, then try WARP high-performance
		   software rasterizer, this is useful for RDP sessions */
		hr = pD3D11CreateDevice(NULL, D3D_DRIVER_TYPE_WARP, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &swap_chain_desc, &pSwapChain, &pDevice, &feature_level, &pContext);
	}

	return true;
}

void
OMCRenderDestroyD3D11()
{

}

void
OMCRenderDrawD3D11()
{
	/* Draw */
	ID3D11DeviceContext_ClearRenderTargetView(pContext, pRTView, &bg.r);
	ID3D11DeviceContext_OMSetRenderTargets(pContext, 1, &pRTView, NULL);
	nk_d3d11_render(pContext, NK_ANTI_ALIASING_ON);
	HRESULT hr = IDXGISwapChain_Present(pSwapChain, 1, 0);
	if (hr == DXGI_ERROR_DEVICE_RESET || hr == DXGI_ERROR_DEVICE_REMOVED) {
		return;
	}
	else if (hr == DXGI_STATUS_OCCLUDED) {
		/* window is not visible, so vsync won't work. Let's sleep a bit to reduce CPU usage */
		Sleep(10);
	}

	OMCRenderNuklear();
}

void
OMCRenderResizeD3D11(
	int Width,
	int Height
)
{

	ID3D11Texture2D* back_buffer = NULL;
	D3D11_RENDER_TARGET_VIEW_DESC desc;
	HRESULT hr = 0;

	if (pRTView) ID3D11RenderTargetView_Release(pRTView);

	ID3D11DeviceContext_OMSetRenderTargets(pContext, 0, NULL, NULL);

	hr = IDXGISwapChain_ResizeBuffers(pSwapChain, 0, Width, Height, DXGI_FORMAT_UNKNOWN, 0);
	if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET || hr == DXGI_ERROR_DRIVER_INTERNAL_ERROR)
	{
		return;
	}
	
	memset(&desc, 0, sizeof(desc));
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;

	hr = IDXGISwapChain_GetBuffer(pSwapChain, 0, &IID_ID3D11Texture2D, (void **)&back_buffer);
	hr = ID3D11Device_CreateRenderTargetView(pDevice, (ID3D11Resource *)back_buffer, &desc, &pRTView);

	ID3D11Texture2D_Release(back_buffer);
}
