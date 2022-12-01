#pragma once

class Device : public Singleton<Device>
{
public:
    Device();
    ~Device();

    void Clear();
    void Present();

    ID3D11Device * GetDevice() { return device; }
    ID3D11DeviceContext * GetDeviceContext() { return deviceContext; }
    IDXGISwapChain* GetSwapChain() { return swapChain; }

private:
    void CreateDeviceAndSwapChain();
    void CreateBuffer();

private:
    ID3D11Device * device;//CPU
    ID3D11DeviceContext * deviceContext;//GPU

    IDXGISwapChain * swapChain;//����� ����
    ID3D11RenderTargetView * renderTargetView;//VRAM ����� �޸� ����
    ID3D11DepthStencilView * depthStencilView;//VRam ���̹��� �޸� ����
};