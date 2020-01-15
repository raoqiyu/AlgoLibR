
#ifndef REGISTER_TYPES
#define REGISTER_TYPES

#define REGISTER_float(func) func(float)
#define REGISTER_double(func) func(double)

#define REGISTER_unsigned_short(func) func(unsigned short)
#define REGISTER_unsigned_int(func) func(unsigned int)
#define REGISTER_unsigned_long(func) func(unsigned long)
#define REGISTER_unsigned_long_long(func) func(unsigned long long)

#define REGISTER_short(func) func(short)
#define REGISTER_int(func) func(int)
#define REGISTER_long(func) func(long)
#define REGISTER_long_long(func) func(long long)


#define REGISTER_SIGNED_INTEGRAL_TYPES(func)                                      \
  REGISTER_short(func) REGISTER_int(func) REGISTER_long(func) REGISTER_long_long(func) 

#define REGISTER_UNSIGNED_INTEGRAL_TYPES(func)                                      \
  REGISTER_unsigned_short(func) REGISTER_unsigned_int(func) REGISTER_unsigned_long(func) REGISTER_unsigned_long_long(func) 

#define REGISTER_INTEGRAL_TYPES(func)                                      \
  REGISTER_SIGNED_INTEGRAL_TYPES(func) REGISTER_UNSIGNED_INTEGRAL_TYPES(func)

#define REGISTER_FLOAT_TYPES(func)                                      \
  REGISTER_float(func) REGISTER_double(func)

#define REGISTER_REAL_NUMBER_TYPES(func)                                      \
  REGISTER_INTEGRAL_TYPES(func) REGISTER_FLOAT_TYPES(func) 

#define REGISTER_bool(func) func(bool)

#endif