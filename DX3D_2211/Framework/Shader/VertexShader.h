#pragma once

class VertexShader : public Shader
{
public:
    VertexShader(wstring file);
    ~VertexShader();

    void Set();

private:
    void CreateInputLayout();

private:
    ID3D11VertexShader * shader;    
    ID3D11InputLayout * inputLayout;

    ID3DBlob * blob;

    ID3D11ShaderReflection* reflection;
};
