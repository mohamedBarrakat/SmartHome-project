#ifndef UTILS
#define UTILS

#define set_bit(var,bitno) ((var) |= ((u8)(0x01<<bitno)))
#define clr_bit(var,bitno) ((var) &= ~((u8)(0x01<<bitno)))
#define toggle_bit(var,bitno) ((var) ^= ((u8)(0x01<<bitno)))
#define get_bit(var,bitno) ((var>>bitno) & (0x01))

#endif
