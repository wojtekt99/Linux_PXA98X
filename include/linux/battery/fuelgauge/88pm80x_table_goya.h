#ifndef __88PM80X_TABLE_H
#define __88PM80X_TABLE_H

/* We assume 3000mV is the power off voltage */
#define POWER_OFF_THRESHOLD			(3350)
#define SAFE_POWER_OFF_THRESHOLD		(3000)

/* temperature for goldenve */
/* -10       89.4050     93.5136     97.7229 */
#define TBAT_M10C	94	/* -10C: 93.5136k ohm */
/* 0        57.5058     59.8810     62.2981 */
#define TBAT_0C		60	/* 0C: 59.8810k ohm */
/* 20       25.7312     26.5772     27.4263 */
#define TBAT_20C	27	/* 20C: 26.5772k ohm */
/* 35       14.7729     15.2854     15.8013 */
#define TBAT_35C	15	/* 35C: 15.2854k ohm */
/* 45       10.4184     10.8172     11.2211 */
#define TBAT_45C	11	/* 45C: 10.8172k ohm */

/* -25C ~ 60C: multipled by 10000 */
static int temperature_table[] = {
	/* -25 ~ -21 */
	1926293, 1831332, 1741659, 1656946, 1576891,
	/* -20 ~ -11*/
	1501207, 1429795, 1362219, 1298249, 1237673, 1180290, 1125914, 1074369, 1025491, 979128,
	/* -10 ~ -1 */
	935136, 893194, 853391, 815603, 779718, 745628, 713233, 682439, 653159, 625308,
	/* 0 ~ 9 */
	598810, 573672, 549729, 526920, 505183, 484463, 464707, 445864, 427888, 410735,
	/* 10 ~ 19 */
	394361, 378705, 363758, 349483, 335847, 322818, 310365, 298460, 287077, 276188,
	/* 20 ~ 29 */
	265772, 255819, 246284, 237149, 228393, 220000, 211953, 204236, 196834, 189733,
	/* 30 ~ 39 */
	182920, 176398, 170142, 164140, 158381, 152854, 147547, 142452, 137558, 132857,
	/* 40 ~ 49 */
	128340, 123985, 119798, 115771, 111898, 108172, 104587, 101136, 97815, 94618,
	/* 50 ~ 59 */
	91539, 88576, 85721, 82972, 80322, 77769, 75308, 72935, 70648, 68442,
	/* 60 ~ 65 */
	66314, 64292, 62342, 60461, 58646, 56895
};

/*
 * Battery parameters from battery vendor for fuel gauge.
 * For SS aruba battery paramters, the extraction was
 * performed at T=25C and with ICHG=IDIS=0.5A, they are:
 * Rs = 0.11 Ohm + 0.01 Ohm;
 * R1 = 0.04 Ohm;
 * R2 = 0.03 Ohm;
 * C1 = 1000F
 * C2 = 10000F
 * Csoc = 5476F (Qtot = 5476C)
 */

/* we use m-Ohm by *1000 for calculation */
static int r1 = 40;
static int r2 = 30;
static int r_s = 120;
static int rtot;
static int c1 = 1000;
static int c2 = 10000;
//static int c_soc = 6286;
//static int c_soc = 5868; //SSG env batt 3
//static int c_soc = 14000; //Asus battery
static int c_soc = 12960; //Goya 3600 mAh battery
//static int c_soc_Tm10 = 5400; //GoldenVE battery capacity at T=-10
//static int c_soc_T0 = 5400; //GoldenVE battery capacity at T=-20
//static int K_T = 1; // c_soc / c_soc(T)

static int r_off_initial = 32;
//static int r_off = 80; //new value obtained with adaptive method
static int r_off = 32; // Value used for Samsung setup (external battery)
static int deltaR_to_store;
static int short_slp_counter = 0; // to take in account of slp_cnt = 1 sec in SSG environment
/*
 * v1, v2 is voltage, the unit of orignal formula design is "Volt",
 * since we can not do float calculation, we introduce the factor of
 * 1024 * 1024 to enlarge the resolution for LSB, the value of it is
 * "Volt with factor" in the driver.
 *
 * v1 and v2 are signded variable, normally, for charging case they
 * are negative value, for discharging case, they are positive value.
 *
 * v3 is SOC, original formular is 0~1, since we can not do float
 * calculation, for improve the resolution of it, the range value
 * is enlarged  by multiply 10000 in v3_res, but we report
 * v3 = v3_res/1000 to APP/Android level.
 */
static int v1, v2, v3, cap = 100;
static int factor = 1024 * 1024;
static int factor2 = 1000;
//static int count_cap = 0;
static int ib_adaptive = 0;
static int term1,term2,term3 = 0;
static int adaptive_gain_x_I0 = 125000;
static int first_long_sleep_flag_adaptive = 0;
static int deltaR = 0;
static int v1_mv, v2_mv, v3_res, v3_res_t1, v3_res_t2;
static int deltat_t2mt1, delta_soc_t1mt2, delta_soc_t1mt3;
static int vbat_mv;
static int t1_start;

static int G_T0 = 1;
static int Off_T0 = 0;
static int G_Tm10 = 25;
static int Off_Tm10 = -150;

/*
 * LUT of exp(-x) function, we need to calcolate exp(-x) with x=SLEEP_CNT/RC,
 * Since 0<SLEEP_CNT<1000 and RCmin=20 we should calculate exp function in [0-50]
 * Because exp(-5)= 0.0067 we can use following approximation:
 *	f(x)= exp(-x) = 0   (if x>5);
 * 20 points in [0-5] with linear interpolation between points.
 *  [-0.25, 0.7788] [-0.50, 0.6065] [-0.75, 0.4724] [-1.00, 0.3679]
 *  [-1.25, 0.2865] [-1.50, 0.2231] [-1.75, 0.1738] [-2.00, 0.1353]
 *  [-2.25, 0.1054] [-2.50, 0.0821] [-2.75, 0.0639] [-3.00, 0.0498]
 *  [-3.25, 0.0388] [-3.50, 0.0302] [-3.75, 0.0235] [-4.00, 0.0183]
 *  [-4.25, 0.0143] [-4.50, 0.0111] [-4.75, 0.0087] [-5.00, 0.0067]
 */
static int exp_data[] = {
	7788, 6065, 4724, 3679,
	2865, 2231, 1738, 1353,
	1054, 821,  639,  498,
	388,  302,  235,  183,
	143,  111,  87,   67 };

/*
 * State of Charge.
 * The first number is voltage, the second number is soc point.
 */
#if 0
static int ocv_table[] = {
 3217, 3347, 3438, 3505, 3551, 3582, 3610, 3636, 3658, 3675,
 3686, 3693, 3699, 3705, 3713, 3723, 3732, 3741, 3748, 3754,
 3759, 3765, 3769, 3772, 3774, 3776, 3778, 3779, 3780, 3781,
 3782, 3783, 3784, 3785, 3786, 3788, 3790, 3792, 3794, 3797,
 3800, 3803, 3806, 3809, 3813, 3817, 3821, 3825, 3830, 3834,
 3840, 3845, 3851, 3858, 3866, 3875, 3886, 3896, 3906, 3915,
 3925, 3933, 3942, 3950, 3958, 3966, 3974, 3982, 3990, 3999,
 4008, 4017, 4026, 4036, 4046, 4056, 4066, 4076, 4086, 4096,
 4107, 4117, 4128, 4139, 4150, 4161, 4172, 4184, 4195, 4207,
 4218, 4230, 4242, 4254, 4266, 4278, 4290, 4302, 4314, 4326 };
#else
static int ocv_dischg[] = {
3373, 3474, 3545, 3598, 3640, 3670, 3683, 3688, 3690, 3692,
3694, 3696, 3701, 3708, 3715, 3719, 3724, 3729, 3734, 3738,
3742, 3745, 3748, 3751, 3755, 3759, 3763, 3767, 3771, 3774,
3778, 3782, 3785, 3788, 3791, 3794, 3797, 3800, 3803, 3806,
3809, 3813, 3816, 3820, 3824, 3828, 3832, 3836, 3840, 3845,
3850, 3854, 3860, 3865, 3871, 3877, 3883, 3890, 3898, 3906,
3916, 3926, 3937, 3948, 3958, 3967, 3976, 3984, 3993, 4001,
4010, 4018, 4027, 4037, 4047, 4056, 4066, 4075, 4084, 4094,
4104, 4114, 4125, 4135, 4145, 4156, 4167, 4177, 4188, 4199,
4210, 4221, 4233, 4244, 4256, 4267, 4279, 4291, 4303, 4316, 4320 };


static int ocv_chg[] = { //Goya battery
3373, 3474, 3545, 3598, 3640, 3670, 3683, 3688, 3690, 3692,
3694, 3696, 3701, 3708, 3715, 3719, 3724, 3729, 3734, 3738,
3742, 3745, 3748, 3751, 3755, 3759, 3763, 3767, 3771, 3774,
3778, 3782, 3785, 3788, 3791, 3794, 3797, 3800, 3803, 3806,
3809, 3813, 3816, 3820, 3824, 3828, 3832, 3836, 3840, 3845,
3850, 3854, 3860, 3865, 3871, 3877, 3883, 3890, 3898, 3906,
3916, 3926, 3937, 3948, 3958, 3967, 3976, 3984, 3993, 4001,
4010, 4018, 4027, 4037, 4047, 4056, 4066, 4075, 4084, 4094,
4104, 4114, 4125, 4135, 4145, 4156, 4167, 4177, 4188, 4199,
4210, 4221, 4233, 4244, 4256, 4267, 4279, 4291, 4303, 4316, 4320 };


#endif
/*
 * The rtot(Rtotal) of battery is much different in different temperature,
 * so we introduced data in different temperature, the typical sample point
 * of temperature are -5/10/25/40 C.
 * For charging case, we support the data of charging current of 1200 mA
 * in those temperatures, so we have 4 table for it.
 * For discharging case, we have data 500/1000/1500 mA discharging current
 * case, then we have 12 tables for it.
 */
static int rtot_tm20_i0p15[] = {//GoldenVE battery, modified from 68 to 100
3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000,
3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000};

static int rtot_tm20_i0p3[] = {//GoldenVE battery, modified from 68 to 100
2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500,
2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500,
2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500,
2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500,
2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500,
2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500,
2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500,
2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500,
2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500,
2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500, 2500};

static int rtot_tm20_i0p5[] = {//GoldenVE battery
2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000,
2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000, 2000};
/*
static int rtot_tm20_i0p5[] = {//GoldenVE battery
10500, 10500, 10500, 10500, 10500, 10500, 10500, 10500, 10500, 10500,
10500, 10500, 10500, 10500, 10500, 10500, 9600, 8790, 8060, 7390,
6780, 6230, 5730, 5280, 4870, 4510, 4190, 3900, 3640, 3420,
3220, 3040, 2880, 2790, 2650, 2540, 2460, 2380, 2320, 2270,
2220, 2180, 2140, 2110, 2080, 2050, 2020, 2000, 1970, 1950,
1930, 1920, 1900, 1890, 1870, 1860, 1860, 1850, 1850, 1850,
1850, 1860, 1860, 1850, 1850, 1850, 1840, 1840, 1840, 1830,
1820, 1810, 1800, 1810, 1820, 1840, 1850, 1860, 1860, 1850,
1840, 1850, 1840, 1840, 1840, 1840, 1840, 1840, 1840, 1840,
1840, 1840, 1840, 1840, 1840, 1840, 1840, 1840, 1840, 1840};
*/
static int rtot_tm20_i0p7[] = {//GoldenVE battery
1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,
1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,
1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,
1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,
1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,
1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,
1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,
1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,
1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500,
1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500, 1500};

static int rtot_tm20_i1p0[] = {//GoldenVE battery, equal to 0.7
1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300,
1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300, 1300};

static int rtot_tm20_i1p5[] = {// da modificare, ottenuto con interpolazione
1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100,
1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100,
1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100,
1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100,
1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100,
1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100,
1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100,
1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100,
1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100,
1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100, 1100};

static int rtot_tm5_i0p15[] = {//GoldenVE battery, modified from 68 to 100.
2200, 1000, 750, 650, 500, 500, 500, 500, 500, 500,
500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
500, 500, 500, 500, 500, 500, 500, 500, 500, 500,
500, 500, 500, 500, 500, 500, 500, 500, 500, 500};

static int rtot_tm5_i0p3[] = {//GoldenVE battery, modified from 78 to 100
2100, 950, 650, 500, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400};
/*
966, 950, 935, 920, 907, 893, 881, 869, 858, 847,
837, 828, 819, 812, 805, 799, 794, 789, 785, 781,
780, 778, 776, 777, 779, 783, 789, 802, 818, 835,
851, 865, 873, 878, 881, 882, 880, 877, 866, 850,
838, 834, 835, 841, 858, 880, 896, 895, 895, 895,
895, 895, 895, 895, 895, 895, 895, 895, 895, 895,
895, 895, 895, 895, 895, 895, 895, 895, 895, 895};*/

static int rtot_tm5_i0p5[] = {//GoldenVE battery
1500, 900, 600, 500, 350, 350, 350, 350, 350, 350,
350, 350, 350, 350, 350, 350, 350, 350, 350, 350,
350, 350, 350, 350, 350, 350, 350, 350, 350, 350,
350, 350, 350, 350, 350, 350, 350, 350, 350, 350,
350, 350, 350, 350, 350, 350, 350, 350, 350, 350,
350, 350, 350, 350, 350, 350, 350, 350, 350, 350,
350, 350, 350, 350, 350, 350, 350, 350, 350, 350,
350, 350, 350, 350, 350, 350, 350, 350, 350, 350,
350, 350, 350, 350, 350, 350, 350, 350, 350, 350,
350, 350, 350, 350, 350, 350, 350, 350, 350, 350};

static int rtot_tm5_i0p7[] = {//GoldenVE battery
1800, 800, 600, 500, 400, 300, 300, 300, 300, 300,
300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
300, 300, 300, 300, 300, 300, 300, 300, 300, 300,
300, 300, 300, 300, 300, 300, 300, 300, 300, 300};

static int rtot_tm5_i1p0[] = {//GoldenVE battery
1300, 700, 500, 350, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250};

static int rtot_tm5_i1p5[] = {
1250, 700, 500, 300, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250,
250, 250, 250, 250, 250, 250, 250, 250, 250, 250};


static int rtot_tm5_i0p3c[] = {//GoldenVE battery
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600};

static int rtot_tm5_i0p5c[] = {//GoldenVE battery
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600};

static int rtot_tm5_i0p7c[] = {
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600};

static int rtot_tm5_i1p0c[] = {
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600,
600, 600, 600, 600, 600, 600, 600, 600, 600, 600};

static int rtot_t10_i0p15[] = {//GoldenVE battery, modified from 73 t0 100
1100, 800, 400, 367, 347, 337, 337, 337, 327, 327,
327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
327, 327, 327, 327, 327, 327, 327, 327, 327, 327,
327, 327, 327, 327, 327, 327, 327, 327, 327, 327};

static int rtot_t10_i0p3[] = {//GoldenVE battery, modified from 78 to 100
1200, 750, 400, 342, 332, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230};

static int rtot_t10_i0p5[] = {//GoldenVE battery, modified from 78 to 100
1200, 650, 350, 242, 232, 200, 180, 180, 180, 180,
180, 180, 180, 180, 180, 180, 180, 180, 180, 180,
180, 180, 180, 180, 180, 180, 180, 180, 180, 180,
180, 180, 180, 180, 180, 180, 180, 180, 180, 180,
180, 180, 180, 180, 180, 180, 180, 180, 180, 180,
180, 180, 180, 180, 180, 180, 180, 180, 180, 180,
180, 180, 180, 180, 180, 180, 180, 180, 180, 180,
180, 180, 180, 180, 180, 180, 180, 180, 180, 180,
180, 180, 180, 180, 180, 180, 180, 180, 180, 180,
180, 180, 180, 180, 180, 180, 180, 180, 180, 180};

static int rtot_t10_i0p7[] = {//GoldenVE battery
1200, 500, 350, 200, 200, 170, 170, 170, 170, 170,
170, 170, 170, 170, 170, 170, 170, 170, 170, 170,
170, 170, 170, 170, 170, 170, 170, 170, 170, 170,
170, 170, 170, 170, 170, 170, 170, 170, 170, 170,
170, 170, 170, 170, 170, 170, 170, 170, 170, 170,
170, 170, 170, 170, 170, 170, 170, 170, 170, 170,
170, 170, 170, 170, 170, 170, 170, 170, 170, 170,
170, 170, 170, 170, 170, 170, 170, 170, 170, 170,
170, 170, 170, 170, 170, 170, 170, 170, 170, 170,
170, 170, 170, 170, 170, 170, 170, 170, 170, 170};

static int rtot_t10_i1p0[] = {//GoldenVE battery
1200, 450, 230, 180, 180, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150};

static int rtot_t10_i1p5[] = {
1200, 450, 230, 180, 180, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150};






static int rtot_t10_i0p3c[] = {//GoldenVE battery
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400};

static int rtot_t10_i0p5c[] = {//GoldenVE battery
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400};


static int rtot_t10_i0p7c[] = {//GoldenVE battery
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400};

static int rtot_t10_i1p0c[] = {//GoldenVE battery
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400,
400, 400, 400, 400, 400, 400, 400, 400, 400, 400};



static int rtot_t25_i0p15[] = {//Goya battery
850, 750, 650, 550, 500, 450, 400, 350, 300, 250,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
//179, 176, 195, 230, 250, 236, 218, 214, 216, 214,
//206, 195, 186, 182, 183, 190, 195, 197, 196, 194,
//194, 193, 191, 187, 184, 182, 180, 180, 179, 179,
//179, 181, 182, 182, 184, 187, 188, 190, 192, 194,
//196, 198, 200, 204, 208, 213, 219, 226, 236, 249,
//264, 282, 298, 306, 303, 297, 286, 277, 270, 265,
//263, 262, 265, 270, 273, 272, 269, 265, 264, 266,
//269, 271, 272, 273, 273, 273, 275, 276, 276, 277,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230};
//277, 278, 280, 281, 280, 280, 280, 280, 283, 140};

static int rtot_t25_i0p3[] = {//Goya battery
650, 550, 450, 400, 350, 300, 280, 250, 200, 171,
151, 151, 151, 151, 151, 151, 151, 151, 151, 151,
151, 151, 151, 151, 151, 151, 151, 151, 151, 151,
151, 151, 151, 151, 151, 151, 151, 151, 151, 151,
151, 151, 151, 151, 151, 151, 151, 151, 151, 151,
151, 151, 151, 151, 151, 151, 151, 151, 151, 151,
151, 151, 151, 151, 151, 151, 151, 151, 151, 151,
151, 151, 151, 151, 151, 151, 151, 151, 151, 151,
151, 151, 151, 151, 151, 151, 151, 151, 151, 151,
151, 151, 151, 151, 151, 151, 151, 151, 151, 151};
//192, 191, 192, 192, 192, 192, 192, 191, 192, 95};

static int rtot_t25_i0p5[] = {//Goya battery
550, 450, 400, 360, 330, 280, 250, 220, 180, 150,
130, 130, 130, 130, 130, 130, 130, 130, 130, 130,
130, 130, 130, 130, 130, 130, 130, 130, 130, 130,
130, 130, 130, 130, 130, 130, 130, 130, 130, 130,
130, 130, 130, 130, 130, 130, 130, 130, 130, 130,
130, 130, 130, 130, 130, 130, 130, 130, 130, 130,
130, 130, 130, 130, 130, 130, 130, 130, 130, 130,
130, 130, 130, 130, 130, 130, 130, 130, 130, 130,
130, 130, 130, 130, 130, 130, 130, 130, 130, 130,
130, 130, 130, 130, 130, 130, 130, 130, 130, 130};
//164, 164, 164, 164, 163, 163, 162, 162, 162, 80};

static int rtot_t25_i0p7[] = {//Goya battery
550, 450, 400, 360, 330, 280, 250, 220, 180, 150,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120};
//150, 150, 150, 150, 149, 149, 149, 149, 149, 75};

static int rtot_t25_i1p0[] = { //Goya battery
550, 450, 400, 360, 330, 280, 250, 220, 180, 150,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
//140, 139, 139, 139, 139, 139, 139, 139, 139, 70};


static int rtot_t25_i1p5[] = {//Goya battery
671, 671, 410, 321, 276, 246, 236, 180, 140, 110,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90};
//133, 133, 133, 133, 133, 133, 133, 133, 133, 65};


static int rtot_t25_i0p3c[] = { //GoldenVE battery
215, 215, 215, 215, 215, 215, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220};

static int rtot_t25_i0p5c[] = {//GoldenVE battery
214, 214, 214, 214, 214, 214, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220,
220, 220, 220, 220, 220, 220, 220, 220, 220, 220};

static int rtot_t25_i0p7c[] = {//GoldenVE battery
218, 218, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150};

static int rtot_t25_i1p0c[] = {//GoldenVE battery
204, 204, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110};

static int rtot_t40_i0p15[] = {//Goya battery = 25
850, 750, 650, 550, 500, 450, 400, 350, 300, 250,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230,
230, 230, 230, 230, 230, 230, 230, 230, 230, 230};
//277, 278, 280, 281, 280, 280, 280, 280, 283, 140};

static int rtot_t40_i0p3[] = {//Goya battery
650, 550, 450, 400, 350, 300, 280, 250, 200, 171,
140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
140, 140, 140, 140, 140, 140, 140, 140, 140, 140,
140, 140, 140, 140, 140, 140, 140, 140, 140, 140};
//182, 182, 183, 184, 184, 185, 186, 186, 187, 95};


static int rtot_t40_i0p5[] = {//Goya battery  not charact
650, 550, 450, 400, 330, 300, 260, 230, 190, 131,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 140,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120,
120, 120, 120, 120, 120, 120, 120, 120, 120, 120};


static int rtot_t40_i0p7[] = {//Goya battery
550, 450, 400, 350, 300, 260, 230, 210, 150, 111,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100,
100, 100, 100, 100, 100, 100, 100, 100, 100, 100};
//136, 136, 136, 136, 136, 136, 136, 136, 136, 70};

static int rtot_t40_i1p0[] = { //Goya battery
450, 400, 350, 300, 265, 255, 230, 180, 140, 110,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 99,
90, 90, 90, 90, 90, 90, 90, 90, 90, 99,
90, 90, 90, 90, 90, 90, 90, 90, 90, 99,
90, 90, 90, 90, 90, 90, 90, 90, 90, 99,
90, 90, 90, 90, 90, 90, 90, 90, 90, 99};
//126, 125, 125, 125, 125, 125, 125, 125, 125, 62};

static int rtot_t40_i1p5[] = {//Goya battery
852, 852, 405, 313, 265, 255, 230, 180, 140, 110,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 90,
90, 90, 90, 90, 90, 90, 90, 90, 90, 99,
90, 90, 90, 90, 90, 90, 90, 90, 90, 99,
90, 90, 90, 90, 90, 90, 90, 90, 90, 99,
90, 90, 90, 90, 90, 90, 90, 90, 90, 99,
90, 90, 90, 90, 90, 90, 90, 90, 90, 99};


static int rtot_t40_i0p3c[] = { //GoldenVE battery
362, 362, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200};

static int rtot_t40_i0p5c[] = { //GoldenVE battery
362, 362, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200,
200, 200, 200, 200, 200, 200, 200, 200, 200, 200};


static int rtot_t40_i0p7c[] = { //GoldenVE battery
218, 218, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150,
150, 150, 150, 150, 150, 150, 150, 150, 150, 150};

static int rtot_t40_i1p0c[] = { //GoldenVE battery
204, 204, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110,
110, 110, 110, 110, 110, 110, 110, 110, 110, 110};

static int* dis_chg_rtot[6][5] = {
	{rtot_tm20_i0p15,  rtot_tm5_i0p15,  rtot_t10_i0p15,  rtot_t25_i0p15,  rtot_t40_i0p15},
	{rtot_tm20_i0p3,  rtot_tm5_i0p3,  rtot_t10_i0p3,  rtot_t25_i0p3,  rtot_t40_i0p3},
	{rtot_tm20_i0p5,  rtot_tm5_i0p5,  rtot_t10_i0p5,  rtot_t25_i0p5,  rtot_t40_i0p5},
	{rtot_tm20_i0p7,  rtot_tm5_i0p7,  rtot_t10_i0p7,  rtot_t25_i0p7,  rtot_t40_i0p7},
	{rtot_tm20_i1p0,  rtot_tm5_i1p0,  rtot_t10_i1p0,  rtot_t25_i1p0,  rtot_t40_i1p0},
	{rtot_tm20_i1p5,  rtot_tm5_i1p5,  rtot_t10_i1p5,  rtot_t25_i1p5,  rtot_t40_i1p5}
};

static int dischg_ib[6] = {150, 300, 500, 700, 1000, 1500};

static int* chg_rtot[4][4] = {
	{rtot_tm5_i0p3c,  rtot_t10_i0p3c,  rtot_t25_i0p3c,  rtot_t40_i0p3c},
	{rtot_tm5_i0p5c,  rtot_t10_i0p5c,  rtot_t25_i0p5c,  rtot_t40_i0p5c},
	{rtot_tm5_i0p7c,  rtot_t10_i0p7c,  rtot_t25_i0p7c,  rtot_t40_i0p7c},
	{rtot_tm5_i1p0c,  rtot_t10_i1p0c,  rtot_t25_i1p0c,  rtot_t40_i1p0c}
};

static int chg_ib[4] = {300,500,700, 1000};

#endif