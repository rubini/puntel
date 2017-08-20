#include <stdint.h>

extern void neopix_rgb(uint8_t r, uint8_t g, uint8_t b);
extern void neopix_reset(void);
/* Warning: order in array is G, R, B */
extern void neopix_array(const uint8_t *a, int len, int fire);

