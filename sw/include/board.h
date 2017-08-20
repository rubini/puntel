#  define GPIO_NEOPIXEL (32 + 25) /* puntel */

static inline void NEOPIX_LOWER(void)
{
        if (GPIO_NEOPIXEL > 0)
                writel(0, __GPIO_WORD(GPIO_NEOPIXEL));
}

static inline void NEOPIX_RAISE(void)
{
        if (GPIO_NEOPIXEL > 0)
                writel(1, __GPIO_WORD(GPIO_NEOPIXEL));
}
