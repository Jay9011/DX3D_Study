// NormalMapping

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
    float3 tangent : TANGENT;
};

struct PixelInput
{
    float4 pos : SV_POSITION;
    float2 uv : UV;
    float3 normal : NORMAL;
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
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
    output.tangent = mul(input.tangent, (float3x3) world);
    output.binormal = cross(output.normal, output.tangent);
    
    return output;
}

Texture2D diffuseMap : register(t0);
Texture2D specularMap : register(t1);
Texture2D normalMap : register(t2);

SamplerState samp : register(s0);

cbuffer LightBuffer : register(b0)
{
    float3 lightDirection;
    float padding;
    
    float4 ambient;
}

cbuffer MaterialBuffer : register(b1)
{
    float4 mDiffuse;
    float4 mSpecular;
    float4 mAmbient;
    
    float shininess;
    
    int hasDiffuseMap;
    int hasSpecularMap;
    int hasNormalMap;
}

float4 PS(PixelInput input) : SV_TARGET
{
    float4 albedo = float4(1, 1, 1, 1);
    
    // DiffuseMap
    [flatten]
    if (hasDiffuseMap)
        albedo = diffuseMap.Sample(samp, input.uv);
    
    // Tangent, Binormal, Normal
    float3 T = normalize(input.tangent);
    float3 B = normalize(input.binormal);
    float3 N = normalize(input.normal);
    
    float3 normal = N;
    float3 light = normalize(lightDirection);
    
    [flatten]
    if(hasNormalMap)
    {
        float3x3 TBN = float3x3(T, B, N);
        
        float4 normalMapping = normalMap.Sample(samp, input.uv);// 0 ~ 1
        normal = normalMapping.rgb * 2.0f - 1.0f;   // -1 ~ 1
        normal = normalize(mul(normal, TBN));
    }
    
    float diffuse = saturate(dot(normal, -light));
    
    float4 specular = 0;
    
    // [branch] 여러개의 조건문 (if~else)를 사용하는 경우
    [flatten]   // 단일 조건문을 사용하는 경우 최적화 시킨다.
    if (diffuse > 0.0f)
    {
        float3 reflection = normalize(reflect(light, normal));
        specular = saturate(dot(-reflection, input.viewDir));
        
        // SpecularMap
        float4 specularIntensity = 1.0f;
        [flatten]
        if (hasSpecularMap)
            specularIntensity = specularMap.Sample(samp, input.uv);
        
        specular = pow(specular, shininess) * specularIntensity;
    }
    
    float4 diffuseColor = albedo * diffuse * mDiffuse;
    float4 specularColor = albedo * specular * mSpecular;
    float4 ambientColor = albedo * ambient * mAmbient;
    
    return diffuseColor + specularColor + ambientColor;
}
