#ifndef ARK_128_H
#define ARK_128_H

byte ARK_BYTES[NB_CONSTANTS][32] = {
    {164, 55,  183, 17,  5,  76, 144, 97, 239, 94, 139, 198, 33,  64, 223, 55,
     145, 203, 22,  114, 56, 3,  241, 33, 83,  15, 7,   215, 251, 43, 44,  47},
    {88,  176, 53,  15,  125, 27,  49,  251, 58,  97, 59,
     18,  59,  182, 69,  54,  209, 234, 189, 43,  43, 210,
     205, 108, 116, 103, 93,  197, 197, 47,  236, 4},
    {182, 176, 236, 116, 95,  190, 113, 103, 43, 82, 243,
     98,  251, 109, 228, 99,  113, 58,  34,  37, 65, 146,
     155, 250, 178, 78,  153, 76,  252, 76,  98, 60},
    {17, 149, 5, 91,  196, 109, 147, 90,  122, 146, 52,  42, 193, 214, 236, 204,
     41, 30,  3, 217, 163, 145, 155, 221, 19,  24,  106, 98, 74,  116, 118, 52},
    {22,  207, 99,  122, 189, 96,  62,  3, 26, 234, 52,  223, 63, 140, 76,  78,
     137, 120, 192, 157, 220, 178, 211, 9, 24, 30,  159, 142, 27, 60,  142, 62},
    {124, 144, 253, 158, 27,  187, 225, 75,  138, 217, 115,
     188, 133, 196, 249, 42,  19,  186, 43,  54,  124, 67,
     122, 36,  32,  62,  149, 248, 26,  244, 57,  20},
    {122, 108, 172, 164, 44,  61,  172, 147, 33,  102, 248,
     40,  49,  235, 87,  175, 49,  117, 226, 30,  159, 79,
     164, 254, 233, 229, 244, 214, 35,  225, 132, 33},
    {22,  148, 114, 22,  200, 164, 237, 163, 150, 179, 201,
     147, 146, 91,  224, 248, 225, 219, 174, 104, 245, 52,
     192, 140, 125, 200, 214, 9,   185, 25,  16,  51},
    {78,  162, 79,  168, 201, 38,  63,  165, 69,  157, 119,
     107, 88,  162, 235, 209, 126, 173, 86,  134, 255, 156,
     236, 198, 160, 163, 63,  222, 22,  139, 7,   0},
    {30,  96, 57,  111, 146, 178, 193, 91,  48, 209, 127,
     207, 35, 36,  120, 133, 122, 78,  159, 79, 2,   255,
     68,  29, 173, 156, 83,  23,  33,  116, 79, 57},
    {121, 215, 67, 77, 253, 118, 213, 142, 0,  195, 165, 11, 14,  227, 17, 3,
     224, 37,  39, 63, 41,  223, 101, 110, 26, 38,  126, 97, 125, 35,  30, 38},
    {104, 54,  138, 244, 1,   180, 19,  69, 139, 210, 117,
     64,  123, 47,  125, 133, 25,  131, 68, 124, 111, 203,
     220, 51,  210, 253, 174, 179, 137, 19, 45,  37},
    {36,  254, 165, 136, 231, 249, 157, 246, 58, 146, 81,
     36,  57,  53,  214, 56,  61,  146, 80,  3,  67,  126,
     191, 103, 223, 112, 219, 163, 221, 169, 92, 2},
    {147, 31,  80, 35,  114, 18, 140, 193, 182, 26,  66, 149, 92,  47, 21, 141,
     177, 240, 83, 215, 237, 23, 229, 23,  182, 213, 10, 20,  206, 42, 44, 29},
    {44,  172, 80,  63,  64,  200, 104, 103, 240, 74,  46,
     244, 33,  235, 121, 64,  67,  132, 166, 134, 189, 122,
     76,  101, 191, 125, 183, 247, 193, 149, 164, 11},
    {40,  158, 239, 46,  112, 96, 175, 216, 225, 235, 195,
     239, 82,  87,  241, 5,   50, 39,  146, 65,  102, 248,
     178, 91,  186, 76,  50,  80, 73,  228, 188, 44},
    {20,  157, 174, 174, 34,  251, 26, 103, 28,  195, 113,
     138, 42,  48,  94,  254, 51,  58, 109, 177, 45,  36,
     228, 149, 109, 66,  191, 58,  13, 126, 118, 36},
    {49,  48,  42,  222, 112, 134, 146, 13,  181, 170, 157,
     186, 224, 113, 169, 184, 129, 234, 58,  200, 252, 83,
     109, 20,  20,  75,  14,  230, 240, 110, 205, 26},
    {235, 161, 166, 77,  17,  134, 28,  204, 237, 126, 46,
     167, 168, 119, 126, 161, 125, 98,  45,  103, 85,  32,
     148, 25,  49,  10,  189, 0,   212, 148, 15,  52},
    {192, 34,  30, 6,  38,  35, 30, 213, 77,  201, 9,  146, 162, 141, 44, 71,
     130, 107, 12, 62, 227, 17, 7,  214, 248, 210, 61, 202, 60,  55,  39, 3},
    {80,  19, 22,  240, 252, 47,  219, 95, 128, 32, 92,  12, 25,  24, 238, 57,
     233, 97, 144, 4,   174, 214, 194, 23, 15,  72, 157, 44, 216, 65, 16,  29},
    {116, 165, 181, 106, 67,  49,  188, 81,  31,  145, 61,
     29,  80,  53,  209, 183, 248, 89,  16,  97,  115, 140,
     94,  137, 87,  82,  139, 150, 15,  117, 228, 13},
    {148, 87,  26,  238, 131, 67,  65,  178, 63,  125, 235,
     208, 12,  75,  69,  17,  186, 204, 22,  201, 153, 154,
     252, 199, 187, 150, 97,  120, 163, 144, 146, 53},
    {54,  128, 46,  236, 92,  11,  194, 24,  100, 3,  239,
     122, 182, 96,  68,  221, 77,  9,   243, 83,  20, 14,
     88,  186, 171, 203, 23,  244, 221, 205, 255, 40},
    {0,   106, 171, 250, 106, 44,  45,  50,  137, 60,  109,
     36,  116, 1,   1,   134, 132, 48,  193, 220, 228, 164,
     153, 222, 245, 211, 142, 104, 223, 195, 118, 14},
    {199, 87,  127, 213, 18,  41,  146, 120, 91, 124, 233,
     128, 110, 172, 66,  124, 239, 194, 25,  58, 107, 138,
     225, 189, 122, 54,  116, 249, 106, 167, 44, 23},
    {95,  25,  146, 198, 77,  250, 100, 155, 63,  253, 0,
     123, 64,  168, 81,  137, 170, 167, 241, 104, 225, 1,
     38,  102, 33,  53,  84,  177, 104, 70,  237, 18},
    {152, 211, 56,  229, 41,  168, 242, 144, 239, 50, 130,
     207, 123, 79,  97,  47,  9,   213, 84,  131, 31, 33,
     215, 111, 165, 206, 148, 152, 106, 160, 46,  12},
    {34, 150, 176, 155, 16,  234, 127, 124, 81,  148, 84,
     48, 161, 142, 93,  181, 227, 138, 3,   155, 104, 89,
     71, 229, 100, 107, 19,  24,  3,   166, 174, 15},
    {39,  107, 230, 161, 134, 254, 123, 40,  113, 163, 120,
     140, 9,   144, 123, 30,  79,  65,  154, 221, 244, 235,
     62,  185, 17,  199, 212, 92,  70,  235, 234, 27},
    {227, 164, 66,  205, 118, 221, 26,  168, 151, 221, 55,
     107, 221, 123, 111, 59,  70,  77,  17,  232, 237, 6,
     43,  44,  26,  91,  202, 188, 185, 148, 28,  53},
    {146, 77,  90,  167, 186, 78,  252, 220, 148, 130, 50,
     146, 43,  214, 110, 187, 89,  164, 89,  242, 220, 132,
     143, 230, 79,  158, 116, 193, 250, 56,  24,  42},
    {251, 112, 246, 226, 250, 11,  35, 205, 152, 234, 102,
     42,  240, 140, 65,  147, 184, 42, 156, 234, 6,   140,
     248, 164, 158, 214, 225, 215, 44, 92,  135, 63},
    {161, 7,   159, 201, 183, 55,  226, 108, 152, 199, 253,
     135, 178, 53,  221, 13,  134, 68,  252, 163, 17,  232,
     95,  20,  134, 155, 82,  18,  52,  74,  34,  49},
    {78, 49,  217, 159, 178, 109, 91, 97,  92, 197, 57, 78, 75,  226, 110, 13,
     62, 226, 186, 191, 25,  17,  42, 180, 35, 230, 58, 99, 185, 178, 86,  21},
    {194, 242, 153, 237, 217, 92,  34,  117, 25,  85, 147,
     62,  176, 58,  255, 106, 52,  251, 229, 113, 28, 202,
     232, 28,  77,  204, 76,  245, 216, 172, 155, 57},
    {227, 128, 175, 187, 123, 153, 240, 242, 186, 14,  210,
     212, 58,  62,  196, 49,  209, 74,  68,  193, 171, 125,
     45,  160, 30,  50,  92,  138, 54,  119, 152, 56},
    {6,   181, 115, 10,  165, 102, 188, 174, 204, 116, 26,
     54,  57,  250, 120, 111, 127, 6,   50,  65,  154, 126,
     209, 198, 187, 145, 41,  116, 96,  38,  243, 14},
    {148, 156, 19,  193, 178, 173, 151, 109, 232, 203, 102,
     18,  240, 153, 122, 251, 33,  146, 92,  70,  90,  209,
     179, 110, 226, 36,  168, 221, 95,  26,  73,  30},
    {167, 10,  127, 254, 250, 96,  125, 160, 232, 151, 19,
     243, 98,  15,  173, 198, 72,  235, 52,  204, 114, 171,
     231, 106, 75,  99,  242, 111, 255, 214, 228, 45},
    {102, 39,  165, 219, 252, 221, 219, 6,   53,  201, 210,
     120, 172, 158, 49,  191, 91,  42,  221, 56,  97,  181,
     165, 242, 167, 240, 184, 5,   128, 163, 131, 18},
    {182, 97,  240, 152, 179, 183, 35,  223, 172, 198, 37,
     0,   150, 26,  201, 179, 80,  128, 29,  104, 113, 202,
     146, 224, 75,  170, 32,  80,  234, 239, 226, 25},
    {93, 136, 236, 143, 36,  72,  127, 11,  3,   206, 148,
     74, 161, 104, 9,   97,  107, 27,  193, 81,  175, 25,
     87, 245, 8,   81,  227, 236, 103, 181, 127, 40},
    {131, 187, 7,  245, 85, 3,   128, 89, 45, 67, 116, 233, 225, 37,  127, 88,
     42,  211, 16, 63,  72, 212, 2,   82, 13, 80, 93,  110, 88,  234, 97,  39},
    {14,  16,  255, 29,  179, 156, 82,  109, 196, 2,   174,
     121, 57,  121, 93,  248, 64,  247, 134, 135, 189, 177,
     24,  175, 94,  179, 77,  247, 164, 215, 119, 47},
    {194, 29,  191, 94, 36, 104, 75, 211, 51,  124, 93,  79,  50, 235, 0,   50,
     241, 200, 157, 11, 18, 94,  74, 13,  105, 122, 110, 126, 45, 134, 144, 3},
    {82,  90,  92,  86, 116, 65,  46,  53,  182, 189, 11,
     215, 165, 110, 25, 213, 127, 201, 156, 26,  193, 81,
     42,  140, 128, 92, 180, 164, 29,  178, 213, 20},
    {85,  231, 209, 215, 201, 102, 133, 63,  127, 115, 200,
     31,  227, 150, 183, 172, 161, 3,   132, 23,  42,  17,
     136, 208, 251, 144, 93,  236, 120, 173, 116, 41},
    {60,  238, 52, 83,  120, 59,  181, 255, 104, 126, 187,
     163, 199, 19, 180, 40,  122, 75,  176, 240, 144, 194,
     161, 163, 31, 204, 173, 82,  112, 143, 181, 54},
    {194, 57,  115, 169, 200, 156, 21,  151, 174, 149, 253,
     177, 62,  153, 196, 25,  57,  54,  100, 63,  9,   112,
     184, 174, 161, 96,  108, 253, 158, 10,  251, 46},
    {255, 193, 152, 92,  128, 30,  182, 41, 34, 176, 75, 170, 247, 143, 82, 209,
     2,   161, 162, 114, 60,  162, 25,  63, 12, 199, 73, 242, 125, 174, 4,  31},
    {176, 12,  142, 77,  92, 49, 99,  19, 138, 125, 97,  140, 59,  13, 253, 145,
     137, 133, 25,  248, 84, 46, 100, 89, 150, 41,  140, 143, 254, 68, 141, 39},
    {6,   36,  89, 193, 193, 77,  52, 227, 162, 194, 239,
     140, 127, 91, 237, 109, 106, 15, 27,  174, 20,  87,
     180, 73,  28, 6,   104, 33,  2,  189, 43,  26},
    {156, 159, 85,  163, 71,  249, 235, 19,  152, 99,  54,
     34,  237, 180, 60,  249, 147, 135, 104, 142, 222, 145,
     138, 223, 126, 169, 147, 49,  247, 226, 13,  15},
    {146, 143, 67,  234, 104, 239, 114, 0,   223, 10,  179,
     208, 153, 214, 108, 183, 153, 147, 160, 50,  210, 195,
     146, 80,  197, 106, 241, 72,  194, 125, 196, 58},
    {84,  160, 52,  62,  101, 121, 199, 179, 60,  4,   34,
     162, 71,  35,  44,  0,   144, 47,  129, 89,  103, 201,
     160, 244, 149, 252, 245, 174, 125, 146, 127, 31},
    {133, 11,  149, 204, 225, 121, 177, 192, 0,   252, 61,
     233, 92,  49,  92,  148, 124, 203, 173, 177, 2,   205,
     227, 230, 24,  38,  215, 134, 175, 79,  11,  37},
    {14,  222, 26,  152, 24,  1,   210, 101, 13,  117, 182,
     250, 196, 188, 136, 114, 63,  21,  18,  223, 103, 137,
     82,  98,  75,  96,  226, 222, 70,  70,  198, 7},
    {29,  255, 173, 219, 150, 175, 147, 238, 239, 50, 113,
     221, 161, 140, 92,  160, 187, 139, 21,  161, 60, 20,
     250, 120, 0,   247, 14,  76,  35,  189, 203, 36},
    {27,  82,  250, 247, 108, 78,  187, 84,  204, 142, 52,
     182, 57,  45,  54,  197, 236, 173, 183, 8,   204, 243,
     187, 253, 39,  154, 51,  239, 148, 223, 142, 32},
    {53, 218, 70,  42,  216, 127, 108, 249, 6,   24, 108,
     61, 150, 17,  95,  244, 219, 20,  77,  44,  61, 157,
     88, 10,  210, 243, 241, 64,  63,  167, 162, 62},
    {122, 44,  117, 162, 62,  167, 115, 89,  225, 155, 27,
     249, 111, 178, 156, 231, 88,  31,  197, 244, 87,  184,
     27,  119, 160, 211, 117, 112, 86,  184, 204, 54},
    {140, 64,  0,   112, 209, 129, 134, 252, 50,  250, 124,
     97,  222, 149, 220, 58,  71,  49,  248, 231, 28,  249,
     205, 169, 186, 145, 80,  154, 100, 75,  101, 8},
    {234, 24,  127, 80,  237, 139, 137, 169, 125, 238, 182,
     197, 101, 200, 250, 165, 14,  142, 42,  229, 142, 48,
     139, 242, 0,   133, 251, 203, 107, 167, 88,  43},
    {46,  154, 213, 37, 98, 137, 21, 125, 115, 142, 190, 51, 37, 143, 237, 226,
     153, 182, 204, 5,  97, 182, 20, 70,  37,  43,  78,  40, 74, 211, 1,   16},
    {156, 188, 84,  99, 204, 134, 66,  156, 28, 101, 177,
     147, 206, 222, 97, 42,  12,  167, 175, 48, 210, 99,
     30,  47,  251, 10, 53,  181, 176, 90,  55, 19},
    {203, 170, 240, 160, 34,  178, 34,  86,  218, 171, 22,
     82,  203, 156, 91,  172, 2,   71,  198, 4,   26,  73,
     114, 236, 186, 255, 242, 111, 212, 105, 113, 42},
    {224, 26, 16, 98, 139, 206, 234, 85,  252, 230, 69,  64,  23, 20,  210, 81,
     246, 82, 24, 76, 114, 148, 96,  152, 41,  107, 253, 237, 91, 181, 62,  3},
    {209, 250, 104, 149, 135, 83,  192, 94,  59,  197, 209,
     213, 116, 127, 92,  121, 113, 28,  117, 238, 38,  18,
     227, 25,  64,  15,  38,  32,  250, 31,  202, 16},
    {84,  104, 189, 48,  4,   152, 240, 241, 157, 72,  71,
     207, 130, 80,  93,  73,  227, 131, 188, 43,  196, 114,
     97,  228, 253, 240, 245, 242, 120, 218, 193, 6},
    {63,  197, 33,  90,  171, 75,  74, 247, 92,  151, 163,
     9,   181, 131, 78,  59,  36,  71, 36,  84,  156, 153,
     216, 253, 183, 162, 209, 133, 0,  191, 233, 26},
    {60, 56, 197, 238, 113, 235, 219, 203, 193, 145, 10,
     1,  6,  228, 139, 211, 129, 46,  0,   30,  99,  44,
     84, 7,  45,  155, 112, 204, 224, 153, 133, 54},
    {50, 79,  88, 233, 56, 129, 120, 34, 66, 36, 151, 147, 103, 50,  143, 137,
     73, 203, 93, 54,  12, 214, 2,   46, 54, 74, 77,  204, 41,  148, 231, 2},
    {77,  209, 73,  29, 214, 43,  168, 160, 103, 155, 217,
     135, 235, 21,  67, 74,  219, 32,  194, 217, 138, 153,
     211, 0,   128, 27, 117, 210, 233, 65,  197, 24},
    {142, 103, 0,   150, 87, 191, 201, 1,   43,  41,  217,
     249, 181, 67,  116, 68, 134, 165, 137, 74,  181, 159,
     155, 180, 227, 226, 19, 227, 213, 7,   117, 25},
    {127, 192, 189, 221, 95,  79,  252, 191, 171, 145, 190,
     65,  112, 15,  71,  111, 146, 0,   231, 37,  78,  22,
     150, 102, 136, 49,  137, 238, 146, 189, 177, 38},
    {190, 253, 229, 167, 113, 173, 140, 77,  114, 119, 69,
     58,  162, 208, 129, 38,  9,   237, 234, 77,  244, 248,
     216, 152, 70,  238, 100, 245, 21,  182, 253, 14},
    {28,  218, 113, 199, 95,  74,  20,  104, 67,  141, 250,
     241, 204, 43,  159, 172, 72,  74,  89,  50,  190, 189,
     113, 122, 136, 50,  248, 197, 221, 93,  106, 38},
    {48,  131, 22,  246, 170, 156, 42,  179, 86,  79, 52,
     10,  66,  251, 117, 181, 41,  127, 145, 240, 45, 142,
     125, 225, 213, 66,  219, 186, 227, 86,  243, 52},
    {175, 188, 94,  244, 99,  58,  139, 37,  90,  13,  13,
     188, 21,  240, 56,  241, 72,  76,  240, 179, 197, 22,
     215, 221, 204, 102, 47,  136, 111, 173, 169, 47},
    {153, 205, 13,  137, 53,  140, 171, 178, 68,  190, 149,
     172, 138, 149, 80,  115, 77,  237, 155, 147, 83,  252,
     244, 132, 39,  210, 205, 134, 51,  99,  11,  33},
    {179, 158, 173, 246, 98,  109, 165, 214, 125, 67, 145,
     207, 214, 249, 55,  9,   97,  175, 175, 57,  22, 171,
     128, 78,  14,  176, 101, 145, 6,   15,  220, 52},
    {140, 119, 248, 92, 69,  176, 38,  51, 115, 220, 199,
     17,  244, 166, 63, 145, 199, 216, 19, 224, 74,  97,
     208, 130, 7,   29, 134, 176, 176, 76, 155, 37},
    {70,  87,  57,  173, 14,  119, 208, 167, 41,  27,  212,
     137, 244, 186, 90,  49,  98,  189, 120, 62,  139, 120,
     96,  198, 61,  7,   217, 197, 182, 216, 136, 15},
    {198, 31, 76,  80, 57,  212, 132, 32, 199, 131, 45,  244, 90, 228, 130, 50,
     133, 55, 147, 93, 219, 243, 174, 91, 159, 17,  115, 203, 30, 209, 171, 48},
    {111, 68,  246, 198, 57,  136, 161, 99,  51,  204, 167,
     187, 10,  152, 252, 94,  4,   236, 186, 213, 9,   175,
     2,   243, 156, 82,  100, 82,  50,  206, 82,  49},
    {53,  14,  39, 60,  97,  193, 247, 52,  108, 255, 89,
     152, 197, 79, 149, 226, 237, 81,  196, 221, 142, 151,
     148, 190, 42, 85,  78,  85,  70,  49,  189, 0},
    {254, 160, 212, 216, 33,  73,  242, 183, 73,  193, 130,
     226, 250, 58,  169, 21,  40,  146, 80,  238, 150, 234,
     28,  238, 50,  26,  145, 239, 200, 244, 30,  44},
    {179, 18, 173, 199, 97,  110, 150, 50,  205, 235, 123,
     109, 68, 188, 216, 189, 91,  51,  181, 222, 1,   26,
     114, 41, 95,  175, 118, 88,  219, 154, 134, 35},
    {89,  85,  62,  168, 145, 73, 234, 226, 157, 212, 190,
     198, 100, 203, 114, 243, 53, 203, 40,  193, 26,  246,
     205, 172, 124, 33,  161, 28, 38,  142, 248, 42},
    {138, 176, 76,  145, 52,  196, 201, 128, 241, 151, 240,
     247, 168, 206, 13,  164, 246, 170, 61,  11,  241, 236,
     87,  162, 136, 165, 61,  192, 214, 118, 93,  27},
    {133, 98,  59,  2,   143, 142, 208, 55,  10,  45, 32,
     118, 196, 159, 89,  254, 58,  124, 2,   47,  61, 189,
     198, 207, 15,  153, 240, 42,  174, 218, 118, 28},
    {127, 121, 40,  131, 44,  169, 94,  184, 173, 24,  82,
     242, 97,  183, 229, 89,  240, 217, 9,   202, 119, 53,
     187, 59,  61,  239, 226, 166, 246, 147, 88,  47},
    {35,  76, 9,   115, 159, 2,  51,  24,  48, 114, 100, 96, 88,  137, 39, 51,
     112, 83, 255, 121, 140, 72, 148, 232, 22, 65,  135, 22, 220, 163, 17, 26},
    {14,  0,  194, 129, 189, 166, 201, 247, 119, 71, 44, 41, 117, 107, 224, 205,
     184, 45, 172, 30,  38,  73,  145, 237, 70,  90, 85, 76, 168, 169, 178, 34},
    {170, 187, 232, 165, 165, 140, 57,  147, 91,  200, 119,
     141, 52,  152, 111, 111, 46,  226, 78,  94,  143, 77,
     32,  114, 193, 118, 40,  73,  238, 1,   114, 31},
    {97,  216, 253, 246, 12,  197, 54,  246, 220, 66, 65,
     143, 49,  171, 30,  33,  248, 200, 16,  25,  49, 238,
     18,  37,  31,  105, 220, 251, 198, 237, 226, 8},
    {22,  102, 224, 97,  247, 34,  223, 3,   7,   35, 50, 153, 27,  24, 10, 223,
     164, 198, 89,  131, 87,  198, 80,  178, 171, 56, 58, 197, 193, 38, 55, 23},
    {86, 132, 135, 227, 81, 3,   88, 137, 137, 84,  226, 193, 16, 132, 154, 114,
     53, 20,  41,  25,  48, 211, 30, 125, 226, 222, 124, 73,  16, 145, 254, 47},
    {120, 68,  204, 209, 30,  0,   225, 141, 127, 143, 115,
     90,  214, 91,  253, 228, 217, 121, 98,  106, 184, 95,
     209, 218, 65,  141, 20,  55,  144, 249, 241, 2},
    {199, 115, 142, 64,  19,  244, 179, 134, 218, 21,  235,
     196, 109, 18,  208, 151, 168, 240, 230, 178, 207, 246,
     74,  240, 14,  152, 162, 77,  191, 77,  44,  10},
    {67,  193, 43, 31,  198, 240, 60,  54,  141, 207, 207,
     237, 129, 60, 250, 20,  58,  226, 59,  217, 123, 89,
     19,  121, 36, 185, 141, 58,  214, 185, 112, 41},
    {193, 101, 31,  87,  24,  209, 30,  119, 26,  144, 16,
     82,  149, 139, 154, 222, 105, 135, 115, 170, 128, 191,
     162, 105, 141, 67,  238, 135, 147, 229, 0,   4},
    {101, 102, 239, 158, 57,  59,  97,  42,  17,  254, 198,
     142, 172, 177, 214, 218, 66,  190, 144, 136, 147, 75,
     97,  188, 152, 163, 16,  249, 136, 106, 190, 37},
    {121, 146, 200, 95,  106, 154, 114, 107, 58,  197, 77,
     51,  139, 202, 116, 173, 251, 65,  23,  252, 19,  209,
     153, 72,  52,  217, 31,  16,  223, 75,  234, 3},
    {79,  28,  111, 209, 52, 137, 65, 65,  252, 87,  95, 25,  3,   115, 7,  211,
     223, 194, 161, 42,  40, 143, 33, 155, 160, 254, 46, 179, 217, 250, 71, 16},
    {172, 153, 14,  143, 192, 116, 33,  52,  85,  27, 222,
     162, 194, 164, 106, 204, 28,  38,  222, 125, 63, 207,
     255, 246, 250, 240, 145, 39,  232, 101, 135, 10},
    {70,  61,  78,  87,  57,  143, 137, 245, 29,  249, 125,
     140, 224, 221, 161, 198, 196, 27,  160, 202, 177, 120,
     253, 67,  237, 220, 235, 160, 37,  250, 38,  35},
    {2,   74,  122, 163, 195, 51,  236, 157, 66,  127, 14,
     143, 233, 105, 196, 99,  104, 194, 204, 241, 142, 141,
     171, 50,  149, 49,  96,  105, 89,  156, 26,  27},
    {244, 220, 214, 21,  94, 174, 33, 12,  161, 254, 15,
     85,  246, 104, 192, 54, 9,   72, 10,  207, 154, 95,
     170, 158, 96,  5,   16, 177, 32, 141, 41,  59},
    {243, 37,  112, 97,  187, 112, 200, 167, 94,  0,   40,
     65,  146, 77,  202, 170, 148, 111, 242, 213, 232, 66,
     138, 72,  238, 117, 61,  63,  57,  106, 119, 21},
    {255, 139, 155, 94,  132, 151, 209, 39,  14,  34,  18,
     106, 90,  207, 206, 112, 223, 206, 115, 209, 226, 242,
     12,  172, 138, 126, 35,  77,  171, 141, 46,  6},
    {183, 137, 164, 16,  199, 54,  32, 41,  119, 34,  228,
     245, 232, 136, 133, 246, 226, 69, 41,  2,   103, 199,
     12,  81,  79,  168, 205, 52,  27, 157, 113, 0},
    {65, 125, 70,  114, 182, 219, 189, 52, 196, 80, 113, 203, 163, 89, 158, 241,
     58, 201, 150, 228, 195, 146, 23,  47, 22,  0,  126, 250, 97,  23, 144, 15},
    {196, 224, 127, 72,  99,  67, 38,  96,  50,  143, 197,
     96,  151, 92,  112, 136, 79, 213, 195, 167, 20,  154,
     118, 63,  244, 34,  204, 43, 208, 155, 243, 24},
    {96, 46, 243, 190, 213, 96, 32, 8,   187, 169, 105, 13, 40,  4, 93,  194,
     31, 40, 47,  60,  31,  52, 96, 238, 95,  18,  127, 79, 130, 8, 118, 22},
    {226, 61,  76,  69,  118, 168, 160, 139, 22,  231, 136,
     171, 234, 144, 191, 165, 134, 197, 241, 64,  130, 168,
     234, 216, 207, 59,  126, 175, 88,  51,  157, 47},
    {59, 158, 207, 235, 63, 106, 157, 7,  24,  227, 6,  199, 150, 96, 220, 106,
     19, 197, 169, 43,  37, 159, 166, 24, 174, 134, 22, 126, 163, 69, 172, 50},
    {50,  222, 215, 34,  195, 208, 204, 85, 51,  157, 98, 46, 33,  83, 174, 235,
     216, 27,  250, 161, 128, 203, 61,  17, 126, 157, 40, 63, 174, 81, 137, 47},
    {254, 101, 10,  4,   71,  214, 109, 239, 64,  252, 78,
     90,  35,  242, 115, 134, 124, 55,  226, 154, 248, 229,
     220, 146, 95,  177, 144, 65,  170, 192, 169, 51},
    {192, 143, 246, 142, 210, 20, 232, 152, 93,  173, 67,
     127, 240, 18,  103, 79,  85, 14,  238, 231, 110, 221,
     120, 83,  67,  50,  215, 69, 187, 123, 220, 22},
    {247, 159, 107, 81,  242, 22,  176, 6,   97,  109, 11,
     166, 211, 148, 182, 20,  82,  147, 75,  220, 31,  120,
     220, 162, 243, 191, 90,  161, 208, 180, 89,  40},
    {177, 76,  56, 248, 76, 127, 194, 50, 236, 71, 220, 163, 219, 198, 7,  150,
     23,  178, 87, 232, 83, 18,  118, 6,  68,  13, 172, 177, 52,  117, 30, 41},
    {103, 191, 40,  244, 174, 145, 206, 155, 20,  161, 169,
     6,   226, 223, 202, 175, 19,  6,   111, 86,  249, 50,
     206, 35,  44,  191, 55,  57,  97,  176, 202, 37},
    {29,  101, 57,  207, 55, 154, 17, 147, 33, 16,  82, 245, 254, 5,  171, 157,
     123, 28,  180, 103, 61, 27,  51, 243, 89, 189, 37, 162, 75,  93, 215, 5},
    {178, 253, 255, 200, 197, 128, 66,  108, 15,  137, 81,
     159, 228, 13,  27,  221, 96,  178, 28,  92,  146, 59,
     253, 151, 64,  235, 234, 42,  73,  172, 241, 8},
    {92,  74,  172, 187, 87,  15,  66,  109, 40,  234, 129,
     133, 73,  185, 15,  251, 81,  190, 95,  224, 189, 133,
     126, 121, 36,  34,  22,  179, 155, 241, 48,  25},
    {173, 125, 24,  80,  28,  146, 1,   191, 84,  207, 211,
     214, 183, 77,  107, 227, 219, 200, 26,  118, 223, 171,
     207, 170, 133, 3,   186, 197, 249, 107, 151, 48},
    {93, 124, 149, 242, 36,  218, 80,  199, 164, 97,  236,
     81, 134, 234, 236, 223, 119, 230, 188, 167, 250, 205,
     11, 61,  94,  103, 158, 136, 60,  94,  86,  36},
    {77, 168, 180, 53,  187, 136, 6,  76,  65,  111, 62, 49, 209, 99, 187, 14,
     91, 248, 110, 204, 88,  53,  79, 233, 164, 26,  77, 99, 214, 99, 73,  27},
    {28, 96,  199, 254, 225, 85,  184, 216, 254, 25, 80,
     39, 197, 129, 42,  16,  150, 135, 232, 29,  40, 60,
     27, 134, 225, 239, 235, 38,  114, 49,  198, 17},
    {53, 43, 129, 122, 170, 132, 63, 224, 47,  42,  245, 17, 65,  73,  212, 253,
     62, 94, 247, 36,  172, 183, 41, 215, 136, 128, 18,  43, 167, 202, 228, 49},
    {9,   165, 17,  2,   250, 0,   150, 247, 1,   109, 26,
     214, 241, 196, 120, 157, 197, 83,  246, 200, 52,  5,
     61,  93,  89,  216, 117, 220, 201, 194, 240, 40},
    {61,  164, 161, 155, 255, 99, 111, 156, 23, 17,  47,
     114, 109, 214, 137, 197, 56, 212, 30,  21, 114, 186,
     147, 23,  115, 55,  5,   86, 230, 217, 46, 45},
    {160, 71,  236, 45,  152, 133, 152, 219, 54,  74, 11,
     233, 71,  144, 141, 46,  236, 99,  152, 193, 8,  170,
     57,  247, 126, 197, 2,   85,  45,  209, 130, 45},
    {22,  112, 96,  53,  18,  76,  224, 55,  76,  237, 8,
     4,   254, 230, 149, 22,  224, 9,   226, 217, 80,  53,
     123, 163, 195, 248, 248, 34,  49,  102, 202, 55},
    {98,  66,  6,   154, 145, 153, 34, 117, 232, 144, 221,
     143, 249, 241, 65,  158, 78,  89, 170, 72,  244, 17,
     170, 253, 243, 146, 126, 146, 19, 166, 174, 35},
    {148, 148, 202, 221, 167, 2,  95, 239, 129, 234, 183,
     87,  84,  249, 230, 36,  18, 78, 93,  52,  205, 175,
     168, 16,  194, 246, 3,   68, 6,  45,  163, 53},
    {219, 9,   116, 83, 63, 64,  28,  58, 150, 80,  30, 1,   152, 146, 216, 77,
     82,  188, 92,  23, 22, 230, 111, 6,  130, 251, 13, 201, 114, 55,  221, 16},
    {117, 224, 172, 176, 174, 216, 17,  62,  163, 230, 45,
     219, 65,  195, 119, 244, 229, 222, 165, 2,   41,  197,
     40,  59,  117, 121, 99,  48,  199, 143, 136, 22},
    {99,  50, 49,  199, 80,  209, 97,  245, 104, 163, 50,
     0,   5,  151, 197, 110, 239, 102, 79,  168, 239, 151,
     133, 25, 198, 183, 181, 106, 211, 135, 116, 21},
    {33, 157, 99,  238, 118, 196, 39,  98,  97, 203, 155, 254, 85, 80,  98,  9,
     69, 199, 245, 3,   137, 61,  162, 168, 59, 146, 23,  91,  89, 104, 219, 9},
    {191, 49,  1,  116, 187, 176, 107, 79,  4,   113, 254,
     145, 165, 93, 120, 109, 89,  140, 112, 24,  19,  68,
     21,  43,  57, 118, 241, 48,  254, 147, 128, 38},
    {99,  57,  149, 118, 211, 28,  83,  95,  37,  174, 110,
     246, 188, 194, 35,  193, 97,  193, 238, 120, 197, 205,
     123, 82,  53,  206, 74,  139, 178, 190, 205, 43},
    {224, 87,  116, 26,  250, 146, 97,  222, 228, 180, 91,
     187, 148, 150, 227, 251, 186, 183, 8,   0,   139, 175,
     209, 18,  135, 109, 202, 173, 11,  126, 251, 21},
    {77,  163, 198, 78, 66,  191, 114, 185, 217, 97,  117,
     99,  185, 155, 41, 148, 208, 99,  36,  102, 127, 225,
     134, 121, 201, 66, 13,  171, 145, 91,  188, 23},
    {50,  51,  94,  245, 77,  176, 6,   185, 27,  162, 115,
     175, 44,  239, 191, 197, 154, 118, 9,   149, 63,  147,
     173, 251, 25,  18,  221, 45,  117, 59,  186, 40},
    {166, 166, 160, 43,  53,  165, 243, 194, 199, 75,  67,
     97,  118, 60,  56,  119, 212, 76,  38,  108, 175, 157,
     158, 58,  201, 151, 7,   218, 229, 27,  194, 8},
    {29,  250, 91, 221, 147, 0,   15,  242, 145, 3, 152,
     34,  245, 18, 15,  32,  30,  215, 243, 176, 7, 169,
     161, 93,  27, 114, 120, 209, 236, 249, 104, 19},
    {116, 8,   23, 152, 133, 140, 51,  170, 208, 103, 39,
     35,  174, 78, 18,  166, 251, 106, 40,  47,  64,  109,
     129, 17,  94, 13,  198, 8,   40,  135, 100, 57},
    {139, 124, 77, 76,  234, 168, 25,  71,  90,  139, 112,
     244, 127, 94, 232, 175, 171, 158, 57,  228, 31,  165,
     148, 67,  5,  180, 178, 76,  6,   216, 128, 25},
    {146, 131, 161, 187, 233, 206, 218, 164, 197, 29,  175,
     7,   74,  9,   45,  233, 99,  119, 119, 234, 254, 104,
     132, 224, 166, 115, 204, 253, 109, 20,  211, 23},
    {159, 5,  31,  170, 174, 154, 146, 81,  96, 70, 98, 75, 175, 95,  186, 199,
     22,  16, 155, 141, 118, 169, 81,  127, 80, 56, 2,  92, 121, 210, 109, 9},
    {11,  77,  110, 75,  83,  118, 95,  144, 40, 135, 171,
     95,  117, 47,  218, 14,  241, 58,  33,  93, 182, 94,
     113, 81,  142, 93,  186, 240, 185, 69,  61, 37},
    {20,  8,   223, 147, 173, 252, 208, 73,  91,  124, 133,
     254, 51,  42,  154, 101, 51,  146, 170, 175, 130, 107,
     254, 125, 207, 31,  175, 141, 77,  32,  67,  12},
    {4,   247, 244, 132, 15,  3,   100, 145, 54,  39,  38,
     127, 168, 101, 157, 218, 193, 90,  255, 20,  103, 175,
     36,  254, 38,  253, 215, 150, 10,  110, 137, 28},
    {185, 72,  222, 52,  131, 225, 185, 167, 230, 34, 127,
     249, 106, 123, 146, 113, 86,  229, 38,  248, 2,  155,
     120, 212, 201, 11,  234, 44,  188, 134, 64,  41},
    {125, 222, 223, 52,  236, 171, 159, 102, 73,  237, 7,
     185, 135, 201, 133, 32,  7,   217, 7,   130, 131, 209,
     90,  246, 152, 223, 225, 96,  196, 9,   228, 35},
    {166, 58,  76,  42,  60,  248, 113, 190, 66,  63,  72,
     229, 193, 250, 214, 183, 50,  208, 70,  137, 220, 47,
     137, 83,  186, 42,  229, 135, 149, 245, 116, 4},
    {88,  0,   92,  132, 178, 143, 54,  162, 94,  58,  135,
     133, 109, 150, 109, 248, 170, 17,  139, 181, 169, 89,
     221, 161, 46,  125, 131, 64,  112, 242, 186, 60},
    {169, 202, 216, 81,  124, 53, 38,  2,   194, 101, 216,
     39,  124, 45,  83,  18,  24, 222, 205, 117, 36,  192,
     136, 150, 35,  206, 148, 22, 246, 105, 63,  54},
    {169, 171, 14, 11,  13,  71,  109, 189, 119, 109, 76,
     125, 97,  55, 151, 46,  142, 123, 171, 138, 197, 146,
     70,  161, 89, 129, 148, 230, 246, 6,   25,  26},
    {226, 137, 17,  137, 168, 36, 53,  177, 167, 61,  65,
     169, 158, 172, 77,  71,  73, 159, 220, 55,  229, 170,
     163, 158, 10,  205, 208, 41, 45,  17,  85,  63},
    {222, 204, 116, 132, 22,  215, 45,  160, 187, 200, 138,
     96,  37,  181, 56,  244, 168, 189, 69,  124, 148, 181,
     21,  186, 6,   87,  4,   236, 55,  44,  172, 53},
    {235, 49,  195, 148, 243, 35,  139, 107, 254, 223, 82,
     47,  122, 220, 37,  120, 127, 239, 77,  204, 36,  167,
     212, 67,  185, 154, 26,  218, 225, 135, 118, 12},
    {203, 33,  56,  14,  192, 132, 117, 5,   180, 38,  214,
     225, 254, 4,   202, 175, 153, 31,  62,  240, 128, 64,
     213, 117, 118, 94,  29,  66,  69,  133, 233, 5},
    {172, 55,  193, 121, 249, 141, 183, 217, 124, 24, 99,
     108, 184, 133, 98,  146, 251, 147, 70,  120, 38, 226,
     14,  154, 97,  155, 171, 252, 170, 142, 11,  46},
    {240, 218, 68,  237, 19,  170, 7,   150, 106, 154, 153,
     163, 79,  158, 91,  211, 194, 204, 45,  196, 35,  120,
     60,  39,  74,  31,  20,  18,  135, 110, 199, 5},
    {12,  156, 186, 86, 28,  72,  42,  139, 254, 214, 52,
     181, 51,  168, 23, 58,  214, 52,  198, 226, 11,  148,
     6,   234, 116, 33, 103, 208, 114, 190, 167, 47},
    {222, 219, 76,  5,  245, 17,  120, 111, 238, 47,  76,
     77,  87,  222, 16, 18,  168, 40,  193, 112, 163, 223,
     153, 100, 103, 80, 147, 19,  57,  100, 183, 15},
    {208, 104, 79,  120, 69,  35,  110, 89, 206, 54,  36,
     90,  69,  244, 211, 235, 193, 13,  92, 106, 249, 105,
     164, 143, 60,  156, 75,  130, 211, 54, 173, 37},
    {70, 102, 216, 188, 227, 50,  2,  92, 199, 79,  209, 246, 3,  106, 111, 135,
     18, 3,   199, 140, 245, 254, 25, 16, 227, 132, 42,  93,  99, 24,  166, 46},
    {33,  79,  70,  40,  198, 118, 241, 213, 90,  203, 88,
     180, 68,  128, 134, 18,  184, 177, 134, 136, 212, 226,
     77,  192, 129, 99,  116, 153, 118, 58,  147, 10},
    {52,  177, 8,   204, 172, 27,  19,  67,  129, 52,  209,
     239, 252, 246, 237, 6,   180, 34,  147, 146, 116, 96,
     139, 51,  34,  152, 194, 187, 156, 35,  198, 31},
    {108, 208, 95,  238, 89,  24,  161, 179, 243, 46, 208,
     151, 161, 252, 127, 51,  118, 112, 219, 18,  55, 32,
     203, 134, 138, 82,  207, 51,  225, 50,  60,  25},
    {81,  79, 234, 52, 70,  240, 33, 252, 172, 93, 117, 94,  159, 88,  60,  37,
     156, 42, 49,  38, 181, 117, 54, 40,  31,  84, 14,  218, 53,  196, 213, 48},
    {138, 90,  231, 106, 58, 253, 22, 238, 250, 38, 125, 104, 60, 150, 92, 121,
     39,  209, 186, 179, 10, 150, 29, 61,  175, 0,  179, 84,  16, 49,  19, 28},
    {143, 220, 254, 158, 84,  239, 155, 49,  30,  203, 51,
     87,  55,  91,  71,  210, 197, 157, 104, 204, 2,   19,
     95,  25,  56,  211, 165, 216, 228, 243, 122, 3},
    {250, 208, 170, 124, 154, 121, 17,  255, 195, 18, 101,
     101, 101, 116, 123, 158, 21,  2,   85,  145, 33, 62,
     80,  0,   209, 125, 230, 180, 213, 197, 31,  6},
    {141, 217, 184, 91,  71,  69,  71,  46,  25,  198, 32,
     87,  69,  183, 134, 238, 177, 176, 234, 0,   130, 247,
     32,  229, 217, 221, 180, 135, 215, 98,  157, 46},
    {241, 211, 254, 169, 168, 34,  100, 54, 31,  180, 68,
     155, 113, 87,  18,  86,  125, 127, 19, 120, 112, 154,
     117, 150, 176, 42,  109, 21,  237, 70, 11,  38},
    {96,  62,  110, 159, 164, 94,  110, 206, 18, 128, 53,
     42,  194, 200, 108, 150, 70,  146, 11,  20, 49,  157,
     248, 134, 31,  159, 31,  205, 207, 134, 70, 0},
    {68, 87,  15, 87,  57,  1,  74,  191, 166, 9, 180, 70,  211, 130, 136, 181,
     48, 220, 61, 201, 205, 92, 134, 166, 198, 8, 144, 135, 170, 222, 46,  51},
    {0,  10,  204, 161, 86,  188, 203, 230, 17,  11, 156,
     50, 76,  217, 254, 7,   116, 228, 223, 231, 33, 109,
     84, 165, 148, 130, 208, 208, 118, 75,  186, 1},
    {146, 91,  69, 96,  59,  141, 219, 230, 72,  133, 204,
     13,  130, 74, 145, 248, 213, 73,  153, 143, 113, 237,
     46,  28,  85, 79,  207, 127, 66,  48,  172, 46},
    {238, 46,  238, 149, 129, 186, 61,  44,  208, 139, 227,
     160, 139, 204, 209, 253, 150, 170, 228, 102, 150, 17,
     149, 189, 169, 62,  215, 73,  191, 50,  60,  48},
    {102, 251, 65, 152, 27,  226, 216, 203, 70, 116, 207,
     105, 53,  11, 75,  201, 8,   251, 195, 18, 7,   129,
     49,  187, 26, 239, 50,  38,  224, 193, 28, 14},
    {126, 126, 230, 150, 246, 218, 175, 92,  16, 198, 71,
     51,  94,  4,   162, 75,  203, 86,  149, 82, 27,  194,
     79,  186, 186, 190, 112, 182, 150, 20,  5,  51},
    {240, 2,   66,  139, 128, 8,   249, 101, 36,  225, 0,
     202, 42,  87,  231, 1,   234, 23,  226, 49,  68,  244,
     167, 144, 205, 83,  44,  10,  244, 163, 171, 14},
    {86,  166, 104, 236, 81,  188, 2,  139, 140, 220, 238,
     200, 163, 209, 110, 201, 42,  66, 205, 149, 3,   11,
     129, 212, 243, 196, 14,  39,  37, 228, 1,   11},
    {116, 166, 115, 180, 162, 255, 188, 126, 193, 136, 32,
     217, 231, 72,  132, 254, 195, 196, 245, 20,  149, 202,
     206, 121, 57,  97,  88,  38,  191, 132, 63,  19},
    {210, 61,  140, 139, 94,  249, 225, 127, 42,  70, 154,
     219, 226, 225, 57,  39,  160, 126, 50,  242, 96, 114,
     152, 18,  165, 194, 228, 66,  155, 244, 189, 60},
    {7,  237, 235, 130, 9,  44, 73,  48,  186, 162, 249, 106, 177, 150, 51, 214,
     23, 106, 191, 162, 68, 53, 219, 103, 204, 121, 83,  252, 65,  176, 56, 45},
    {37,  221, 38,  61,  251, 27,  9,  124, 22,  194, 250,
     200, 224, 254, 252, 173, 222, 59, 141, 153, 18,  218,
     224, 11,  166, 84,  1,   69,  15, 72,  230, 58},
    {5,  33, 197, 234, 88,  155, 87,  16, 112, 69, 11, 177, 43, 231, 102, 48,
     45, 29, 106, 26,  100, 5,   112, 42, 44,  63, 66, 37,  15, 228, 172, 1},
    {40,  128, 198, 153, 120, 124, 249, 46,  147, 153, 216,
     106, 45,  226, 140, 178, 204, 121, 19,  162, 75,  183,
     162, 254, 79,  177, 54,  89,  86,  250, 18,  18},
    {253, 80,  95, 61, 137, 35,  174, 250, 66, 181, 211, 114, 41,  48, 15,  154,
     225, 145, 60, 24, 79,  244, 39,  70,  54, 31,  78,  14,  154, 56, 102, 33},
    {194, 85,  215, 98,  181, 22,  190, 163, 232, 121, 211,
     101, 245, 108, 87,  56,  69,  232, 147, 249, 45,  109,
     56,  44,  207, 245, 254, 145, 167, 66,  222, 10}};

#endif
