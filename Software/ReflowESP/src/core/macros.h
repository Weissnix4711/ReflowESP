/**
 * Adapted from Marlin FW Project, copyright notice below.
 *
 *
 *
 * Marlin 3D Printer Firmware
 * Copyright (c) 2020 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#pragma once

// Macros to chain up to 40 conditions
#define _DO_1(W,C,A)       (_##W##_1(A))
#define _DO_2(W,C,A,B)     (_##W##_1(A) C _##W##_1(B))
#define _DO_3(W,C,A,V...)  (_##W##_1(A) C _DO_2(W,C,V))
#define _DO_4(W,C,A,V...)  (_##W##_1(A) C _DO_3(W,C,V))
#define _DO_5(W,C,A,V...)  (_##W##_1(A) C _DO_4(W,C,V))
#define _DO_6(W,C,A,V...)  (_##W##_1(A) C _DO_5(W,C,V))
#define _DO_7(W,C,A,V...)  (_##W##_1(A) C _DO_6(W,C,V))
#define _DO_8(W,C,A,V...)  (_##W##_1(A) C _DO_7(W,C,V))
#define _DO_9(W,C,A,V...)  (_##W##_1(A) C _DO_8(W,C,V))
#define _DO_10(W,C,A,V...) (_##W##_1(A) C _DO_9(W,C,V))
#define _DO_11(W,C,A,V...) (_##W##_1(A) C _DO_10(W,C,V))
#define _DO_12(W,C,A,V...) (_##W##_1(A) C _DO_11(W,C,V))
#define _DO_13(W,C,A,V...) (_##W##_1(A) C _DO_12(W,C,V))
#define _DO_14(W,C,A,V...) (_##W##_1(A) C _DO_13(W,C,V))
#define _DO_15(W,C,A,V...) (_##W##_1(A) C _DO_14(W,C,V))
#define _DO_16(W,C,A,V...) (_##W##_1(A) C _DO_15(W,C,V))
#define _DO_17(W,C,A,V...) (_##W##_1(A) C _DO_16(W,C,V))
#define _DO_18(W,C,A,V...) (_##W##_1(A) C _DO_17(W,C,V))
#define _DO_19(W,C,A,V...) (_##W##_1(A) C _DO_18(W,C,V))
#define _DO_20(W,C,A,V...) (_##W##_1(A) C _DO_19(W,C,V))
#define _DO_21(W,C,A,V...) (_##W##_1(A) C _DO_20(W,C,V))
#define _DO_22(W,C,A,V...) (_##W##_1(A) C _DO_21(W,C,V))
#define _DO_23(W,C,A,V...) (_##W##_1(A) C _DO_22(W,C,V))
#define _DO_24(W,C,A,V...) (_##W##_1(A) C _DO_23(W,C,V))
#define _DO_25(W,C,A,V...) (_##W##_1(A) C _DO_24(W,C,V))
#define _DO_26(W,C,A,V...) (_##W##_1(A) C _DO_25(W,C,V))
#define _DO_27(W,C,A,V...) (_##W##_1(A) C _DO_26(W,C,V))
#define _DO_28(W,C,A,V...) (_##W##_1(A) C _DO_27(W,C,V))
#define _DO_29(W,C,A,V...) (_##W##_1(A) C _DO_28(W,C,V))
#define _DO_30(W,C,A,V...) (_##W##_1(A) C _DO_29(W,C,V))
#define _DO_31(W,C,A,V...) (_##W##_1(A) C _DO_30(W,C,V))
#define _DO_32(W,C,A,V...) (_##W##_1(A) C _DO_31(W,C,V))
#define _DO_33(W,C,A,V...) (_##W##_1(A) C _DO_32(W,C,V))
#define _DO_34(W,C,A,V...) (_##W##_1(A) C _DO_33(W,C,V))
#define _DO_35(W,C,A,V...) (_##W##_1(A) C _DO_34(W,C,V))
#define _DO_36(W,C,A,V...) (_##W##_1(A) C _DO_35(W,C,V))
#define _DO_37(W,C,A,V...) (_##W##_1(A) C _DO_36(W,C,V))
#define _DO_38(W,C,A,V...) (_##W##_1(A) C _DO_37(W,C,V))
#define _DO_39(W,C,A,V...) (_##W##_1(A) C _DO_38(W,C,V))
#define _DO_40(W,C,A,V...) (_##W##_1(A) C _DO_39(W,C,V))
#define __DO_N(W,C,N,V...) _DO_##N(W,C,V)
#define _DO_N(W,C,N,V...)  __DO_N(W,C,N,V)
#define DO(W,C,V...)       (_DO_N(W,C,NUM_ARGS(V),V))

// Macros to support option testing
#define _CAT(a,V...) a##V
#define CAT(a,V...) _CAT(a,V)

#define _ISENA_     ~,1
#define _ISENA_1    ~,1
#define _ISENA_0x1  ~,1
#define _ISENA_true ~,1
#define _ISENA(V...)        IS_PROBE(V)

#define _ENA_1(O)           _ISENA(CAT(_IS,CAT(ENA_, O)))
#define _DIS_1(O)           NOT(_ENA_1(O))
#define ENABLED(V...)       DO(ENA,&&,V)
#define NENABLED(V...)      DO(DIS,&&,V)
#define COUNT_ENABLED(V...) DO(ENA,+,V)

#define ANY(V...)          !NENABLED(V)
#define NONE(V...)          NENABLED(V)
#define ALL(V...)           ENABLED(V)
#define BOTH(V1,V2)         ALL(V1,V2)
#define EITHER(V1,V2)       ANY(V1,V2)

// Use NUM_ARGS(__VA_ARGS__) to get the number of variadic arguments
#define _NUM_ARGS(_,n,m,l,k,j,i,h,g,f,e,d,c,b,a,Z,Y,X,W,V,U,T,S,R,Q,P,O,N,M,L,K,J,I,H,G,F,E,D,C,B,A,OUT,...) OUT
#define NUM_ARGS(V...) _NUM_ARGS(0,V,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)

//
// Primitives supporting precompiler REPEAT
//
#define FIRST(a,...)     a
#define SECOND(a,b,...)  b
#define THIRD(a,b,c,...) c

#define IS_PROBE(V...) SECOND(V, 0)     // Get the second item passed, or 0
#define PROBE() ~, 1                    // Second item will be 1 if this is passed
#define _NOT_0 PROBE()
#define NOT(x) IS_PROBE(_CAT(_NOT_, x)) //   NOT('0') gets '1'. Anything else gets '0'.
#define _BOOL(x) NOT(NOT(x))            // _BOOL('0') gets '0'. Anything else gets '1'.
