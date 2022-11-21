#pragma once

class PixelShader : public Shader
{
public:
    PixelShader(wstring file);
    ~PixelShader();

    void Set();

private:
    ID3D11PixelShader * shader;

    ID3DBlob * blob;
};