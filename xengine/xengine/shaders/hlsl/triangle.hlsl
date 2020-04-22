cbuffer Matrices
{
    matrix world_pos;
    matrix view_pos;
    matrix projection_pos;
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

    output.pos = mul(input.pos, world_pos);
    output.pos = mul(output.pos, view_pos);
    output.pos = mul(output.pos, projection_pos);

    output.color = input.color;

    return output;
}
