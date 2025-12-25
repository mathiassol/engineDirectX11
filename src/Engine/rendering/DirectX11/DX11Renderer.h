#pragma once
#include "../IRenderer.h"
#include <d3d11.h>
#include <dxgi.h>
#include <wrl/client.h>

namespace EngineCore {

    class DX11Renderer : public IRenderer {
    public:
        DX11Renderer();
        ~DX11Renderer() override;

        void Initialize(void* windowHandle) override;
        void BeginFrame() override;
        void DrawEntity(const Entity& entity) override;
        void EndFrame() override;

    private:
        void CreateDeviceAndSwapChain(HWND hwnd);
        void CreateRenderTarget();

    private:
        Microsoft::WRL::ComPtr<ID3D11Device> device;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> context;
        Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView;
    };

}
