#pragma once

class Material
{
public:
    Material();
    Material(wstring shaderFile);
    ~Material();

    void SetShader(wstring file);
    void SetDiffuseMap(wstring file);
    void SetSpecularMap(wstring file);

    void Set();

private:
    VertexShader* vertexShader;
    PixelShader* pixelShader;

    Texture* diffuseMap = nullptr;
    Texture* specularMap = nullptr;
};