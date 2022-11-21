#pragma once
//GlobalBuffer

class MatrixBuffer : public ConstBuffer
{
private:
    struct Data
    {
        Matrix matrix;
    };

public:
    MatrixBuffer() : ConstBuffer(&data, sizeof(Data))
    {
        data.matrix = XMMatrixIdentity();
    }

    void Set(Matrix value)
    {
        data.matrix = XMMatrixTranspose(value);
    }

private:
    Data data;
};

class ViewBuffer : public ConstBuffer
{
private:
    struct Data
    {
        Matrix view;
        Matrix invView;
    };

public:
    ViewBuffer() : ConstBuffer(&data, sizeof(Data))
    {
        data.view = XMMatrixIdentity();
        data.invView = XMMatrixIdentity();
    }

    void Set(Matrix view, Matrix invView)
    {
        data.view = XMMatrixTranspose(view);
        data.invView = XMMatrixTranspose(invView);
    }

private:
    Data data;
};

class ColorBuffer : public ConstBuffer
{
private:
    struct Data
    {
        Float4 color;
    };

public:
    ColorBuffer() : ConstBuffer(&data, sizeof(Data))
    {
        data.color = { 1, 1, 1, 1 };
    }

    void Set(float r, float g, float b, float a = 1.0f)
    {
        data.color = { r, g, b, a };
    }

private:
    Data data;
};

class LightBuffer : public ConstBuffer
{
private:
    struct Data
    {
        Float3 lightDir;
        float shininess;

        Float4 ambient;
    };

public:
    LightBuffer() : ConstBuffer(&data, sizeof(Data))
    {
        data.lightDir = { 0, -1, 0 };
        data.shininess = 24.0f;

        data.ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
    }

    Float3& GetLightDir() { return data.lightDir; }
    float& GetShininess() { return data.shininess; }

    Float4& GetAmbient() { return data.ambient; }

private:
    Data data;
};

class FloatValueBuffer : public ConstBuffer
{
public:
    FloatValueBuffer() : ConstBuffer(values, sizeof(float) * 4)
    {        
    }

    float values[4] = {};
};

class RayBuffer : public ConstBuffer
{
public:
    struct Data
    {
        Float3 position = { 0, 0, 0 };
        float triangleSize = 0.0f;

        Float3 direction = { 0, 0, 0 };
        float padding;
    }data;

    RayBuffer() : ConstBuffer(&data, sizeof(Data))
    {
    }
};