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

#define LED_G GPIO_NR(0, 12)
#define LED_Y GPIO_NR(0, 13)
#define LED_R GPIO_NR(0, 14)
