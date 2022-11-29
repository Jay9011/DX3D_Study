#pragma once

class Material
{
private:
    enum MapType 
    {
        DIFFUSE, SPECULAR, NORMAL
    };

public:
    class MaterialBuffer : public ConstBuffer
    {
    public:
        struct Data
        {
            Float4 diffuse = {1, 1, 1, 1};
            Float4 specular = { 1, 1, 1, 1};            
            Float4 ambient = { 1, 1, 1, 1};            
            
            float shininess = 24.0f;

            int hasDiffuseMap = 0;
            int hasSpecularMap = 0;
            int hasNormalMap = 0;                 
        }data;
    
        MaterialBuffer() : ConstBuffer(&data, sizeof(Data))
        {
        }
    };

public:
    Material();
    Material(wstring shaderFile);
    ~Material();

    void Set();

    void GUIRender();

    void SetDiffuseMap(wstring file);
    void SetSpecularMap(wstring file);
    void SetNormalMap(wstring file);

    void SetShader(wstring file);

    void Save(string file);
    void Load(string file);

    void SetName(string name) { this->name = name; }
    string GetName() { return name; }

    MaterialBuffer::Data& GetData() { return buffer->data; }

private:
    void SelectShader();

    void SelectMap(string name, MapType type);
    void UnselectMap(MapType type);

    void SaveDialog();
    void LoadDialog();

private:
    string name = "Default";
    string file;

    VertexShader* vertexShader = nullptr;
    PixelShader* pixelShader = nullptr;

    Texture* diffuseMap = nullptr;
    Texture* specularMap = nullptr;
    Texture* normalMap = nullptr;

    MaterialBuffer* buffer;
};