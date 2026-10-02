asm void RealMode(register unsigned int config)
{
    nofralloc

    clrlwi  config, config, 2
    mtsrr0  config
    mfmsr   config
    rlwinm  config, config, 0, 28, 25
    mtsrr1  config
    rfi
}
