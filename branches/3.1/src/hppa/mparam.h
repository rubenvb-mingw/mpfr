/* Generated by MPFR's tuneup.c, 2011-07-31, gcc 4.3.2 */
/* generated on gcc61.fsffrance.org (HP PA-8600) with GMP 5.0.2 */


#define MPFR_MULHIGH_TAB  \
 -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
 0,0,0,0,0,0,0,0,48,47,48,47,48,47,48,47, \
 48,47,64,63,64,63,64,63,64,63,64,63,64,63,64,63, \
 64,63,64,63,64,63,64,63,64,63,64,63,64,63,64,63, \
 64,63,64,72,64,72,64,93,64,93,64,93,92,93,92,93, \
 92,93,92,93,92,93,92,93,92,93,92,93,92,93,92,93, \
 92,93,92,93,105,93,105,93,105,93,105,93,105,105,105,108, \
 105,105,105,105,108,105,105,105,108,108,108,117,108,117,108,141, \
 140,141,140,141,140,141,140,141,140,141,140,141,140,141,140,141, \
 140,141,140,141,140,141,140,141,140,141,140,141,140,141,140,141, \
 140,141,140,141,140,141,140,141,141,153,140,141,140,141,140,140, \
 144,140,140,141,140,139,140,141,140,141,140,141,188,188,188,187, \
 188,187,188,188,188,188,188,188,188,188,188,188,188,188,188,187, \
 187,187,188,188,188,188,188,188,210,188,210,188,188,210,188,188, \
 188,188,188,188,188,188,188,188,188,188,186,188,210,188,188,187, \
 188,188,210,210,210,210,210,210,210,210,210,210,210,210,210,210, \
 210,210,210,210,210,210,210,208,210,209,210,210,210,210,210,233, \
 234,234,234,233,232,234,234,234,234,234,234,234,234,234,234,276, \
 234,276,234,276,234,276,276,276,276,276,276,276,282,276,282,276, \
 282,276,276,276,276,276,282,281,276,276,276,276,276,276,276,276, \
 276,276,276,276,276,276,282,276,282,276,282,276,282,281,282,281, \
 282,281,282,281,282,281,282,281,282,281,282,306,282,306,282,306, \
 306,306,306,306,306,306,306,306,306,306,306,306,306,306,306,306, \
 306,372,306,371,306,372,372,372,372,372,372,371,372,372,372,372, \
 372,372,372,372,372,372,372,372,372,372,372,372,372,372,372,372, \
 372,371,372,372,372,372,372,372,372,372,372,372,372,372,372,372, \
 372,372,372,372,372,372,372,372,372,372,372,372,372,372,372,372, \
 372,372,372,372,372,372,372,372,372,372,372,372,372,372,372,372, \
 372,372,372,372,372,372,372,372,372,372,372,372,372,372,372,372, \
 372,372,372,372,372,372,372,372,426,372,426,426,426,426,426,426, \
 426,426,426,426,426,425,426,425,426,426,426,426,426,426,426,426, \
 426,426,426,426,426,424,426,426,426,426,426,426,426,426,426,426, \
 426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426, \
 426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,503, \
 504,503,504,503,504,503,504,503,504,503,504,503,504,503,504,503, \
 504,503,504,503,504,503,504,503,502,503,504,503,504,503,504,503, \
 504,496,504,503,504,503,504,503,504,503,504,503,504,503,504,503, \
 504,503,504,503,504,503,504,503,504,503,568,568,568,568,568,568, \
 568,567,568,568,568,567,568,567,568,567,568,568,568,567,568,568, \
 568,568,568,568,568,567,568,568,568,568,568,568,568,568,568,568, \
 568,568,568,568,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,568,568,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,568,567,568,568,568,568,568,567,568,567,568,568,568,567, \
 568,567,568,567,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,568,568,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,568,568,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,567,568,568,568,568,568,568,632,568,568,568,568,631,568,568, \
 568,568,568,568,568,567,568,567,568,568,568,568,632,632,632,631, \
 632,631,632,631,632,632,632,631,632,632,632,631,632,632,632,728, \
 728,727,728,727,728,728,728,727,728,727,728,727,728,727,728,728, \
 728,728,728,728,728,728,728,728,728,728,728,728,728,728,728,728, \
 728,728,728,728,728,728,728,728,728,728,728,728,728,728,728,728, \
 728,752,728,752,728,752,728,752,752,752,728,752,752,752,752,752, \
 752,752,752,752,752,752,752,752,752,752,752,752,752,751,752,751, \
 752,751,752,751,728,728,728,728,752,728,728,728,728,728,728,728, \
 728,752,832,751,832,752,832,752,832,752,832,752,832,752,832,751, \
 832,831,832,752,832,831,832,832,832,832,832,832,832,824,832,832, \
 832,832,832,832,832,832,832,832,832,832,832,832,832,832,832,832, \
 832,832,832,832,832,832,832,831,832,831,832,831,832,831,832,831, \
 832,831,832,832,832,831,832,831,832,831,832,831,832,831,832,831, \
 832,832,832,831,832,832,832,832,832,831,832,832,832,832,832,832 \
  
#define MPFR_SQRHIGH_TAB  \
 -1,0,0,0,0,0,0,0,0,0,0,7,0,8,9,9, \
 10,10,11,11,12,13,14,13,14,15,16,15,16,17,18,17, \
 18,19,20,19,20,21,22,21,22,23,24,23,24,25,26,25, \
 26,27,28,27,28,29,30,29,30,31,32,31,32,33,34,33, \
 34,35,36,35,36,37,38,37,38,39,40,39,40,41,42,41, \
 42,43,44,43,44,47,48,47,48,47,48,47,48,51,52,51, \
 52,51,52,51,56,55,56,55,56,55,56,59,60,59,60,59, \
 60,63,60,63,64,63,64,63,68,63,68,67,68,67,68,71, \
 68,71,72,71,72,71,72,75,76,75,76,75,76,79,80,79, \
 80,79,80,75,76,83,84,79,80,79,80,79,80,83,84,83, \
 84,83,84,83,88,93,88,93,88,93,96,93,88,93,96,99, \
 96,93,92,93,92,93,96,93,96,99,96,99,96,99,98,99, \
 102,99,102,99,102,105,102,105,102,105,104,105,108,111,108,111, \
 108,117,114,117,116,117,116,117,116,117,120,117,120,123,120,123, \
 120,123,128,129,126,129,128,129,132,129,132,141,138,141,140,141, \
 140,141,140,141,140,141,140,141,140,153,152,153,152,153,152,153, \
 152,153,152,153,152,153,152,153,164,165,164,165,164,165,164,165, \
 164,165,164,165,164,177,176,177,176,177,176,177,176,177,176,177, \
 176,177,180,177,165,189,165,189,165,189,165,164,165,164,165,164, \
 165,164,177,176,177,176,177,176,177,176,177,176,177,176,177,188, \
 189,188,189,188,189,188,189,188,189,188,189,188,189,188,189,200, \
 189,200,201,200,201,200,201,200,201,200,201,212,213,212,213,212, \
 213,212,213,212,213,212,213,212,213,212,213,212,213,224,225,213, \
 225,213,225,213,225,213,225,213,225,213,237,225,237,225,237,225, \
 201,225,201,200,201,201,201,252,201,201,201,201,201,212,213,213, \
 213,213,213,212,213,213,213,212,213,213,213,213,213,213,225,225, \
 225,225,225,225,225,225,225,225,225,225,225,237,237,237,237,237, \
 237,236,237,237,237,252,252,252,252,252,252,252,252,252,252,252, \
 252,252,252,252,252,252,252,252,268,268,268,268,268,268,268,268, \
 268,266,268,268,268,268,268,268,268,268,275,268,275,268,275,268, \
 275,294,294,294,294,294,294,294,300,294,300,294,300,300,300,300, \
 300,300,300,300,300,300,318,318,318,318,318,318,318,318,318,318, \
 318,318,318,318,324,318,318,318,318,324,324,318,324,324,330,330, \
 330,330,342,342,342,342,342,342,342,342,342,342,342,342,342,342, \
 342,348,348,348,348,348,348,348,348,348,348,366,366,366,366,366, \
 366,366,366,366,372,366,372,366,372,372,366,372,372,372,372,372, \
 372,372,372,372,372,372,378,390,378,390,390,390,390,390,390,390, \
 390,390,396,390,396,390,366,390,396,396,372,396,372,396,372,396, \
 378,414,366,414,366,414,366,414,366,414,372,414,372,414,372,414, \
 372,372,372,395,396,395,396,390,390,390,390,390,390,390,390,390, \
 390,390,366,390,396,365,366,371,396,396,372,371,372,390,378,414, \
 378,414,378,414,414,414,414,414,390,414,390,389,390,389,390,395, \
 396,395,396,395,396,396,402,414,402,395,396,395,396,389,414,413, \
 414,413,414,413,414,413,414,414,420,395,420,419,420,395,396,401, \
 396,419,420,419,414,413,414,413,414,413,414,413,414,413,414,413, \
 414,413,420,419,420,419,420,419,420,419,426,425,426,437,438,437, \
 438,437,438,437,438,437,444,437,444,443,438,443,444,443,444,443, \
 444,443,444,443,444,461,462,461,462,461,462,461,462,461,462,461, \
 462,461,462,467,468,467,468,467,468,467,468,467,468,467,474,473, \
 486,485,486,485,486,485,414,485,486,485,486,491,492,491,492,519, \
 520,491,504,503,420,503,504,437,504,503,504,437,504,437,438,437, \
 520,443,444,519,520,519,520,519,520,519,520,519,520,527,520,527, \
 528,527,528,461,528,461,528,461,462,461,462,467,468,467,468,467, \
 468,551,552,551,552,551,552,551,552,551,560,551,552,551,552,551, \
 552,551,552,559,560,559,560,559,560,503,568,567,504,503,504,503, \
 504,503,504,519,520,519,520,519,520,519,520,520,520,519,520,519, \
 520,519,520,519,520,527,528,527,528,527,528,527,528,527,528,527, \
 528,535,552,551,552,551,552,551,552,552,552,551,552,551,552,551, \
 552,551,552,551,552,551,552,551,552,559,560,551,560,559,560,559, \
 560,567,568,567,568,583,568,567,584,583,584,583,584,583,584,583, \
 584,583,584,583,584,583,584,583,584,583,592,591,592,591,592,591, \
 592,591,592,591,592,615,616,519,520,615,520,519,520,615,616,615, \
 616,615,528,615,616,615,528,527,528,615,528,623,624,623,536,552, \
 552,551,552,551,552,551,552,551,552,551,552,551,552,551,552,551 \
  
#define MPFR_DIVHIGH_TAB  \
 0,1,2,3,4,5,6,7,6,7,10,11,10,11,12,13, \
 10,11,11,11,12,12,14,15,14,14,16,16,16,16,18,17, \
 22,19,22,23,22,23,26,27,26,23,30,29,26,27,26,27, \
 30,31,30,31,30,35,30,35,30,35,34,31,34,35,38,35, \
 34,36,38,39,38,39,38,43,38,40,42,43,42,44,42,43, \
 42,44,46,47,46,44,46,51,50,48,50,51,54,52,54,52, \
 50,51,54,55,58,55,54,56,58,56,62,60,58,63,58,63, \
 62,64,62,64,62,64,62,64,62,67,66,71,66,67,74,71, \
 70,67,70,71,74,72,74,75,70,76,74,79,74,75,74,79, \
 74,79,78,80,78,76,78,80,78,79,82,84,82,80,82,87, \
 86,84,86,84,86,84,86,88,90,88,90,92,90,88,94,96, \
 90,92,94,92,94,92,94,96,94,102,98,96,100,102,98,102, \
 98,104,100,102,102,104,104,102,102,102,104,104,104,104,108,112, \
 128,110,128,110,128,128,128,128,128,128,128,128,128,128,128,128, \
 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128, \
 128,128,128,128,128,128,128,128,128,128,128,128,128,128,142,142, \
 142,142,140,142,144,144,144,142,144,142,140,142,140,142,142,144, \
 140,142,140,142,140,144,144,144,144,144,144,144,144,144,148,146, \
 148,160,148,150,148,158,156,158,156,160,156,158,160,160,156,160, \
 164,158,156,160,164,160,164,182,180,182,164,184,182,184,182,182, \
 180,182,182,182,182,186,184,182,180,182,184,184,184,185,182,184, \
 182,185,182,185,182,185,184,185,184,185,182,185,184,184,184,182, \
 184,185,184,186,184,185,182,182,184,184,184,184,184,184,186,185, \
 186,206,200,206,188,206,196,198,196,208,196,198,196,198,196,206, \
 200,206,208,206,196,198,200,208,200,206,200,206,200,208,216,208, \
 208,206,208,206,216,208,216,208,216,208,216,208,216,208,216,220, \
 216,210,216,220,256,220,216,220,216,224,216,222,256,250,248,254, \
 256,256,256,254,256,254,256,254,256,254,256,254,256,256,256,256, \
 256,254,256,254,256,256,256,254,256,254,256,254,256,256,256,254, \
 256,254,256,254,256,254,256,256,256,254,256,254,256,256,256,254, \
 256,254,256,256,256,254,256,254,256,254,256,256,256,254,256,254, \
 256,254,256,254,256,254,256,254,256,282,280,256,256,256,282,284, \
 282,284,282,288,280,281,282,288,282,288,282,282,280,281,280,282, \
 282,287,288,288,280,282,282,288,282,288,282,288,282,288,282,288, \
 282,284,282,288,280,288,282,288,282,284,282,288,282,288,282,288, \
 282,288,288,288,288,288,288,288,288,288,288,288,288,288,296,300, \
 296,304,296,304,298,300,296,300,296,300,312,302,296,306,312,300, \
 312,320,312,300,312,370,312,320,312,302,312,320,312,370,312,371, \
 312,371,312,369,372,371,372,371,368,370,372,370,372,370,372,370, \
 371,369,372,370,368,370,372,370,372,370,372,370,370,370,364,370, \
 371,370,372,370,370,370,372,370,372,370,372,370,370,370,372,370, \
 370,372,370,370,372,370,372,370,372,370,368,370,370,372,372,370, \
 370,370,372,370,372,372,372,370,372,370,370,366,372,370,370,370, \
 372,368,368,370,370,370,372,370,370,370,372,370,372,370,368,370, \
 372,370,372,370,369,370,372,370,372,369,372,370,372,371,372,370, \
 372,370,368,372,372,371,372,369,372,371,370,371,372,370,372,372, \
 372,370,372,372,372,372,376,416,376,416,376,416,414,416,416,420, \
 384,416,415,416,414,416,415,416,392,420,400,416,420,420,392,420, \
 400,416,416,416,416,420,416,412,416,416,416,416,418,416,414,416, \
 418,420,418,420,418,416,416,416,418,420,414,420,418,420,420,420, \
 416,416,418,420,418,418,416,416,420,416,418,416,432,420,432,420, \
 416,416,416,420,416,420,432,420,418,420,432,420,418,416,418,420, \
 420,420,432,420,420,420,432,468,464,512,432,468,432,444,432,444, \
 512,508,432,468,512,512,464,510,432,510,512,512,512,512,512,512, \
 512,512,512,512,512,508,512,508,512,512,512,508,512,510,512,512, \
 512,512,512,512,512,512,512,508,512,512,512,508,512,512,512,512, \
 512,512,512,512,512,512,512,512,512,512,512,508,512,512,512,512, \
 512,512,512,512,512,508,512,512,512,512,512,468,464,512,564,468, \
 512,564,512,512,564,512,512,512,564,508,564,508,564,503,564,508, \
 512,508,512,512,564,508,512,508,564,512,512,512,512,512,512,508, \
 512,510,512,512,512,512,512,512,512,512,512,512,512,512,512,512, \
 512,508,512,508,512,512,512,512,512,512,512,512,512,512,512,512, \
 512,512,512,512,512,512,512,512,512,564,562,564,560,512,564,564, \
 562,564,560,564,564,564,560,564,564,564,564,564,564,564,564,562 \
  
#define MPFR_MUL_THRESHOLD 6 /* limbs */
#define MPFR_SQR_THRESHOLD 8 /* limbs */
#define MPFR_DIV_THRESHOLD 23 /* limbs */
#define MPFR_EXP_2_THRESHOLD 530 /* bits */
#define MPFR_EXP_THRESHOLD 2918 /* bits */
#define MPFR_SINCOS_THRESHOLD 28251 /* bits */
#define MPFR_AI_THRESHOLD1 -21852 /* threshold for negative input of mpfr_ai */
#define MPFR_AI_THRESHOLD2 2256
#define MPFR_AI_THRESHOLD3 34310
/* Tuneup completed successfully, took 8236 seconds */
