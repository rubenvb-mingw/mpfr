/* Various Thresholds of MPFR, not exported.  -*- mode: C -*-

Copyright 2005, 2006, 2007, 2008, 2009, 2010, 2011 Free Software Foundation, Inc.

This file is part of the GNU MPFR Library.

The GNU MPFR Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 3 of the License, or (at your
option) any later version.

The GNU MPFR Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the GNU MPFR Library; see the file COPYING.LESSER.  If not, see
http://www.gnu.org/licenses/ or write to the Free Software Foundation, Inc.,
51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA. */

/* Generated by MPFR's tuneup.c, 2011-07-31, gcc 3.3.5 */
/* gcc64.fsffrance.org (sparc64) with gmp 5.0.2 */


#define MPFR_MULHIGH_TAB  \
 -1,0,0,-1,0,-1,-1,-1,7,-1,9,9,11,11,11,13, \
 11,13,13,15,15,17,15,19,17,17,19,19,19,19,21,21, \
 23,23,23,23,25,27,23,30,30,30,30,30,30,30,34,34, \
 34,34,34,34,38,38,38,38,38,38,42,42,41,42,42,42, \
 42,42,42,46,46,46,46,46,46,50,50,50,50,50,50,60, \
 60,60,60,60,60,60,60,60,60,68,60,68,68,60,68,68, \
 68,68,68,68,68,68,68,68,76,76,76,76,76,76,76,76, \
 76,76,76,76,84,76,84,84,84,76,84,84,84,84,84,84, \
 84,84,84,84,84,84,92,92,92,92,92,92,92,84,92,92, \
 92,92,100,100,100,100,100,100,100,100,100,100,120,100,120,120, \
 120,120,120,120,120,120,120,120,120,120,120,120,120,120,120,120, \
 120,120,119,120,119,120,120,136,136,136,136,136,136,136,136,136, \
 136,136,136,136,136,136,136,136,136,136,136,136,136,136,136,152, \
 152,152,152,136,152,152,152,136,152,136,152,152,136,152,152,152, \
 152,152,152,136,152,152,168,168,168,201,168,168,201,201,201,201, \
 201,201,201,201,201,200,201,200,201,200,201,201,201,201,201,201, \
 201,201,201,201,201,200,201,201,201,201,201,201,201,201,201,201, \
 201,201,201,201,201,201,201,201,201,201,201,201,201,201,201,201, \
 201,201,201,201,200,201,200,201,201,201,201,201,201,201,201,201, \
 225,224,225,225,225,225,225,224,225,224,225,224,225,225,225,282, \
 225,282,282,282,282,282,282,294,294,294,294,294,294,294,294,294, \
 282,294,294,294,294,294,294,294,294,294,294,294,294,294,294,294, \
 294,294,293,294,294,294,294,294,294,294,294,294,294,294,294,294, \
 294,294,294,294,293,294,294,294,294,294,294,294,294,294,293,294, \
 294,294,294,294,294,294,294,294,294,294,294,294,294,318,294,318, \
 294,294,294,360,359,360,360,358,360,360,360,360,359,360,360,360, \
 360,360,360,360,360,360,360,360,360,360,360,360,360,360,360,360, \
 360,360,360,360,360,360,359,360,360,360,360,360,360,360,360,360, \
 360,360,360,360,360,360,360,358,360,360,360,360,360,360,354,360, \
 360,360,360,360,360,360,360,392,360,360,392,392,360,392,391,392, \
 391,392,392,392,391,392,391,392,354,392,391,392,391,392,391,392, \
 391,392,391,392,391,392,391,392,392,392,391,392,392,392,392,392, \
 424,392,391,392,424,392,424,424,424,392,424,424,424,424,424,472, \
 424,424,424,472,424,472,472,472,472,472,472,472,472,472,472,471, \
 472,472,472,472,472,472,472,472,472,472,472,471,472,472,472,471, \
 472,472,472,472,472,472,472,472,472,472,472,472,472,472,471,472, \
 472,472,472,472,472,472,472,472,472,472,472,472,472,472,472,472, \
 472,472,472,472,472,472,472,472,472,472,472,472,472,472,472,472, \
 472,472,472,472,472,471,472,472,472,472,472,472,472,472,472,472, \
 472,472,472,472,472,472,472,472,472,472,472,472,472,472,472,472, \
 472,472,472,536,536,536,536,536,536,528,536,536,536,536,536,536, \
 536,536,536,536,536,536,544,536,536,536,536,600,536,599,600,600, \
 599,599,600,600,600,600,600,600,599,600,600,600,600,599,600,600, \
 600,600,600,600,600,599,600,599,600,600,600,599,600,600,600,600, \
 600,599,600,599,600,600,600,599,600,600,600,600,600,600,600,600, \
 600,600,600,599,599,600,600,600,600,600,600,600,600,600,600,600, \
 600,600,600,600,600,599,600,600,599,600,599,600,599,600,600,600, \
 599,600,600,600,599,600,600,664,600,664,600,600,600,600,600,663, \
 599,664,600,664,600,664,664,664,664,664,664,664,663,664,664,664, \
 663,664,664,664,663,664,663,664,664,664,663,664,663,664,664,664, \
 664,664,664,664,664,664,663,664,664,663,664,664,664,664,664,664, \
 663,663,664,664,664,664,663,664,663,664,663,664,663,664,663,664, \
 663,664,663,664,664,664,664,664,664,664,663,664,663,664,664,664, \
 664,664,664,664,664,664,664,664,663,728,663,728,728,727,728,728, \
 728,728,728,728,728,728,728,728,727,728,728,728,727,728,728,728, \
 728,728,728,728,727,728,727,728,728,728,727,728,727,728,728,728, \
 727,728,728,728,727,728,728,728,728,728,727,728,728,728,728,728, \
 727,728,728,728,727,728,792,792,727,728,727,728,791,792,728,728, \
 728,728,728,728,728,728,792,792,727,792,792,792,792,792,791,792, \
 792,792,792,792,792,792,792,792,792,792,792,792,792,792,791,790, \
 791,792,791,792,792,792,791,792,791,792,791,792,791,792,791,792, \
 791,792,792,792,791,792,792,792,791,792,792,792,791,792,791,791, \
 791,791,791,792,792,791,792,792,791,792,792,792,791,792,792,792, \
 792,791,792,792,791,792,792,856,792,792,792,856,792,791,792,856 \
  
#define MPFR_SQRHIGH_TAB  \
 -1,0,0,0,0,-1,5,5,7,7,9,7,9,8,9,10, \
 11,10,11,11,13,12,13,13,17,14,16,16,16,16,17,18, \
 18,18,19,20,20,22,21,24,22,24,23,24,24,26,26,26, \
 28,28,28,30,28,29,30,31,30,31,32,33,32,33,34,35, \
 34,35,36,36,36,37,38,40,40,40,40,40,42,43,42,44, \
 45,47,50,44,44,44,50,48,50,51,47,48,49,48,49,50, \
 51,52,53,52,53,52,53,54,55,56,57,58,59,56,57,58, \
 59,58,59,62,61,60,61,62,63,62,63,64,65,64,65,70, \
 67,72,72,72,76,74,72,72,74,76,76,76,76,74,80,80, \
 74,76,84,80,80,82,80,84,82,84,84,88,84,90,88,82, \
 86,88,88,84,84,86,88,88,88,88,88,88,88,88,90,92, \
 90,92,92,92,96,94,96,96,96,96,100,96,96,116,98,100, \
 98,98,100,100,117,117,118,119,119,120,116,119,120,119,118,119, \
 119,119,122,128,120,119,120,119,116,121,120,118,120,125,125,119, \
 125,124,131,131,130,131,134,131,132,134,124,125,133,143,137,138, \
 131,144,138,137,135,138,130,135,137,143,143,137,137,143,130,138, \
 131,140,138,137,136,149,149,142,143,156,149,149,144,154,149,147, \
 149,156,149,152,147,147,155,156,149,150,149,146,160,160,163,168, \
 167,167,156,166,156,164,156,158,161,172,161,166,167,161,173,164, \
 167,174,173,162,171,172,173,176,173,171,165,182,174,174,173,184, \
 171,170,174,173,178,176,176,168,179,176,177,182,178,180,191,174, \
 186,184,176,192,180,180,173,174,179,185,175,182,184,180,179,178, \
 179,180,179,186,185,185,188,184,186,188,186,190,191,191,195,192, \
 198,192,194,200,213,197,225,198,201,200,191,210,195,212,224,212, \
 213,213,212,212,213,213,221,218,218,224,199,224,219,224,225,225, \
 225,222,225,228,229,213,237,228,218,224,234,240,237,240,242,242, \
 243,240,242,242,235,228,231,228,237,230,231,236,236,237,336,336, \
 336,336,336,336,336,336,336,336,336,336,341,336,336,336,336,336, \
 336,336,341,336,336,336,336,342,336,336,342,336,336,336,336,342, \
 336,336,336,336,336,336,336,342,336,336,336,336,342,336,336,336, \
 336,336,336,336,336,336,336,342,336,336,336,336,342,336,336,342, \
 336,336,342,336,336,336,336,336,336,336,342,336,336,336,336,342, \
 336,342,342,336,342,342,336,342,336,342,336,336,342,336,336,342, \
 336,336,342,336,336,342,336,342,342,342,341,348,342,348,348,348, \
 342,342,354,348,354,354,348,336,354,354,354,336,342,360,360,354, \
 354,342,360,360,366,366,360,372,354,360,354,360,354,360,360,353, \
 336,336,342,360,366,342,360,336,336,342,342,336,336,336,341,341, \
 336,336,336,336,342,342,336,342,342,342,342,336,342,342,341,342, \
 348,342,342,360,354,348,348,342,354,348,360,348,354,354,353,354, \
 354,354,354,456,360,360,456,366,372,366,366,456,354,366,456,456, \
 456,378,456,456,455,456,456,456,378,366,390,384,378,378,360,378, \
 372,366,378,456,378,464,472,378,472,472,336,456,472,456,456,456, \
 472,472,456,456,472,464,456,456,456,342,426,456,426,455,472,456, \
 472,472,426,472,348,456,472,456,456,455,456,480,455,456,455,456, \
 456,455,456,456,454,456,456,456,456,455,456,456,454,455,456,456, \
 456,464,456,456,455,456,455,456,456,464,456,456,472,456,456,464, \
 472,472,456,456,455,456,456,456,455,472,479,456,472,472,488,464, \
 472,472,471,488,472,472,488,488,472,472,488,456,480,472,456,488, \
 472,472,479,463,488,426,456,426,426,426,426,425,455,455,425,456, \
 455,455,456,480,455,456,456,456,456,455,456,456,454,456,455,456, \
 456,455,456,456,455,455,455,456,456,454,456,456,455,456,456,456, \
 456,455,456,456,472,456,456,456,456,455,464,464,472,472,472,464, \
 472,472,456,455,472,472,471,456,472,480,456,480,480,480,456,488, \
 480,488,488,488,472,472,488,488,472,472,488,480,496,472,456,480, \
 496,472,488,456,480,456,456,456,456,488,456,456,488,456,456,456, \
 456,455,456,456,455,455,456,464,456,512,456,456,512,472,464,456, \
 472,512,456,480,464,480,472,471,472,472,471,479,470,480,471,471, \
 472,472,480,488,478,480,488,487,480,480,488,488,568,485,488,488, \
 512,488,488,471,568,512,512,512,512,496,511,511,512,512,520,511, \
 512,512,520,520,568,512,520,520,512,512,520,520,519,520,519,519, \
 520,568,520,536,536,536,536,528,536,528,535,535,534,512,535,512, \
 536,536,552,552,536,552,552,520,567,544,552,552,552,568,567,567, \
 568,568,567,567,568,568,535,584,568,512,568,567,512,568,567,568, \
 576,568,567,584,568,600,584,584,600,568,597,592,591,600,599,599 \
  
#define MPFR_DIVHIGH_TAB  \
 0,1,2,3,4,5,6,7,6,7,8,9,10,11,12,13, \
 10,10,11,11,13,12,13,13,14,14,15,15,18,17,19,19, \
 18,21,19,20,22,21,27,27,22,22,27,28,27,27,27,30, \
 27,27,27,27,31,31,30,30,31,31,31,35,34,33,35,35, \
 38,37,36,38,39,39,39,37,39,39,43,43,47,42,43,43, \
 45,47,54,43,54,54,45,54,54,54,54,55,54,54,55,54, \
 54,54,54,54,54,54,54,54,54,54,58,58,60,60,60,60, \
 60,60,68,62,60,60,65,68,68,68,68,68,67,68,76,68, \
 67,68,67,68,76,76,71,73,76,76,77,76,79,73,79,84, \
 76,76,78,76,76,84,84,84,84,83,84,84,92,92,83,84, \
 92,92,84,84,92,84,88,108,86,108,108,108,108,108,108,108, \
 108,92,108,108,92,108,108,108,120,120,108,108,120,120,120,120, \
 120,120,108,108,108,120,108,108,120,108,118,108,108,108,108,120, \
 120,120,108,108,120,120,118,120,120,120,120,120,120,120,120,120, \
 120,120,120,120,120,120,136,120,120,120,125,136,136,120,136,136, \
 136,136,136,136,136,136,136,136,136,136,136,136,136,136,136,136, \
 136,136,136,136,152,136,135,136,152,152,136,136,152,152,152,152, \
 152,152,152,152,151,152,152,152,152,152,149,150,152,152,152,152, \
 152,152,151,152,152,168,167,168,152,152,167,152,152,152,165,157, \
 168,168,167,168,168,184,168,168,168,168,168,168,168,168,168,168, \
 168,167,168,168,184,168,168,168,184,184,184,184,184,184,184,184, \
 172,184,179,180,184,184,184,184,184,184,176,180,184,184,216,216, \
 184,184,184,216,184,184,216,184,184,216,184,216,216,184,216,216, \
 240,240,216,216,240,240,216,216,240,240,239,214,240,240,216,240, \
 240,240,238,240,240,240,216,240,240,239,240,216,240,240,216,238, \
 240,240,240,216,240,240,240,238,240,240,239,240,240,240,240,240, \
 240,239,240,240,240,240,240,240,240,240,239,238,240,240,240,240, \
 240,240,240,238,240,240,240,240,240,240,239,238,240,240,240,240, \
 240,240,238,238,240,240,240,240,240,239,239,240,240,240,240,240, \
 240,240,240,240,240,240,271,240,240,240,240,271,240,240,272,272, \
 272,272,272,272,272,272,272,272,270,271,272,272,272,272,272,272, \
 272,271,272,272,272,269,272,272,272,270,269,272,272,272,272,272, \
 272,272,272,269,272,272,272,272,304,267,271,272,272,272,272,272, \
 271,272,272,272,272,272,271,272,272,270,272,272,272,272,273,301, \
 304,304,300,301,304,303,304,304,304,303,303,304,304,304,303,301, \
 304,304,303,298,304,304,303,304,304,303,301,304,304,303,301,302, \
 304,303,304,304,304,304,301,304,304,304,301,302,304,304,301,304, \
 304,303,303,304,304,304,304,304,304,304,303,304,304,304,336,336, \
 336,335,336,334,336,336,336,336,336,336,336,336,336,336,336,336, \
 336,336,334,336,336,336,336,336,336,336,335,336,336,336,336,336, \
 336,336,336,336,336,328,336,336,336,336,335,336,336,336,336,336, \
 336,368,336,334,336,336,336,336,336,336,336,336,336,336,396,400, \
 398,384,368,400,384,399,399,400,368,368,368,400,368,368,368,400, \
 400,400,399,400,400,376,400,400,400,367,399,400,368,367,400,366, \
 367,368,400,366,368,368,365,368,368,368,400,399,400,400,368,399, \
 368,368,366,368,368,368,400,368,368,368,368,368,368,368,400,400, \
 396,400,397,374,400,399,400,400,400,400,397,398,400,401,400,400, \
 400,400,400,396,399,397,400,400,400,400,400,396,400,401,400,432, \
 400,398,399,400,396,396,432,432,400,432,400,396,400,397,399,400, \
 400,400,400,396,400,401,432,432,432,399,432,400,400,432,432,432, \
 432,432,432,432,432,433,432,432,432,432,432,480,480,432,432,432, \
 432,432,432,432,432,432,432,432,432,431,431,432,432,480,432,432, \
 480,480,432,478,480,432,432,480,432,432,432,432,480,432,432,432, \
 432,432,432,432,480,480,432,432,480,432,432,432,432,432,480,478, \
 480,447,477,480,480,480,480,480,480,479,440,444,480,445,448,480, \
 480,479,464,464,480,480,480,478,480,480,478,480,480,480,480,480, \
 480,479,480,479,480,480,478,480,480,480,478,478,480,480,480,480, \
 480,480,480,478,480,480,480,478,480,479,478,480,480,476,480,478, \
 480,480,478,478,480,480,480,480,480,479,479,478,480,480,480,480, \
 480,479,480,478,480,480,480,480,480,479,543,544,544,480,544,544, \
 542,543,544,544,544,540,544,544,544,544,544,542,544,544,544,544, \
 542,542,542,542,544,544,544,560,542,542,575,543,544,544,544,542, \
 544,575,575,544,544,544,544,544,561,561,543,559,544,560,560,560, \
 608,587,573,575,575,608,583,585,560,575,585,575,588,573,608,577 \
  
#define MPFR_MUL_THRESHOLD 13 /* limbs */
#define MPFR_SQR_THRESHOLD 11 /* limbs */
#define MPFR_DIV_THRESHOLD 19 /* limbs */
#define MPFR_EXP_2_THRESHOLD 1092 /* bits */
#define MPFR_EXP_THRESHOLD 11053 /* bits */
#define MPFR_SINCOS_THRESHOLD 25857 /* bits */
#define MPFR_AI_THRESHOLD1 -19352 /* threshold for negative input of mpfr_ai */
#define MPFR_AI_THRESHOLD2 1476
#define MPFR_AI_THRESHOLD3 30069
/* Tuneup completed successfully, took 8167 seconds */