const uint8_t a2bpm = 135;
const int a2start = 600; //milliseconds when song starts
const float a2t = 444.44f; //milliseconds between beats

//const PROGMEM int a2dPos[] = {50, 50, 100, 100, 150, 150, 200, 200, 250, 250, 200, 250, 150, 250, 150, 200, 150, 100, 150, 150, 100, 150, 200, 250, 100, 150, 250, 100, 100, 250};

const PROGMEM uint8_t a2dPos[] = {0, 7, 1, 1, 0, 2, 5, 2, 4, 3, 2, 3, 5, 6, 2, 3,
0, 2, 1, 5, 6, 2, 4, 3, 0, 4, 3, 2, 6, 5, 7, 1, 5, 3,
0, 3, 6, 5, 7, 2, 3, 2, 7, 1, 0, 2, 4, 0, 7, 0, 2, 5,
0, 1, 2, 4, 3, 5, 7, 6,
0, 4, 2, 6, 7, 3, 1, 5, 1, 2, 5, 6, 7, 4, 5, 0,
0, 1, 0, 0, 3, 3, 4, 5, 7, 5, 3, 5, 6, 2, 1, 0, 6, 7, 0, 4,
0, 1, 2, 3, 1, 0, 7, 5, 6, 4, 3, 5, 0, 2, 6, 0,
3, 5, 6, 1, 2, 0, 3, 7, 5, 6, 1, 0, 7, 3, 4, 5,
4, 5, 1, 0, 3, 2, 6, 5, 3, 4, 1, 0, 7, 3, 5, 4,
0, 2, 6, 5, 3, 4, 7, 0, 2, 3, 5, 7, 2, 0, 5, 3,
0, 1, 2, 3, 4, 7, 6, 5, 4, 0, 1, 2, 3, 0, 7, 5, 2, 3,
2, 3, 1, 7, 4, 2, 3, 1, 0, 2, 1, 5,
3, 2, 1, 5, 6, 4, 3, 2, 4, 3,
0, 1, 5, 2, 3, 4, 1, 0, 2, 7, 6, 0,
2, 1, 3, 4, 1, 2, 5, 1, 3, 6, 5, 4, 7, 0, 2, 1,
6, 5, 4, 1, 0, 1, 3, 2, 7, 0, 4, 5, 3, 7, 5, 4, 2, 1,
2, 5, 4, 2,
5, 0, 1, 2, 3, 5, 7, 1, 2, 4, 2, 6};

//const PROGMEM unsigned long int a2dTime[] = {1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000};

const PROGMEM unsigned long int a2dTime[] = {a2start+a2t*0, a2start+a2t*2, a2start+a2t*4, a2start+a2t*6, a2start+a2t*9, a2start+a2t*14, a2start+a2t*15.5, a2start+a2t*16.5,
a2start+a2t*17.5, a2start+a2t*19, a2start+a2t*20, a2start+a2t*24, a2start+a2t*25, a2start+a2t*26, a2start+a2t*27, a2start+a2t*27.5, a2start+a2t*28,
a2start+a2t*29, a2start+a2t*30, a2start+a2t*31, a2start+a2t*31.5, a2start+a2t*32, a2start+a2t*33, a2start+a2t*34, a2start+a2t*35, a2start+a2t*35.5,
a2start+a2t*36, a2start+a2t*37, a2start+a2t*38, a2start+a2t*39, 
a2start+a2t*40, a2start+a2t*41, a2start+a2t*42, a2start+a2t*42.5, a2start+a2t*43, a2start+a2t*44, a2start+a2t*45, a2start+a2t*46,
a2start+a2t*48, a2start+a2t*49, a2start+a2t*50, a2start+a2t*50.5, a2start+a2t*51, a2start+a2t*52, a2start+a2t*53, a2start+a2t*54, a2start+a2t*54.5, a2start+a2t*55,
a2start+a2t*56, a2start+a2t*57, a2start+a2t*58, a2start+a2t*60, a2start+a2t*61, a2start+a2t*62, a2start+a2t*62.5, a2start+a2t*63,
a2start+a2t*64, a2start+a2t*65, a2start+a2t*66, a2start+a2t*68, a2start+a2t*69, a2start+a2t*70, a2start+a2t*70.5, a2start+a2t*71,
a2start+a2t*72, a2start+a2t*73, a2start+a2t*74, a2start+a2t*76, a2start+a2t*77, a2start+a2t*78, a2start+a2t*78.5, a2start+a2t*79,
a2start+a2t*80, a2start+a2t*81, a2start+a2t*82, a2start+a2t*84, a2start+a2t*85, a2start+a2t*86, a2start+a2t*86.5, a2start+a2t*87,
a2start+a2t*88, a2start+a2t*89, a2start+a2t*89.5, a2start+a2t*90, a2start+a2t*95, a2start+a2t*96, a2start+a2t*97, a2start+a2t*98, a2start+a2t*98.5,
a2start+a2t*100, a2start+a2t*100.5, a2start+a2t*101, a2start+a2t*101.5, a2start+a2t*103, a2start+a2t*104,
a2start+a2t*105, a2start+a2t*105.5, a2start+a2t*108, a2start+a2t*109, a2start+a2t*109.5,
a2start+a2t*112, a2start+a2t*113, a2start+a2t*114, a2start+a2t*116, a2start+a2t*117, a2start+a2t*118,
a2start+a2t*120, a2start+a2t*121, a2start+a2t*122, a2start+a2t*123, a2start+a2t*124, a2start+a2t*125, a2start+a2t*126, a2start+a2t*127,
a2start+a2t*128, a2start+a2t*128.5, a2start+a2t*129, a2start+a2t*129.5, a2start+a2t*130, a2start+a2t*130.5, a2start+a2t*131, a2start+a2t*131.5, a2start+a2t*132,
a2start+a2t*133, a2start+a2t*135,
a2start+a2t*136, a2start+a2t*137, a2start+a2t*137.75, a2start+a2t*138.25, a2start+a2t*139, a2start+a2t*140,
a2start+a2t*141, a2start+a2t*142.5, a2start+a2t*143, a2start+a2t*143.75};
