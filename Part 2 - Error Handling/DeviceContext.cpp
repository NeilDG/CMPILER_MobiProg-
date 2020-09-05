#include "DeviceContext.h"
#include "SwapChain.h"

DeviceContext::DeviceContext(ID3D11DeviceContext* deviceContext): myContext(deviceContext)
{

}

DeviceContext::~DeviceContext()
{
}

void DeviceContext::clearRenderTargetColor(SwapChain* swapChain, float red, float green, float blue, float alpha)
{
	FLOAT clearColor[] = {red, green, blue, alpha};
	ID3D11RenderTargetView* renderView = swapChain->getRenderTargetView();
	ID3D11DepthStencilView* depthView = swapChain->getDepthStencilView();
	this->myContext->ClearRenderTargetView(renderView, clearColor);
	this->myContext->ClearDepthStencilView(depthView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1, 0);
	this->myContext->OMSetRenderTargets(1, &renderView, depthView);
}

void DeviceContext::setViewportSize(UINT width, UINT height)
{
	D3D11_VIEWPORT vp = {}; //IMPORTANT: all structs in Direct3D must have this to initialize any default values.
	vp.Width = width;
	vp.Height = height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;

	this->myContext->RSSetViewports(1, &vp);
}

void DeviceContext::release()
{
	this->myContext->Release();
}

ID3D11DeviceContext* DeviceContext::getContext()
{
	return this->myContext;
}
