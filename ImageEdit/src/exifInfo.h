/*
 * File:	exif.h
 * Purpose:	cpp EXIF reader
 * 16/Mar/2003 <ing.davide.pizzolato@libero.it>
 * based on jhead-1.8 by Matthias Wandel <mwandel(at)rim(dot)net>
 */
////////////////////////////////////图片信息////////////////////////
/////////////////////////////////获取图片的信息////////////////
#if !defined(__exif_h)
#define __exif_h

#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

#define MAX_COMMENT 1000
#define MAX_SECTIONS 20

typedef struct tag_ExifInfo {
	char  Version      [5];
    char  CameraMake   [32];//相机生产厂家
    char  CameraModel  [40];//设备型号
    char  DateTime     [20];//拍摄时间
    int   Height, Width;//图片尺寸
    int   Orientation;
    int   IsColor;
    int   Process;
    int   FlashUsed;//'0' 表示闪光灯没有闪光, '1' 表示闪光灯闪光, '5' 表示闪光但没有检测反射光, '7' 表示闪光且检测了反射光.
    float FocalLength;//焦距  摄照片时的镜头的焦距长度. 单位是毫米.
    float ExposureTime;//快门速度
    float ApertureFNumber;//光圈值
    float Distance;
    float CCDWidth;
    float ExposureBias;//	曝光补偿
    int   Whitebalance;//白平衡   "AUTO"（0）, "WHITE PRESET"（1） etc.
    int   MeteringMode;//测光模式   '0' 表示未知, '1' 为平均测光, '2' 为中央重点测光, '3' 是点测光, '4' 是多点测光, '5' 是多区域测光, '6' 部分测光, '255' 则是其他.
    int   ExposureProgram;
    int   ISOequivalent;//感光度
    int   CompressionLevel;
	float FocalplaneXRes;
	float FocalplaneYRes;
	float FocalplaneUnits;
	float Xresolution;
	float Yresolution;
	float ResolutionUnit;
	float Brightness;
    char  Comments[MAX_COMMENT];

    unsigned char * ThumbnailPointer;  /* Pointer at the thumbnail */
    unsigned ThumbnailSize;     /* Size of thumbnail. */

	bool  IsExif;

	char  LatitudeRef[4];		  // 纬度参考，例如南纬
//	char  Latitude[17];			  // 纬度值
	double Latitude;
	char  LongitudeRef[4];		  // 经度参考，例如东经
//	char  Longitude[17];		  // 经度值
	double Longitude;
	char  AltitudeRef[15];		  // 海拔高度参考
	float Altitude;				  // 海拔高度
	char  TimeStamp[15];		  // GPS时间

    unsigned long SpecialMode;


} EXIFINFO;

//--------------------------------------------------------------------------
// JPEG markers consist of one or more 0xFF unsigned chars, followed by a marker
// code unsigned char (which is not an FF).  Here are the marker codes of interest
// in this program.  (See jdmarker.c for a more complete list.)
//--------------------------------------------------------------------------

#define M_SOF0  0xC0            // Start Of Frame N
#define M_SOF1  0xC1            // N indicates which compression process
#define M_SOF2  0xC2            // Only SOF0-SOF2 are now in common use
#define M_SOF3  0xC3
#define M_SOF5  0xC5            // NB: codes C4 and CC are NOT SOF markers
#define M_SOF6  0xC6
#define M_SOF7  0xC7
#define M_SOF9  0xC9
#define M_SOF10 0xCA
#define M_SOF11 0xCB
#define M_SOF13 0xCD
#define M_SOF14 0xCE
#define M_SOF15 0xCF
#define M_SOI   0xD8            // Start Of Image (beginning of datastream)
#define M_EOI   0xD9            // End Of Image (end of datastream)
#define M_SOS   0xDA            // Start Of Scan (begins compressed data)
#define M_JFIF  0xE0            // Jfif marker
#define M_EXIF  0xE1            // Exif marker
#define M_COM   0xFE            // COMment 

class Cexif
{

typedef struct tag_Section_t{
    unsigned char*    Data;
    int      Type;
    unsigned Size;
} Section_t;

public:
	char m_szLastError[256];
	Cexif(EXIFINFO* info = NULL);
	~Cexif();
	bool DecodeExif(FILE* hFile);

	void getExifinfo(EXIFINFO* exifinfo)
	{ memcpy( exifinfo,m_exifinfo, sizeof(EXIFINFO));}
protected:
	bool process_EXIF(unsigned char * CharBuf, unsigned int length);
	void process_COM (const unsigned char * Data, int length);
	void process_SOFn (const unsigned char * Data, int marker);
	int Get16u(void * Short);
	int Get16m(void * Short);
	long Get32s(void * Long);
	unsigned long Get32u(void * Long);
	double ConvertAnyFormat(void * ValuePtr, int Format);
	bool ProcessExifDir(unsigned char * DirStart, unsigned char * OffsetBase, unsigned ExifLength,
                           EXIFINFO * const pInfo, unsigned char ** const LastExifRefdP);
	int ExifImageWidth;
	int MotorolaOrder;
	Section_t Sections[MAX_SECTIONS];
	int SectionsRead;
	bool freeinfo;
	EXIFINFO* m_exifinfo;
	
};

#endif
