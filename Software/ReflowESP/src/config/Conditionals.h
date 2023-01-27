#pragma once

/**
 * Conditionals.h
 * Conditionals that have to be met by Configuration.h
 */

#ifdef HAS_MAX6675
  #ifdef HAS_MAX31855
    #error "Cannot have both HAS_MAX6675 and HAS_MAX31855 defined"
  #endif
#endif

// #if ANY(HAS_MAX6675, HAS_MAX31855)
//   #if !(THERM_CS0 >= 0) && !(THERM_CS1 >= 0)
//     #error "Must define pins for one of THERM_CS0 or THERM_CS1"
//   #endif
// #endif

#if !defined(SSR1) && !defined(SSR2)
  #error "Must define one of SSR1 and SSR2"
#endif

#if !defined(MAX_DEPTH) ||  !defined(FONT_WIDTH) || !defined(FONT_HEIGHT) || !defined(GFX_WIDTH) || !defined(GFX_HEIGHT)
  #error "Define all MAX_DEPTH, FONT(WIDTH|HEIGHT), GFX(WIDTH|HEIGHT)"
#endif
