#include "Framework.h"

map<wstring, Texture*> Texture::textures;

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
    : srv(srv), image(move(image))
{
}

Texture::~Texture()
{
    if(isCreate)
        srv->Release();        
}

Texture* Texture::Add(wstring file)
{
    if (textures.count(file) > 0)
        return textures[file];

    ScratchImage image;

    wstring extenstion = GetExtension(file);

    if (extenstion == L"tga")
        LoadFromTGAFile(file.c_str(), nullptr, image);
    else if(extenstion == L"dds")
        LoadFromDDSFile(file.c_str(), DDS_FLAGS_NONE, nullptr, image);
    else
        LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    ID3D11ShaderResourceView* srv;

    CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &srv);

    textures[file] = new Texture(srv, image);
    textures[file]->file = file;    

    return textures[file];
}

Texture* Texture::Add(wstring file, wstring key)
{
    if (textures.count(key) > 0)
        return textures[key];

    ScratchImage image;

    wstring extenstion = GetExtension(file);

    if (extenstion == L"tga")
        LoadFromTGAFile(file.c_str(), nullptr, image);
    else if (extenstion == L"dds")
        LoadFromDDSFile(file.c_str(), DDS_FLAGS_NONE, nullptr, image);
    else
        LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);

    ID3D11ShaderResourceView* srv;

    CreateShaderResourceView(DEVICE, image.GetImages(), image.GetImageCount(), image.GetMetadata(), &srv);

    textures[key] = new Texture(srv, image);
    textures[key]->file = file;

    return textures[key];
}

Texture* Texture::Add(wstring key, ID3D11ShaderResourceView* srv)
{
    if (textures.count(key) > 0)
        return textures[key];

    ScratchImage image;
    textures[key] = new Texture(srv, image);  
    textures[key]->isCreate = false;

    return textures[key];
}

void Texture::Delete()
{
    for (pair<wstring, Texture*> texture : textures)
        delete texture.second;
}

void Texture::PSSet(UINT slot)
{
    DC->PSSetShaderResources(slot, 1, &srv);
}

void Texture::DSSet(UINT slot)
{
    DC->DSSetShaderResources(slot, 1, &srv);
}

vector<Float4> Texture::ReadPixels()
{
    uint8_t* colors = image.GetPixels();
    UINT size = image.GetPixelsSize();

    float scale = 1.0f / 255.0f;

    vector<Float4> result(size / 4);
    
    UINT count = 0;
    for (Float4& color : result)
    {
        color.x = colors[count++] * scale;
        color.y = colors[count++] * scale;
        color.z = colors[count++] * scale;
        color.w = colors[count++] * scale;
    }

    return result;
}
