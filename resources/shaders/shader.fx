
struct VS_OUTPUT
{
  float4 Pos : SV_POSITION;
  float4 Col : COLOR0;
};

VS_OUTPUT VS( float4 Pos : POSITION, float4 Col : COLOR)
{
  VS_OUTPUT output;
  output.Pos = Pos;
  output.Col = Col;
  return output;
}

float4 PS(VS_OUTPUT input) : SV_Target
{
  return input.Col;
}
