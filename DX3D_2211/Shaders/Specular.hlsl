// Specular
cbuffer WorldBuffer : register(b0)
{
    matrix world;
}

cbuffer ViewBuffer : register(b1)
{
    matrix view;
    matrix invView;
}

cbuffer ProjectionBuffer : register(b2)
{
    matrix projection;
}

struct VertexInput
{
    float4 pos : POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 viewDir : VIEWDIR;
};

PixelInput VS(VertexInput input)
{
    PixelInput output;
    output.pos = mul(input.pos, world);
    
    output.viewDir = normalize(output.pos.xyz - invView._41_42_43);
    
    output.pos = mul(output.pos, view);
    output.pos = mul(output.pos, projection);
    
    output.uv = input.uv;
    
    output.normal = mul(input.normal, (float3x3) world);
    
    return output;
}

Texture2D diffuseMap : register(t0);
SamplerState samp : register(s0);

cbuffer LightBuffer : register(b0)
{
    float3 lightDirection;
    float shininess;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 albedo = diffuseMap.Sample(samp, input.uv);
    
    float3 normal = normalize(input.normal);
    float3 light = normalize(lightDirection);
    
    float diffuse = saturate(dot(normal, -light));
    
    float4 specular = 0;
    
    // [branch] 여러개의 조건문 (if~else)를 사용하는 경우
    [flatten]   // 단일 조건문을 사용하는 경우 최적화 시킨다.
    if(diffuse > 0.0f)
    {
        float3 reflection = normalize(reflect(light, normal));
        specular = saturate(dot(-reflection, input.viewDir));
        
        specular = pow(specular, shininess);
    }
    
    float4 diffuseColor = albedo * diffuse;
    float4 specularColor = albedo * specular;
    float4 ambientColor = albedo * 0.1f;
    
    return diffuseColor + specularColor + ambientColor;
}
