const uint8_t a3bpm = 178;
const int a3start = 1095; //milliseconds when song starts
const float a3t = 337.08f; //milliseconds between beats

const PROGMEM uint8_t a3dPos[] = {0, 7, 6, 5, 4, 3, 1, 0, 0,
2, 3, 2, 7, 5, 6, 4, 3,
6, 1, 0, 6, 1, 3, 2,
3, 4, 5, 6, 7, 6, 5, 4, 3, 2,
0, 0, 4, 4, 6, 2, 2, 3, 4, 6,
6, 6, 0, 4, 5, 3, 7, 1, 5,
3, 3, 3, 5, 1, 1, 1, 7, 0,
4, 4, 4, 5, 3, 7, 6, 2, 2,
2, 1, 5, 1, 1, 1, 4, 0, 3,
7, 7, 7, 6, 6, 5, 4, 3,
3, 2, 1, 6, 6, 5, 4, 0,
3, 2, 1, 4, 0, 1, 7, 0, 0,
0, 4, 3, 2, 1, 7, 6, 5, 4,
3, 2, 1, 4, 4, 4, 5, 5, 5,
3, 1, 2, 2,
0, 3, 5, 7, 1, 5, 1, 5,
4, 1, 7, 5, 3, 7, 3, 7,
0, 5, 3, 1, 2, 6, 2, 6,
5, 4, 0, 1, 0, 4, 5,
7, 3, 7, 3, 0, 1, 2, 3,
7, 6, 0, 0, 0};

const PROGMEM unsigned long int a3dTime[] = {a3start, a3start+a3t*2, a3start+a3t*2.5, a3start+a3t*4.5, a3start+a3t*7, a3start+a3t*9.2, a3start+a3t*13.25, a3start+a3t*16, a3start+a3t*18,
a3start+a3t*21.75, a3start+a3t*24, a3start+a3t*28, a3start+a3t*31.25, a3start+a3t*32.25, a3start+a3t*33.25, a3start+a3t*34.5, a3start+a3t*36.25,
a3start+a3t*38.25, a3start+a3t*39.75, a3start+a3t*41.75, a3start+a3t*44.25, a3start+a3t*49.25, a3start+a3t*50, a3start+a3t*52.25,
a3start+a3t*59.5, a3start+a3t*60.5, a3start+a3t*61.5, a3start+a3t*62.5, a3start+a3t*63.5, a3start+a3t*65.25, a3start+a3t*66.25, a3start+a3t*68.25, a3start+a3t*70.75, a3start+a3t*72.5,
a3start+a3t*75.25, a3start+a3t*76.25, a3start+a3t*80.25, a3start+a3t*81.75, a3start+a3t*85.25, a3start+a3t*86.25, a3start+a3t*88.75, a3start+a3t*90.75, a3start+a3t*92.75, a3start+a3t*92.25,
a3start+a3t*95.25, a3start+a3t*96.25, a3start+a3t*97.5, a3start+a3t*99.25, a3start+a3t*103.5, a3start+a3t*104.75, a3start+a3t*105.75, a3start+a3t*107, a3start+a3t*108.25,
a3start+a3t*110.25, a3start+a3t*111.75, a3start+a3t*114.75, a3start+a3t*116.75, a3start+a3t*118.25, a3start+a3t*119.25, a3start+a3t*120.25, a3start+a3t*121.75, a3start+a3t*129.75,
a3start+a3t*134.25, a3start+a3t*135.75, a3start+a3t*137.25, a3start+a3t*138.25, a3start+a3t*139.25, a3start+a3t*140.25, a3start+a3t*141.75, a3start+a3t*142.25, a3start+a3t*144.25,
a3start+a3t*145.75, a3start+a3t*146.75, a3start+a3t*148.75, a3start+a3t*150.25, a3start+a3t*151.25, a3start+a3t*152.25, a3start+a3t*153.5, a3start+a3t*154.75, a3start+a3t*156.75,
a3start+a3t*158.25, a3start+a3t*159.25, a3start+a3t*160.25, a3start+a3t*161.5, a3start+a3t*163, a3start+a3t*166.75, a3start+a3t*167.25, a3start+a3t*169.75,
a3start+a3t*173.75, a3start+a3t*175.25, a3start+a3t*176.25, a3start+a3t*177.75, a3start+a3t*181.75, a3start+a3t*183.25, a3start+a3t*184.75, a3start+a3t*186.25,
a3start+a3t*190.25, a3start+a3t*192, a3start+a3t*193.75, a3start+a3t*200.25, a3start+a3t*201.75, a3start+a3t*203, a3start+a3t*204.25, a3start+a3t*206.25, a3start+a3t*210,
a3start+a3t*213.75, a3start+a3t*215, a3start+a3t*216.5, a3start+a3t*218, a3start+a3t*220, a3start+a3t*225.75, a3start+a3t*227.25, a3start+a3t*228.75, a3start+a3t*230,
a3start+a3t*233.25, a3start+a3t*237.75, a3start+a3t*241.75, a3start+a3t*245.75, a3start+a3t*247.75, a3start+a3t*249.75, a3start+a3t*254.25, a3start+a3t*256.25, a3start+a3t*257.25,
a3start+a3t*258.5, a3start+a3t*259.75, a3start+a3t*263, a3start+a3t*266.75,
a3start+a3t*270.25, a3start+a3t*271.25, a3start+a3t*272.25, a3start+a3t*273, a3start+a3t*273.75, a3start+a3t*274.75, a3start+a3t*275.75, a3start+a3t*276.75,
a3start+a3t*277.75, a3start+a3t*279.25, a3start+a3t*280.25, a3start+a3t*281.25, a3start+a3t*281.75, a3start+a3t*282.75, a3start+a3t*283.75, a3start+a3t*284.75,
a3start+a3t*286.25, a3start+a3t*287.25, a3start+a3t*288.25, a3start+a3t*289.25, a3start+a3t*289.75, a3start+a3t*290.75, a3start+a3t*291.75, a3start+a3t*292.75,
a3start+a3t*294.25, a3start+a3t*296.5, a3start+a3t*299.25, a3start+a3t*302.25, a3start+a3t*303.25, a3start+a3t*304.25, a3start+a3t*305.25,
a3start+a3t*305.75, a3start+a3t*306.75, a3start+a3t*307.75, a3start+a3t*308.75, a3start+a3t*309.75, a3start+a3t*311, a3start+a3t*312, a3start+a3t*313,
a3start+a3t*314.25, a3start+a3t*315.25, a3start+a3t*318.5, a3start+a3t*320.25, a3start+a3t*322.75};