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
  { M1, 1,  FWD, 0, 0, 0, "Vörösmarty tér" },  // SEG_A, DIG0 (terminus)
  { M1, 2,  FWD, 0, 1, 0, "Deák Ferenc tér" },  // SEG_A, DIG1
  { M1, 2,  BWD, 0, 2, 0, "Deák Ferenc tér" },  // SEG_A, DIG2
  { M1, 3,  FWD, 0, 3, 0, "Bajcsy-Zsilinszky út" },  // SEG_A, DIG3
  { M1, 3,  BWD, 0, 4, 0, "Bajcsy-Zsilinszky út" },  // SEG_A, DIG4
  { M1, 4,  FWD, 0, 5, 0, "Opera" },  // SEG_A, DIG5
  { M1, 4,  BWD, 0, 6, 0, "Opera" },  // SEG_A, DIG6
  { M1, 5,  FWD, 0, 0, 1, "Oktogon" },  // SEG_B, DIG0
  { M1, 5,  BWD, 0, 1, 1, "Oktogon" },  // SEG_B, DIG1
  { M1, 6,  FWD, 0, 2, 1, "Vörösmarty utca" },  // SEG_B, DIG2
  { M1, 6,  BWD, 0, 3, 1, "Vörösmarty utca" },  // SEG_B, DIG3
  { M1, 7,  FWD, 0, 4, 1, "Kodály körönd" },  // SEG_B, DIG4
  { M1, 7,  BWD, 0, 5, 1, "Kodály körönd" },  // SEG_B, DIG5
  { M1, 8,  FWD, 0, 6, 1, "Bajza utca" },  // SEG_B, DIG6
  { M1, 8,  BWD, 0, 7, 1, "Bajza utca" },  // SEG_B, DIG7
  { M1, 9,  FWD, 0, 0, 2, "Hősök tere" },  // SEG_C, DIG0
  { M1, 9,  BWD, 0, 1, 2, "Hősök tere" },  // SEG_C, DIG1
  { M1, 10, FWD, 0, 2, 2, "Széchenyi fürdő" },  // SEG_C, DIG2
  { M1, 10, BWD, 0, 3, 2, "Széchenyi fürdő" },  // SEG_C, DIG3
  { M1, 11, FWD, 0, 4, 2, "Mexikói út" },  // SEG_C, DIG4 (terminus)

  // M2
  { M2, 1,  FWD, 0, 0, 3, "Déli pályaudvar" },  // SEG_D, DIG0 (terminus)
  { M2, 2,  FWD, 0, 1, 3, "Széll Kálmán tér" },  // SEG_D, DIG1
  { M2, 2,  BWD, 0, 2, 3, "Széll Kálmán tér" },  // SEG_D, DIG2
  { M2, 3,  FWD, 0, 3, 3, "Batthyány tér" },  // SEG_D, DIG3
  { M2, 3,  BWD, 0, 4, 3, "Batthyány tér" },  // SEG_D, DIG4
  { M2, 4,  FWD, 0, 5, 3, "Kossuth Lajos tér" },  // SEG_D, DIG5
  { M2, 4,  BWD, 0, 6, 3, "Kossuth Lajos tér" },  // SEG_D, DIG6
  { M2, 5,  FWD, 0, 0, 4, "Deák Ferenc tér" },  // SEG_E, DIG0
  { M2, 5,  BWD, 0, 1, 4, "Deák Ferenc tér" },  // SEG_E, DIG1
  { M2, 6,  FWD, 0, 2, 4, "Astoria" },  // SEG_E, DIG2
  { M2, 6,  BWD, 0, 3, 4, "Astoria" },  // SEG_E, DIG3
  { M2, 7,  FWD, 0, 4, 4, "Blaha Lujza tér" },  // SEG_E, DIG4
  { M2, 7,  BWD, 0, 5, 4, "Blaha Lujza tér" },  // SEG_E, DIG5
  { M2, 8,  FWD, 0, 6, 4, "Keleti pályaudvar" },  // SEG_E, DIG6
  { M2, 8,  BWD, 0, 7, 4, "Keleti pályaudvar" },  // SEG_E, DIG7
  { M2, 9,  FWD, 0, 0, 5, "Puskás Ferenc Stadion" },  // SEG_F, DIG0
  { M2, 9,  BWD, 0, 1, 5, "Puskás Ferenc Stadion" },  // SEG_F, DIG1
  { M2, 10, FWD, 0, 2, 5, "Pillangó utca" },  // SEG_F, DIG2
  { M2, 10, BWD, 0, 3, 5, "Pillangó utca" },  // SEG_F, DIG3
  { M2, 11, FWD, 0, 4, 5, "Örs vezér tere" },  // SEG_F, DIG4 (terminus)

  // M3
  { M3, 1,  FWD, 1, 0, 0, "Kőbánya-Kispest" },  // SEG_A, DIG0 (terminus)
  { M3, 2,  FWD, 1, 1, 0, "Határ út" },  // SEG_A, DIG1
  { M3, 2,  BWD, 1, 2, 0, "Határ út" },  // SEG_A, DIG2
  { M3, 3,  FWD, 1, 3, 0, "Pöttyös utca" },  // SEG_A, DIG3
  { M3, 3,  BWD, 1, 4, 0, "Pöttyös utca" },  // SEG_A, DIG4
  { M3, 4,  FWD, 1, 5, 0, "Ecseri út" },  // SEG_A, DIG5
  { M3, 4,  BWD, 1, 6, 0, "Ecseri út" },  // SEG_A, DIG6
  { M3, 5,  FWD, 1, 0, 1, "Népliget" },  // SEG_B, DIG0
  { M3, 5,  BWD, 1, 1, 1, "Népliget" },  // SEG_B, DIG1
  { M3, 6,  FWD, 1, 2, 1, "Nagyvárad tér" },  // SEG_B, DIG2
  { M3, 6,  BWD, 1, 3, 1, "Nagyvárad tér" },  // SEG_B, DIG3
  { M3, 7,  FWD, 1, 4, 1, "Klinikák" },  // SEG_B, DIG4
  { M3, 7,  BWD, 1, 5, 1, "Klinikák" },  // SEG_B, DIG5
  { M3, 8,  FWD, 1, 6, 1, "Corvin-negyed" },  // SEG_B, DIG6
  { M3, 8,  BWD, 1, 7, 1, "Corvin-negyed" },  // SEG_B, DIG7
  { M3, 9,  FWD, 1, 0, 2, "Kálvin tér" },  // SEG_C, DIG0
  { M3, 9,  BWD, 1, 1, 2, "Kálvin tér" },  // SEG_C, DIG1
  { M3, 10, FWD, 1, 2, 2, "Ferenciek tere" },  // SEG_C, DIG2
  { M3, 10, BWD, 1, 3, 2, "Ferenciek tere" },  // SEG_C, DIG3
  { M3, 11, FWD, 1, 4, 2, "Deák Ferenc tér" },  // SEG_C, DIG4
  { M3, 11, BWD, 1, 5, 2, "Deák Ferenc tér" },  // SEG_C, DIG5
  { M3, 12, FWD, 1, 6, 2, "Arany János utca" },  // SEG_C, DIG6
  { M3, 12, BWD, 1, 7, 2, "Arany János utca" },  // SEG_C, DIG7
  { M3, 13, FWD, 1, 0, 3, "Nyugati pályaudvar" },  // SEG_D, DIG0
  { M3, 13, BWD, 1, 1, 3, "Nyugati pályaudvar" },  // SEG_D, DIG1
  { M3, 14, FWD, 1, 2, 3, "Lehel tér" },  // SEG_D, DIG2
  { M3, 14, BWD, 1, 3, 3, "Lehel tér" },  // SEG_D, DIG3
  { M3, 15, FWD, 1, 4, 3, "Dózsa György út" },  // SEG_D, DIG4
  { M3, 15, BWD, 1, 5, 3, "Dózsa György út" },  // SEG_D, DIG5
  { M3, 16, FWD, 1, 6, 3, "Árpád híd" },  // SEG_D, DIG6
  { M3, 16, BWD, 1, 7, 3, "Árpád híd" },  // SEG_D, DIG7
  { M3, 17, FWD, 1, 0, 4, "Forgách utca" },  // SEG_E, DIG0
  { M3, 17, BWD, 1, 1, 4, "Forgách utca" },  // SEG_E, DIG1
  { M3, 18, FWD, 1, 2, 4, "Gyöngyösi utca" },  // SEG_E, DIG2
  { M3, 18, BWD, 1, 3, 4, "Gyöngyösi utca" },  // SEG_E, DIG3
  { M3, 19, FWD, 1, 4, 4, "Újpest-városkapu" },  // SEG_E, DIG4
  { M3, 19, BWD, 1, 5, 4, "Újpest-városkapu" },  // SEG_E, DIG5
  { M3, 20, FWD, 1, 6, 4, "Újpest-Központ" },  // SEG_E, DIG6 (terminus)

  // M4
  { M4, 1,  FWD, 1, 0, 5, "Kelenföld vasútállomás" },  // SEG_F, DIG0 (terminus)
  { M4, 2,  FWD, 1, 1, 5, "Bikás park" },  // SEG_F, DIG1
  { M4, 2,  BWD, 1, 2, 5, "Bikás park" },  // SEG_F, DIG2
  { M4, 3,  FWD, 1, 3, 5, "Újbuda-központ" },  // SEG_F, DIG3
  { M4, 3,  BWD, 1, 4, 5, "Újbuda-központ" },  // SEG_F, DIG4
  { M4, 4,  FWD, 1, 5, 5, "Móricz Zsigmond körtér" },  // SEG_F, DIG5
  { M4, 4,  BWD, 1, 6, 5, "Móricz Zsigmond körtér" },  // SEG_F, DIG6
  { M4, 5,  FWD, 1, 0, 6, "Szent Gellért tér" },  // SEG_G, DIG0
  { M4, 5,  BWD, 1, 1, 6, "Szent Gellért tér" },  // SEG_G, DIG1
  { M4, 6,  FWD, 1, 2, 6, "Fővám tér" },  // SEG_G, DIG2
  { M4, 6,  BWD, 1, 3, 6, "Fővám tér" },  // SEG_G, DIG3
  { M4, 7,  FWD, 1, 4, 6, "Kálvin tér" },  // SEG_G, DIG4
  { M4, 7,  BWD, 1, 5, 6, "Kálvin tér" },  // SEG_G, DIG5
  { M4, 8,  FWD, 1, 6, 6, "Rákóczi tér" },  // SEG_G, DIG6
  { M4, 8,  BWD, 1, 7, 6, "Rákóczi tér" },  // SEG_G, DIG7
  { M4, 9,  FWD, 1, 0, 7, "II. János Pál pápa tér" },  // SEG_DP, DIG0
  { M4, 9,  BWD, 1, 1, 7, "II. János Pál pápa tér" },  // SEG_DP, DIG1
  { M4, 10, FWD, 1, 2, 7, "Keleti pályaudvar" },  // SEG_DP, DIG2 (terminus)
};

const uint8_t LED_COUNT = sizeof(LED_MAP) / sizeof(LED_MAP[0]);
