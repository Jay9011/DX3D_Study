#pragma once

class Texture
{
private:
    bool isCreate = true;

    wstring file;

    ScratchImage image;

    ID3D11ShaderResourceView* srv;

    static map<wstring, Texture*> textures;

    Texture(ID3D11ShaderResourceView* srv, ScratchImage& image);    
    ~Texture();

public:
    static Texture* Add(wstring file);  
    static Texture* Add(wstring file, wstring key);
    static Texture* Add(wstring key, ID3D11ShaderResourceView* srv);
    static void Delete();

    void PSSet(UINT slot);
    void DSSet(UINT slot);

    vector<Float4> ReadPixels();

    UINT Width() { return image.GetMetadata().width; }
    UINT Height() { return image.GetMetadata().height; }

    wstring GetFile() { return file; }

    ID3D11ShaderResourceView*& GetSRV() { return srv; }
};

