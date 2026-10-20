// Dead-zone remap of a stick axis: +-0.1 maps to 0, the rest is rescaled, squared with its sign and clamped to [-1, 1].
float fn_80446ACC(register float x)
{
    if ((x < 0.0f ? -x : x) <= 0.1f)
        return 0.0f;
    if (x < 0.0f)
    {
        x = (x + 0.1f) * (1.0f / 0.9f);
        x = x * -x;
    }
    else
    {
        x = (x - 0.1f) * (1.0f / 0.9f);
        x = x * x;
    }
    return x >= -1.0f ? (x <= 1.0f ? x : 1.0f) : -1.0f;
}
