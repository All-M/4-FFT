/******************************************************************
* @file         Source.cpp
* @date         2016-2-24 11:26:40
* @author       YoGiJY
* @e-mail       yao.jiang@tongji.edu.cn
* @brief        4-FFT For fixed Computing
*
*****************************************************************/
#include <iostream>
#include <windows.h>
#include<time.h>

using namespace std;
#define SIZE 1024
#define pi 3.141592654

typedef struct {
	float real;
	float image;
} Fcomplex;

typedef struct {
	unsigned short real;           //表示16bit
	unsigned short image;          //表示16bit
} Bcomplex;

typedef struct {
	char real[17];
	char image[17];
} FixedComplex;

short addr0[SIZE];
short addr1[SIZE];
short addr2[SIZE];
short addr3[SIZE];
short addr4[SIZE];
short addr5[SIZE];

//存放的旋转因子
Bcomplex DataRom;
Bcomplex DataRom0[16];
Bcomplex DataRom1[64];
Bcomplex DataRom2[256];
Bcomplex DataRom3[1024];

//旋转因子的地址
short Addr0Rom[SIZE];
short Addr1Rom[SIZE];
short Addr2Rom[SIZE];
short Addr3Rom[SIZE];

Fcomplex Fdata[SIZE];
Bcomplex Idata[SIZE];
Bcomplex Odata[SIZE];
FixedComplex FixedData[SIZE];

void GeneralFloatPoint();
void GeneralFxiedPoint();
void LevelFftAddr();
void RomAddrGenerate();
void RomDataFromTxt();
void BufflyFFT();
void ComputeData(Bcomplex *x1, Bcomplex *x2, Bcomplex *x3, Bcomplex *x4, Bcomplex r1, Bcomplex r2, Bcomplex r3, Bcomplex r4);


//将采集的数据定点化使用的Format(Q10.5),largest positive:1023.96875，Least negative value:-1024
void GeneralFxiedPoint() {
	char real[17] = { 0 };
	char image[17] = { 0 };

	for (int i = 0; i < SIZE; ++i) {
		Idata[i].real = Fdata[i].real * 32;
		Idata[i].image = Fdata[i].image * 32;
	}
}

//将Modelsim中计算的数据转化为float型Format(Q10.5)
void GeneralFloatPoint() {

}

void LevelFftAddr() {

	//Level One FFT Addr0
	for (short i = 0; i < SIZE; ++i) {
		addr0[i] = ((short)(i / 4) + ((short)(i % 4) * 256)) & 0x03ff;
		//{addr0[1:0],addr0[9:2]};
		//cout << i<<":"<<addr0[i] << endl;
	}

	//Level Two FFT Addr1
	for (short i = 0; i < SIZE; ++i) {
		short temp;
		short temp1;
		temp = i & 0x0300;
		temp1 = i & 0x00ff;
		addr1[i] = (temp + temp1 / 4 + (temp1 % 4) * 64) & 0x3ff;//{addr1[9:8],addr1[1:0],addr1[7:2]};
																 //cout << i<<":"<<addr0[i] << endl;
	}

	//Level Three FFT Addr2
	for (short i = 0; i < SIZE; ++i) {
		short temp;
		short temp1;
		temp = i & 0x03c0;
		temp1 = i & 0x003f;
		addr2[i] = (temp + temp1 / 4 + (temp1 % 4) * 16) & 0x3ff;//{addr2[9:6], addr2[1:0], addr2[5:2]}
																 //cout << i<<":"<<addr2[i] << endl;
	}

	//Level Four FFT Addr3
	for (short i = 0; i < SIZE; ++i) {
		short temp;
		short temp1;
		temp = i & 0x03f0;
		temp1 = i & 0x000f;
		addr3[i] = (temp + temp1 / 4 + (temp1 % 4) * 4) & 0x3ff;//{addr3[9:4], addr3[1:0], addr3[3:2]}
	}

	//Level Five FFT Addr4
	for (short i = 0; i < SIZE; ++i) {
		addr4[i] = i; //assign out_addr4= addr4;
	}

	//For Output data 
	for (short i = 0; i < SIZE; ++i) {
		short temp;
		short temp1;
		short temp2;
		short temp3;
		short temp4;
		temp = i % 4;          //[1:0]
		temp1 = (i / 4) % 4;   //[3:2]
		temp2 = (i / 16) % 4;  //[5:4]
		temp3 = (i / 64) % 4;  //[7:6]
		temp4 = (i / 256) % 4; //[9:8]
		addr5[i] = (temp * 256 + temp1 * 64 + temp2 * 16 + temp3 * 4 + temp4) & 0x3ff; //{addr5[1:0], addr5[3:2], addr5[5:4], addr5[7:6], addr5[9:8]}
	}
}

void RomDataFromTxt()
{
	short real;
	short imag;
	short k;
	short A = pow(2, 8) - 1;

	//AddrRom   第一级使用的旋转因子
	DataRom.real = A;
	DataRom.image = 0;

	//DataRom0[16] 第二级使用的旋转因子
	k = 0;
	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			real = (short)(A*cos(-2 * 64 * i*j*pi / 1024));
			if (real >= 0)
			{
				real = real & 0x01ff;
			}
			else
			{
				real = (real + 512) & 0x01ff;//加上符号位就好了
			}
			imag = (short)(A*sin(-2 * 64 * i*j*pi / 1024));
			if (imag >= 0)
			{
				imag = imag & 0x01ff;
			}
			else
			{
				imag = (imag + 512) & 0x01ff;//将负数转化为补码再加上符号位
			}
			DataRom0[k].real = real;
			DataRom0[k].image = imag;
			k = k + 1;
		}
	}
	//DataRom1[64] 第三极使用的旋转因子
	k = 0;
	int num;
	for (int L = 0; L < 4; ++L)
	{
		for (int i = 0; i < 4; ++i)
		{
			num = L + i * 4;
			for (int j = 0; j < 4; ++j)
			{
				real = (short)(A*cos(-2 * 16 * num*j*pi / 1024));
				if (real >= 0)
				{
					real = real & 0x01ff;
				}
				else
				{
					real = (real + 512) & 0x01ff;//加上符号位就好了
				}
				imag = (short)(A*sin(-2 * 16 * num*j*pi / 1024));
				if (imag >= 0)
				{
					imag = imag & 0x01ff;
				}
				else
				{
					imag = (imag + 512) & 0x01ff;//将负数转化为补码再加上符号位
				}
				DataRom1[k].real = real;
				DataRom1[k].image = imag;
				k = k + 1;
			}
		}
	}

	//DataRom2[256] 第四级使用的旋转因子
	k = 0;
	num = 0;
	for (int L1 = 0; L1 < 4; ++L1)
	{
		for (int L = 0; L < 4; ++L)
		{
			for (int i = 0; i < 4; ++i)
			{
				num = L1 + (L + i * 4) * 4;
				for (int j = 0; j < 4; ++j)
				{
					real = (short)(A*cos(-2 * 4 * num*j*pi / 1024));
					if (real >= 0)
					{
						real = real & 0x01ff;
					}
					else
					{
						real = (real + 512) & 0x01ff;//加上符号位就好了
					}
					imag = (short)(A*sin(-2 * 4 * num*j*pi / 1024));
					if (imag >= 0)
					{
						imag = imag & 0x01ff;
					}
					else
					{
						imag = (imag + 512) & 0x01ff;//将负数转化为补码再加上符号位
					}
					DataRom2[k].real = real;
					DataRom2[k].image = imag;
					k = k + 1;
				}
			}
		}
	}
	//DataRom3[1024] 第五级使用的旋转因子
	k = 0;
	num = 0;
	for (int L2 = 0; L2 < 4; ++L2)
	{
		for (int L1 = 0; L1 < 4; ++L1)
		{
			for (int L = 0; L < 4; ++L)
			{
				for (int i = 0; i < 4; ++i)
				{
					num = L2 + (L1 + (L + i * 4) * 4) * 4;
					for (int j = 0; j < 4; ++j)
					{
						real = (short)(A*cos(-2 * num*j*pi / 1024));
						if (real >= 0)
						{
							real = real & 0x01ff;
						}
						else
						{
							real = (real + 512) & 0x01ff;//加上符号位就好了
						}
						imag = (short)(A*sin(-2 * num*j*pi / 1024));
						if (imag >= 0)
						{
							imag = imag & 0x01ff;
						}
						else
						{
							imag = (imag + 512) & 0x01ff;//将负数转化为补码再加上符号位
						}
						DataRom3[k].real = real;
						DataRom3[k].image = imag;
						k = k + 1;
					}
				}
			}
		}
	}
}

void RomAddrGenerate() {
	for (int i = 0; i < SIZE; ++i)
	{
		int temp;
		int temp1;
		temp = i / 256;
		temp1 = i % 4;
		Addr0Rom[i] = temp * 4 + temp1;//{ad_reg2[9:8], ad_reg2[1:0]}
	}

	for (int i = 0; i < SIZE; ++i)
	{
		int temp;
		int temp1;
		temp = i / 64;
		temp1 = i % 4;
		Addr1Rom[i] = temp * 4 + temp1;//{ad_reg3[9:6], ad_reg3[1:0]}
	}

	for (int i = 0; i < SIZE; ++i)
	{
		int temp;
		int temp1;
		temp = i / 16;
		temp1 = i % 4;// {ad_reg4[9:4], ad_reg4[1:0]}
		Addr2Rom[i] = temp * 4 + temp1;
	}

	for (int i = 0; i < SIZE; ++i) {
		Addr3Rom[i] = i;
	}
}


void ComputeData(Bcomplex *x1, Bcomplex *x2, Bcomplex *x3, Bcomplex *x4, Bcomplex r1, Bcomplex r2, Bcomplex r3, Bcomplex r4) {
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

	if (r2.real > 256) {
		r2r = -512 + r2.real;
	}
	else {
		r2r = r2.real;
	}

	if (r2.image > 256) {
		r2i = -512 + r2.image;
	}
	else {
		r2i = r2.image;
	}

	if (r3.real > 256) {
		r3r = -512 + r3.real;
	}
	else {
		r3r = r3.real;
	}

	if (r3.image > 256) {
		r3i = -512 + r3.image;
	}
	else {
		r3i = r3.image;
	}

	if (r4.real > 256) {
		r4r = -512 + r4.real;
	}
	else {
		r4r = r4.real;
	}

	if (r4.image > 256) {
		r4i = -512 + r4.image;
	}
	else {
		r4i = r4.image;
	}


	//  将无符号数据转化为有符号数据，这里直接使用(signed)

	brw1pr = ((signed)x2->real)*r2i; biw1pi = ((signed)x2->image)*r2i;
	crw2pr = ((signed)x3->real)*r3r; ciw2pi = ((signed)x3->image)*r3i;
	drw3pr = ((signed)x4->real)*r4r; diw3pi = ((signed)x4->image)*r4i;
	brw1pi = ((signed)x2->real)*r2i; biw1pr = ((signed)x2->image)*r2r;
	crw2pi = ((signed)x3->real)*r3i; ciw2pr = ((signed)x3->image)*r3r;
	drw3pi = ((signed)x4->real)*r4i; diw3pr = ((signed)x4->image)*r4r;

	mer = (signed)(x1->real) * 256 + brw1pr - biw1pi + crw2pr - ciw2pi + drw3pr - diw3pi;
	mei = (signed)(x1->image) * 256 + brw1pi + biw1pr + crw2pi + ciw2pr + drw3pi + diw3pr;
	mfr = (signed)(x1->real) * 256 + brw1pi + biw1pr - crw2pr + ciw2pi - drw3pi - diw3pr; //原+crw2pr+ciw2pi
	mfi = (signed)(x1->image) * 256 - brw1pr + biw1pi - crw2pi - ciw2pr + drw3pr - diw3pi;
	mgr = (signed)(x1->real) * 256 - brw1pr + biw1pi + crw2pr - ciw2pi - drw3pr + diw3pi;
	mgi = (signed)(x1->image) * 256 - brw1pi - biw1pr + crw2pi + ciw2pr - drw3pi - diw3pr;
	mhr = (signed)(x1->real) * 256 - brw1pi - biw1pr - crw2pr + ciw2pi + drw3pi + diw3pr;//原+crw2pr+ciw2pi
	mhi = (signed)(x1->image) * 256 + brw1pr - biw1pi - crw2pi - ciw2pr - drw3pr + diw3pi;

	//计算的数据进行截位处理
	unsigned int temp;
	unsigned int temp1;
	unsigned int temp2;

	temp2 = mer;
	temp = temp2 / 256;
	temp1 = temp % 2;
	temp = (temp2 >> 9);
	er = temp;
	if (temp1 == 1) {
		er = er + 1;
	}
	// 	er = er & 0x00007fff;
	// 	er = temp2 & 0x7fff;
	temp2 = mei;
	temp = mei / 256;
	temp1 = temp % 2;
	temp = (temp2 >> 9);
	ei = temp;
	if (temp1 == 1) {
		ei = ei + 1;
	}
	//	ei = ei & 0x00007fff;
	// 	ei = temp2 & 0x7fff;

	temp2 = mfr;
	temp = temp2 / 256;
	temp1 = temp % 2;
	temp = (temp2 >> 9);
	fr = temp;
	if (temp1 == 1) {
		fr = fr + 1;
	}
	// 	fr = fr & 0x00007fff;
	// 	fr = temp2 & 0x7fff;
	temp2 = mfi;
	temp = temp2 / 256;
	temp1 = temp % 2;
	temp = (temp2 >> 9);
	fi = temp;
	if (temp1 == 1) {
		fi = fi + 1;
	}
	//	fi = fi & 0x00007fff;
	// 	fi = temp2 & 0x7fff;
	temp2 = mgr;
	temp = temp2 / 256;
	temp1 = temp % 2;
	temp = (temp2 >> 9);
	gr = temp;
	if (temp1 == 1) {
		gr = gr + 1;
	}
	//    gr = gr & 0x00007fff;
	// 	gr = temp2;
	temp2 = mgi;
	temp = temp2 / 256;
	temp1 = temp % 2;
	temp = (temp2 >> 9);
	gi = temp;
	if (temp1 == 1) {
		gi = gi + 1;
	}
	//	gi = gi & 0x00007fff;
	// 	gi = temp2 & 0x7fff;
	temp2 = mhr;
	temp = temp2 / 256;
	temp1 = temp % 2;
	temp = (temp2 >> 9);
	hr = temp;
	if (temp1 == 1) {
		hr = hr + 1;
	}
	// 	hr = hr & 0x00007fff;
	// 	hr = temp2 & 0x7fff;
	temp2 = mhi;
	temp = temp2 / 256;
	temp1 = temp % 2;
	temp = (temp2 >> 9);
	hi = temp;
	if (temp1 == 1) {
		hi = hi + 1;
	}
	//    hi = hi & 0x00007fff;
	// 	hi = temp2 & 0x7fff;

	x1->real = er;
	x1->image = ei;

	x2->real = fr;
	x2->image = fi;

	x3->real = gr;
	x3->image = gi;

	x4->real = hr;
	x4->image = hi;
}


void BufflyFFT() {
	// 蝶形计算的数据，Idata[SIZE]

	//第一级蝶形计算
	//地址:addr0[SIZE]
	//旋转因子:DataRom
	for (int i = 0; i < 1024; i = i + 4) {
		Bcomplex x1, x2, x3, x4;
		Bcomplex r1, r2, r3, r4;
		x1 = Idata[addr0[i]];
		x2 = Idata[addr0[i + 1]];
		x3 = Idata[addr0[i + 2]];
		x4 = Idata[addr0[i + 3]];

		r1 = DataRom;
		r2 = DataRom;
		r3 = DataRom;
		r4 = DataRom;

		ComputeData(&x1, &x2, &x3, &x4, r1, r2, r3, r4);
		Idata[addr0[i]] = x1;
		Idata[addr0[i + 1]] = x2;
		Idata[addr0[i + 2]] = x3;
		Idata[addr0[i + 3]] = x4;
	}

	//第二级蝶形计算
	//地址:addr1[SIZE]
	//旋转因子:DataRom0[16]
	//旋转因子地址:Addr0Rom[SIZE]

	for (int i = 0; i < 1024; i = i + 4) {
		Bcomplex x1, x2, x3, x4;
		Bcomplex r1, r2, r3, r4;
		x1 = Idata[addr1[i]];
		x2 = Idata[addr1[i + 1]];
		x3 = Idata[addr1[i + 2]];
		x4 = Idata[addr1[i + 3]];

		r1 = DataRom0[Addr0Rom[i]];
		r2 = DataRom0[Addr0Rom[i + 1]];
		r3 = DataRom0[Addr0Rom[i + 2]];
		r4 = DataRom0[Addr0Rom[i + 3]];

		ComputeData(&x1, &x2, &x3, &x4, r1, r2, r3, r4);
		Idata[addr1[i]] = x1;
		Idata[addr1[i + 1]] = x2;
		Idata[addr1[i + 2]] = x3;
		Idata[addr1[i + 3]] = x4;

	}

	//第三级蝶形计算
	//地址:addr2[SIZE]
	//旋转因子:DataRom1[64]
	//旋转因子地址:Addr1Rom[SIZE]

	for (int i = 0; i < 1024; i = i + 4) {
		Bcomplex x1, x2, x3, x4;
		Bcomplex r1, r2, r3, r4;
		x1 = Idata[addr2[i]];
		x2 = Idata[addr2[i + 1]];
		x3 = Idata[addr2[i + 2]];
		x4 = Idata[addr2[i + 3]];

		r1 = DataRom1[Addr1Rom[i]];
		r2 = DataRom1[Addr1Rom[i + 1]];
		r3 = DataRom1[Addr1Rom[i + 2]];
		r4 = DataRom1[Addr1Rom[i + 3]];

		ComputeData(&x1, &x2, &x3, &x4, r1, r2, r3, r4);
		Idata[addr1[i]] = x1;
		Idata[addr1[i + 1]] = x2;
		Idata[addr1[i + 2]] = x3;
		Idata[addr1[i + 3]] = x4;
	}

	//第四级蝶形计算
	//地址:addr3[SIZE]
	//旋转因子:DataRom2[256]
	//旋转因子地址:Addr2Rom[SIZE]
	for (int i = 0; i < 1024; i = i + 4) {
		Bcomplex x1, x2, x3, x4;
		Bcomplex r1, r2, r3, r4;
		x1 = Idata[addr3[i]];
		x2 = Idata[addr3[i + 1]];
		x3 = Idata[addr3[i + 2]];
		x4 = Idata[addr3[i + 3]];

		r1 = DataRom2[Addr2Rom[i]];
		r2 = DataRom2[Addr2Rom[i + 1]];
		r3 = DataRom2[Addr2Rom[i + 2]];
		r4 = DataRom2[Addr2Rom[i + 3]];

		ComputeData(&x1, &x2, &x3, &x4, r1, r2, r3, r4);
		Idata[addr3[i]] = x1;
		Idata[addr3[i + 1]] = x2;
		Idata[addr3[i + 2]] = x3;
		Idata[addr3[i + 3]] = x4;
	}

	//第五级蝶形计算
	//地址:addr4[SIZE]
	//旋转因子:DataRom3[256]
	//旋转因子地址:Addr3Rom[SIZE]
	for (int i = 0; i < 1024; i = i + 4) {
		Bcomplex x1, x2, x3, x4;
		Bcomplex r1, r2, r3, r4;
		x1 = Idata[addr4[i]];
		x2 = Idata[addr4[i + 1]];
		x3 = Idata[addr4[i + 2]];
		x4 = Idata[addr4[i + 3]];

		r1 = DataRom3[Addr3Rom[i]];
		r2 = DataRom3[Addr3Rom[i + 1]];
		r3 = DataRom3[Addr3Rom[i + 2]];
		r4 = DataRom3[Addr3Rom[i + 3]];

		ComputeData(&x1, &x2, &x3, &x4, r1, r2, r3, r4);
		Idata[addr4[i]] = x1;
		Idata[addr4[i + 1]] = x2;
		Idata[addr4[i + 2]] = x3;
		Idata[addr4[i + 3]] = x4;
	}

	//将计算之后的数据倒叙出来
	//地址:addr5[SIZE]
	for (int i = 0; i < SIZE; ++i) {
		Odata[i] = Idata[addr5[i]];
	}
}


int main() {
	for (int i = 0; i < SIZE; ++i) {
		Fdata[i].real = 1 / 32.0;
		Fdata[i].image = 0;
	}

	Bcomplex x1, x2, x3, x4;
	Bcomplex r1, r2, r3, r4;
	GeneralFxiedPoint();
	LevelFftAddr();
	RomDataFromTxt();
	RomAddrGenerate();
	BufflyFFT();

	for (int i = 0; i < SIZE; ++i) {
		unsigned short real;
		unsigned short image;
		real = Odata[i].real;
		image = Odata[i].image;
		cout << "real:" << real << "  image:" << image << endl;
	}

	system("pause");
	return 0;
}

