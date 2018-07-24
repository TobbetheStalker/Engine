/* TYPEDEF */
struct PixelInputType
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

/* PIXEL SHADER */
float4 PS_main(PixelInputType input) : SV_Target
{
    return input.color;
}