#ifndef	__SR030PC30_REGS_H__
#define __SR030PC30_REGS_H__

typedef struct tagCamReg16 {
	unsigned short value;
} tagCamReg16_t;

/* PV 1st */

tagCamReg16_t sr030pc30_Init_Reg[] = {
0x0300,
0x01f1,
0x01f3,
0x01f1,

0x0320,
0x101c,
0x0322,
0x107b,

//Page0
0x0300,
0x1000,
0x1193, //On Var Frame - None : 90, X Flip : 91, Y Flip :
0x1224,//PCLK Inversion
0x2000,
0x2106,
0x2200,
0x2306,
0x2401,
0x25e0,
0x2602,
0x2780,
0x4001, //Hblank 336
0x4150,

0x4201, //Vblank 336
0x4350,
                     
//BLC
0x803e,
0x8196,
0x8290,
0x8300,
0x842c,

0x900c, //BLC_TIME_TH_ON
0x910c, //BLC_TIME_TH_OFF 
0x92b8, //BLC_AG_TH_ON
0x93b0, //BLC_AG_TH_OFF
0x9488,
0x9580,

0x9820,
0xa040,
0xa241,
0xa440,
0xa641,
0xa844,
0xaa43,
0xac44,
0xae43,

//Page2
0x0302,
0x1000,
0x1300,
0x181C,
0x1900,
0x1a00,
0x1b08,
0x1C00,
0x1D00,
0x2033,
0x21aa,
0x22a6,
0x23b0,
0x3199,
0x3200,
0x3300,
0x343C,
0x5021,
0x5430,
0x56fe,
0x6278,
0x639E,
0x6478,
0x659E,
0x727A,
0x739A,
0x747A,
0x759A,
0x8209,
0x8409,
0x8609,
0xa003,
0xa81D,
0xaa49,
0xb98A,
0xbb8A,
0xbc04,
0xbd10,
0xbe04,
0xbf10,

//Page10
0x0310,//
0x1001,//ISPCTL1
0x1230,//Y offet, dy offseet enable
0x4080,
0x4105,//
0x5078,//

0x601f,
0x6185,
0x6285,
0x63f0,
0x6480,

//Page11
0x0311,
0x1099,
0x1108, //0e,
0x2129,
0x5005,
0x600f,
0x6243,
0x6363,
0x7408,
0x7508,

//Page12
0x0312,
0x4023,
0x413b,
0x5005,
0x701d,
0x7405,
0x7504,
0x7720,
0x7810,
0x9134,
0xb0c9,
0xd0b1,

//Page13
0x0313,
0x103b,
0x1103,
0x1200,
0x1302,
0x1400, //08,

0x2002,
0x2101,
0x2324,
0x2406,
0x2502,
0x2800,
0x29f0,
0x30ff,
0x800D,
0x8113,

0x835d,

0x9003,
0x9102,
0x933d,
0x9403,
0x958f,

//Page14
0x0314,
0x1001,
0x2080,
0x2178,
0x2251, //53,
0x2340,
0x243e,

//Page 15 CmC
0x0315,
0x1003,

0x143c,
0x162c,
0x172f,

0x30cb,
0x3161,
0x3216,
0x3323,
0x34ce,
0x352b,
0x3601,
0x3734,
0x3875,

0x4087,
0x4118,
0x4291,
0x4394,
0x449f,
0x4533,
0x4600,
0x4794,
0x4814,

0x0316,
0x1001,
0x3000,
0x3109,
0x321b,
0x3335,
0x345d,
0x357a,
0x3693,
0x37a7,
0x38b8,
0x39c6,
0x3ad2,
0x3be4,
0x3cf1,
0x3df9,
0x3eff,

//Page20 AE
0x0320,
0x101c,
0x1104,

0x2001,
0x283f,
0x29a3,
0x2af0,
0x2bf4,

0x30f8,

0x60d5,

0x6834,
0x696e,
0x6A28,
0x6Bc8,

0x7034,//Y Target

0x7812,//Yth 1
0x7911,//Yth 2
0x7A23,

0x8300, //EXP Normal 33.33 fps 
0x84af, 
0x85c8,

0x8600,//ExpMin 6000.00 fps
0x87fa,

0x8802,//ExpMax 8fps
0x89bf,
0x8a20,

0x8b3a,//Exp100
0x8c98,

0x8d30,//Exp120
0x8ed4,

0x8f04,
0x9093,

0x9102,
0x92d2,
0x93a8,

0x988C,
0x9923,

0x9c08, //EXP Limit 857.14 fps 
0x9dca, 
0x9e00, //EXP Unit
0x9ffa,

0xb014,
0xb114,
0xb2c0,
0xb314,
0xb41c,
0xb548,
0xb632,
0xb72b,
0xb827,
0xb925,
0xba23,
0xbb22,
0xbc22,
0xbd21,

0xc014,

0xc870,
0xc980,

//Page 22 AWB
0x0322,
0x10e2,
0x1126,
0x2100,

0x3080,
0x3180,
0x3811,
0x3933,
0x40f0,
0x4133,
0x4232,
0x43f3,
0x4455,
0x4544,
0x4602,

0x50d0,
0x51a0,
0x52aa,

0x8040,
0x8120,
0x8238,

0x8354,//54
0x841f,//22 29 27
0x8554,//54 53 50
0x8620,//22

0x8742,
0x883a,
0x8934, //2c, //30,
0x8a2e, //20, //22,

0x8b01,
0x8d22,
0x8e71,

0x8f5c,
0x9059,
0x9156,
0x9252,
0x9346,
0x943f,
0x9537,
0x9633,
0x972c,
0x9823,
0x991c,
0x9a17,
0x9b09,

0x0322,
0x10fb,

0x0320,
0x109c,
0x01f0,

0xff14, //200ms

};

tagCamReg16_t sr030pc30_VT_Init_Reg[] = {
0x0300, 
0x01f1, 
0x01f3, 
0x01f1,

0x0320, 
0x101c, 
0x0322, 
0x107b, 

0x0300, //Page 0
0x1000, //no change(v sync type)
0x1197, //Fixed On(fixed frame enable : BIT 2)
0x1204, //00,
0x2000, 
0x2106, 
0x2200, 
0x2306, 
0x2401, 
0x25e0, 
0x2602, 
0x2780, 
0x4001, //Hblank 336
0x4150, //
0x4200, //Vsync 4
0x4304, //

0x803e, //BLC
0x8196, 
0x8290, 
0x8300, 
0x842c, 
0x900e, 
0x910f, 
0x923a, 
0x9330, 
0x9488, 
0x9580, 
0x9820, 
0xa040, 
0xa241, 
0xa440, 
0xa641, 
0xa844, 
0xaa43, 
0xac44, 
0xae43,

0x0302, //Page 2
0x1000, 
0x1300, 
0x181c, 
0x1900, 
0x1a00, 
0x1b08, 
0x1c00, 
0x1d00, 
0x2033, 
0x21aa, 
0x22a6, 
0x23b0, 
0x3199, 
0x3200, 
0x3300, 
0x343c, 
0x5021, 
0x5430, 
0x56fe, 
0x6278, 
0x639e, 
0x6478, 
0x659e, 
0x727a, 
0x739a, 
0x747a, 
0x759a, 
0x8209, 
0x8409, 
0x8609, 
0xa003, 
0xa81d, 
0xaa49, 
0xb98a, 
0xbb8a, 
0xbc04, 
0xbd10, 
0xbe04, 
0xbf10, 

0x0310, //Page 10
0x1003, //ISPCTL1, YUV ORDER(FIX)
0x1230, //Y offet, dy offseet enable
0x4009, //80
0x4138, //00 DYOFS
0x50ee, 
0x601f, 
0x6190, 
0x6280, 
0x63f0, 
0x6480, 

0x0311, //Page 11
0x1099, 
0x110e, 
0x2129, 
0x5005, 
0x600f, 
0x6243, 
0x6363, 
0x7408, 
0x7508, 

0x0312, //Page 12
0x4023, 
0x413b, 
0x5005, 
0x701d, 
0x7405, 
0x7504, 
0x7720, 
0x7810, 
0x9134, 
0xb0c9, 
0xd0b1, 

0x0313, //Page 13
0x103b, 
0x1103, 
0x1200, 
0x1302, 
0x1418, 
0x2002, 
0x2101, 
0x2324, 
0x2406, 
0x254a, 
0x2800, 
0x2978, 
0x30ff, 
0x800d, 
0x8113, 
0x835d, 
0x9003, 
0x9102, 
0x933d, 
0x9403, 
0x958f, 

0x0314, //Page 14
0x1001, 
0x2080, 
0x2178, 
0x2251, // 53
0x2340, // 40
0x243e, // 3e

0x0315, //Page 15 CMC
0x1003, 
0x143c, 
0x162c, 
0x172f, 
0x30cb, 
0x3161, 
0x3216, 
0x3323, 
0x34ce, 
0x352b, 
0x3601, 
0x3734, 
0x3875, 
0x4087, 
0x4118, 
0x4291, 
0x4394, 
0x449f, 
0x4533, 
0x4600, 
0x4794, 
0x4814, 

0x0316, //page 16 gamma
0x1001, 
0x3000, 
0x3109, // 0b /
0x3217, // 19 /
0x3335, 
0x3460, // 5d /
0x3582, // 7a /
0x3696, // 93 /
0x37a7, 
0x38b8, 
0x39c6, 
0x3ad4, 
0x3be7, 
0x3cf5, 
0x3dfc, 
0x3eff,  

//Page18  image scaling QCIF
0x0318,  
0x1007,  // control image scaling
0x2000,  // H width
0x21C0,  // L width
0x2200,  // H Height
0x2390,  // L Height
0x2400,  // H start x
0x2508,  // L start x
0x2600,  // H start y
0x2700,  // L start y
0x2800,  // H end x
0x29B8,  // L end x
0x2A00,  // H end y
0x2B90,  // L end y
0x2C1A,  // H WID step
0x2DAA,  // L WID step
0x2E1A,  // H HI step
0x2FAA,  // L HI step
0x3060,  // delay

0x0320, //Page 20 AE
0x101c, 
0x1104, 
0x2001, 
0x283f, 
0x29a3, 

0x2a90, 
0x2bf5, 
0x30f8, 
0x60d5, //d5, 99
0x683c, 
0x6964, 
0x6a28, 
0x6bc8, 
0x7034, //30 normal luminance value 42(Y Target)
0x7812, //Yth 1
0x7913, //Yth 2
0x7a23, 

0x8300, //EXP Normal 33.33 fps 
0x84af, 
0x85c8, 
0x8600, //EXPMin 6000.00 fps
0x87fa, 
0x8802, //EXP Max 
0x890f, 
0x8a58, 
0x8b3a, //EXP100 
0x8c98, 
0x8d30, //EXP120 
0x8ed4, 

0x8f04, 
0x9093, 

0x9102, //EXP Fix 10.00 fps
0x9240, 
0x932c,

0x988c, 
0x9923, 
0x9c06, //EXP Limit 857.14 fps 
0x9dd6,
0x9e00, //EXP Unit 
0x9ffa,  
0xb014, 
0xb114, 
0xb2f0, 
0xb314, 
0xb41c, 
0xb548, 
0xb632, 
0xb72b, 
0xb827, 
0xb925, 
0xba23, 
0xbb22, 
0xbc22, 
0xbd21, 
0xc014, 
0xc8f0, //digital global gain 80
0xc980, 

0x0322, //Page 22 AWB
0x10e2, 
0x1126, 
0x2140, 
0x3080, 
0x3180, 
0x3811, 
0x3933, 
0x40f0, 
0x4133, 
0x4233, 
0x43f3, 
0x4455, 
0x4544, 
0x4602, 
0x8045, 
0x8120, 
0x8248, 
0x8362, // RMAX Default : 50
0x841c, //1c 20 1E / // RMIN Default : 20
0x855d, //5b 5e 6a, // BMAX Default : 50
0x861f, // BMIN Default : 20
0x8747, //49, //4a, //50, // RMAXB Default : 50
0x8844, //45, //3e, //40, //45, // RMINB Default : 3e
0x892f, //2d, //2e, //2d, //30, //2d, // BMAXB Default : 2e
0x8a26, //28, //22, // BMINB Default : 20
0x8b00, 
0x8d21, 
0x8e71, 
0x8f63, 
0x9060, 
0x915c, 
0x9259, 
0x9355, 
0x9450, 
0x9548, 
0x963e, 
0x9737, 
0x9830, 
0x9929, 
0x9a26, 
0x9b09, 


0x0322, 
0x10fb, 

0x0320, 
0x109c, 

0x01f0, 


0xff64,  //delay 100ms
  
};

tagCamReg16_t sr030pc30_Preview[]  = {
0x0300,
0x1193,
};

tagCamReg16_t sr030pc30_preview_176x144[] = {
//Page18  image scaling QCIF
0x0300,
0x1000,
0x0318,
0x1007,
0x2000,
0x21C0,
0x2200,
0x2390,
0x2400,
0x2508,
0x2600,
0x2700,
0x2800,
0x29B8,
0x2A00,
0x2B90,
0x2C1A,
0x2DAA,
0x2E1A,
0x2FAA,
0x3060,
0x0313,
0x800c,
0xffc8,
};

tagCamReg16_t sr030pc30_preview_320x240[] = {
//Page18  image scaling CIF
0x0318,
0x1000,
0x0300,
0x1010,
0x0313,
0x800d,
0xffc8,
};

tagCamReg16_t sr030pc30_preview_352x288[] = {
//Page18  image scaling CIF
0x0300,
0x1000,
0x0318,  
0x1007,  // control image scaling
0x2001,  // H width
0x2180,  // L width
0x2201,  // H Height
0x2320,  // L Height
0x2400,  // H start x
0x2510,  // L start x
0x2600,  // H start y
0x2700,  // L start y
0x2801,  // H end x
0x2970,  // L end x
0x2A01,  // H end y
0x2B20,  // L end y     
0x2C0d,  // H WID step
0x2D55,  // L WID step    
0x2E0d,  // H HI step
0x2F55,  // L HI step
0x3060,  // delay
0x0313,
0x800c,
};

tagCamReg16_t sr030pc30_preview_640x360[] = {
0x0300,
0x1000,
0x0318,
0x1007,
0x2002,
0x2180,
0x2201,
0x23e0,
0x2400,
0x2500,
0x2600,
0x273c,
0x2802,
0x2980,
0x2A01,
0x2Ba4,
0x2C08,
0x2D00,
0x2E08,
0x2F00,
0x3060,
0x0313,
0x800c,
0xffc8,
};
tagCamReg16_t sr030pc30_preview_640x480[] = {
//Page18  image scaling CIF
0x0300,
0x1000,
0x0318,
0x1000,
0x0313,
0x800d,
0xffc8,
};

tagCamReg16_t sr030pc30_stop_stream[]  = {
0xff00,
};

tagCamReg16_t sr030pc30_i2c_check[]  = {
0x0300,
0x0100,

0xff0a,

};

tagCamReg16_t sr030pc30_Capture[]  = {
0x0300,
0x1193, /*B[0]_horizontal flip funtion(0:off,1:on)*/
};

tagCamReg16_t sr030pc30_Capture_X_Flip[] = {
0x0300,
0x1191, /*B[0]_horizontal flip funtion(0:off,1:on)*/
};

tagCamReg16_t sr030pc30_Capture_Y_Flip[] = {
0x0300,
0x1192, /*B[1]_vertical flip funtion(0:off,1:on)*/
};

tagCamReg16_t sr030pc30_brightness_M4[] = {
0x0310,
0x40d0,
};

tagCamReg16_t sr030pc30_brightness_M3[] = {
0x0310,
0x40B0,
};

tagCamReg16_t sr030pc30_brightness_M2[] = {
0x0310,
0x40A0,
};

tagCamReg16_t sr030pc30_brightness_M1[] = {
0x0310,
0x4090,
};

tagCamReg16_t sr030pc30_brightness_default[] = {
0x0310,
0x4080,
};

tagCamReg16_t sr030pc30_brightness_P1[] = {
0x0310,
0x4010,
};

tagCamReg16_t sr030pc30_brightness_P2[] = {
0x0310,
0x4020,
};

tagCamReg16_t sr030pc30_brightness_P3[] = {
0x0310,
0x4030,
};

tagCamReg16_t sr030pc30_brightness_P4[] = {
0x0310,
0x4050,
};

tagCamReg16_t sr030pc30_Effect_Normal[] ={
0x0310,
0x1103,
0x1230,
0x0313,
0x103b,
0x2002,
};

tagCamReg16_t sr030pc30_Effect_Negative[] ={
0x0310,
0x1103,
0x1238,
0x0313,
0x103b,
0x2002,
};

tagCamReg16_t sr030pc30_Effect_Gray[] ={
0x0310,
0x1103,
0x1233,
0x4480,
0x4580,
0x0313,
0x103b,
0x2002,
};

tagCamReg16_t sr030pc30_Effect_Sepia[] ={
0x0310,
0x1103,
0x1233,
0x4470,
0x4598,
0x0313,
0x103b,
0x2002,
};

tagCamReg16_t sr030pc30_Effect_Aqua[] ={
0x0310,
0x1103,
0x1233,
0x44b0,
0x4540,
0x0313,
0x103b,
0x2002,
};

//WhiteBalance
tagCamReg16_t sr030pc30_WB_Auto[] = {
0x0322,
0x107b,
0x1126,
0x8040,
0x8120,
0x8238,
0x8354,//54
0x841f,//22 29 27
0x8554,//54 53 50
0x8620,//22 
0x10fb,
};

tagCamReg16_t sr030pc30_WB_Daylight[] = {
0x0322, //MWB Sunny
0x107b,
0x1124,
0x8032, //R Gain
0x8120, //G Gain
0x8237, //B Gain
0x8333, //R Max 
0x8431, //R Min
0x8538, //B Max
0x8635, //B Min
0x10fb,
};

tagCamReg16_t sr030pc30_WB_Cloudy[] = {
0x0322, //MWB Cloudy
0x107b,
0x1124,
0x804f, //R Gain
0x8120, //G Gain
0x8225, //B Gain
0x8353, //R Max
0x8448, //R Min
0x8535, //B Max
0x862b, //B Min
0x10fb,
};

tagCamReg16_t sr030pc30_WB_Fluorescent[] = {
0x0322,
0x107b,
0x1124,
0x8042,
0x8120,
0x8251,
0x834a,
0x843a,
0x8555,
0x8645,
0x10fb,
};

tagCamReg16_t sr030pc30_WB_Incandescent[] = {
0x0322,
0x1074,
0x1126,
0x8020, 
0x8120, 
0x8257, 
0x8321,
0x841d,
0x8559, 
0x8656,
0x10fb,
};

tagCamReg16_t sr030pc30_Auto_fps_normal[] = {
0x0300,
0x0171, //sleep
       
0x0300,
0x1193, //fixed fps disable
0x4201, //Vblank 336
0x4350,

0x900c, //BLC_TIME_TH_ON
0x910c, //BLC_TIME_TH_OFF 
0x9278, //BLC_AG_TH_ON
0x9370, //BLC_AG_TH_OFF

0x0320,
0x101c, //ae off
0x2af0, //antibanding
0x2bf4,
0x30f8,

0x8802, //exp max 8 fps
0x89bf,
0x8a20,

0xb280,

0x0320,                                                           
0x109c, //ae on

0x0300,
0x0170,

0xff28, //delay 400ms
};

tagCamReg16_t sr030pc30_Auto_fps[] = {
0x0300,
0x0171, //sleep

0x0300,
0x1193, //fixed fps disable
0x4201, //Vblank 336
0x4350,
                     
0x900c, //BLC_TIME_TH_ON
0x910c, //BLC_TIME_TH_OFF 
0x9278, //BLC_AG_TH_ON
0x9370, //BLC_AG_TH_OFF

0x0320,
0x101c, //ae off
0x2af0, //antibanding
0x2bf4,
0x30f8,

0x8802, //exp max 8 fps
0x89bf,
0x8a20,

0xb280,

0x0320,
0x109c, //ae on

0x0300,
0x0170,

0xff28, //delay 400ms
};

tagCamReg16_t sr030pc30_Auto_fps_dark[] = {
0x0300,
0x0171, //sleep
       
0x0300,
0x1193, //fixed fps disable
0x4201, //Vblank 336
0x4350,

0x900c, //BLC_TIME_TH_ON
0x910c, //BLC_TIME_TH_OFF 
0x9278, //BLC_AG_TH_ON
0x9370, //BLC_AG_TH_OFF

0x0320,
0x101c, //ae off
0x2af0, //antibanding
0x2bf4,
0x30f8,

0x8302, //EXP Normal 33.33 fps 
0x84b5, 
0x855c,

0x8802, //exp max 8 fps
0x89b5,
0x8a5c,

0xb280,

0x0320,                                                           
0x109c, //ae on

0x0300,
0x0170,

0xff28, //delay 400ms
};

tagCamReg16_t sr030pc30_7fps[] = {
0x0300, //7
0x0171,
0x1197,
0x1488,
0x4001, //Hblank 336
0x4150, 
0x4200, //Vblank 20
0x4314, 
0x0320, //Page 20
0x101c, //AE Off
0x8300, //EXP Normal 33.33 fps 
0x84af, 
0x85c8, 
0x8600, //EXPMin 6000.00 fps
0x87fa, 
0xa003, //EXP Max(100Hz) 7.14 fps 
0xa134, 
0xa250, 
0x8B3a, //EXP100 
0x8C98, 
0x8D30, //EXP120 
0x8Ed4, 
0x9103, //EXP Fix 7.00 fps
0x9244, 
0x93b8, 
0x9c06, //EXP Limit 857.14 fps 
0x9dd6, 
0x9e00, //EXP Unit 
0x9ffa, 
0x109c, // AE on
0x0300,
0x1197, //Fixed enable
0x01f0, //Sleep Off


};

tagCamReg16_t  sr030pc30_10fps[] = { 
0x0300, //7
0x0171,
0x1197,
0x1488,
0x4001, //Hblank 336
0x4150, 
0x4200, //Vblank 20
0x4314, 
0x0320, //Page 20
0x101c, //AE Off
0x8300, //EXP Normal 33.33 fps 
0x84af, 
0x85c8, 
0x8600, //EXPMin 6000.00 fps
0x87fa, 
0xa002, //EXP Max(100Hz) 11.11 fps 
0xa10f, 
0xa258,
0x8B3a, //EXP100 
0x8C98, 
0x8D30, //EXP120 
0x8Ed4, 
0x9102, //EXP Fix 10.00 fps
0x9249, 
0x93f0, 
0x9c06, //EXP Limit 857.14 fps 
0x9dd6, 
0x9e00, //EXP Unit 
0x9ffa, 
0x109c, // AE on
0x0300,
0x1197, //Fixed enable
0x01f0, //Sleep Off


};

tagCamReg16_t sr030pc30_15fps[] = { 
0x0300, //7
0x0171,
0x1197,
0x1488,
0x4001, //Hblank 336
0x4150, 
0x4200, //Vblank 20
0x4314, 
0x0320, //Page 20
0x101c, //AE Off
0x8300, //EXP Normal 33.33 fps 
0x84af, 
0x85c8, 
0x8600, //EXPMin 6000.00 fps
0x87fa, 
0xa001, //EXP Max(100Hz) 16.67 fps 
0xa15f, 
0xa290,
0x8B3a, //EXP100 
0x8C98, 
0x8D30, //EXP120 
0x8Ed4, 
0x9101, //EXP Fix 14.30 fps
0x9299, 
0x93c4, 
0x9c06, //EXP Limit 857.14 fps 
0x9dd6, 
0x9e00, //EXP Unit 
0x9ffa, 
0x109c, // AE on
0x0300,
0x1197, //Fixed enable
0x01f0, //Sleep Off


};

tagCamReg16_t sr030pc30_20fps[]  = {
0x0300, //7
0x0171,
0x1197,
0x1488,
0x4001, //Hblank 336
0x4150, 
0x4200, //Vblank 2
0x4302, 
0x0320, //Page 20
0x101c, //AE Off

0x8600, //EXPMin 6000.00 fps
0x87fa, 
0x8800, //EXP Max 25.00 fps 
0x89ea, 
0x8a60, 
0x8B3a, //EXP100 
0x8C98, 
0x8D30, //EXP120 
0x8Ed4, 
0x9101, //EXP Fix 19.02 fps
0x9233, 
0x9321, 
0x9c06, //EXP Limit 857.14 fps 
0x9dd6, 
0x9e00, //EXP Unit 
0x9ffa, 
0x109c, // AE on
0x0300,
0x1197, //Fixed enable
0x01f0, //Sleep Off


};

tagCamReg16_t sr030pc30_15fps_60Hz[]  = {
0x0300,
0x0171,
0x1197,
0x1488,

0x4000, //Hblank 144
0x4190,
0x4200, //Vblank 20
0x4314,

0x9007, //BLC_TIME_TH_ON
0x9107, //BLC_TIME_TH_OFF
0x9298, //BLC_AG_TH_ON
0x9390, //BLC_AG_TH_OFF

0x0320, //Page 20
0x100c,

0x2a90,
0x2bf5,
0x30f8,

0x8300, //EXP Normal 30.00 fps 
0x84c3, 
0x8550, 

0x8801, //EXP Max(120Hz) 17.14 fps 
0x8955, 
0x8acc, 

0x9101, //EXP Fix 15.00 fps
0x9286, 
0x93a0, 

0x108c,
0x0300,
0x0170,

0xff28,//100ms delay
};

tagCamReg16_t sr030pc30_20fps_60Hz[]  = {
0x0300,
0x0171,
0x1197,
0x1488,

0x4000, //Hblank 144
0x4190,
0x4200, //Vblank 20
0x4314,

0x9005, //BLC_TIME_TH_ON
0x9105, //BLC_TIME_TH_OFF
0x9298, //BLC_AG_TH_ON
0x9390, //BLC_AG_TH_OFF

0x0320, //Page 20
0x100c,

0x2a90,
0x2bf5,
0x30f8,

0x8300, //EXP Normal 30.00 fps
0x84c3,
0x8550,

0x8800, /*EXP Max(120Hz) 24.00 fps*/
0x89f4,
0x8a24,

0x9101, //EXP Fix 20.00 fps
0x9224,
0x93f8,

0x108c,
0x0300,
0x0170,

0xff28,//100ms delay
};

tagCamReg16_t sr030pc30_saturation_m2[] = {

0x0310,
0x12f0,
0x4210,
0x4300,

};

tagCamReg16_t sr030pc30_saturation_m1[] = {

0x0310,      
0x12f0,       
0x4208,       
0x4300,

};

tagCamReg16_t sr030pc30_saturation_default[] = {

0x0310,       
0x1230,       
0x4200,       
0x4300,

};

tagCamReg16_t sr030pc30_saturation_p1[] = {

0x0310,       
0x12f0,       
0x4200,       
0x4308

};

tagCamReg16_t sr030pc30_saturation_p2[] = {

0x0310,
0x12f0,
0x4200,
0x4310,

};

tagCamReg16_t sr030pc30_contrast_m2[] = {

0x0316,
0x1001,
0x3000,
0x3109,
0x320f,
0x331b,
0x3430,
0x3545,
0x365a,
0x376d,
0x3880,
0x3993,
0x3aa3,
0x3bc2,
0x3cdb,
0x3df0,
0x3eff,

};

tagCamReg16_t sr030pc30_contrast_m1[] = {

0x0316,
0x1001,
0x3000,
0x310c,
0x3213,
0x3321,
0x343b,
0x3553,
0x3669,
0x377e,
0x3892,
0x39a4,
0x3ab4,
0x3bd0,
0x3ce5,
0x3df4,
0x3eff,

};

tagCamReg16_t sr030pc30_contrast_default[] = {

0x0316,
0x1001,
0x3000,
0x3109,
0x321b,
0x3335,
0x345d,
0x357a,
0x3693,
0x37a7,
0x38b8,
0x39c6,
0x3ad2,
0x3be4,
0x3cf1,
0x3df9,
0x3eff,

};

tagCamReg16_t sr030pc30_contrast_p1[] = {
0x0316,
0x1001,
0x3000,
0x3110,
0x321c,
0x3334,
0x3460,
0x3585,
0x36a3,
0x37bb,
0x38cc,
0x39da,
0x3ae5,
0x3bf2,
0x3cf9,
0x3dfd,
0x3eff,

};

tagCamReg16_t sr030pc30_contrast_p2[] = {
0x0316,
0x1001,
0x3000,
0x3110,
0x3226,
0x3352,
0x3499,
0x35c5,
0x36de,
0x37ed,
0x38f5,
0x39f9,
0x3afc,
0x3bfe,
0x3cff,
0x3dff,
0x3eff,

};

tagCamReg16_t sr030pc30_DTP_On[] = {
0x0300, // 0 Page
0x5005, //Internal Image

0x0300, //0 page
0x8006,//BLC Off

0x0310,
0x1200, //YOFS DYOFS disable

0x0311, //11page
0x1098,//Z-LPF Off

0x0312, //12page
0x4020,//yc2d LPF Off
0x701c,//G-LPF Off

0x0313, //13page
0x103a,//Sharp Off

0x0313, //13page 
0x800c,//Sharp 2D Off 

0x0314, //14page 
0x1000,//Shading Off 

0x0315, //15page 
0x1002,//CMC Off 

0x0316, //16page 
0x1000,//Gamma Off

0x0320, //20page 
0x100c,//AE Off

0x0322, //22page 
0x107b,//AWB Off
};

tagCamReg16_t sr030pc30_DTP_Off[] = {
0x0300, // 0 Page 
0x5000, //Normal Image 

0x0300, //0 page 
0x800e, 

0x0310, 
0x1230, //YOFS DYOFS enable 

0x0311, //11page 
0x1099, 

0x0312, //12page 
0x4023, 
0x701d, 

0x0313, //13page 
0x103b, 

0x0313, //13page 
0x800d, 

0x0314, //14page 
0x1001, 

0x0315, //15page 
0x1003, 

0x0316, //16page 
0x1001, 

0x0320, //20page 
0x108c, 

0x0322, //22page 
0x10fb,
};
#endif
