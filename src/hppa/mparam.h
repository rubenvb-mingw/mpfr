/* Generated by MPFR's tuneup.c, 2010-10-23, gcc 4.3.4, gmp 5.0.1 */
/* Produced on a HP-UX hpbox B.11.11 U 9000/785 */
/* used MPFR svn revision 7240 */

#define MPFR_MULHIGH_TAB  \
 -1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, \
 0,0,0,0,0,0,32,0,0,0,32,0,0,0,0,0, \
 0,0,0,0,0,0,0,0,0,0,48,47,48,47,48,47, \
 64,47,64,63,64,63,64,63,64,63,64,63,64,63,64,63, \
 64,63,64,63,64,63,64,63,64,63,64,63,64,63,64,63, \
 64,63,64,63,64,93,64,93,64,93,92,93,92,93,92,93, \
 92,93,92,93,92,93,92,93,92,93,92,93,92,93,92,93, \
 92,93,92,93,92,93,105,93,105,93,105,93,105,93,105,93, \
 105,105,105,108,108,117,105,115,108,117,117,141,116,141,140,141, \
 140,141,140,141,140,141,140,141,140,141,140,141,140,141,140,141, \
 140,141,140,141,140,141,141,141,140,141,141,141,140,141,141,141, \
 140,141,141,141,140,141,140,141,140,141,140,141,140,141,140,141, \
 140,141,140,141,140,141,140,141,140,188,140,188,188,188,188,188, \
 188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188, \
 188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188, \
 188,188,188,188,188,188,188,188,188,188,188,188,188,188,188,188, \
 188,210,188,188,188,210,210,210,210,210,210,210,210,210,210,210, \
 210,210,210,210,210,210,210,210,210,210,210,210,210,210,210,234, \
 234,234,234,234,234,234,234,276,234,276,234,276,276,276,276,276, \
 276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276, \
 276,276,276,276,276,276,276,276,276,276,276,276,276,276,276,276, \
 276,276,276,276,276,276,276,276,276,276,276,276,276,276,282,276, \
 282,276,282,276,282,281,282,281,282,281,282,276,282,276,300,276, \
 300,276,306,276,306,276,306,276,306,276,306,276,306,276,306,276, \
 306,276,306,276,306,372,372,372,372,372,372,372,372,372,372,372, \
 372,372,372,372,372,372,372,372,372,372,372,372,372,372,372,372, \
 372,372,372,372,372,372,372,372,372,372,372,372,372,372,372,372, \
 372,372,372,372,372,372,372,372,372,372,372,372,372,372,372,372, \
 372,372,372,372,372,372,372,372,372,372,372,372,372,372,372,372, \
 372,372,372,372,372,372,372,372,372,372,372,372,372,372,372,372, \
 372,372,372,372,372,372,372,372,426,372,426,426,426,372,426,426, \
 426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426, \
 426,426,426,426,426,426,426,426,426,426,426,426,426,426,426,426, \
 426,426,426,426,425,426,426,426,426,426,426,426,426,426,425,426, \
 426,425,426,426,426,426,426,425,426,426,504,503,504,503,504,503, \
 504,503,504,503,504,503,504,503,504,503,504,503,504,503,504,503, \
 504,503,504,503,504,503,504,503,504,503,504,503,504,504,504,503, \
 504,504,504,503,504,504,504,504,504,504,504,504,504,504,504,504, \
 504,504,504,504,504,504,504,504,504,504,504,503,504,504,504,503, \
 504,503,504,503,504,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,568,568,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,568,568,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,567,568,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,568,568,568,568,568,568,568,568,568,568,568,568,568,567, \
 568,568,568,568,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,568,568,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,568,568,568,568,568,568,568,568,568,568,568,568,568,568, \
 568,568,632,632,632,631,632,631,632,631,632,631,632,631,632,631, \
 632,631,632,631,632,632,632,632,632,632,632,632,632,632,632,632, \
 632,632,632,632,632,632,632,632,632,632,728,728,728,632,728,728, \
 728,728,728,728,728,728,728,727,728,727,728,728,728,728,728,728, \
 728,728,728,728,728,728,728,728,728,728,728,728,728,728,728,728, \
 728,728,728,728,728,728,728,728,728,728,728,728,728,728,728,727, \
 728,728,728,728,728,728,728,728,728,728,728,752,728,752,728,752, \
 728,752,728,728,728,728,728,728,728,728,728,728,728,728,728,728, \
 728,728,728,728,728,728,728,728,728,728,728,728,728,728,728,728, \
 728,728,728,728,728,728,728,728,728,728,752,752,752,752,752,752, \
 752,752,752,752,752,752,752,752,752,752,752,752,832,832,831,832, \
 832,832,832,832,832,832,831,832,832,832,832,832,832,832,832,832, \
 832,832,832,832,832,832,832,832,832,832,832,832,832,832,832,832, \
 832,831,832,832,832,832,832,831,832,832,832,832,832,832,832,832, \
 832,832,832,832,832,832,832,832,832,832,832,832,832,832,832,832 \

#define MPFR_SQRHIGH_TAB  \
 -1,0,0,0,0,0,0,0,0,0,0,7,8,8,9,9, \
 10,10,11,11,12,12,13,13,14,14,15,15,16,16,17,17, \
 18,18,19,19,20,20,21,21,22,22,23,25,24,24,25,25, \
 26,26,27,27,28,28,29,29,30,30,31,31,32,32,33,33, \
 34,34,35,35,36,36,37,37,38,38,39,39,40,40,41,41, \
 42,42,43,43,44,47,45,47,48,47,52,51,52,51,52,51, \
 52,51,52,55,56,52,56,55,56,55,56,59,60,59,60,63, \
 60,63,64,63,64,67,68,63,64,67,68,67,68,71,72,71, \
 72,74,68,71,72,71,72,75,76,75,76,79,80,79,80,79, \
 80,79,80,83,84,76,77,77,78,79,80,79,80,80,81,83, \
 84,83,84,87,88,87,88,93,92,93,96,93,96,99,96,99, \
 98,99,102,105,102,105,104,105,96,99,96,99,96,99,97,99, \
 102,99,102,99,102,105,102,105,108,105,108,105,108,111,114,111, \
 114,117,114,117,116,117,114,117,116,117,122,117,122,123,122,123, \
 126,123,126,129,126,129,128,129,132,129,132,141,132,141,140,141, \
 140,141,140,141,140,141,146,153,152,153,152,153,152,153,152,153, \
 152,153,152,153,156,165,164,165,164,165,164,165,164,165,164,165, \
 164,165,164,165,176,177,176,177,176,177,176,177,176,177,176,177, \
 153,177,165,189,165,189,165,164,165,164,165,164,165,164,165,164, \
 165,176,177,176,177,176,177,176,177,176,177,176,177,176,189,188, \
 189,188,189,188,189,188,189,188,189,188,189,188,189,188,189,200, \
 201,200,201,200,201,200,201,200,201,200,201,212,213,212,213,212, \
 213,212,213,212,213,212,213,224,225,212,213,224,225,224,225,224, \
 225,188,189,188,189,188,189,189,190,190,201,200,201,200,195,200, \
 201,200,201,200,201,200,201,200,201,200,201,212,213,212,213,212, \
 213,212,213,212,213,212,213,224,225,224,213,224,225,224,225,224, \
 225,224,225,225,223,224,225,236,237,236,237,236,237,236,237,237, \
 235,236,237,248,235,236,237,252,249,252,249,252,251,252,249,252, \
 251,252,249,268,251,252,267,268,267,268,267,268,267,268,265,268, \
 267,268,265,276,267,268,267,268,275,268,267,268,275,294,275,294, \
 293,294,293,294,293,294,293,294,300,300,299,300,300,300,300,294, \
 299,300,306,306,306,318,317,318,317,318,317,318,317,318,317,318, \
 318,324,317,318,323,324,317,318,324,324,330,330,330,324,330,330, \
 341,342,341,342,341,342,341,342,342,342,342,342,347,348,341,342, \
 341,342,342,342,341,342,347,348,365,366,365,366,365,366,366,366, \
 366,372,365,366,372,372,365,366,365,366,365,366,365,372,378,372, \
 372,372,378,378,377,378,378,390,390,378,389,390,372,396,389,390, \
 378,390,389,390,389,390,389,390,395,390,395,396,390,390,366,414, \
 366,366,366,414,372,366,366,414,372,414,366,414,372,414,378,414, \
 372,414,378,378,378,378,378,390,390,390,390,390,390,390,390,390, \
 390,390,390,390,396,390,390,396,396,396,372,396,396,414,378,414, \
 378,414,414,414,378,414,414,414,390,414,390,414,390,414,390,414, \
 390,414,396,414,396,414,396,414,396,414,402,438,414,438,414,413, \
 414,414,414,438,414,413,414,414,414,413,414,419,414,438,420,419, \
 426,425,426,425,426,425,426,437,438,437,438,437,438,437,438,437, \
 438,437,438,443,444,443,444,443,444,443,444,443,444,437,450,461, \
 438,461,462,461,438,461,462,462,462,461,462,467,468,467,468,467, \
 468,467,468,467,468,467,474,461,462,462,462,461,462,461,462,414, \
 462,461,468,467,468,520,468,413,414,503,414,414,414,503,414,503, \
 504,503,504,503,504,419,504,425,426,425,520,425,520,520,520,519, \
 520,519,520,437,438,437,438,438,438,437,438,443,444,443,444,443, \
 444,443,444,443,444,519,520,461,520,462,462,461,462,461,462,461, \
 462,467,468,467,468,467,468,467,468,473,468,467,468,473,468,551, \
 552,485,552,551,486,551,486,551,486,485,552,551,552,520,492,520, \
 504,503,504,503,504,503,504,503,504,503,504,503,504,503,504,519, \
 504,519,520,519,520,519,520,519,520,519,520,519,520,520,520,520, \
 520,527,528,527,528,527,536,552,536,535,536,535,536,552,536,551, \
 552,551,552,551,552,551,552,551,552,552,552,551,552,552,552,551, \
 552,551,552,551,552,567,568,567,568,567,568,567,568,567,568,567, \
 568,583,568,583,584,583,584,583,584,583,584,583,584,583,584,583, \
 584,584,584,583,592,591,592,592,592,591,592,591,592,599,592,599, \
 592,615,616,615,616,615,616,615,616,615,616,616,616,616,616,615, \
 616,615,624,623,624,623,624,623,624,623,624,623,624,631,624,631, \
 632,631,624,631,632,647,648,647,648,647,648,647,648,647,648,647 \

#define MPFR_DIVHIGH_TAB  \
 0,1,2,3,4,5,6,7,8,7,10,11,10,11,14,15, \
 14,15,14,15,12,15,14,13,14,14,15,16,16,16,18,20, \
 22,20,22,23,26,24,26,23,26,23,30,27,26,27,26,31, \
 30,31,30,28,34,31,34,32,30,35,34,31,34,36,38,35, \
 34,36,35,39,38,40,38,43,38,40,42,43,42,43,42,41, \
 42,48,46,48,46,48,46,48,50,48,47,48,48,52,54,52, \
 50,52,54,56,54,56,54,56,58,56,62,59,58,60,62,63, \
 62,64,62,64,66,64,62,64,62,72,66,71,66,64,74,68, \
 70,67,67,71,70,72,74,72,70,76,74,79,78,76,74,79, \
 74,83,78,84,76,79,82,80,78,79,79,84,82,80,82,87, \
 86,84,86,84,86,84,90,88,90,88,87,87,90,88,90,89, \
 90,92,91,104,92,92,94,93,94,96,98,96,96,104,98,104, \
 98,104,100,104,100,102,104,104,102,104,104,104,104,104,108,112, \
 112,110,128,112,128,128,128,112,128,128,128,128,128,128,128,128, \
 128,128,128,128,128,128,128,128,128,128,128,128,128,128,128,128, \
 128,128,128,128,128,128,128,128,128,128,128,128,128,128,129,129, \
 130,130,140,142,140,142,140,142,140,142,148,144,140,142,142,142, \
 140,142,140,142,140,144,141,144,142,144,144,144,160,144,145,145, \
 148,158,148,160,160,158,156,158,160,160,156,160,156,158,156,160, \
 160,160,160,182,156,160,164,182,182,182,182,184,182,184,182,182, \
 184,182,182,182,182,186,184,184,186,186,184,182,184,184,182,186, \
 182,185,182,185,184,185,186,185,182,185,182,185,184,184,184,182, \
 182,182,180,182,182,182,182,182,182,184,184,183,184,184,185,185, \
 186,186,187,187,188,198,196,198,196,208,196,198,196,208,196,208, \
 200,208,208,206,196,208,208,208,208,208,208,208,208,208,208,208, \
 208,208,208,208,208,208,216,208,208,208,208,208,216,208,224,224, \
 216,224,224,224,224,224,216,224,224,224,256,224,256,224,224,224, \
 256,256,256,254,256,254,256,254,256,254,256,256,256,256,256,256, \
 256,254,256,254,256,256,256,254,256,254,256,254,256,254,256,254, \
 256,256,256,254,256,256,256,254,256,256,256,256,256,256,256,254, \
 256,254,256,256,256,254,256,256,256,254,256,256,256,254,256,254, \
 256,254,280,256,256,254,280,282,282,282,280,256,280,256,282,257, \
 282,282,282,288,280,281,280,282,282,280,282,282,280,281,280,282, \
 282,282,280,282,281,282,282,288,282,282,282,288,282,288,288,288, \
 282,282,282,288,280,288,282,282,282,282,282,288,282,288,281,288, \
 282,282,283,288,284,288,288,288,288,288,288,288,288,288,289,289, \
 290,304,296,304,304,304,304,302,304,302,312,302,296,302,304,304, \
 312,304,312,302,304,370,312,304,372,304,312,304,304,370,372,370, \
 306,371,372,371,372,370,372,370,370,370,372,370,370,370,372,370, \
 371,370,372,371,372,370,372,370,370,370,372,370,370,370,370,370, \
 370,370,372,370,370,370,372,370,372,370,372,370,370,370,372,370, \
 370,370,370,370,372,370,372,370,372,370,372,370,370,372,372,370, \
 370,370,372,370,370,372,372,370,370,370,372,370,372,370,372,370, \
 372,370,368,370,370,370,372,372,369,370,372,370,372,370,371,370, \
 371,370,372,370,369,370,372,370,372,370,372,371,372,370,371,370, \
 372,370,370,371,372,370,372,370,372,370,370,372,372,370,372,372, \
 372,370,372,371,372,372,373,373,374,416,376,416,376,416,377,418, \
 378,416,384,416,384,416,416,416,392,416,400,416,392,416,416,416, \
 404,416,416,416,416,416,416,416,416,416,416,416,416,416,416,416, \
 416,416,416,416,418,418,416,416,416,420,416,416,418,416,418,416, \
 416,416,418,416,418,416,416,416,432,416,416,416,416,416,432,416, \
 416,416,416,418,416,416,416,418,416,420,418,416,416,416,464,417, \
 468,420,464,419,464,468,464,421,464,468,464,468,464,468,468,512, \
 512,508,512,468,512,468,464,510,468,510,512,512,512,512,512,512, \
 512,512,512,512,512,512,512,508,512,512,512,512,512,512,512,512, \
 512,512,512,512,512,512,512,512,512,508,512,508,512,512,512,512, \
 512,512,512,512,564,512,512,512,512,512,512,512,512,512,512,512, \
 564,512,512,512,560,512,560,512,560,564,564,564,560,512,560,564, \
 564,564,560,564,564,564,564,564,564,564,564,564,564,564,564,564, \
 564,562,564,564,564,564,564,512,564,512,512,564,564,564,564,508, \
 564,564,564,512,564,564,564,512,512,564,564,512,512,564,512,512, \
 564,564,512,512,564,510,512,512,512,512,512,512,564,564,512,512, \
 564,564,512,512,512,564,564,564,564,564,564,564,560,552,564,564, \
 562,564,564,564,564,564,564,564,564,564,564,564,564,564,564,562 \
  
#define MPFR_MUL_THRESHOLD 10 /* limbs */
#define MPFR_SQR_THRESHOLD 16 /* limbs */
#define MPFR_EXP_2_THRESHOLD 685 /* bits */
#define MPFR_EXP_THRESHOLD 4590 /* bits */
#define MPFR_SINCOS_THRESHOLD 15228 /* bits */
#define MPFR_AI_THRESHOLD1 -18514 /* threshold for negative input of mpfr_ai */
#define MPFR_AI_THRESHOLD2 2390
#define MPFR_AI_THRESHOLD3 33640
/* Tuneup completed successfully, took 7301 seconds */
