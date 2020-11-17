/*
 * g722_1 - a library for the G.722.1 and Annex C codecs
 *
 * sam2coef.h
 *
 * Adapted by Steve Underwood <steveu@coppice.org> from the reference
 * code supplied with ITU G.722.1, which is:
 *
 *   (C) 2004 Polycom, Inc.
 *   All rights reserved.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 */

#if defined(G722_1_USE_FIXED_POINT)
const int16_t samples_to_rmlt_window[DCT_LENGTH] =
{
       44,   134,   224,   314,   404,   494,   584,   674,   764,   853,
      943,  1033,  1123,  1213,  1302,  1392,  1482,  1571,  1661,  1750,
     1840,  1929,  2019,  2108,  2197,  2286,  2376,  2465,  2554,  2643,
     2732,  2821,  2909,  2998,  3087,  3175,  3264,  3352,  3441,  3529,
     3617,  3705,  3793,  3881,  3969,  4057,  4144,  4232,  4319,  4407,
     4494,  4581,  4668,  4755,  4842,  4928,  5015,  5101,  5188,  5274,
     5360,  5446,  5532,  5617,  5703,  5788,  5873,  5959,  6043,  6128,
     6213,  6297,  6382,  6466,  6550,  6634,  6718,  6801,  6885,  6968,
     7051,  7134,  7217,  7299,  7382,  7464,  7546,  7628,  7709,  7791,
     7872,  7953,  8034,  8115,  8195,  8276,  8356,  8436,  8515,  8595,
     8674,  8753,  8832,  8911,  8989,  9068,  9146,  9223,  9301,  9378,
     9455,  9532,  9609,  9685,  9762,  9838,  9913,  9989, 10064, 10139,
    10214, 10288, 10363, 10437, 10510, 10584, 10657, 10730, 10803, 10875,
    10948, 11020, 11091, 11163, 11234, 11305, 11375, 11446, 11516, 11586,
    11655, 11724, 11793, 11862, 11930, 11998, 12066, 12134, 12201, 12268,
    12334, 12401, 12467, 12532, 12598, 12663, 12728, 12792, 12857, 12920,
    12984, 13047, 13110, 13173, 13235, 13297, 13359, 13420, 13481, 13542,
    13602, 13662, 13722, 13782, 13841, 13899, 13958, 14016, 14074, 14131,
    14188, 14245, 14301, 14357, 14413, 14468, 14523, 14578, 14632, 14686,
    14739, 14793, 14845, 14898, 14950, 15002, 15053, 15104, 15155, 15205,
    15255, 15305, 15354, 15403, 15451, 15500, 15547, 15595, 15642, 15688,
    15734, 15780, 15826, 15871, 15916, 15960, 16004, 16047, 16091, 16133,
    16176, 16218, 16259, 16300, 16341, 16382, 16422, 16461, 16501, 16540,
    16578, 16616, 16654, 16691, 16728, 16764, 16800, 16836, 16871, 16906,
    16940, 16974, 17008, 17041, 17074, 17106, 17138, 17170, 17201, 17232,
    17262, 17292, 17321, 17350, 17379, 17407, 17435, 17462, 17489, 17516,
    17542, 17567, 17593, 17617, 17642, 17666, 17689, 17713, 17735, 17758,
    17779, 17801, 17822, 17842, 17863, 17882, 17901, 17920, 17939, 17957,
    17974, 17991, 18008, 18024, 18040, 18055, 18070, 18085, 18099, 18113,
    18126, 18139, 18151, 18163, 18174, 18185, 18196, 18206, 18216, 18225,
    18234, 18242, 18250, 18257, 18265, 18271, 18277, 18283, 18288, 18293,
    18298, 18302, 18305, 18308, 18311, 18313, 18315, 18316, 18317, 18317,
};

const int16_t max_samples_to_rmlt_window[MAX_DCT_LENGTH] =
{
        0,    43,    89,   133,   178,   222,   268,   314,   357,   403,
      447,   493,   538,   582,   628,   671,   717,   763,   807,   853,
      896,   942,   987,  1031,  1077,  1121,  1166,  1212,  1256,  1301,
     1345,  1390,  1436,  1480,  1526,  1569,  1615,  1660,  1704,  1749,
     1793,  1838,  1884,  1928,  1973,  2016,  2062,  2107,  2151,  2196,
     2239,  2285,  2331,  2374,  2419,  2463,  2508,  2553,  2597,  2642,
     2685,  2730,  2776,  2819,  2864,  2908,  2952,  2998,  3041,  3086,
     3129,  3174,  3219,  3263,  3307,  3350,  3396,  3440,  3483,  3528,
     3571,  3616,  3661,  3704,  3748,  3791,  3836,  3881,  3923,  3968,
     4011,  4055,  4100,  4143,  4187,  4230,  4274,  4318,  4362,  4406,
     4448,  4493,  4537,  4580,  4624,  4666,  4710,  4755,  4797,  4841,
     4883,  4927,  4971,  5013,  5057,  5099,  5144,  5187,  5229,  5273,
     5315,  5359,  5402,  5444,  5488,  5530,  5573,  5617,  5658,  5702,
     5743,  5787,  5830,  5871,  5915,  5956,  6000,  6043,  6084,  6127,
     6169,  6211,  6254,  6296,  6339,  6380,  6423,  6465,  6507,  6549,
     6590,  6633,  6675,  6716,  6759,  6799,  6842,  6884,  6925,  6967,
     7007,  7050,  7092,  7132,  7175,  7215,  7257,  7299,  7339,  7381,
     7421,  7462,  7504,  7544,  7586,  7626,  7667,  7709,  7749,  7790,
     7830,  7871,  7912,  7952,  7993,  8032,  8073,  8114,  8153,  8194,
     8234,  8275,  8315,  8355,  8395,  8434,  8474,  8515,  8554,  8594,
     8632,  8673,  8713,  8752,  8792,  8830,  8871,  8910,  8949,  8989,
     9027,  9066,  9106,  9144,  9184,  9221,  9261,  9300,  9338,  9378,
     9415,  9454,  9493,  9531,  9570,  9607,  9646,  9685,  9722,  9761,
     9798,  9836,  9875,  9912,  9950,  9987, 10025, 10064, 10100, 10138,
    10175, 10213, 10250, 10287, 10325, 10361, 10398, 10436, 10472, 10510,
    10545, 10583, 10620, 10656, 10692, 10728, 10766, 10803, 10838, 10874,
    10910, 10947, 10983, 11018, 11055, 11089, 11126, 11162, 11197, 11233,
    11268, 11303, 11340, 11374, 11410, 11444, 11480, 11515, 11549, 11585,
    11619, 11654, 11689, 11723, 11758, 11791, 11826, 11861, 11895, 11930,
    11963, 11997, 12032, 12065, 12099, 12132, 12166, 12201, 12233, 12267,
    12300, 12333, 12367, 12400, 12433, 12465, 12499, 12532, 12563, 12597,
    12629, 12662, 12695, 12727, 12759, 12790, 12823, 12856, 12887, 12920,
    12951, 12983, 13016, 13046, 13078, 13109, 13141, 13173, 13203, 13235,
    13266, 13296, 13328, 13358, 13389, 13419, 13450, 13481, 13510, 13541,
    13571, 13602, 13632, 13661, 13692, 13721, 13751, 13781, 13810, 13840,
    13869, 13898, 13929, 13957, 13986, 14015, 14044, 14073, 14101, 14130,
    14158, 14187, 14216, 14244, 14272, 14300, 14328, 14357, 14384, 14412,
    14439, 14468, 14495, 14522, 14550, 14577, 14604, 14632, 14658, 14686,
    14711, 14739, 14765, 14792, 14819, 14844, 14871, 14897, 14923, 14949,
    14975, 15001, 15027, 15053, 15079, 15103, 15129, 15155, 15180, 15205,
    15229, 15255, 15280, 15304, 15329, 15353, 15378, 15403, 15426, 15451,
    15475, 15499, 15523, 15546, 15570, 15594, 15618, 15641, 15664, 15688,
    15711, 15734, 15757, 15780, 15802, 15825, 15848, 15871, 15892, 15915,
    15937, 15960, 15982, 16003, 16026, 16047, 16069, 16090, 16112, 16133,
    16154, 16175, 16197, 16217, 16239, 16259, 16279, 16301, 16320, 16341,
    16361, 16382, 16402, 16421, 16441, 16461, 16481, 16501, 16520, 16539,
    16558, 16578, 16597, 16615, 16635, 16653, 16672, 16691, 16709, 16728,
    16746, 16764, 16782, 16800, 16818, 16835, 16853, 16871, 16888, 16905,
    16923, 16940, 16957, 16974, 16991, 17008, 17024, 17041, 17057, 17074,
    17090, 17106, 17122, 17138, 17154, 17169, 17185, 17201, 17216, 17231,
    17246, 17262, 17277, 17291, 17306, 17321, 17336, 17350, 17364, 17379,
    17393, 17407, 17421, 17435, 17449, 17462, 17476, 17490, 17502, 17515,
    17528, 17542, 17554, 17567, 17580, 17592, 17605, 17618, 17629, 17642,
    17653, 17666, 17678, 17689, 17701, 17712, 17724, 17736, 17746, 17757,
    17768, 17779, 17790, 17800, 17811, 17822, 17832, 17842, 17852, 17862,
    17872, 17882, 17892, 17902, 17911, 17920, 17930, 17938, 17947, 17956,
    17965, 17974, 17983, 17991, 17999, 18008, 18016, 18025, 18032, 18040,
    18047, 18055, 18063, 18070, 18078, 18085, 18092, 18099, 18106, 18112,
    18119, 18126, 18132, 18138, 18144, 18151, 18157, 18163, 18168, 18174,
    18179, 18185, 18191, 18196, 18201, 18206, 18211, 18216, 18220, 18225,
    18229, 18234, 18238, 18242, 18246, 18250, 18254, 18257, 18260, 18264,
    18268, 18271, 18274, 18277, 18280, 18283, 18286, 18288, 18291, 18293,
    18295, 18297, 18300, 18301, 18303, 18305, 18306, 18308, 18309, 18311,
    18312, 18312, 18314, 18315, 18315, 18316, 18316, 18317, 18317, 18317
};

#else
const float samples_to_rmlt_window[DCT_LENGTH] =
{
    2.45436677e-03f,
    7.36304140e-03f,
    1.22715384e-02f,
    1.71797387e-02f,
    2.20875274e-02f,
    2.69947816e-02f,
    3.19013856e-02f,
    3.68072242e-02f,
    4.17121723e-02f,
    4.66161147e-02f,
    5.15189357e-02f,
    5.64205162e-02f,
    6.13207370e-02f,
    6.62194788e-02f,
    7.11166263e-02f,
    7.60120600e-02f,
    8.09056610e-02f,
    8.57973099e-02f,
    9.06868950e-02f,
    9.55742970e-02f,
    1.00459397e-01f,
    1.05342068e-01f,
    1.10222206e-01f,
    1.15099691e-01f,
    1.19974397e-01f,
    1.24846213e-01f,
    1.29715025e-01f,
    1.34580702e-01f,
    1.39443144e-01f,
    1.44302234e-01f,
    1.49157837e-01f,
    1.54009849e-01f,
    1.58858150e-01f,
    1.63702607e-01f,
    1.68543145e-01f,
    1.73379600e-01f,
    1.78211898e-01f,
    1.83039889e-01f,
    1.87863469e-01f,
    1.92682534e-01f,
    1.97496936e-01f,
    2.02306598e-01f,
    2.07111374e-01f,
    2.11911172e-01f,
    2.16705844e-01f,
    2.21495315e-01f,
    2.26279438e-01f,
    2.31058106e-01f,
    2.35831216e-01f,
    2.40598634e-01f,
    2.45360255e-01f,
    2.50115961e-01f,
    2.54865646e-01f,
    2.59609193e-01f,
    2.64346480e-01f,
    2.69077420e-01f,
    2.73801863e-01f,
    2.78519690e-01f,
    2.83230811e-01f,
    2.87935108e-01f,
    2.92632490e-01f,
    2.97322810e-01f,
    3.02005947e-01f,
    3.06681812e-01f,
    3.11350316e-01f,
    3.16011280e-01f,
    3.20664644e-01f,
    3.25310290e-01f,
    3.29948097e-01f,
    3.34577948e-01f,
    3.39199722e-01f,
    3.43813360e-01f,
    3.48418683e-01f,
    3.53015602e-01f,
    3.57604057e-01f,
    3.62183869e-01f,
    3.66754949e-01f,
    3.71317208e-01f,
    3.75870496e-01f,
    3.80414754e-01f,
    3.84949833e-01f,
    3.89475614e-01f,
    3.93992037e-01f,
    3.98498952e-01f,
    4.02996302e-01f,
    4.07483906e-01f,
    4.11961704e-01f,
    4.16429549e-01f,
    4.20887381e-01f,
    4.25335079e-01f,
    4.29772526e-01f,
    4.34199601e-01f,
    4.38616246e-01f,
    4.43022281e-01f,
    4.47417676e-01f,
    4.51802284e-01f,
    4.56175983e-01f,
    4.60538715e-01f,
    4.64890331e-01f,
    4.69230771e-01f,
    4.73559886e-01f,
    4.77877587e-01f,
    4.82183784e-01f,
    4.86478359e-01f,
    4.90761191e-01f,
    4.95032221e-01f,
    4.99291331e-01f,
    5.03538370e-01f,
    5.07773340e-01f,
    5.11996031e-01f,
    5.16206384e-01f,
    5.20404279e-01f,
    5.24589658e-01f,
    5.28762400e-01f,
    5.32922447e-01f,
    5.37069619e-01f,
    5.41203797e-01f,
    5.45324981e-01f,
    5.49433053e-01f,
    5.53527832e-01f,
    5.57609320e-01f,
    5.61677337e-01f,
    5.65731823e-01f,
    5.69772661e-01f,
    5.73799789e-01f,
    5.77813089e-01f,
    5.81812501e-01f,
    5.85797846e-01f,
    5.89769125e-01f,
    5.93726158e-01f,
    5.97668886e-01f,
    6.01597190e-01f,
    6.05511069e-01f,
    6.09410286e-01f,
    6.13294840e-01f,
    6.17164612e-01f,
    6.21019542e-01f,
    6.24859512e-01f,
    6.28684402e-01f,
    6.32494152e-01f,
    6.36288643e-01f,
    6.40067816e-01f,
    6.43831551e-01f,
    6.47579789e-01f,
    6.51312411e-01f,
    6.55029356e-01f,
    6.58730507e-01f,
    6.62415802e-01f,
    6.66085124e-01f,
    6.69738352e-01f,
    6.73375487e-01f,
    6.76996410e-01f,
    6.80601001e-01f,
    6.84189200e-01f,
    6.87760890e-01f,
    6.91316009e-01f,
    6.94854498e-01f,
    6.98376238e-01f,
    7.01881170e-01f,
    7.05369174e-01f,
    7.08840132e-01f,
    7.12294042e-01f,
    7.15730846e-01f,
    7.19150364e-01f,
    7.22552538e-01f,
    7.25937307e-01f,
    7.29304552e-01f,
    7.32654274e-01f,
    7.35986352e-01f,
    7.39300668e-01f,
    7.42597163e-01f,
    7.45875776e-01f,
    7.49136388e-01f,
    7.52379000e-01f,
    7.55603433e-01f,
    7.58809686e-01f,
    7.61997640e-01f,
    7.65167236e-01f,
    7.68318415e-01f,
    7.71451116e-01f,
    7.74565160e-01f,
    7.77660549e-01f,
    7.80737221e-01f,
    7.83795059e-01f,
    7.86834061e-01f,
    7.89854050e-01f,
    7.92855024e-01f,
    7.95836926e-01f,
    7.98799574e-01f,
    8.01743031e-01f,
    8.04667175e-01f,
    8.07571888e-01f,
    8.10457170e-01f,
    8.13322961e-01f,
    8.16169083e-01f,
    8.18995595e-01f,
    8.21802378e-01f,
    8.24589312e-01f,
    8.27356398e-01f,
    8.30103517e-01f,
    8.32830667e-01f,
    8.35537732e-01f,
    8.38224709e-01f,
    8.40891480e-01f,
    8.43537927e-01f,
    8.46164107e-01f,
    8.48769844e-01f,
    8.51355195e-01f,
    8.53919983e-01f,
    8.56464207e-01f,
    8.58987808e-01f,
    8.61490726e-01f,
    8.63972843e-01f,
    8.66434157e-01f,
    8.68874609e-01f,
    8.71294141e-01f,
    8.73692632e-01f,
    8.76070082e-01f,
    8.78426433e-01f,
    8.80761623e-01f,
    8.83075595e-01f,
    8.85368288e-01f,
    8.87639642e-01f,
    8.89889598e-01f,
    8.92118096e-01f,
    8.94325137e-01f,
    8.96510601e-01f,
    8.98674488e-01f,
    9.00816679e-01f,
    9.02937174e-01f,
    9.05035973e-01f,
    9.07112896e-01f,
    9.09168005e-01f,
    9.11201179e-01f,
    9.13212419e-01f,
    9.15201604e-01f,
    9.17168796e-01f,
    9.19113874e-01f,
    9.21036780e-01f,
    9.22937512e-01f,
    9.24816012e-01f,
    9.26672220e-01f,
    9.28506076e-01f,
    9.30317581e-01f,
    9.32106674e-01f,
    9.33873296e-01f,
    9.35617447e-01f,
    9.37339008e-01f,
    9.39037979e-01f,
    9.40714359e-01f,
    9.42368090e-01f,
    9.43999052e-01f,
    9.45607305e-01f,
    9.47192788e-01f,
    9.48755443e-01f,
    9.50295210e-01f,
    9.51812088e-01f,
    9.53306019e-01f,
    9.54777002e-01f,
    9.56224978e-01f,
    9.57649946e-01f,
    9.59051788e-01f,
    9.60430503e-01f,
    9.61786151e-01f,
    9.63118553e-01f,
    9.64427769e-01f,
    9.65713739e-01f,
    9.66976464e-01f,
    9.68215883e-01f,
    9.69431996e-01f,
    9.70624685e-01f,
    9.71794009e-01f,
    9.72939968e-01f,
    9.74062443e-01f,
    9.75161433e-01f,
    9.76236939e-01f,
    9.77288961e-01f,
    9.78317380e-01f,
    9.79322255e-01f,
    9.80303526e-01f,
    9.81261134e-01f,
    9.82195139e-01f,
    9.83105481e-01f,
    9.83992159e-01f,
    9.84855056e-01f,
    9.85694289e-01f,
    9.86509740e-01f,
    9.87301409e-01f,
    9.88069296e-01f,
    9.88813400e-01f,
    9.89533663e-01f,
    9.90230083e-01f,
    9.90902662e-01f,
    9.91551340e-01f,
    9.92176116e-01f,
    9.92776990e-01f,
    9.93353963e-01f,
    9.93906975e-01f,
    9.94436026e-01f,
    9.94941175e-01f,
    9.95422304e-01f,
    9.95879471e-01f,
    9.96312618e-01f,
    9.96721745e-01f,
    9.97106910e-01f,
    9.97467995e-01f,
    9.97805059e-01f,
    9.98118103e-01f,
    9.98407066e-01f,
    9.98672009e-01f,
    9.98912871e-01f,
    9.99129653e-01f,
    9.99322355e-01f,
    9.99491036e-01f,
    9.99635577e-01f,
    9.99756038e-01f,
    9.99852419e-01f,
    9.99924719e-01f,
    9.99972880e-01f,
    9.99996960e-01f
};

const float max_samples_to_rmlt_window[MAX_DCT_LENGTH] =
{
    1.22718432e-03f,
    3.68154561e-03f,
    6.13588467e-03f,
    8.59018695e-03f,
    1.10444371e-02f,
    1.34986211e-02f,
    1.59527231e-02f,
    1.84067301e-02f,
    2.08606254e-02f,
    2.33143959e-02f,
    2.57680248e-02f,
    2.82214992e-02f,
    3.06748040e-02f,
    3.31279226e-02f,
    3.55808437e-02f,
    3.80335487e-02f,
    4.04860228e-02f,
    4.29382585e-02f,
    4.53902297e-02f,
    4.78419326e-02f,
    5.02933450e-02f,
    5.27444519e-02f,
    5.51952459e-02f,
    5.76457046e-02f,
    6.00958169e-02f,
    6.25455678e-02f,
    6.49949387e-02f,
    6.74439222e-02f,
    6.98924959e-02f,
    7.23406523e-02f,
    7.47883692e-02f,
    7.72356316e-02f,
    7.96824396e-02f,
    8.21287632e-02f,
    8.45745876e-02f,
    8.70199054e-02f,
    8.94647017e-02f,
    9.19089541e-02f,
    9.43526551e-02f,
    9.67957899e-02f,
    9.92383435e-02f,
    1.01680294e-01f,
    1.04121633e-01f,
    1.06562346e-01f,
    1.09002419e-01f,
    1.11441828e-01f,
    1.13880575e-01f,
    1.16318628e-01f,
    1.18755989e-01f,
    1.21192627e-01f,
    1.23628542e-01f,
    1.26063704e-01f,
    1.28498107e-01f,
    1.30931750e-01f,
    1.33364588e-01f,
    1.35796621e-01f,
    1.38227850e-01f,
    1.40658244e-01f,
    1.43087775e-01f,
    1.45516455e-01f,
    1.47944272e-01f,
    1.50371179e-01f,
    1.52797192e-01f,
    1.55222267e-01f,
    1.57646418e-01f,
    1.60069630e-01f,
    1.62491858e-01f,
    1.64913118e-01f,
    1.67333379e-01f,
    1.69752643e-01f,
    1.72170877e-01f,
    1.74588069e-01f,
    1.77004218e-01f,
    1.79419294e-01f,
    1.81833297e-01f,
    1.84246197e-01f,
    1.86657995e-01f,
    1.89068660e-01f,
    1.91478193e-01f,
    1.93886578e-01f,
    1.96293786e-01f,
    1.98699802e-01f,
    2.01104641e-01f,
    2.03508258e-01f,
    2.05910638e-01f,
    2.08311796e-01f,
    2.10711688e-01f,
    2.13110313e-01f,
    2.15507656e-01f,
    2.17903703e-01f,
    2.20298439e-01f,
    2.22691849e-01f,
    2.25083917e-01f,
    2.27474615e-01f,
    2.29863957e-01f,
    2.32251912e-01f,
    2.34638467e-01f,
    2.37023607e-01f,
    2.39407316e-01f,
    2.41789594e-01f,
    2.44170398e-01f,
    2.46549740e-01f,
    2.48927608e-01f,
    2.51303971e-01f,
    2.53678799e-01f,
    2.56052136e-01f,
    2.58423895e-01f,
    2.60794103e-01f,
    2.63162762e-01f,
    2.65529811e-01f,
    2.67895281e-01f,
    2.70259142e-01f,
    2.72621363e-01f,
    2.74981946e-01f,
    2.77340859e-01f,
    2.79698104e-01f,
    2.82053679e-01f,
    2.84407526e-01f,
    2.86759704e-01f,
    2.89110124e-01f,
    2.91458815e-01f,
    2.93805718e-01f,
    2.96150893e-01f,
    2.98494250e-01f,
    3.00835848e-01f,
    3.03175598e-01f,
    3.05513531e-01f,
    3.07849646e-01f,
    3.10183883e-01f,
    3.12516272e-01f,
    3.14846754e-01f,
    3.17175359e-01f,
    3.19502026e-01f,
    3.21826786e-01f,
    3.24149609e-01f,
    3.26470494e-01f,
    3.28789383e-01f,
    3.31106305e-01f,
    3.33421230e-01f,
    3.35734159e-01f,
    3.38045061e-01f,
    3.40353906e-01f,
    3.42660725e-01f,
    3.44965458e-01f,
    3.47268134e-01f,
    3.49568695e-01f,
    3.51867169e-01f,
    3.54163527e-01f,
    3.56457740e-01f,
    3.58749807e-01f,
    3.61039728e-01f,
    3.63327444e-01f,
    3.65612984e-01f,
    3.67896348e-01f,
    3.70177478e-01f,
    3.72456372e-01f,
    3.74733001e-01f,
    3.77007425e-01f,
    3.79279524e-01f,
    3.81549388e-01f,
    3.83816928e-01f,
    3.86082143e-01f,
    3.88345033e-01f,
    3.90605599e-01f,
    3.92863810e-01f,
    3.95119667e-01f,
    3.97373140e-01f,
    3.99624199e-01f,
    4.01872873e-01f,
    4.04119104e-01f,
    4.06362921e-01f,
    4.08604264e-01f,
    4.10843164e-01f,
    4.13079590e-01f,
    4.15313542e-01f,
    4.17544961e-01f,
    4.19773877e-01f,
    4.22000259e-01f,
    4.24224108e-01f,
    4.26445425e-01f,
    4.28664148e-01f,
    4.30880278e-01f,
    4.33093816e-01f,
    4.35304761e-01f,
    4.37513083e-01f,
    4.39718753e-01f,
    4.41921771e-01f,
    4.44122136e-01f,
    4.46319848e-01f,
    4.48514849e-01f,
    4.50707138e-01f,
    4.52896714e-01f,
    4.55083579e-01f,
    4.57267702e-01f,
    4.59449053e-01f,
    4.61627662e-01f,
    4.63803470e-01f,
    4.65976506e-01f,
    4.68146712e-01f,
    4.70314115e-01f,
    4.72478658e-01f,
    4.74640369e-01f,
    4.76799220e-01f,
    4.78955209e-01f,
    4.81108308e-01f,
    4.83258516e-01f,
    4.85405803e-01f,
    4.87550169e-01f,
    4.89691585e-01f,
    4.91830051e-01f,
    4.93965566e-01f,
    4.96098131e-01f,
    4.98227656e-01f,
    5.00354230e-01f,
    5.02477765e-01f,
    5.04598260e-01f,
    5.06715715e-01f,
    5.08830130e-01f,
    5.10941505e-01f,
    5.13049781e-01f,
    5.15154958e-01f,
    5.17257035e-01f,
    5.19356012e-01f,
    5.21451831e-01f,
    5.23544490e-01f,
    5.25634050e-01f,
    5.27720451e-01f,
    5.29803634e-01f,
    5.31883657e-01f,
    5.33960402e-01f,
    5.36033988e-01f,
    5.38104355e-01f,
    5.40171444e-01f,
    5.42235315e-01f,
    5.44295907e-01f,
    5.46353221e-01f,
    5.48407257e-01f,
    5.50457954e-01f,
    5.52505374e-01f,
    5.54549456e-01f,
    5.56590199e-01f,
    5.58627546e-01f,
    5.60661554e-01f,
    5.62692225e-01f,
    5.64719439e-01f,
    5.66743314e-01f,
    5.68763733e-01f,
    5.70780754e-01f,
    5.72794318e-01f,
    5.74804425e-01f,
    5.76811075e-01f,
    5.78814268e-01f,
    5.80813944e-01f,
    5.82810163e-01f,
    5.84802806e-01f,
    5.86791992e-01f,
    5.88777602e-01f,
    5.90759695e-01f,
    5.92738211e-01f,
    5.94713151e-01f,
    5.96684515e-01f,
    5.98652303e-01f,
    6.00616455e-01f,
    6.02577031e-01f,
    6.04533970e-01f,
    6.06487215e-01f,
    6.08436823e-01f,
    6.10382795e-01f,
    6.12325072e-01f,
    6.14263654e-01f,
    6.16198599e-01f,
    6.18129730e-01f,
    6.20057225e-01f,
    6.21980906e-01f,
    6.23900890e-01f,
    6.25817120e-01f,
    6.27729595e-01f,
    6.29638255e-01f,
    6.31543100e-01f,
    6.33444190e-01f,
    6.35341406e-01f,
    6.37234867e-01f,
    6.39124453e-01f,
    6.41010165e-01f,
    6.42892063e-01f,
    6.44770086e-01f,
    6.46644175e-01f,
    6.48514390e-01f,
    6.50380731e-01f,
    6.52243137e-01f,
    6.54101610e-01f,
    6.55956089e-01f,
    6.57806695e-01f,
    6.59653306e-01f,
    6.61495924e-01f,
    6.63334608e-01f,
    6.65169239e-01f,
    6.66999936e-01f,
    6.68826580e-01f,
    6.70649171e-01f,
    6.72467709e-01f,
    6.74282253e-01f,
    6.76092684e-01f,
    6.77899063e-01f,
    6.79701388e-01f,
    6.81499600e-01f,
    6.83293700e-01f,
    6.85083687e-01f,
    6.86869502e-01f,
    6.88651264e-01f,
    6.90428793e-01f,
    6.92202210e-01f,
    6.93971455e-01f,
    6.95736527e-01f,
    6.97497368e-01f,
    6.99254036e-01f,
    7.01006532e-01f,
    7.02754736e-01f,
    7.04498768e-01f,
    7.06238508e-01f,
    7.07974017e-01f,
    7.09705234e-01f,
    7.11432219e-01f,
    7.13154852e-01f,
    7.14873254e-01f,
    7.16587305e-01f,
    7.18297064e-01f,
    7.20002532e-01f,
    7.21703589e-01f,
    7.23400354e-01f,
    7.25092709e-01f,
    7.26780772e-01f,
    7.28464365e-01f,
    7.30143666e-01f,
    7.31818497e-01f,
    7.33488917e-01f,
    7.35154986e-01f,
    7.36816585e-01f,
    7.38473713e-01f,
    7.40126431e-01f,
    7.41774678e-01f,
    7.43418455e-01f,
    7.45057762e-01f,
    7.46692598e-01f,
    7.48322904e-01f,
    7.49948740e-01f,
    7.51570046e-01f,
    7.53186822e-01f,
    7.54799008e-01f,
    7.56406724e-01f,
    7.58009851e-01f,
    7.59608388e-01f,
    7.61202395e-01f,
    7.62791812e-01f,
    7.64376581e-01f,
    7.65956819e-01f,
    7.67532349e-01f,
    7.69103348e-01f,
    7.70669639e-01f,
    7.72231340e-01f,
    7.73788393e-01f,
    7.75340736e-01f,
    7.76888490e-01f,
    7.78431475e-01f,
    7.79969811e-01f,
    7.81503439e-01f,
    7.83032358e-01f,
    7.84556568e-01f,
    7.86076069e-01f,
    7.87590802e-01f,
    7.89100826e-01f,
    7.90606081e-01f,
    7.92106569e-01f,
    7.93602288e-01f,
    7.95093238e-01f,
    7.96579361e-01f,
    7.98060715e-01f,
    7.99537241e-01f,
    8.01008999e-01f,
    8.02475870e-01f,
    8.03937972e-01f,
    8.05395186e-01f,
    8.06847572e-01f,
    8.08295071e-01f,
    8.09737682e-01f,
    8.11175466e-01f,
    8.12608361e-01f,
    8.14036310e-01f,
    8.15459430e-01f,
    8.16877604e-01f,
    8.18290830e-01f,
    8.19699109e-01f,
    8.21102500e-01f,
    8.22500944e-01f,
    8.23894441e-01f,
    8.25282931e-01f,
    8.26666474e-01f,
    8.28045070e-01f,
    8.29418600e-01f,
    8.30787182e-01f,
    8.32150757e-01f,
    8.33509326e-01f,
    8.34862888e-01f,
    8.36211383e-01f,
    8.37554872e-01f,
    8.38893294e-01f,
    8.40226650e-01f,
    8.41554999e-01f,
    8.42878222e-01f,
    8.44196379e-01f,
    8.45509470e-01f,
    8.46817434e-01f,
    8.48120332e-01f,
    8.49418104e-01f,
    8.50710809e-01f,
    8.51998329e-01f,
    8.53280723e-01f,
    8.54557991e-01f,
    8.55830133e-01f,
    8.57097089e-01f,
    8.58358860e-01f,
    8.59615505e-01f,
    8.60866964e-01f,
    8.62113178e-01f,
    8.63354266e-01f,
    8.64590168e-01f,
    8.65820825e-01f,
    8.67046237e-01f,
    8.68266463e-01f,
    8.69481444e-01f,
    8.70691240e-01f,
    8.71895730e-01f,
    8.73094976e-01f,
    8.74288976e-01f,
    8.75477731e-01f,
    8.76661181e-01f,
    8.77839327e-01f,
    8.79012227e-01f,
    8.80179822e-01f,
    8.81342113e-01f,
    8.82499099e-01f,
    8.83650780e-01f,
    8.84797096e-01f,
    8.85938108e-01f,
    8.87073815e-01f,
    8.88204098e-01f,
    8.89329076e-01f,
    8.90448749e-01f,
    8.91562998e-01f,
    8.92671883e-01f,
    8.93775403e-01f,
    8.94873500e-01f,
    8.95966232e-01f,
    8.97053599e-01f,
    8.98135543e-01f,
    8.99212062e-01f,
    9.00283158e-01f,
    9.01348829e-01f,
    9.02409077e-01f,
    9.03463900e-01f,
    9.04513299e-01f,
    9.05557215e-01f,
    9.06595707e-01f,
    9.07628715e-01f,
    9.08656240e-01f,
    9.09678340e-01f,
    9.10694897e-01f,
    9.11706030e-01f,
    9.12711620e-01f,
    9.13711786e-01f,
    9.14706349e-01f,
    9.15695488e-01f,
    9.16679084e-01f,
    9.17657137e-01f,
    9.18629646e-01f,
    9.19596672e-01f,
    9.20558095e-01f,
    9.21514034e-01f,
    9.22464430e-01f,
    9.23409224e-01f,
    9.24348474e-01f,
    9.25282121e-01f,
    9.26210225e-01f,
    9.27132785e-01f,
    9.28049684e-01f,
    9.28961039e-01f,
    9.29866791e-01f,
    9.30766940e-01f,
    9.31661487e-01f,
    9.32550430e-01f,
    9.33433771e-01f,
    9.34311450e-01f,
    9.35183525e-01f,
    9.36049938e-01f,
    9.36910748e-01f,
    9.37765896e-01f,
    9.38615382e-01f,
    9.39459205e-01f,
    9.40297425e-01f,
    9.41129923e-01f,
    9.41956758e-01f,
    9.42777932e-01f,
    9.43593442e-01f,
    9.44403291e-01f,
    9.45207417e-01f,
    9.46005821e-01f,
    9.46798563e-01f,
    9.47585583e-01f,
    9.48366940e-01f,
    9.49142516e-01f,
    9.49912429e-01f,
    9.50676560e-01f,
    9.51435030e-01f,
    9.52187717e-01f,
    9.52934682e-01f,
    9.53675926e-01f,
    9.54411447e-01f,
    9.55141187e-01f,
    9.55865145e-01f,
    9.56583381e-01f,
    9.57295835e-01f,
    9.58002567e-01f,
    9.58703458e-01f,
    9.59398627e-01f,
    9.60088015e-01f,
    9.60771620e-01f,
    9.61449385e-01f,
    9.62121427e-01f,
    9.62787628e-01f,
    9.63448048e-01f,
    9.64102626e-01f,
    9.64751422e-01f,
    9.65394437e-01f,
    9.66031611e-01f,
    9.66663003e-01f,
    9.67288494e-01f,
    9.67908204e-01f,
    9.68522072e-01f,
    9.69130158e-01f,
    9.69732344e-01f,
    9.70328689e-01f,
    9.70919251e-01f,
    9.71503913e-01f,
    9.72082734e-01f,
    9.72655654e-01f,
    9.73222792e-01f,
    9.73784029e-01f,
    9.74339366e-01f,
    9.74888861e-01f,
    9.75432515e-01f,
    9.75970268e-01f,
    9.76502120e-01f,
    9.77028131e-01f,
    9.77548242e-01f,
    9.78062451e-01f,
    9.78570819e-01f,
    9.79073226e-01f,
    9.79569793e-01f,
    9.80060399e-01f,
    9.80545104e-01f,
    9.81023967e-01f,
    9.81496871e-01f,
    9.81963873e-01f,
    9.82424974e-01f,
    9.82880116e-01f,
    9.83329356e-01f,
    9.83772695e-01f,
    9.84210074e-01f,
    9.84641552e-01f,
    9.85067070e-01f,
    9.85486686e-01f,
    9.85900342e-01f,
    9.86308098e-01f,
    9.86709893e-01f,
    9.87105727e-01f,
    9.87495601e-01f,
    9.87879574e-01f,
    9.88257587e-01f,
    9.88629639e-01f,
    9.88995671e-01f,
    9.89355803e-01f,
    9.89709973e-01f,
    9.90058184e-01f,
    9.90400434e-01f,
    9.90736723e-01f,
    9.91067052e-01f,
    9.91391361e-01f,
    9.91709769e-01f,
    9.92022157e-01f,
    9.92328584e-01f,
    9.92628992e-01f,
    9.92923498e-01f,
    9.93211925e-01f,
    9.93494451e-01f,
    9.93770957e-01f,
    9.94041502e-01f,
    9.94306028e-01f,
    9.94564593e-01f,
    9.94817138e-01f,
    9.95063663e-01f,
    9.95304286e-01f,
    9.95538831e-01f,
    9.95767415e-01f,
    9.95989978e-01f,
    9.96206582e-01f,
    9.96417165e-01f,
    9.96621728e-01f,
    9.96820271e-01f,
    9.97012854e-01f,
    9.97199416e-01f,
    9.97379959e-01f,
    9.97554541e-01f,
    9.97723043e-01f,
    9.97885585e-01f,
    9.98042107e-01f,
    9.98192608e-01f,
    9.98337090e-01f,
    9.98475552e-01f,
    9.98608053e-01f,
    9.98734474e-01f,
    9.98854935e-01f,
    9.98969316e-01f,
    9.99077737e-01f,
    9.99180079e-01f,
    9.99276459e-01f,
    9.99366820e-01f,
    9.99451101e-01f,
    9.99529421e-01f,
    9.99601722e-01f,
    9.99667943e-01f,
    9.99728203e-01f,
    9.99782383e-01f,
    9.99830604e-01f,
    9.99872744e-01f,
    9.99908864e-01f,
    9.99939024e-01f,
    9.99963105e-01f,
    9.99981165e-01f,
    9.99993205e-01f,
    9.99999225e-01f
};
#endif
/*- End of file ------------------------------------------------------------*/
