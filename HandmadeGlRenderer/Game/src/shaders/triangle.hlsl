cbuffer Matrices
{
    matrix worldPos;
    matrix viewPos;
    matrix projectionPos;
};

struct VSIN
{
    float4 pos : POSITION;
    float4 color : COLOR;
};

struct PSIN
{
    float4 pos : SV_POSITION;
    float4 color : COLOR;
};


PSIN main(VSIN input)
{
    PSIN output;

    input.pos.w = 1.0f;

    output.pos = mul(input.pos, worldPos);
    output.pos = mul(output.pos, viewPos);
    output.pos = mul(output.pos, projectionPos);

    output.color = input.color;

    return output;
}
