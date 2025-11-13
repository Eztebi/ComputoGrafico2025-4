struct VSInput {
    float3 position : POSITION;
    float3 normal : NORMAL;
};

struct PSInput {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
};

cbuffer cb0 : register(b0) {
    float4x4 model;
    float4x4 view;
    float4x4 projection;
    
    float4 eye;
    float4 center;
    float4 up;

    uint angle;
    
    float3 padding;
}

// Vertex Shader
PSInput VSMain(VSInput input) {
    PSInput output;
    // Compute the rotation matrix
    float rotation_speed = -0.01f;
    
    float cosTheta = cos(angle * rotation_speed);
    float sinTheta = sin(angle * rotation_speed);
    
    //position
    output.position = mul(projection, mul(view, mul(model, float4(input.position.xyz, 1.0f))));

    
    //normal
    float rotated_normal_x = input.normal.x * cosTheta - input.normal.z * sinTheta;
    float rotated_normal_y = input.normal.x * sinTheta + input.normal.z * cosTheta;
    output.normal = float3(rotated_normal_x, input.normal.y, rotated_normal_y);

    return output;
}

// Pixel Shader
float4 PSMain(PSInput input) : SV_TARGET {
    float3 dir_light_color = float3(0.5, 0.5, 0.5);
    float3 dir_light_direction = normalize(float3(0, -1, 0));
    float dir_light_brightness = dot(input.normal, -dir_light_direction);
    float3 dir_light_final_color = dir_light_brightness * dir_light_color;
    
    float3 ambient_color = float3(1.0, 0.41, 0.70);
    float3 final_color = ambient_color + dir_light_final_color;
    
    return float4(final_color.x, final_color.y, final_color.z, 1.0);
}