/**************************************************
 *
 * Target Access Plugin demo (for Cortex-M)
 *
 * Copyright (c) 2023 IAR Systems AB.
 *
 * See LICENSE for detailed license information.
 *
 **************************************************/

#if !defined(SIMULATOR) // Set in `Preprocessor`
#include <arm_itm.h>
#else
#warning "ITM events require hardware. No support provided in Simulator."
#endif
#include <stdint.h>
#include <stddef.h>

__root uint8_t  buffer[4] @ 0x20001000 = "ABCD";
__root uint32_t val       @ 0x20002000 = 0x48474645;

void demo()
{
  uint8_t value = 0;
  uint32_t sum = 0;

  while (1)
  {
    if (value++ % 10 == 0)
    {
      sum += value;

#if !defined(SIMULATOR)
      ITM_EVENT8(20, value);
      ITM_EVENT32_WITH_PC(21, sum);
#endif

      for (size_t i = 100; i > 0; --i); // Delay
    }
  }
}
