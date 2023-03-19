# Target Application Example

The `arm_itm.h` header file (located in `arm/inc/c`) contains predefined preprocessor macros for setting ITM events. 

The following code shows a simple example of how these macros can be used in combination with the `itm-logger` program introduced in the previous section. Although only 2 `ITM_EVENT` macros are called, there are actually 3 ITM events set in the `while (1)` loop. 
```c
  /* ... */
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
```
The reason is that the `ITM_EVENT32_WITH_PC()` macro also sets the current value of the PC register at ITM port 5. The `arm_itm.h` header file contains macros for 8, 16 and 32 bits; `ITM_EVENT8()`, `ITM_EVENT16()`, and `ITM_EVENT32()`, respectively. Each of these also has a corresponding macro setting the current `PC` value (`ITM_EVENT8_WITH_PC()`, `ITM_EVENT16_WITH_PC()` and `ITM_EVENT32_WITH_PC()`).
