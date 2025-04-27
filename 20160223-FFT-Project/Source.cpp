
#include <iostream>
#include <windows.h>
#include <time.h>

#define Version	(0x000002)

using namespace std;

#define SIZE	1024
#define pi		3.141592654


static const unsigned short sine_50Hz_q10[1024] = {
		   0,           6,          13,          19,          25,          31,          38,          44,
		  50,          56,          63,          69,          75,          82,          88,          94,
		 100,         107,         113,         119,         125,         131,         138,         144,
		 150,         156,         163,         169,         175,         181,         187,         193,
		 200,         206,         212,         218,         224,         230,         236,         242,
		 249,         255,         261,         267,         273,         279,         285,         291,
		 297,         303,         309,         315,         321,         327,         333,         339,
		 345,         351,         356,         362,         368,         374,         380,         386,
		 391,         397,         403,         409,         415,         420,         426,         432,
		 437,         443,         449,         454,         460,         466,         471,         477,
		 482,         488,         493,         499,         504,         510,         515,         521,
		 526,         531,         537,         542,         547,         553,         558,         563,
		 568,         574,         579,         584,         589,         594,         599,         604,
		 609,         614,         619,         624,         629,         634,         639,         644,
		 649,         654,         659,         663,         668,         673,         678,         682,
		 687,         692,         696,         701,         705,         710,         714,         719,
		 723,         728,         732,         737,         741,         745,         750,         754,
		 758,         762,         766,         771,         775,         779,         783,         787,
		 791,         795,         799,         803,         806,         810,         814,         818,
		 822,         825,         829,         833,         836,         840,         844,         847,
		 851,         854,         858,         861,         864,         868,         871,         874,
		 877,         881,         884,         887,         890,         893,         896,         899,
		 902,         905,         908,         911,         914,         917,         919,         922,
		 925,         927,         930,         933,         935,         938,         940,         943,
		 945,         948,         950,         952,         954,         957,         959,         961,
		 963,         965,         967,         969,         971,         973,         975,         977,
		 979,         981,         983,         984,         986,         988,         989,         991,
		 992,         994,         995,         997,         998,         999,        1001,        1002,
		1003,        1005,        1006,        1007,        1008,        1009,        1010,        1011,
		1012,        1013,        1014,        1015,        1015,        1016,        1017,        1017,
		1018,        1019,        1019,        1020,        1020,        1021,        1021,        1021,
		1022,        1022,        1022,        1023,        1023,        1023,        1023,        1023,
		1023,        1023,        1023,        1023,        1023,        1023,        1022,        1022,
		1022,        1021,        1021,        1021,        1020,        1020,        1019,        1019,
		1018,        1017,        1017,        1016,        1015,        1015,        1014,        1013,
		1012,        1011,        1010,        1009,        1008,        1007,        1006,        1005,
		1003,        1002,        1001,         999,         998,         997,         995,         994,
		 992,         991,         989,         988,         986,         984,         983,         981,
		 979,         977,         975,         973,         971,         969,         967,         965,
		 963,         961,         959,         957,         954,         952,         950,         948,
		 945,         943,         940,         938,         935,         933,         930,         927,
		 925,         922,         919,         917,         914,         911,         908,         905,
		 902,         899,         896,         893,         890,         887,         884,         881,
		 877,         874,         871,         868,         864,         861,         858,         854,
		 851,         847,         844,         840,         836,         833,         829,         825,
		 822,         818,         814,         810,         806,         803,         799,         795,
		 791,         787,         783,         779,         775,         771,         766,         762,
		 758,         754,         750,         745,         741,         737,         732,         728,
		 723,         719,         714,         710,         705,         701,         696,         692,
		 687,         682,         678,         673,         668,         663,         659,         654,
		 649,         644,         639,         634,         629,         624,         619,         614,
		 609,         604,         599,         594,         589,         584,         579,         574,
		 568,         563,         558,         553,         547,         542,         537,         531,
		 526,         521,         515,         510,         504,         499,         493,         488,
		 482,         477,         471,         466,         460,         454,         449,         443,
		 437,         432,         426,         420,         415,         409,         403,         397,
		 391,         386,         380,         374,         368,         362,         356,         351,
		 345,         339,         333,         327,         321,         315,         309,         303,
		 297,         291,         285,         279,         273,         267,         261,         255,
		 249,         242,         236,         230,         224,         218,         212,         206,
		 200,         193,         187,         181,         175,         169,         163,         156,
		 150,         144,         138,         131,         125,         119,         113,         107,
		 100,          94,          88,          82,          75,          69,          63,          56,
		  50,          44,          38,          31,          25,          19,          13,           6,
		   0,          -6,         -13,         -19,         -25,         -31,         -38,         -44,
		 -50,         -56,         -63,         -69,         -75,         -82,         -88,         -94,
		-100,        -107,        -113,        -119,        -125,        -131,        -138,        -144,
		-150,        -156,        -163,        -169,        -175,        -181,        -187,        -193,
		-200,        -206,        -212,        -218,        -224,        -230,        -236,        -242,
		-249,        -255,        -261,        -267,        -273,        -279,        -285,        -291,
		-297,        -303,        -309,        -315,        -321,        -327,        -333,        -339,
		-345,        -351,        -356,        -362,        -368,        -374,        -380,        -386,
		-391,        -397,        -403,        -409,        -415,        -420,        -426,        -432,
		-437,        -443,        -449,        -454,        -460,        -466,        -471,        -477,
		-482,        -488,        -493,        -499,        -504,        -510,        -515,        -521,
		-526,        -531,        -537,        -542,        -547,        -553,        -558,        -563,
		-568,        -574,        -579,        -584,        -589,        -594,        -599,        -604,
		-609,        -614,        -619,        -624,        -629,        -634,        -639,        -644,
		-649,        -654,        -659,        -663,        -668,        -673,        -678,        -682,
		-687,        -692,        -696,        -701,        -705,        -710,        -714,        -719,
		-723,        -728,        -732,        -737,        -741,        -745,        -750,        -754,
		-758,        -762,        -766,        -771,        -775,        -779,        -783,        -787,
		-791,        -795,        -799,        -803,        -806,        -810,        -814,        -818,
		-822,        -825,        -829,        -833,        -836,        -840,        -844,        -847,
		-851,        -854,        -858,        -861,        -864,        -868,        -871,        -874,
		-877,        -881,        -884,        -887,        -890,        -893,        -896,        -899,
		-902,        -905,        -908,        -911,        -914,        -917,        -919,        -922,
		-925,        -927,        -930,        -933,        -935,        -938,        -940,        -943,
		-945,        -948,        -950,        -952,        -954,        -957,        -959,        -961,
		-963,        -965,        -967,        -969,        -971,        -973,        -975,        -977,
		-979,        -981,        -983,        -984,        -986,        -988,        -989,        -991,
		-992,        -994,        -995,        -997,        -998,        -999,       -1001,       -1002,
	   -1003,       -1005,       -1006,       -1007,       -1008,       -1009,       -1010,       -1011,
	   -1012,       -1013,       -1014,       -1015,       -1015,       -1016,       -1017,       -1017,
	   -1018,       -1019,       -1019,       -1020,       -1020,       -1021,       -1021,       -1021,
	   -1022,       -1022,       -1022,       -1023,       -1023,       -1023,       -1023,       -1023,
	   -1023,       -1023,       -1023,       -1023,       -1023,       -1023,       -1022,       -1022,
	   -1022,       -1021,       -1021,       -1021,       -1020,       -1020,       -1019,       -1019,
	   -1018,       -1017,       -1017,       -1016,       -1015,       -1015,       -1014,       -1013,
	   -1012,       -1011,       -1010,       -1009,       -1008,       -1007,       -1006,       -1005,
	   -1003,       -1002,       -1001,        -999,        -998,        -997,        -995,        -994,
		-992,        -991,        -989,        -988,        -986,        -984,        -983,        -981,
		-979,        -977,        -975,        -973,        -971,        -969,        -967,        -965,
		-963,        -961,        -959,        -957,        -954,        -952,        -950,        -948,
		-945,        -943,        -940,        -938,        -935,        -933,        -930,        -927,
		-925,        -922,        -919,        -917,        -914,        -911,        -908,        -905,
		-902,        -899,        -896,        -893,        -890,        -887,        -884,        -881,
		-877,        -874,        -871,        -868,        -864,        -861,        -858,        -854,
		-851,        -847,        -844,        -840,        -836,        -833,        -829,        -825,
		-822,        -818,        -814,        -810,        -806,        -803,        -799,        -795,
		-791,        -787,        -783,        -779,        -775,        -771,        -766,        -762,
		-758,        -754,        -750,        -745,        -741,        -737,        -732,        -728,
		-723,        -719,        -714,        -710,        -705,        -701,        -696,        -692,
		-687,        -682,        -678,        -673,        -668,        -663,        -659,        -654,
		-649,        -644,        -639,        -634,        -629,        -624,        -619,        -614,
		-609,        -604,        -599,        -594,        -589,        -584,        -579,        -574,
		-568,        -563,        -558,        -553,        -547,        -542,        -537,        -531,
		-526,        -521,        -515,        -510,        -504,        -499,        -493,        -488,
		-482,        -477,        -471,        -466,        -460,        -454,        -449,        -443,
		-437,        -432,        -426,        -420,        -415,        -409,        -403,        -397,
		-391,        -386,        -380,        -374,        -368,        -362,        -356,        -351,
		-345,        -339,        -333,        -327,        -321,        -315,        -309,        -303,
		-297,        -291,        -285,        -279,        -273,        -267,        -261,        -255,
		-249,        -242,        -236,        -230,        -224,        -218,        -212,        -206,
		-200,        -193,        -187,        -181,        -175,        -169,        -163,        -156,
		-150,        -144,        -138,        -131,        -125,        -119,        -113,        -107,
		-100,         -94,         -88,         -82,         -75,         -69,         -63,         -56,
		 -50,         -44,         -38,         -31,         -25,         -19,         -13,          -6

};




typedef struct
{
	float real;
	float image;
}Fcomplex;

typedef struct
{
	unsigned short real;	// 16bit
	unsigned short image;   // 16bit
}Bcomplex;


short addr0[SIZE], addr1[SIZE], addr2[SIZE], addr3[SIZE], addr4[SIZE], addr5[SIZE];

/* 存放的旋转因子 */
Bcomplex DataRom0, DataRom1[16], DataRom2[64], DataRom3[256], DataRom4[1024];

/* 旋转因子的地址 */
short Addr0Rom[SIZE], Addr1Rom[SIZE], Addr2Rom[SIZE], Addr3Rom[SIZE];

Fcomplex Fdata[SIZE];	// FFT测试输入浮点数
Bcomplex Idata[SIZE];	// FFT输入浮点数转换成定点数
Bcomplex Odata[SIZE];	// FFT输出结果


void GeneralFixedPoint();
void StageFftAddr();
void RomAddrGenerate();
void RomDataFromTxt();
void BufflyFFT();
void ComputeData(Bcomplex *x1, Bcomplex *x2, Bcomplex *x3, Bcomplex *x4, Bcomplex r1, Bcomplex r2, Bcomplex r3, Bcomplex r4);
void WrData2TXT(const char* filename, const unsigned short* data, int count);


/*
// 将采集的数据定点化为Format(Q10.5) largest positive 。
//	输入浮点数范围：[-1024,1023.96875]
//	输出定点数范围：[-32768, 32767] 
*/
void GeneralFixedPoint()
{
	//for(int i = 0; i < SIZE; i++)
	//{
	//	Idata[i].real	= Fdata[i].real * 32;	// 加强制转换会有精度损失到0
	//	Idata[i].image	= Fdata[i].image * 32;
	//}
	for (int i = 0; i < SIZE; i++)
	{
		Idata[i].real	= sine_50Hz_q10[i];
		Idata[i].image	= 0;
	}
}


/*
//计算并存储FFT每一级蝶形操作时的输入输出地址组合
*/
void StageFftAddr()
{
	// Stage 1 FFT addr0
	for(short i = 0; i < SIZE; i++)
	{
		// {i[1:0],i[9:2]}
		addr0[i] = ((short)(i / 4) + ((short)(i % 4) * 256)) & 0x03ff;
		//cout << i<<":"<<addr0[i] << endl;
	}

	// Stage 2 FFT addr1
	for(short i = 0; i < SIZE; i++)
	{
		short temp, temp1;

		temp	= i & 0x0300;	// {i[9:8],8'b0}
		temp1	= i & 0x00ff;	// i[7:0]

		// {i[9:8],i[1:0],i[7:2]};
		addr1[i] = (temp  + (temp1 % 4) * 64 + temp1 / 4) & 0x3ff;
		//cout << i<<":"<<addr1[i] << endl;
	}

	// Stage 3 FFT addr2
	for(short i = 0; i < SIZE; i++)
	{
		short temp, temp1;

		temp	= i & 0x03c0;	// {i[9:6],6'b0}
		temp1	= i & 0x003f;	// i[5:0]

		// {i[9:6], i[1:0], i[5:2]}
		addr2[i] = (temp + (temp1 % 4) * 16 + temp1 / 4) & 0x3ff;
		//cout << i<<":"<<addr2[i] << endl;
	}

	// Stage 4 FFT addr3
	for(short i = 0; i < SIZE; i++)
	{
		short temp, temp1;

		temp	= i & 0x03f0;	// {i[9:4],4'b0}
		temp1	= i & 0x000f;	// i[3:0]
		
		// {i[9:4], i[1:0], i[3:2]}
		addr3[i] = (temp + (temp1 % 4) * 4 + temp1 / 4) & 0x3ff;
		//cout << i<<":"<<addr3[i] << endl;
	}

	// Stage 5 FFT Addr4
	for(short i = 0; i < SIZE; i++)
	{
		addr4[i] = i;
		//cout << i<<":"<<addr4[i] << endl;
	}

	// For Output data 
	for (short i = 0; i < SIZE; i++)
	{
		short temp, temp1, temp2, temp3, temp4;

		temp	= i % 4;			// i[1:0]
		temp1	= (i / 4)	% 4;	// i[3:2]
		temp2	= (i / 16)	% 4;	// i[5:4]
		temp3	= (i / 64)	% 4;	// i[7:6]
		temp4	= (i / 256)	% 4;	// i[9:8]

		// {addr5[1:0],addr5[3:2],addr5[5:4],addr5[7:6],addr5[9:8]}
		addr5[i] = (temp * 256 + temp1 * 64 + temp2 * 16 + temp3 * 4 + temp4) & 0x3ff;
		//cout << i<<":"<<addr5[i] << endl;
	}
}


/*
// 预先生成旋转因子
*/
void RomDataFromTxt()
{
	short temp_real, temp_imag;

	short k;
	short A = (short)pow(2, 8) - 1;	// 2^8-1=255

	//AddrRom0   Stage 1 旋转因子
	DataRom0.real	= A;
	DataRom0.image	= 0;

	//DataRom1[16] Stage 2 旋转因子
	k = 0;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; ++j)
		{
			// Stage 2 旋转因子的实部
			temp_real = (short)(A*cos(-2 * 64 * i*j*pi / 1024));
			// Q9
			if(temp_real >= 0)
				temp_real = temp_real & 0x01ff;
			else
				temp_real = (temp_real + 512) & 0x01ff;	// 加上符号位

			// Stage 2 旋转因子的虚部
			temp_imag = (short)(A*sin(-2 * 64 * i*j*pi / 1024));
			// Q9
			if(temp_imag >= 0)
				temp_imag = temp_imag & 0x01ff;
			else
				temp_imag = (temp_imag + 512) & 0x01ff;	// 加上符号位

			DataRom1[k].real	= temp_real;
			DataRom1[k].image	= temp_imag;

			k = k + 1;
		}
	}

	//DataRom2[64] Stage 3 旋转因子
	k = 0;
	int temp_num;
	for(int L = 0; L < 4; L++)
	{
		for(int i = 0; i < 4; i++)
		{
			temp_num = L + i * 4;

			for(int j = 0; j < 4; j++)
			{
				// Stage 3 旋转因子的实部
				temp_real = (short)(A*cos(-2 * 16 * temp_num*j*pi / 1024));
				// Q9
				if(temp_real >= 0)
					temp_real = temp_real & 0x01ff;
				else
					temp_real = (temp_real + 512) & 0x01ff;	// 加上符号位

				// Stage 3 旋转因子的虚部
				temp_imag = (short)(A*sin(-2 * 16 * temp_num*j*pi / 1024));
				// Q9
				if(temp_imag >= 0)
					temp_imag = temp_imag & 0x01ff;
				else
					temp_imag = (temp_imag + 512) & 0x01ff;	//加上符号位

				DataRom2[k].real	= temp_real;
				DataRom2[k].image	= temp_imag;

				k = k + 1;
			}
		}
	}

	//DataRom3[256] Stage 4 旋转因子
	k = 0;
	temp_num = 0;
	for(int L1 = 0; L1 < 4; L1++)
	{
		for(int L = 0; L < 4; L++)
		{
			for(int i = 0; i < 4; i++)
			{
				temp_num = L1 + (L + i * 4) * 4;
				for(int j = 0; j < 4; j++)
				{
					// Stage 4 旋转因子的实部
					temp_real = (short)(A*cos(-2 * 4 * temp_num*j*pi / 1024));
					// Q9
					if(temp_real >= 0)
						temp_real = temp_real & 0x01ff;
					else
						temp_real = (temp_real + 512) & 0x01ff;	//加上符号位

					// Stage 4 旋转因子的虚部
					temp_imag = (short)(A*sin(-2 * 4 * temp_num*j*pi / 1024));
					// Q9
					if(temp_imag >= 0)
						temp_imag = temp_imag & 0x01ff;
					else
						temp_imag = (temp_imag + 512) & 0x01ff;	//加上符号位

					DataRom3[k].real	= temp_real;
					DataRom3[k].image	= temp_imag;

					k = k + 1;
				}
			}
		}
	}

	// DataRom4[1024] Stage 5 旋转因子
	k = 0;
	temp_num = 0;
	for(int L2 = 0; L2 < 4; L2++)
	{
		for(int L1 = 0; L1 < 4; L1++)
		{
			for(int L = 0; L < 4; L++)
			{
				for(int i = 0; i < 4; i++)
				{
					temp_num = L2 + (L1 + (L + i * 4) * 4) * 4;
					for(int j = 0; j < 4; ++j)
					{
						// Stage 5 旋转因子的实部
						temp_real = (short)(A*cos(-2 * temp_num*j*pi / 1024));
						// Q9
						if (temp_real >= 0)
							temp_real = temp_real & 0x01ff;
						else
							temp_real = (temp_real + 512) & 0x01ff;	//加上符号位

						// Stage 5 旋转因子的虚部
						temp_imag = (short)(A*sin(-2 * temp_num*j*pi / 1024));
						// Q9
						if (temp_imag >= 0)
							temp_imag = temp_imag & 0x01ff;
						else
							temp_imag = (temp_imag + 512) & 0x01ff;//加上符号位
						
						DataRom4[k].real	= temp_real;
						DataRom4[k].image	= temp_imag;
						
						k = k + 1;
					}
				}
			}
		}
	}
}

/* 
// 查表定位对应的旋转因子
*/
void RomAddrGenerate()
{
	// Stage 1 的旋转因子恒等于1

	// Stage 2 旋转因子地址表
	for(int i = 0; i < SIZE; i++)
	{
		int temp, temp1;

		temp	= i / 256;	// i[9:8]
		temp1	= i % 4;	// i[1:0]

		// {i[9:8], i[1:0]}
		Addr0Rom[i] = temp * 4 + temp1;
	}

	// Stage 3 旋转因子地址表
	for(int i = 0; i < SIZE; i++)
	{
		int temp, temp1;

		temp	= i / 64;	// i[9:6]
		temp1	= i % 4;	// i[1:0]

		// {i[9:6], i[1:0]}
		Addr1Rom[i] = temp * 4 + temp1;
	}

	// Stage 4 旋转因子地址表
	for(int i = 0; i < SIZE; i++)
	{
		int temp, temp1;

		temp	= i / 16;	// i[9:4]
		temp1	= i % 4;	// i[1:0]
		
		// {i[9:4], i[1:0]}
		Addr2Rom[i] = temp * 4 + temp1;
	}

	// Stage 5 旋转因子地址表
	for(int i = 0; i < SIZE; i++)
	{
		Addr3Rom[i] = i;
	}
}



/* 蝶型运算
	输入：	4个数据点 x1, x2, x3, x4
			4个旋转因子 r1, r2,r3,r4
*/

void ComputeData(	Bcomplex *x1, Bcomplex *x2, Bcomplex *x3, Bcomplex *x4,
					Bcomplex r1, Bcomplex r2, Bcomplex r3, Bcomplex r4)
{
	int brw1pr, biw1pi,		
		crw2pr, ciw2pi,		
		drw3pr, diw3pi,
		brw1pi, biw1pr,
		crw2pi, ciw2pr,
		drw3pi, diw3pr;
	
	int mer, mei,
		mfr, mfi,
		mgr, mgi,
		mhr, mhi;
	
	unsigned short
		er, ei,
		fr, fi,
		gr, gi,
		hr, hi;

	int r2r, r2i,
		r3r, r3i,
		r4r, r4i;

	// 无符号Q9转带符号Q8
	r2r = (r2.real	> 256) ? (-512 + r2.real)	: r2.real;
	r2i = (r2.image > 256) ? (-512 + r2.image)	: r2.image;
	r3r = (r3.real	> 256) ? (-512 + r3.real)	: r3.real;
	r3i = (r3.image > 256) ? (-512 + r3.image)	: r3.image;
	r4r = (r4.real	> 256) ? (-512 + r4.real)	: r4.real;
	r4i = (r4.image > 256) ? (-512 + r4.image)	: r4.image;


	/* (a + jb)(c + jd) = (ac - bd) + j(ad + bc) */
	brw1pr = ((signed)x2->real)*r2i;/*x2.ad*/	biw1pi = ((signed)x2->image) * r2i;/*x2.bd*/
	crw2pr = ((signed)x3->real)*r3r;/*x3.ac*/	ciw2pi = ((signed)x3->image) * r3i;/*x3.bd*/
	drw3pr = ((signed)x4->real)*r4r;/*x4.ac*/	diw3pi = ((signed)x4->image) * r4i;/*x4.bd*/
	brw1pi = ((signed)x2->real)*r2i;/*x2.ad*/	biw1pr = ((signed)x2->image) * r2r;/*x2.bc*/
	crw2pi = ((signed)x3->real)*r3i;/*x3.ad*/	ciw2pr = ((signed)x3->image) * r3r;/*x3.bc*/
	drw3pi = ((signed)x4->real)*r4i;/*x4.ad*/	diw3pr = ((signed)x4->image) * r4r;/*x4.bc*/

	/* x1.a * 256 + x2.ad - x2.bd + x3.ac - x3.bd + x4.ac - x4.bd */
	mer = (signed)(x1->real) * 256 + brw1pr - biw1pi + crw2pr - ciw2pi + drw3pr - diw3pi;
	/* x1.b * 256 + x2.ad + x2.bc + x3.ad + x3.bc + x4.ad + x4.bc */
	mei = (signed)(x1->image) * 256 + brw1pi + biw1pr + crw2pi + ciw2pr + drw3pi + diw3pr;
	/* x1.a * 256 + x2.ad + x2.bc - x3.ac + x3.bd - x4.ad - x4.bc */
	mfr = (signed)(x1->real) * 256 + brw1pi + biw1pr - crw2pr + ciw2pi - drw3pi - diw3pr; //原+crw2pr+ciw2pi
	/* x1.b * 256 - x2.ad + x2.bd - x3.ad - x3.bc + x4.ac - x4.bd */
	mfi = (signed)(x1->image) * 256 - brw1pr + biw1pi - crw2pi - ciw2pr + drw3pr - diw3pi;
	/* x1.a * 256 - x2.ad + x2.bd + x3.ac - x3.bd - x4.ac + x4.bd */
	mgr = (signed)(x1->real) * 256 - brw1pr + biw1pi + crw2pr - ciw2pi - drw3pr + diw3pi;
	/* x1.b * 256 - x2.ad - x2.bc + x3.ad + x3.bc - x4.ad - x4.bc */
	mgi = (signed)(x1->image) * 256 - brw1pi - biw1pr + crw2pi + ciw2pr - drw3pi - diw3pr;
	/* x1.a * 256 - x2.ad - x2.bc - x3.ac + x3.bd + x4.ad + x4.bc */
	mhr = (signed)(x1->real) * 256 - brw1pi - biw1pr - crw2pr + ciw2pi + drw3pi + diw3pr;//原+crw2pr+ciw2pi
	/* x1.b * 256 + x2.ad - x2.bd - x3.ad - x3.bc - x4.ac + x4.bd */
	mhi = (signed)(x1->image) * 256 + brw1pr - biw1pi - crw2pi - ciw2pr - drw3pr + diw3pi;


	//计算的数据进行截位处理
	unsigned int temp, temp1, temp2;

	temp2	= mer;			// mer[31:0]
	temp	= temp2 / 256;	// mer[31:8]
	temp1	= temp % 2;		// mer[8]
	temp	= (temp2 >> 9);	// mer[31:9]
	er		= temp;			// er截断为mer[31:9]

	if(temp1 == 1)	//第8位余1，则第9为补1。即做四舍五入处理
		er = er + 1;
	// 	er = er & 0x00007fff;
	// 	er = temp2 & 0x7fff;

	temp2	= mei;
	temp	= mei / 256;
	temp1	= temp % 2;
	temp	= (temp2 >> 9);
	ei		= temp;
	if(temp1 == 1)
		ei = ei + 1;
	//	ei = ei & 0x00007fff;
	// 	ei = temp2 & 0x7fff;

	temp2	= mfr;
	temp	= temp2 / 256;
	temp1	= temp % 2;
	temp	= (temp2 >> 9);
	fr		= temp;
	if(temp1 == 1)
		fr = fr + 1;
	// 	fr = fr & 0x00007fff;
	// 	fr = temp2 & 0x7fff;

	temp2	= mfi;
	temp	= temp2 / 256;
	temp1	= temp % 2;
	temp	= (temp2 >> 9);
	fi		= temp;
	if(temp1 == 1)
		fi = fi + 1;
	//	fi = fi & 0x00007fff;
	// 	fi = temp2 & 0x7fff;
	
	temp2	= mgr;
	temp	= temp2 / 256;
	temp1	= temp % 2;
	temp	= (temp2 >> 9);
	gr		= temp;
	if(temp1 == 1)
		gr = gr + 1;
	//  gr = gr & 0x00007fff;
	// 	gr = temp2;
	
	temp2	= mgi;
	temp	= temp2 / 256;
	temp1	= temp % 2;
	temp	= (temp2 >> 9);
	gi		= temp;
	if(temp1 == 1)
		gi = gi + 1;
	//	gi = gi & 0x00007fff;
	// 	gi = temp2 & 0x7fff;

	temp2	= mhr;
	temp	= temp2 / 256;
	temp1	= temp % 2;
	temp	= (temp2 >> 9);
	hr		= temp;
	if(temp1 == 1)
		hr = hr + 1;
	// 	hr = hr & 0x00007fff;
	// 	hr = temp2 & 0x7fff;

	temp2	= mhi;
	temp	= temp2 / 256;
	temp1	= temp % 2;
	temp	= (temp2 >> 9);
	hi		= temp;
	if(temp1 == 1)
		hi = hi + 1;
	//  hi = hi & 0x00007fff;
	// 	hi = temp2 & 0x7fff;

	x1->real	= er;
	x1->image	= ei;

	x2->real	= fr;
	x2->image	= fi;

	x3->real	= gr;
	x3->image	= gi;

	x4->real	= hr;
	x4->image	= hi;
}



// 蝶形计算的数据，Idata[SIZE]
void BufflyFFT()
{
	// Stage 1 蝶形计算
	// 地址:addr0[SIZE]
	// 旋转因子:DataRom
	for(int i = 0; i < 1024; i = i + 4)
	{
		Bcomplex	temp_x1, temp_x2, temp_x3, temp_x4,
					temp_r1, temp_r2, temp_r3, temp_r4;

		temp_x1 = Idata[addr0[i]];
		temp_x2 = Idata[addr0[i + 1]];
		temp_x3 = Idata[addr0[i + 2]];
		temp_x4 = Idata[addr0[i + 3]];

		temp_r1 = DataRom0;
		temp_r2 = DataRom0;
		temp_r3 = DataRom0;
		temp_r4 = DataRom0;

		ComputeData(&temp_x1, &temp_x2, &temp_x3, &temp_x4, temp_r1, temp_r2, temp_r3, temp_r4);

		Idata[addr0[i]]		= temp_x1;
		Idata[addr0[i + 1]] = temp_x2;
		Idata[addr0[i + 2]] = temp_x3;
		Idata[addr0[i + 3]] = temp_x4;
	}

	// Stage 2 蝶形计算
	// 地址:addr1[SIZE]
	// 旋转因子:DataRom0[16]
	// 旋转因子地址:Addr0Rom[SIZE]
	for(int i = 0; i < 1024; i = i + 4)
	{
		Bcomplex	temp_x1, temp_x2, temp_x3, temp_x4,
					temp_r1, temp_r2, temp_r3, temp_r4;

		temp_x1 = Idata[addr1[i]];
		temp_x2 = Idata[addr1[i + 1]];
		temp_x3 = Idata[addr1[i + 2]];
		temp_x4 = Idata[addr1[i + 3]];

		temp_r1 = DataRom1[Addr0Rom[i]];
		temp_r2 = DataRom1[Addr0Rom[i + 1]];
		temp_r3 = DataRom1[Addr0Rom[i + 2]];
		temp_r4 = DataRom1[Addr0Rom[i + 3]];

		ComputeData(&temp_x1, &temp_x2, &temp_x3, &temp_x4, temp_r1, temp_r2, temp_r3, temp_r4);

		Idata[addr1[i]]		= temp_x1;
		Idata[addr1[i + 1]] = temp_x2;
		Idata[addr1[i + 2]] = temp_x3;
		Idata[addr1[i + 3]] = temp_x4;
	}

	// Stage 3 蝶形计算
	// 地址:addr2[SIZE]
	// 旋转因子:DataRom1[64]
	// 旋转因子地址:Addr1Rom[SIZE]
	for(int i = 0; i < 1024; i = i + 4)
	{
		Bcomplex	temp_x1, temp_x2, temp_x3, temp_x4,
					temp_r1, temp_r2, temp_r3, temp_r4;

		temp_x1 = Idata[addr2[i]];
		temp_x2 = Idata[addr2[i + 1]];
		temp_x3 = Idata[addr2[i + 2]];
		temp_x4 = Idata[addr2[i + 3]];

		temp_r1 = DataRom2[Addr1Rom[i]];
		temp_r2 = DataRom2[Addr1Rom[i + 1]];
		temp_r3 = DataRom2[Addr1Rom[i + 2]];
		temp_r4 = DataRom2[Addr1Rom[i + 3]];

		ComputeData(&temp_x1, &temp_x2, &temp_x3, &temp_x4, temp_r1, temp_r2,temp_r3, temp_r4);

		Idata[addr1[i]]		= temp_x1;
		Idata[addr1[i + 1]] = temp_x2;
		Idata[addr1[i + 2]] = temp_x3;
		Idata[addr1[i + 3]] = temp_x4;
	}

	// Stage 4蝶形计算
	//	地址:addr3[SIZE]
	//	旋转因子:DataRom2[256]
	//	旋转因子地址:Addr2Rom[SIZE]
	for(int i = 0; i < 1024; i = i + 4)
	{
		Bcomplex	temp_x1, temp_x2, temp_x3, temp_x4,
					temp_r1, temp_r2, temp_r3, temp_r4;

		temp_x1 = Idata[addr3[i]];
		temp_x2 = Idata[addr3[i + 1]];
		temp_x3 = Idata[addr3[i + 2]];
		temp_x4 = Idata[addr3[i + 3]];

		temp_r1 = DataRom3[Addr2Rom[i]];
		temp_r2 = DataRom3[Addr2Rom[i + 1]];
		temp_r3 = DataRom3[Addr2Rom[i + 2]];
		temp_r4 = DataRom3[Addr2Rom[i + 3]];

		ComputeData(&temp_x1, &temp_x2, &temp_x3, &temp_x4, temp_r1, temp_r2, temp_r3, temp_r4);

		Idata[addr3[i]]		= temp_x1;
		Idata[addr3[i + 1]] = temp_x2;
		Idata[addr3[i + 2]] = temp_x3;
		Idata[addr3[i + 3]] = temp_x4;
	}

	// Stage 5 蝶形计算
	// 地址:addr4[SIZE]
	// 旋转因子:DataRom3[256]
	// 旋转因子地址:Addr3Rom[SIZE]
	for(int i = 0; i < 1024; i = i + 4)
	{
		Bcomplex	temp_x1, temp_x2, temp_x3, temp_x4,
					temp_r1, temp_r2, temp_r3, temp_r4;
		temp_x1 = Idata[addr4[i]];
		temp_x2 = Idata[addr4[i + 1]];
		temp_x3 = Idata[addr4[i + 2]];
		temp_x4 = Idata[addr4[i + 3]];

		temp_r1 = DataRom4[Addr3Rom[i]];
		temp_r2 = DataRom4[Addr3Rom[i + 1]];
		temp_r3 = DataRom4[Addr3Rom[i + 2]];
		temp_r4 = DataRom4[Addr3Rom[i + 3]];

		ComputeData(&temp_x1, &temp_x2, &temp_x3, &temp_x4, temp_r1, temp_r2, temp_r3, temp_r4);
		Idata[addr4[i]]		= temp_x1;
		Idata[addr4[i + 1]] = temp_x2;
		Idata[addr4[i + 2]] = temp_x3;
		Idata[addr4[i + 3]] = temp_x4;
	}

	// 将计算之后的数据倒叙出来
	// 地址:addr5[SIZE]
	for(int i = 0; i < SIZE; i++)
		Odata[i] = Idata[addr5[i]];
}

/*
//void WrData2TXT(const char* filename, const double* data, int count)
void WrData2TXT(const char* filename, const int* data, int count)
{
	FILE* file = fopen(filename, "w");	// VS 2014版本

	if (file == NULL)
	{
		printf("打开文件失败 %s\n", filename);
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < count; i++)
		fprintf(file, "%d\n", i, data[i]);

	fclose(file);
}
*/
void WrData2TXT(const char* filename, const unsigned short* data, int count)
{
	FILE* file = NULL; // 先声明为空
	errno_t err;

	err = fopen_s(&file, filename, "w"); // 安全版 fopen_s

	if (err != 0 || file == NULL) // 打开失败
	{
		printf("打开文件失败 %s\n", filename);
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < count; i++)
		fprintf(file, "%d\n", data[i]); // 正确地写入每个 data[i]

	fclose(file); // 最后关闭文件
}


int main()
{
	for(int i = 0; i < SIZE; i++)
	{
		Fdata[i].real	= 1 / 32.0;
		Fdata[i].image	= 0;
	}

	GeneralFixedPoint();
	StageFftAddr();
	RomDataFromTxt();
	RomAddrGenerate();
	BufflyFFT();

	unsigned short print_real[SIZE], print_image[SIZE];
	for(int i = 0; i < SIZE; i++)
	{
		print_real[i] = Odata[i].real;
		print_image[i] = Odata[i].image;
		cout << "real:" << print_real[i] << "  image:" << print_image[i] << endl;
	}
	WrData2TXT("OutputReal.txt", &print_real[0], SIZE);
	WrData2TXT("OutputImage.txt", &print_image[0], SIZE);

	system("pause");
	return 0;
}

