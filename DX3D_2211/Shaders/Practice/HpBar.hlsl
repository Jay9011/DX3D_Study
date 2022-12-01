cbuffer WorldBuffer : register(b0)
{
    matrix world;
}

cbuffer ViewBuffer : register(b1)
{
    matrix view;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.pos = mul(input.pos, world);
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = input.uv;
    
    return output;
}

Texture2D frontMap : register(t0);
Texture2D backMap : register(t1);

SamplerState samp : register(s0);

cbuffer ValueBuffer : register(b0)
{
    float fillAmount;
}

float4 PS(PixelInput input) : SV_TARGET
{
    [flatten]
    if (input.uv.x < fillAmount)
        return frontMap.Sample(samp, input.uv);
    
    return backMap.Sample(samp, input.uv);
}
