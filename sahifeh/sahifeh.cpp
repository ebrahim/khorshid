#include <cstdio>
#include <stdint.h>

#define MAX_SIZE (1<<24)
#define NEW_PAGE 0x000182
#define ENGLISH_START 0x020181
#define ENGLISH_END 0x01007A

// TODO: Separate two consecutive joining characters which should be non-joined using a JWNJ

int main(int argc, const char* argv[])
{
	if (argc > 1 && freopen(argv[1], "r", stdin) == NULL)
	{
		fputs("Error: Failed to open input file\n", stderr);
		return 1;
	}
	const char* map[256] = { NULL };
	uint8_t map_size[256] = { 0 };
	for (int i = 0; i < 256; ++i)
		switch (i)
		{
			case 0x01:		// که
				map[i] = "\xDA\xA9\xD9\x87";
				map_size[i] = 4;
				break;
			case 0x02:		// به
				map[i] = "\xD8\xA8\xD9\x87";
				map_size[i] = 4;
				break;
			case 0x03:		// را
				map[i] = "\xD8\xB1\xD8\xA7";
				map_size[i] = 4;
				break;
			case 0x04:		// در
				map[i] = "\xD8\xAF\xD8\xB1";
				map_size[i] = 4;
				break;
			case 0x05:		// این
				map[i] = "\xD8\xA7\xDB\x8C\xD9\x86";
				map_size[i] = 6;
				break;
			case 0x06:		// از
				map[i] = "\xD8\xA7\xD8\xB2";
				map_size[i] = 4;
				break;
			case 0x07:		// است
				map[i] = "\xD8\xA7\xD8\xB3\xD8\xAA";
				map_size[i] = 6;
				break;
			case 0x08:		// ما
				map[i] = "\xD9\x85\xD8\xA7";
				map_size[i] = 4;
				break;
			case 0x20:		// فاصله
				map[i] = " ";
				map_size[i] = 1;
				break;
			case 0x65:		// .
				map[i] = ".";
				map_size[i] = 1;
				break;
			case 0x66:		// :
				map[i] = ":";
				map_size[i] = 1;
				break;
			case 0x67:		// ؛
				map[i] = "\xD8\x9B";
				map_size[i] = 2;
				break;
			case 0x69:		// ، (ویرگول)
				map[i] = "\xD8\x8C";
				map_size[i] = 2;
				break;
			case 0x6A:		// ؟
				map[i] = "\xD8\x9F";
				map_size[i] = 2;
				break;
			case 0x6B:		// (
				map[i] = "(";
				map_size[i] = 1;
				break;
			case 0x6C:		// )
				map[i] = ")";
				map_size[i] = 1;
				break;
			case 0x6D:		// [
				map[i] = "[";
				map_size[i] = 1;
				break;
			case 0x6E:		// ]
				map[i] = "]";
				map_size[i] = 1;
				break;
			case 0x71:		// !
				map[i] = "!";
				map_size[i] = 1;
				break;
			case 0x72:		// -
				map[i] = "-";
				map_size[i] = 1;
				break;
			case 0x73:		// «
				map[i] = "\xC2\xAB";
				map_size[i] = 2;
				break;
			case 0x74:		// »
				map[i] = "\xC2\xBB";
				map_size[i] = 2;
				break;
			case 0x00:		// سر خط؟
			case 0x75:		// سر خط
				map[i] = "\n";
				map_size[i] = 1;
				break;
			case 0x76:		// tab
				map[i] = "\t";
				map_size[i] = 1;
				break;
			case 0x77:		// /
				map[i] = "/";
				map_size[i] = 1;
				break;
			case 0x7A:		// *
				map[i] = "*";
				map_size[i] = 1;
				break;
			case 0x85:		// خط افقی (برای جدا کردن پاورقی)
				map[i] = "--------------------";
				map_size[i] = 20;
				break;
			case 0x8D:		// ۰
				map[i] = "\xDB\xB0";
				map_size[i] = 2;
				break;
			case 0x8E:		// ۱
				map[i] = "\xDB\xB1";
				map_size[i] = 2;
				break;
			case 0x8F:		// ۲
				map[i] = "\xDB\xB2";
				map_size[i] = 2;
				break;
			case 0x90:		// ۳
				map[i] = "\xDB\xB3";
				map_size[i] = 2;
				break;
			case 0x91:		// ۴
				map[i] = "\xDB\xB4";
				map_size[i] = 2;
				break;
			case 0x92:		// ۵
				map[i] = "\xDB\xB5";
				map_size[i] = 2;
				break;
			case 0x93:		// ۶
				map[i] = "\xDB\xB6";
				map_size[i] = 2;
				break;
			case 0x94:		// ۷
				map[i] = "\xDB\xB7";
				map_size[i] = 2;
				break;
			case 0x95:		// ۸
				map[i] = "\xDB\xB8";
				map_size[i] = 2;
				break;
			case 0x96:		// ۹
				map[i] = "\xDB\xB9";
				map_size[i] = 2;
				break;
			case 0x97:		// فتحه
				map[i] = "\xD9\x8E";
				map_size[i] = 2;
				break;
			case 0x98:		// کسره
				map[i] = "\xD9\x90";
				map_size[i] = 2;
				break;
			case 0x99:		// ضمه
				map[i] = "\xD9\x8F";
				map_size[i] = 2;
				break;
			case 0x9A:		// الف مقصوره مفتوح
				map[i] = "\xD9\xB0";
				map_size[i] = 2;
				break;
			case 0x9B:		// الف مقصوره مکسور
				map[i] = "\xD9\x96";
				map_size[i] = 2;
				break;
			case 0x9C:		// تنوین نصب
				map[i] = "\xD9\x8B";
				map_size[i] = 2;
				break;
			case 0x9D:		// تنوین کسر
				map[i] = "\xD9\x8D";
				map_size[i] = 2;
				break;
			case 0xA1:		// تنوین رفع
				map[i] = "\xD9\x8C";
				map_size[i] = 2;
				break;
			case 0xA2:		// تشدید مفتوح
				map[i] = "\xD9\x91\xD9\x8E";
				map_size[i] = 4;
				break;
			case 0xA4:		// تشدید مکسور
				map[i] = "\xD9\x91\xD9\x90";
				map_size[i] = 4;
				break;
			case 0xA5:		// تشدید مرفوع
				map[i] = "\xD9\x91\xD9\x8F";
				map_size[i] = 4;
				break;
			case 0xA8:		// تشدید و الف مقصوره
				map[i] = "\xD9\x91\xD9\xB0";
				map_size[i] = 0;		// الف عمداً حذف شد
				break;
			case 0xA9:		// تشدید و تنوین نصب
				map[i] = "\xD9\x91\xD9\x8B";
				map_size[i] = 4;
				break;
			case 0xAA:		// تشدید و تنوین کسر
				map[i] = "\xD9\x91\xD9\x8D";
				map_size[i] = 4;
				break;
			case 0xAB:		// تشدید و تنوین رفع
				map[i] = "\xD9\x91\xD9\x8C";
				map_size[i] = 4;
				break;
			case 0xAC:		// تشدید
				map[i] = "\xD9\x91";
				map_size[i] = 2;
				break;
			case 0xAD:		// علامت سکون
				map[i] = "\xD9\x92";
				map_size[i] = 2;
				break;
			case 0xB0:		// آ جدا
			case 0xB1:		// آ آخری (مثل الآن)
				map[i] = "\xD8\xA2";
				map_size[i] = 2;
				break;
			case 0xB2:		// الف جدا
			case 0xB3:		// الف آخر
				map[i] = "\xD8\xA7";
				map_size[i] = 2;
				break;
			case 0xB4:		// همزه جدا
				map[i] = "\xD8\xA1";
				map_size[i] = 2;
				break;
			case 0xB5:		// الف و همزه مفتوح اول
			case 0xB6:		// الف و همزه مفتوح آخر
				map[i] = "\xD8\xA3";
				map_size[i] = 2;
				break;
			case 0xB7:		// ﺎﻠﻓ ﻭ ﻪﻣﺰﻫ ﻡکﺱﻭﺭ ﺍﻮﻟ
			case 0xB8:		// ﺎﻠﻓ ﻭ ﻪﻣﺰﻫ ﻡکﺱﻭﺭ آخر
				map[i] = "\xD8\xA5";
				map_size[i] = 2;
				break;
			case 0xB9:		// ؤ آخر
				map[i] = "\xD8\xA4";
				map_size[i] = 2;
				break;
			case 0xBA:		// ئ آخر
				map[i] = "\xD8\xA6";
				map_size[i] = 2;
				break;
			case 0xBC:		// همزه اول
				map[i] = "\xD8\xA6";
				map_size[i] = 2;
				break;
			case 0xBD:		// ب آخر
			case 0xBE:		// ب اول
				map[i] = "\xD8\xA8";
				map_size[i] = 2;
				break;
			case 0xBF:		// پ آخر
			case 0xC0:		// پ وسط
				map[i] = "\xD9\xBE";
				map_size[i] = 2;
				break;
			case 0xC1:		// ت آخر
			case 0xC2:		// ت وسط
				map[i] = "\xD8\xAA";
				map_size[i] = 2;
				break;
			case 0xC3:		// ة جدا
				map[i] = "\xD8\xA9";
				map_size[i] = 2;
				break;
			case 0xC4:		// ث آخر
			case 0xC5:		// ث اول
				map[i] = "\xD8\xAB";
				map_size[i] = 2;
				break;
			case 0xC6:		// جیم آخر
			case 0xC7:		// جیم اول
				map[i] = "\xD8\xAC";
				map_size[i] = 2;
				break;
			case 0xC8:		// چ آخر
			case 0xC9:		// چ اول
				map[i] = "\xDA\x86";
				map_size[i] = 2;
				break;
			case 0xCA:		// ح آخر
			case 0xCB:		// ح اول
				map[i] = "\xD8\xAD";
				map_size[i] = 2;
				break;
			case 0xCC:		// خ آخر
			case 0xCD:		// خ اول و وسط
				map[i] = "\xD8\xAE";
				map_size[i] = 2;
				break;
			case 0xCE:		// دال جدا و آخر
				map[i] = "\xD8\xAF";
				map_size[i] = 2;
				break;
			case 0xCF:		// ذال جدا
				map[i] = "\xD8\xB0";
				map_size[i] = 2;
				break;
			case 0xD0:		// ر آخر
				map[i] = "\xD8\xB1";
				map_size[i] = 2;
				break;
			case 0xD1:		// ز جدا و آخر
				map[i] = "\xD8\xB2";
				map_size[i] = 2;
				break;
			case 0xD2:		// ژ آخر
				map[i] = "\xDA\x98";
				map_size[i] = 2;
				break;
			case 0xD3:		// سین آخر
			case 0xD4:		// سین اول
				map[i] = "\xD8\xB3";
				map_size[i] = 2;
				break;
			case 0xD5:		// شین جدا
			case 0xD6:		// شین اول و وسط
				map[i] = "\xD8\xB4";
				map_size[i] = 2;
				break;
			case 0xD7:		// صاد آخر
			case 0xD8:		// صاد وسط
				map[i] = "\xD8\xB5";
				map_size[i] = 2;
				break;
			case 0xD9:		// ضاد آخر
			case 0xDA:		// ضاد اول
				map[i] = "\xD8\xB6";
				map_size[i] = 2;
				break;
			case 0xDB:		// طای اول
				map[i] = "\xD8\xB7";
				map_size[i] = 2;
				break;
			case 0xDC:		// ظای اول
				map[i] = "\xD8\xB8";
				map_size[i] = 2;
				break;
			case 0xDD:		// عین جدا
			case 0xDE:		// عین آخر
			case 0xDF:		// عین اول
			case 0xE1:		// عین وسط
				map[i] = "\xD8\xB9";
				map_size[i] = 2;
				break;
			case 0xE2:		// غین جدا
			case 0xE3:		// غین آخر
			case 0xE4:		// غین اول
			case 0xE5:		// غین وسط
				map[i] = "\xD8\xBA";
				map_size[i] = 2;
				break;
			case 0xE6:		// ف آخر
			case 0xE7:		// ف وسط
				map[i] = "\xD9\x81";
				map_size[i] = 2;
				break;
			case 0xE8:		// قاف جدا
			case 0xE9:		// قاف اول
				map[i] = "\xD9\x82";
				map_size[i] = 2;
				break;
			case 0xEA:		// کاف آخر
			case 0xEB:		// کاف وسط
				map[i] = "\xDA\xA9";
				map_size[i] = 2;
				break;
			case 0xEC:		// گاف آخر
			case 0xED:		// گاف اول
				map[i] = "\xDA\xAF";
				map_size[i] = 2;
				break;
			case 0xEE:		// لام جدا
			case 0xF0:		// لام اول و وسط
				map[i] = "\xD9\x84";
				map_size[i] = 2;
				break;
			case 0xF1:		// میم جدا
			case 0xF2:		// میم اول
				map[i] = "\xD9\x85";
				map_size[i] = 2;
				break;
			case 0xF3:		// نون جدا
			case 0xF4:		// نون اول
				map[i] = "\xD9\x86";
				map_size[i] = 2;
				break;
			case 0xF5:		// ه آخر و جدا
			case 0xF6:		// ه آخر با ی ربط
			case 0xF7:		// ه اول
				map[i] = "\xD9\x87";
				map_size[i] = 2;
				break;
			case 0xF8:		// واو آخر و جدا
				map[i] = "\xD9\x88";
				map_size[i] = 2;
				break;
			case 0xF9:		// ی جدا
			case 0xFB:		// ی آخر
			case 0xFD:		// ی اول و وسط
				map[i] = "\xDB\x8C";
				map_size[i] = 2;
				break;
			case 0xFA:		// ي عربی جدا
			case 0xFC:		// ي عربی آخر
				map[i] = "\xD9\x8A";
				map_size[i] = 2;
				break;
			default:
				break;
		}
	char map_en[256] = { NULL };
	for (int i = 0; i < 256; ++i)
		switch (i)
		{
			case 0x20:
				map_en[i] = ' ';
				break;
			case 0x6A:
				map_en[i] = ')';
				break;
			case 0x6B:
				map_en[i] = '(';
				break;
			case 0x8D:
			case 0x8E:
			case 0x8F:
			case 0x90:
			case 0x91:
			case 0x92:
			case 0x93:
			case 0x94:
			case 0x95:
			case 0x96:
			case 0x97:
			case 0x98:
			case 0x99:
			case 0x9A:
			case 0x9B:
			case 0x9C:
			case 0x9D:
			case 0x9E:
			case 0x9F:
			case 0xA0:
			case 0xA1:
			case 0xA2:
			case 0xA3:
			case 0xA4:
			case 0xA5:
			case 0xA6:
				map_en[i] = i + 'A' - 0x8D;
				break;
			case 0xA7:
			case 0xA8:
			case 0xA9:
			case 0xAA:
			case 0xAB:
			case 0xAC:
			case 0xAD:
			case 0xAE:
			case 0xAF:
			case 0xB0:
			case 0xB1:
			case 0xB2:
			case 0xB3:
			case 0xB4:
			case 0xB5:
			case 0xB6:
			case 0xB7:
			case 0xB8:
			case 0xB9:
			case 0xBA:
			case 0xBB:
			case 0xBC:
			case 0xBD:
			case 0xBE:
			case 0xBF:
			case 0xC0:
				map_en[i] = i + 'a' - 0xA7;
				break;
			default:
				break;
		}

	uint8_t* buf = new uint8_t[MAX_SIZE];
	size_t size = fread(buf, 1, MAX_SIZE, stdin);

	bool english = false;
	const uint8_t* data = buf;
	while (size > 0)
	{
		if (size > 6)
		{
			uint32_t signature = 0xFFFFFF & *(uint32_t*) data;
			data += 3;
			size -= 3;
			switch (signature)
			{
				case NEW_PAGE:
				{
					uint8_t volume = *data;
					++data;
					--size;
					uint16_t page = *(uint16_t*) data;
					data += 2;
					size -= 2;
					printf("\n=================== volume #%d page #%d ====================\n", volume, page);
					break;
				}
				case ENGLISH_START:
					english = true;
					fwrite("\xE2\x80\xAE", 1, 3, stdout);
					break;
				case ENGLISH_END:
					english = false;
					break;
				default:
					data -= 3;
					size += 3;
					break;
			}
		}
		uint8_t byte = *data;
		switch (byte)
		{
			case 0x7D:		// آغاز یک بخش؟ تعیین رنگ و قلم؟
			case 0x7E:		// آغاز یک بخش؟ تعیین رنگ و قلم؟
				++data;
				--size;
				switch (*data)
				{
					case 0x01:		// عنوان
						printf(" !!! عنوان !!! ");
						break;
					case 0x03:		// حدیث
						printf(" !!! حدیث !!! ");
						break;
					case 0x04:		// آیه
						printf(" !!! آیه !!! ");
						break;
					case 0x05:		// شعر
						printf(" !!! شعر !!! ");
						break;
					case 0x08:		// ترجمه
						printf(" !!! ترجمه !!! ");
						break;
					case 0x0B:		// پاورقی
						printf(" !!! پاورقی !!! ");
						break;
					case 0x0C:		// آیه در پاورقی
						printf(" !!! آیه در پاورقی !!! ");
						break;
					case 0x0D:		// حدیث در پاورقی
						printf(" !!! حدیث در پاورقی !!! ");
						break;
					case 0x0E:		// شعر در پاورقی
						printf(" !!! شعر در پاورقی !!! ");
						break;
					case 0x0F:		// توضیح در پاورقی
						printf(" !!! توضیح در پاورقی !!! ");
						break;
					default:
						printf(" !!! ناشناس [%#.2x] !!! ", *data);
						break;
				}
				break;
			case 0x80:		// اتمام یک بخش؟
				printf(" !!! پایان !!! ");
				break;
			default:
				const char* to = NULL;
				uint16_t to_size = 0;
				if (english)
				{
					if (map_en[byte])
					{
						to = &map_en[byte];
						to_size = 1;
					}
				}
				else
				{
					to = map[byte];
					to_size = map_size[byte];
				}
				if (to_size)
					fwrite(to, 1, to_size, stdout);
				else if (!to)
				{
					printf("<[%#.2x]>", byte);
					fprintf(stderr, "unknown byte: %#.2x\n", byte);
				}
				break;
		}
		++data;
		--size;
	}

	delete [] buf;
	return 0;
}
