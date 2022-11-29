#include "Framework.h"

Material::Material()
{
    buffer = new MaterialBuffer();
}

Material::Material(wstring shaderFile)
{
    SetShader(shaderFile);
    buffer = new MaterialBuffer();
}

Material::~Material()
{    
    delete buffer;
}

void Material::Set()
{
    buffer->SetPSBuffer(1);

    if (diffuseMap != nullptr)
        diffuseMap->PSSet(0);

    if (specularMap != nullptr)
        specularMap->PSSet(1);

    if (normalMap != nullptr)
        normalMap->PSSet(2);

    vertexShader->Set();
    pixelShader->Set();
}

void Material::GUIRender()
{
    if (ImGui::TreeNode((name + "_Material").c_str()))
    {
        SelectShader();

        ImGui::ColorEdit3("Diffuse", (float*)&buffer->data.diffuse, ImGuiColorEditFlags_PickerHueBar);
        ImGui::ColorEdit3("Specular", (float*)&buffer->data.specular, ImGuiColorEditFlags_PickerHueBar);
        ImGui::ColorEdit3("Ambient", (float*)&buffer->data.ambient, ImGuiColorEditFlags_PickerHueBar);

        ImGui::SliderFloat("Shininess", &buffer->data.shininess, 1.0f, 50.0f);

        SelectMap("DM", DIFFUSE);
        ImGui::SameLine();
        UnselectMap(DIFFUSE);
        ImGui::SameLine();
        SelectMap("SM", SPECULAR);
        ImGui::SameLine();
        UnselectMap(SPECULAR);
        ImGui::SameLine();
        SelectMap("NM", NORMAL);  
        ImGui::SameLine();
        UnselectMap(NORMAL);        

        SaveDialog();
        LoadDialog();

        ImGui::TreePop();
    }
}

void Material::SetDiffuseMap(wstring file)
{
    if (file.length() == 0)
    {
        diffuseMap = nullptr;
        buffer->data.hasDiffuseMap = 0;
        return;
    }

    diffuseMap = Texture::Add(file);
    buffer->data.hasDiffuseMap = true;
}

void Material::SetSpecularMap(wstring file)
{
    if (file.length() == 0)
    {
        specularMap = nullptr;
        buffer->data.hasSpecularMap = 0;
        return;
    }

    specularMap = Texture::Add(file);
    buffer->data.hasSpecularMap = true;
}

void Material::SetNormalMap(wstring file)
{
    if (file.length() == 0)
    {
        normalMap = nullptr;
        buffer->data.hasNormalMap = 0;
        return;
    }

    normalMap = Texture::Add(file);
    buffer->data.hasNormalMap = true;
}

void Material::SetShader(wstring file)
{
    vertexShader = Shader::AddVS(file);
    pixelShader = Shader::AddPS(file);
}

void Material::Save(string file)
{
    BinaryWriter* writer = new BinaryWriter(file);

    writer->String(name);

    if (vertexShader)
        writer->WString(vertexShader->GetFile());
    else
        writer->WString(L"");

    if (pixelShader)
        writer->WString(pixelShader->GetFile());
    else
        writer->WString(L"");

    if (diffuseMap)
        writer->WString(diffuseMap->GetFile());
    else
        writer->WString(L"");

    if (specularMap)
        writer->WString(specularMap->GetFile());
    else
        writer->WString(L"");

    if (normalMap)
        writer->WString(normalMap->GetFile());
    else
        writer->WString(L"");

    writer->Float4(buffer->data.diffuse);
    writer->Float4(buffer->data.specular);
    writer->Float4(buffer->data.ambient);

    writer->Float(buffer->data.shininess);

    delete writer;
}

void Material::Load(string file)
{
    BinaryReader* reader = new BinaryReader(file);

    if (reader->IsFailed())
    {
        delete reader;
        return;
    }

    this->file = file;

    name = reader->String();    

    vertexShader = Shader::AddVS(reader->WString());
    pixelShader = Shader::AddPS(reader->WString());

    SetDiffuseMap(reader->WString());
    SetSpecularMap(reader->WString());
    SetNormalMap(reader->WString());

    buffer->data.diffuse = reader->Float4();
    buffer->data.specular = reader->Float4();
    buffer->data.ambient = reader->Float4();

    buffer->data.shininess = reader->Float();

    delete reader;
}

void Material::SelectShader()
{
    if (ImGui::Button((name + "Shader").c_str()))
    {
        DIALOG->OpenDialog(name + "Shader", "SelectShader", ".hlsl", ".");
    } 

    if (DIALOG->Display(name + "Shader"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            char path[128];
            GetCurrentDirectoryA(128, path);

            file = file.substr(strlen(path) + 1, file.length());

            SetShader(ToWString(file));
        }

        DIALOG->Close();
    }
}

void Material::SelectMap(string name, MapType type)
{
    ImTextureID textureID = nullptr;
    
    switch (type)
    {
    case Material::DIFFUSE:
        if(diffuseMap)
            textureID = diffuseMap->GetSRV();
        break;
    case Material::SPECULAR:
        if (specularMap)
            textureID = specularMap->GetSRV();
        break;
    case Material::NORMAL:
        if (normalMap)
            textureID = normalMap->GetSRV();
        break;
    default:
        break;
    }

    if (textureID)
    {
        if(ImGui::ImageButton(textureID, ImVec2(50, 50)))
        {
            DIALOG->OpenDialog(this->name + name, name,
                ".png,.jpg,.tga,.jfif", ".");
        }
    }
    else
    {
        if (ImGui::Button(name.c_str(), ImVec2(50, 50)))
        {
            DIALOG->OpenDialog(this->name + name, name,
                ".png,.jpg,.tga,.jfif", ".");
        }
    }

    if (DIALOG->Display(this->name + name))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            char path[128];
            GetCurrentDirectoryA(128, path);

            file = file.substr(strlen(path) + 1, file.length());

            switch (type)
            {
            case Material::DIFFUSE:
                SetDiffuseMap(ToWString(file));
                break;
            case Material::SPECULAR:
                SetSpecularMap(ToWString(file));
                break;
            case Material::NORMAL:
                SetNormalMap(ToWString(file));
                break;
            default:
                break;
            }
        }

        DIALOG->Close();
    }
}

void Material::UnselectMap(MapType type)
{
    Texture* tex = nullptr;
    wstring key;

    switch (type)
    {
    case Material::DIFFUSE:
        key = ToWString(name + "DM");
        tex = Texture::Add(L"Textures/UI/cancel.png", key);
        if (ImGui::ImageButton(tex->GetSRV(), ImVec2(30, 30)))
            SetDiffuseMap(L"");
        break;
    case Material::SPECULAR:
        key = ToWString(name + "SM");
        tex = Texture::Add(L"Textures/UI/cancel.png", key);
        if (ImGui::ImageButton(tex->GetSRV(), ImVec2(30, 30)))
            SetSpecularMap(L"");
        break;
    case Material::NORMAL:
        key = ToWString(name + "NM");
        tex = Texture::Add(L"Textures/UI/cancel.png", key);
        if (ImGui::ImageButton(tex->GetSRV(), ImVec2(30, 30)))
            SetNormalMap(L"");
        break;    
    }
}

void Material::SaveDialog()
{
    if (ImGui::Button("Save"))
    {
        if (file.empty())
            file = "TextData/Materials/" + name + ".mat";

        Save(file);
    }

    ImGui::SameLine();

    if (ImGui::Button("SaveAs"))
    {
        DIALOG->OpenDialog(name + "SaveMaterial", "SaveMaterial",
            ".mat", ".");
    }

    if (DIALOG->Display(name + "SaveMaterial"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            char path[128];
            GetCurrentDirectoryA(128, path);

            file = file.substr(strlen(path) + 1, file.length());

            Save(file);
        }

        DIALOG->Close();
    }
}

void Material::LoadDialog()
{
    if (ImGui::Button("Load"))
    {
        DIALOG->OpenDialog(name + "LoadMaterial", "LoadMaterial",
            ".mat", ".");
    }

    if (DIALOG->Display(name + "LoadMaterial"))
    {
        if (DIALOG->IsOk())
        {
            string file = DIALOG->GetFilePathName();

            char path[128];
            GetCurrentDirectoryA(128, path);

            file = file.substr(strlen(path) + 1, file.length());

            Load(file);
        }

        DIALOG->Close();
    }
}
