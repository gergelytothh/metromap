// station_map.h - which LED belongs to which station.
//
// One row per LED: 96 rows, in map order along each line (M1, M2, M3, M4).
// Rows are listed in the same order the walk test lights them.
// Same data as hardware/led-mapping.csv.
//
// chip: 0 = U1 (M1 + M2), 1 = U2 (M3 + M4)
// dig:  0..7 = DIG0..DIG7 (cathode / row)
// seg:  0..7 = SEG_A..SEG_G, then SEG_DP (anode / column)

#pragma once
#include <stdint.h>

enum Line : uint8_t { M1, M2, M3, M4 };
enum Dir  : uint8_t { FWD, BWD };

struct LedAddr {
  uint8_t     id;        // 1..96, same as the led column in led-mapping.csv
  Line        line;
  uint8_t     stop;      // 1 = first station in map order
  Dir         dir;
  uint8_t     chip;
  uint8_t     dig;
  uint8_t     seg;
  const char* station;
};

const LedAddr LED_MAP[] = {
  // M1
  { 1,  M1, 1,  FWD, 0, 0, 0, "Vörösmarty tér" },  // SEG_A, DIG0 (terminus)
  { 2,  M1, 2,  FWD, 0, 1, 0, "Deák Ferenc tér" },  // SEG_A, DIG1
  { 3,  M1, 2,  BWD, 0, 2, 0, "Deák Ferenc tér" },  // SEG_A, DIG2
  { 4,  M1, 3,  FWD, 0, 3, 0, "Bajcsy-Zsilinszky út" },  // SEG_A, DIG3
  { 5,  M1, 3,  BWD, 0, 4, 0, "Bajcsy-Zsilinszky út" },  // SEG_A, DIG4
  { 6,  M1, 4,  FWD, 0, 5, 0, "Opera" },  // SEG_A, DIG5
  { 7,  M1, 4,  BWD, 0, 6, 0, "Opera" },  // SEG_A, DIG6
  { 8,  M1, 5,  FWD, 0, 0, 1, "Oktogon" },  // SEG_B, DIG0
  { 9,  M1, 5,  BWD, 0, 1, 1, "Oktogon" },  // SEG_B, DIG1
  { 10, M1, 6,  FWD, 0, 2, 1, "Vörösmarty utca" },  // SEG_B, DIG2
  { 11, M1, 6,  BWD, 0, 3, 1, "Vörösmarty utca" },  // SEG_B, DIG3
  { 12, M1, 7,  FWD, 0, 4, 1, "Kodály körönd" },  // SEG_B, DIG4
  { 13, M1, 7,  BWD, 0, 5, 1, "Kodály körönd" },  // SEG_B, DIG5
  { 14, M1, 8,  FWD, 0, 6, 1, "Bajza utca" },  // SEG_B, DIG6
  { 15, M1, 8,  BWD, 0, 7, 1, "Bajza utca" },  // SEG_B, DIG7
  { 16, M1, 9,  FWD, 0, 0, 2, "Hősök tere" },  // SEG_C, DIG0
  { 17, M1, 9,  BWD, 0, 1, 2, "Hősök tere" },  // SEG_C, DIG1
  { 18, M1, 10, FWD, 0, 2, 2, "Széchenyi fürdő" },  // SEG_C, DIG2
  { 19, M1, 10, BWD, 0, 3, 2, "Széchenyi fürdő" },  // SEG_C, DIG3
  { 20, M1, 11, FWD, 0, 4, 2, "Mexikói út" },  // SEG_C, DIG4 (terminus)

  // M2
  { 21, M2, 1,  FWD, 0, 0, 3, "Déli pályaudvar" },  // SEG_D, DIG0 (terminus)
  { 22, M2, 2,  FWD, 0, 1, 3, "Széll Kálmán tér" },  // SEG_D, DIG1
  { 23, M2, 2,  BWD, 0, 2, 3, "Széll Kálmán tér" },  // SEG_D, DIG2
  { 24, M2, 3,  FWD, 0, 3, 3, "Batthyány tér" },  // SEG_D, DIG3
  { 25, M2, 3,  BWD, 0, 4, 3, "Batthyány tér" },  // SEG_D, DIG4
  { 26, M2, 4,  FWD, 0, 5, 3, "Kossuth Lajos tér" },  // SEG_D, DIG5
  { 27, M2, 4,  BWD, 0, 6, 3, "Kossuth Lajos tér" },  // SEG_D, DIG6
  { 28, M2, 5,  FWD, 0, 0, 4, "Deák Ferenc tér" },  // SEG_E, DIG0
  { 29, M2, 5,  BWD, 0, 1, 4, "Deák Ferenc tér" },  // SEG_E, DIG1
  { 30, M2, 6,  FWD, 0, 2, 4, "Astoria" },  // SEG_E, DIG2
  { 31, M2, 6,  BWD, 0, 3, 4, "Astoria" },  // SEG_E, DIG3
  { 32, M2, 7,  FWD, 0, 4, 4, "Blaha Lujza tér" },  // SEG_E, DIG4
  { 33, M2, 7,  BWD, 0, 5, 4, "Blaha Lujza tér" },  // SEG_E, DIG5
  { 34, M2, 8,  FWD, 0, 6, 4, "Keleti pályaudvar" },  // SEG_E, DIG6
  { 35, M2, 8,  BWD, 0, 7, 4, "Keleti pályaudvar" },  // SEG_E, DIG7
  { 36, M2, 9,  FWD, 0, 0, 5, "Puskás Ferenc Stadion" },  // SEG_F, DIG0
  { 37, M2, 9,  BWD, 0, 1, 5, "Puskás Ferenc Stadion" },  // SEG_F, DIG1
  { 38, M2, 10, FWD, 0, 2, 5, "Pillangó utca" },  // SEG_F, DIG2
  { 39, M2, 10, BWD, 0, 3, 5, "Pillangó utca" },  // SEG_F, DIG3
  { 40, M2, 11, FWD, 0, 4, 5, "Örs vezér tere" },  // SEG_F, DIG4 (terminus)

  // M3
  { 41, M3, 1,  FWD, 1, 0, 0, "Kőbánya-Kispest" },  // SEG_A, DIG0 (terminus)
  { 42, M3, 2,  FWD, 1, 1, 0, "Határ út" },  // SEG_A, DIG1
  { 43, M3, 2,  BWD, 1, 2, 0, "Határ út" },  // SEG_A, DIG2
  { 44, M3, 3,  FWD, 1, 3, 0, "Pöttyös utca" },  // SEG_A, DIG3
  { 45, M3, 3,  BWD, 1, 4, 0, "Pöttyös utca" },  // SEG_A, DIG4
  { 46, M3, 4,  FWD, 1, 5, 0, "Ecseri út" },  // SEG_A, DIG5
  { 47, M3, 4,  BWD, 1, 6, 0, "Ecseri út" },  // SEG_A, DIG6
  { 48, M3, 5,  FWD, 1, 0, 1, "Népliget" },  // SEG_B, DIG0
  { 49, M3, 5,  BWD, 1, 1, 1, "Népliget" },  // SEG_B, DIG1
  { 50, M3, 6,  FWD, 1, 2, 1, "Nagyvárad tér" },  // SEG_B, DIG2
  { 51, M3, 6,  BWD, 1, 3, 1, "Nagyvárad tér" },  // SEG_B, DIG3
  { 52, M3, 7,  FWD, 1, 4, 1, "Klinikák" },  // SEG_B, DIG4
  { 53, M3, 7,  BWD, 1, 5, 1, "Klinikák" },  // SEG_B, DIG5
  { 54, M3, 8,  FWD, 1, 6, 1, "Corvin-negyed" },  // SEG_B, DIG6
  { 55, M3, 8,  BWD, 1, 7, 1, "Corvin-negyed" },  // SEG_B, DIG7
  { 56, M3, 9,  FWD, 1, 0, 2, "Kálvin tér" },  // SEG_C, DIG0
  { 57, M3, 9,  BWD, 1, 1, 2, "Kálvin tér" },  // SEG_C, DIG1
  { 58, M3, 10, FWD, 1, 2, 2, "Ferenciek tere" },  // SEG_C, DIG2
  { 59, M3, 10, BWD, 1, 3, 2, "Ferenciek tere" },  // SEG_C, DIG3
  { 60, M3, 11, FWD, 1, 4, 2, "Deák Ferenc tér" },  // SEG_C, DIG4
  { 61, M3, 11, BWD, 1, 5, 2, "Deák Ferenc tér" },  // SEG_C, DIG5
  { 62, M3, 12, FWD, 1, 6, 2, "Arany János utca" },  // SEG_C, DIG6
  { 63, M3, 12, BWD, 1, 7, 2, "Arany János utca" },  // SEG_C, DIG7
  { 64, M3, 13, FWD, 1, 0, 3, "Nyugati pályaudvar" },  // SEG_D, DIG0
  { 65, M3, 13, BWD, 1, 1, 3, "Nyugati pályaudvar" },  // SEG_D, DIG1
  { 66, M3, 14, FWD, 1, 2, 3, "Lehel tér" },  // SEG_D, DIG2
  { 67, M3, 14, BWD, 1, 3, 3, "Lehel tér" },  // SEG_D, DIG3
  { 68, M3, 15, FWD, 1, 4, 3, "Dózsa György út" },  // SEG_D, DIG4
  { 69, M3, 15, BWD, 1, 5, 3, "Dózsa György út" },  // SEG_D, DIG5
  { 70, M3, 16, FWD, 1, 6, 3, "Árpád híd" },  // SEG_D, DIG6
  { 71, M3, 16, BWD, 1, 7, 3, "Árpád híd" },  // SEG_D, DIG7
  { 72, M3, 17, FWD, 1, 0, 4, "Forgách utca" },  // SEG_E, DIG0
  { 73, M3, 17, BWD, 1, 1, 4, "Forgách utca" },  // SEG_E, DIG1
  { 74, M3, 18, FWD, 1, 2, 4, "Gyöngyösi utca" },  // SEG_E, DIG2
  { 75, M3, 18, BWD, 1, 3, 4, "Gyöngyösi utca" },  // SEG_E, DIG3
  { 76, M3, 19, FWD, 1, 4, 4, "Újpest-városkapu" },  // SEG_E, DIG4
  { 77, M3, 19, BWD, 1, 5, 4, "Újpest-városkapu" },  // SEG_E, DIG5
  { 78, M3, 20, FWD, 1, 6, 4, "Újpest-Központ" },  // SEG_E, DIG6 (terminus)

  // M4
  { 79, M4, 1,  FWD, 1, 0, 5, "Kelenföld vasútállomás" },  // SEG_F, DIG0 (terminus)
  { 80, M4, 2,  FWD, 1, 1, 5, "Bikás park" },  // SEG_F, DIG1
  { 81, M4, 2,  BWD, 1, 2, 5, "Bikás park" },  // SEG_F, DIG2
  { 82, M4, 3,  FWD, 1, 3, 5, "Újbuda-központ" },  // SEG_F, DIG3
  { 83, M4, 3,  BWD, 1, 4, 5, "Újbuda-központ" },  // SEG_F, DIG4
  { 84, M4, 4,  FWD, 1, 5, 5, "Móricz Zsigmond körtér" },  // SEG_F, DIG5
  { 85, M4, 4,  BWD, 1, 6, 5, "Móricz Zsigmond körtér" },  // SEG_F, DIG6
  { 86, M4, 5,  FWD, 1, 0, 6, "Szent Gellért tér" },  // SEG_G, DIG0
  { 87, M4, 5,  BWD, 1, 1, 6, "Szent Gellért tér" },  // SEG_G, DIG1
  { 88, M4, 6,  FWD, 1, 2, 6, "Fővám tér" },  // SEG_G, DIG2
  { 89, M4, 6,  BWD, 1, 3, 6, "Fővám tér" },  // SEG_G, DIG3
  { 90, M4, 7,  FWD, 1, 4, 6, "Kálvin tér" },  // SEG_G, DIG4
  { 91, M4, 7,  BWD, 1, 5, 6, "Kálvin tér" },  // SEG_G, DIG5
  { 92, M4, 8,  FWD, 1, 6, 6, "Rákóczi tér" },  // SEG_G, DIG6
  { 93, M4, 8,  BWD, 1, 7, 6, "Rákóczi tér" },  // SEG_G, DIG7
  { 94, M4, 9,  FWD, 1, 0, 7, "II. János Pál pápa tér" },  // SEG_DP, DIG0
  { 95, M4, 9,  BWD, 1, 1, 7, "II. János Pál pápa tér" },  // SEG_DP, DIG1
  { 96, M4, 10, FWD, 1, 2, 7, "Keleti pályaudvar" },  // SEG_DP, DIG2 (terminus)
};

const uint8_t LED_COUNT = sizeof(LED_MAP) / sizeof(LED_MAP[0]);
