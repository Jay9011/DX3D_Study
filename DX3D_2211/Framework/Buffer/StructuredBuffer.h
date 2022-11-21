#pragma once

class StructuredBuffer
{
public:
    StructuredBuffer(void* inputData, UINT inputStride, UINT inputCount,
        UINT outputStride, UINT outputCount);
    ~StructuredBuffer();

    void Copy(void* data, UINT size);

    void UpdateInput(void* data);

    ID3D11UnorderedAccessView*& GetUAV() { return uav; }
    ID3D11ShaderResourceView*& GetSRV() { return srv; }

private:
    void CreateInput();
    void CreateSRV();
    void CreateOutput();
    void CreateUAV();
    void CreateResult();

private:
    ID3D11Resource* input;//CPU->input
    ID3D11ShaderResourceView* srv;

    ID3D11Resource* output;//GPU->output
    ID3D11UnorderedAccessView* uav;

    ID3D11Resource* result;//result->CPU

    void* inputData;

    UINT inputStride, inputCount;
    UINT outputStride, outputCount;
};