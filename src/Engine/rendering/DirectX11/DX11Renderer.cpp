#include "DX11Renderer.h"
#include "../../Entity.h"
#include <stdexcept>

namespace EngineCore {

DX11Renderer::DX11Renderer() = default;
DX11Renderer::~DX11Renderer() = default;

void DX11Renderer::Initialize(void* windowHandle) {
    HWND hwnd = static_cast<HWND>(windowHandle);
    CreateDeviceAndSwapChain(hwnd);
    CreateRenderTarget();
}

void DX11Renderer::CreateDeviceAndSwapChain(HWND hwnd) {
    DXGI_SWAP_CHAIN_DESC scd{};
    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hwnd;
    scd.SampleDesc.Count = 1;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    UINT flags = 0;
#if defined(_DEBUG)
    flags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0
    };

    HRESULT hr = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        flags,
        featureLevels,
        1,
        D3D11_SDK_VERSION,
        &scd,
        swapChain.GetAddressOf(),
        device.GetAddressOf(),
        nullptr,
        context.GetAddressOf()
    );

    if (FAILED(hr)) {
        throw std::runtime_error("Failed to create DX11 device");
    }
}

void DX11Renderer::CreateRenderTarget() {
    Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

    swapChain->GetBuffer(
        0,
        IID_PPV_ARGS(backBuffer.GetAddressOf())
    );

    device->CreateRenderTargetView(
        backBuffer.Get(),
        nullptr,
        renderTargetView.GetAddressOf()
    );
}

void DX11Renderer::BeginFrame() {
    float clearColor[4] = { 0.1f, 0.1f, 0.15f, 1.0f };

    context->OMSetRenderTargets(
        1,
        renderTargetView.GetAddressOf(),
        nullptr
    );

    context->ClearRenderTargetView(
        renderTargetView.Get(),
        clearColor
    );
}

void DX11Renderer::DrawEntity(const Entity& /*entity*/) {
    // NOT YET: mesh binding, shaders, buffers
    // This will come next
}

void DX11Renderer::EndFrame() {
    swapChain->Present(1, 0);
}

}
