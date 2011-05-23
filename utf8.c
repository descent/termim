#include <stdint.h>
#include <stdlib.h>
#include "utf8.h"

static const struct width_interval width_table[] = {
	{0x0, 0xA0, HALF},
	{0xA1, 0xA1, AMBI},
	{0xA2, 0xA3, HALF},
	{0xA4, 0xA4, AMBI},
	{0xA5, 0xA6, HALF},
	{0xA7, 0xA8, AMBI},
	{0xA9, 0xA9, HALF},
	{0xAA, 0xAA, AMBI},
	{0xAB, 0xAC, HALF},
	{0xAD, 0xAE, AMBI},
	{0xAF, 0xAF, HALF},
	{0xB0, 0xB4, AMBI},
	{0xB5, 0xB5, HALF},
	{0xB6, 0xBA, AMBI},
	{0xBB, 0xBB, HALF},
	{0xBC, 0xBF, AMBI},
	{0xC0, 0xC5, HALF},
	{0xC6, 0xC6, AMBI},
	{0xC7, 0xCF, HALF},
	{0xD0, 0xD0, AMBI},
	{0xD1, 0xD6, HALF},
	{0xD7, 0xD8, AMBI},
	{0xD9, 0xDD, HALF},
	{0xDE, 0xE1, AMBI},
	{0xE2, 0xE5, HALF},
	{0xE6, 0xE6, AMBI},
	{0xE7, 0xE7, HALF},
	{0xE8, 0xEA, AMBI},
	{0xEB, 0xEB, HALF},
	{0xEC, 0xED, AMBI},
	{0xEE, 0xEF, HALF},
	{0xF0, 0xF0, AMBI},
	{0xF1, 0xF1, HALF},
	{0xF2, 0xF3, AMBI},
	{0xF4, 0xF6, HALF},
	{0xF7, 0xFA, AMBI},
	{0xFB, 0xFB, HALF},
	{0xFC, 0xFC, AMBI},
	{0xFD, 0xFD, HALF},
	{0xFE, 0xFE, AMBI},
	{0xFF, 0x100, HALF},
	{0x101, 0x101, AMBI},
	{0x102, 0x110, HALF},
	{0x111, 0x111, AMBI},
	{0x112, 0x112, HALF},
	{0x113, 0x113, AMBI},
	{0x114, 0x11A, HALF},
	{0x11B, 0x11B, AMBI},
	{0x11C, 0x125, HALF},
	{0x126, 0x127, AMBI},
	{0x128, 0x12A, HALF},
	{0x12B, 0x12B, AMBI},
	{0x12C, 0x130, HALF},
	{0x131, 0x133, AMBI},
	{0x134, 0x137, HALF},
	{0x138, 0x138, AMBI},
	{0x139, 0x13E, HALF},
	{0x13F, 0x142, AMBI},
	{0x143, 0x143, HALF},
	{0x144, 0x144, AMBI},
	{0x145, 0x147, HALF},
	{0x148, 0x14B, AMBI},
	{0x14C, 0x14C, HALF},
	{0x14D, 0x14D, AMBI},
	{0x14E, 0x151, HALF},
	{0x152, 0x153, AMBI},
	{0x154, 0x165, HALF},
	{0x166, 0x167, AMBI},
	{0x168, 0x16A, HALF},
	{0x16B, 0x16B, AMBI},
	{0x16C, 0x1CD, HALF},
	{0x1CE, 0x1CE, AMBI},
	{0x1CF, 0x1CF, HALF},
	{0x1D0, 0x1D0, AMBI},
	{0x1D1, 0x1D1, HALF},
	{0x1D2, 0x1D2, AMBI},
	{0x1D3, 0x1D3, HALF},
	{0x1D4, 0x1D4, AMBI},
	{0x1D5, 0x1D5, HALF},
	{0x1D6, 0x1D6, AMBI},
	{0x1D7, 0x1D7, HALF},
	{0x1D8, 0x1D8, AMBI},
	{0x1D9, 0x1D9, HALF},
	{0x1DA, 0x1DA, AMBI},
	{0x1DB, 0x1DB, HALF},
	{0x1DC, 0x1DC, AMBI},
	{0x1DD, 0x250, HALF},
	{0x251, 0x251, AMBI},
	{0x252, 0x260, HALF},
	{0x261, 0x261, AMBI},
	{0x262, 0x2C3, HALF},
	{0x2C4, 0x2C4, AMBI},
	{0x2C5, 0x2C6, HALF},
	{0x2C7, 0x2C7, AMBI},
	{0x2C8, 0x2C8, HALF},
	{0x2C9, 0x2CB, AMBI},
	{0x2CC, 0x2CC, HALF},
	{0x2CD, 0x2CD, AMBI},
	{0x2CE, 0x2CF, HALF},
	{0x2D0, 0x2D0, AMBI},
	{0x2D1, 0x2D7, HALF},
	{0x2D8, 0x2DB, AMBI},
	{0x2DC, 0x2DC, HALF},
	{0x2DD, 0x2DD, AMBI},
	{0x2DE, 0x2DE, HALF},
	{0x2DF, 0x2DF, AMBI},
	{0x2E0, 0x2FF, HALF},
	{0x300, 0x36F, AMBI},
	{0x370, 0x390, HALF},
	{0x391, 0x3A9, AMBI},
	{0x3AA, 0x3B0, HALF},
	{0x3B1, 0x3C1, AMBI},
	{0x3C2, 0x3C2, HALF},
	{0x3C3, 0x3C9, AMBI},
	{0x3CA, 0x400, HALF},
	{0x401, 0x401, AMBI},
	{0x402, 0x40F, HALF},
	{0x410, 0x44F, AMBI},
	{0x450, 0x450, HALF},
	{0x451, 0x451, AMBI},
	{0x452, 0x10FC, HALF},
	{0x1100, 0x115F, FULL},
	{0x1160, 0x11A2, HALF},
	{0x11A3, 0x11A7, FULL},
	{0x11A8, 0x11F9, HALF},
	{0x11FA, 0x11FF, FULL},
	{0x1200, 0x200F, HALF},
	{0x2010, 0x2010, AMBI},
	{0x2011, 0x2012, HALF},
	{0x2013, 0x2016, AMBI},
	{0x2017, 0x2017, HALF},
	{0x2018, 0x2019, AMBI},
	{0x201A, 0x201B, HALF},
	{0x201C, 0x201D, AMBI},
	{0x201E, 0x201F, HALF},
	{0x2020, 0x2022, AMBI},
	{0x2023, 0x2023, HALF},
	{0x2024, 0x2027, AMBI},
	{0x2028, 0x202F, HALF},
	{0x2030, 0x2030, AMBI},
	{0x2031, 0x2031, HALF},
	{0x2032, 0x2033, AMBI},
	{0x2034, 0x2034, HALF},
	{0x2035, 0x2035, AMBI},
	{0x2036, 0x203A, HALF},
	{0x203B, 0x203B, AMBI},
	{0x203C, 0x203D, HALF},
	{0x203E, 0x203E, AMBI},
	{0x203F, 0x2071, HALF},
	{0x2074, 0x2074, AMBI},
	{0x2075, 0x207E, HALF},
	{0x207F, 0x207F, AMBI},
	{0x2080, 0x2080, HALF},
	{0x2081, 0x2084, AMBI},
	{0x2085, 0x20AB, HALF},
	{0x20AC, 0x20AC, AMBI},
	{0x20AD, 0x2102, HALF},
	{0x2103, 0x2103, AMBI},
	{0x2104, 0x2104, HALF},
	{0x2105, 0x2105, AMBI},
	{0x2106, 0x2108, HALF},
	{0x2109, 0x2109, AMBI},
	{0x210A, 0x2112, HALF},
	{0x2113, 0x2113, AMBI},
	{0x2114, 0x2115, HALF},
	{0x2116, 0x2116, AMBI},
	{0x2117, 0x2120, HALF},
	{0x2121, 0x2122, AMBI},
	{0x2123, 0x2125, HALF},
	{0x2126, 0x2126, AMBI},
	{0x2127, 0x212A, HALF},
	{0x212B, 0x212B, AMBI},
	{0x212C, 0x2152, HALF},
	{0x2153, 0x2154, AMBI},
	{0x2155, 0x215A, HALF},
	{0x215B, 0x215E, AMBI},
	{0x215F, 0x215F, HALF},
	{0x2160, 0x216B, AMBI},
	{0x216C, 0x216F, HALF},
	{0x2170, 0x2179, AMBI},
	{0x217A, 0x2188, HALF},
	{0x2189, 0x2199, AMBI},
	{0x219A, 0x21B7, HALF},
	{0x21B8, 0x21B9, AMBI},
	{0x21BA, 0x21D1, HALF},
	{0x21D2, 0x21D2, AMBI},
	{0x21D3, 0x21D3, HALF},
	{0x21D4, 0x21D4, AMBI},
	{0x21D5, 0x21E6, HALF},
	{0x21E7, 0x21E7, AMBI},
	{0x21E8, 0x21FF, HALF},
	{0x2200, 0x2200, AMBI},
	{0x2201, 0x2201, HALF},
	{0x2202, 0x2203, AMBI},
	{0x2204, 0x2206, HALF},
	{0x2207, 0x2208, AMBI},
	{0x2209, 0x220A, HALF},
	{0x220B, 0x220B, AMBI},
	{0x220C, 0x220E, HALF},
	{0x220F, 0x220F, AMBI},
	{0x2210, 0x2210, HALF},
	{0x2211, 0x2211, AMBI},
	{0x2212, 0x2214, HALF},
	{0x2215, 0x2215, AMBI},
	{0x2216, 0x2219, HALF},
	{0x221A, 0x221A, AMBI},
	{0x221B, 0x221C, HALF},
	{0x221D, 0x2220, AMBI},
	{0x2221, 0x2222, HALF},
	{0x2223, 0x2223, AMBI},
	{0x2224, 0x2224, HALF},
	{0x2225, 0x2225, AMBI},
	{0x2226, 0x2226, HALF},
	{0x2227, 0x222C, AMBI},
	{0x222D, 0x222D, HALF},
	{0x222E, 0x222E, AMBI},
	{0x222F, 0x2233, HALF},
	{0x2234, 0x2237, AMBI},
	{0x2238, 0x223B, HALF},
	{0x223C, 0x223D, AMBI},
	{0x223E, 0x2247, HALF},
	{0x2248, 0x2248, AMBI},
	{0x2249, 0x224B, HALF},
	{0x224C, 0x224C, AMBI},
	{0x224D, 0x2251, HALF},
	{0x2252, 0x2252, AMBI},
	{0x2253, 0x225F, HALF},
	{0x2260, 0x2261, AMBI},
	{0x2262, 0x2263, HALF},
	{0x2264, 0x2267, AMBI},
	{0x2268, 0x2269, HALF},
	{0x226A, 0x226B, AMBI},
	{0x226C, 0x226D, HALF},
	{0x226E, 0x226F, AMBI},
	{0x2270, 0x2281, HALF},
	{0x2282, 0x2283, AMBI},
	{0x2284, 0x2285, HALF},
	{0x2286, 0x2287, AMBI},
	{0x2288, 0x2294, HALF},
	{0x2295, 0x2295, AMBI},
	{0x2296, 0x2298, HALF},
	{0x2299, 0x2299, AMBI},
	{0x229A, 0x22A4, HALF},
	{0x22A5, 0x22A5, AMBI},
	{0x22A6, 0x22BE, HALF},
	{0x22BF, 0x22BF, AMBI},
	{0x22C0, 0x2311, HALF},
	{0x2312, 0x2312, AMBI},
	{0x2313, 0x2328, HALF},
	{0x2329, 0x232A, FULL},
	{0x232B, 0x244A, HALF},
	{0x2460, 0x24E9, AMBI},
	{0x24EA, 0x24EA, HALF},
	{0x24EB, 0x254B, AMBI},
	{0x254C, 0x254F, HALF},
	{0x2550, 0x2573, AMBI},
	{0x2574, 0x257F, HALF},
	{0x2580, 0x258F, AMBI},
	{0x2590, 0x2591, HALF},
	{0x2592, 0x2595, AMBI},
	{0x2596, 0x259F, HALF},
	{0x25A0, 0x25A1, AMBI},
	{0x25A2, 0x25A2, HALF},
	{0x25A3, 0x25A9, AMBI},
	{0x25AA, 0x25B1, HALF},
	{0x25B2, 0x25B3, AMBI},
	{0x25B4, 0x25B5, HALF},
	{0x25B6, 0x25B7, AMBI},
	{0x25B8, 0x25BB, HALF},
	{0x25BC, 0x25BD, AMBI},
	{0x25BE, 0x25BF, HALF},
	{0x25C0, 0x25C1, AMBI},
	{0x25C2, 0x25C5, HALF},
	{0x25C6, 0x25C8, AMBI},
	{0x25C9, 0x25CA, HALF},
	{0x25CB, 0x25CB, AMBI},
	{0x25CC, 0x25CD, HALF},
	{0x25CE, 0x25D1, AMBI},
	{0x25D2, 0x25E1, HALF},
	{0x25E2, 0x25E5, AMBI},
	{0x25E6, 0x25EE, HALF},
	{0x25EF, 0x25EF, AMBI},
	{0x25F0, 0x2604, HALF},
	{0x2605, 0x2606, AMBI},
	{0x2607, 0x2608, HALF},
	{0x2609, 0x2609, AMBI},
	{0x260A, 0x260D, HALF},
	{0x260E, 0x260F, AMBI},
	{0x2610, 0x2613, HALF},
	{0x2614, 0x2615, AMBI},
	{0x2616, 0x261B, HALF},
	{0x261C, 0x261C, AMBI},
	{0x261D, 0x261D, HALF},
	{0x261E, 0x261E, AMBI},
	{0x261F, 0x263F, HALF},
	{0x2640, 0x2640, AMBI},
	{0x2641, 0x2641, HALF},
	{0x2642, 0x2642, AMBI},
	{0x2643, 0x265F, HALF},
	{0x2660, 0x2661, AMBI},
	{0x2662, 0x2662, HALF},
	{0x2663, 0x2665, AMBI},
	{0x2666, 0x2666, HALF},
	{0x2667, 0x266A, AMBI},
	{0x266B, 0x266B, HALF},
	{0x266C, 0x266D, AMBI},
	{0x266E, 0x266E, HALF},
	{0x266F, 0x266F, AMBI},
	{0x2670, 0x269D, HALF},
	{0x269E, 0x269F, AMBI},
	{0x26A0, 0x26BD, HALF},
	{0x26BE, 0x26BF, AMBI},
	{0x26C0, 0x26C3, HALF},
	{0x26C4, 0x26CD, AMBI},
	{0x26CE, 0x26CE, HALF},
	{0x26CF, 0x26E1, AMBI},
	{0x26E2, 0x26E2, HALF},
	{0x26E3, 0x26E3, AMBI},
	{0x26E4, 0x26E7, HALF},
	{0x26E8, 0x26FF, AMBI},
	{0x2701, 0x273C, HALF},
	{0x273D, 0x273D, AMBI},
	{0x273E, 0x2756, HALF},
	{0x2757, 0x2757, AMBI},
	{0x2758, 0x2775, HALF},
	{0x2776, 0x277F, AMBI},
	{0x2780, 0x2B54, HALF},
	{0x2B55, 0x2B59, AMBI},
	{0x2C00, 0x2E31, HALF},
	{0x2E80, 0x303E, FULL},
	{0x303F, 0x303F, HALF},
	{0x3041, 0x3247, FULL},
	{0x3248, 0x324F, AMBI},
	{0x3250, 0x4DBF, FULL},
	{0x4DC0, 0x4DFF, HALF},
	{0x4E00, 0xA4C6, FULL},
	{0xA4D0, 0xA95F, HALF},
	{0xA960, 0xA97C, FULL},
	{0xA980, 0xABF9, HALF},
	{0xAC00, 0xD7FB, FULL},
	{0xD800, 0xDFFF, HALF},
	{0xE000, 0xF8FF, AMBI},
	{0xF900, 0xFAFF, FULL},
	{0xFB00, 0xFDFD, HALF},
	{0xFE00, 0xFE0F, AMBI},
	{0xFE10, 0xFE19, FULL},
	{0xFE20, 0xFE26, HALF},
	{0xFE30, 0xFE6B, FULL},
	{0xFE70, 0xFEFF, HALF},
	{0xFF01, 0xFF60, FULL},
	{0xFF61, 0xFFDC, HALF},
	{0xFFE0, 0xFFE6, FULL},
	{0xFFE8, 0xFFFC, HALF},
	{0xFFFD, 0xFFFD, AMBI},
	{0x10000, 0x16A38, HALF},
	{0x1B000, 0x1B001, FULL},
	{0x1D000, 0x1F0DF, HALF},
	{0x1F100, 0x1F12D, AMBI},
	{0x1F12E, 0x1F12E, HALF},
	{0x1F130, 0x1F19A, AMBI},
	{0x1F1E6, 0x1F1FF, HALF},
	{0x1F200, 0x1F251, FULL},
	{0x1F300, 0x1F773, HALF},
	{0x20000, 0x3FFFD, FULL},
	{0xE0001, 0xE007F, HALF},
};

int ustrlen(const char *s, int l){
	int r=0;
	while(unext(&s, &l)!=NULL)
		r+=1;
	return r;
}

int ustrwidth(const char *s, int l){
	int max, min, mid;
	int ret=0;
	const char *p;
	uint32_t ucs;
	while((p=unext(&s, &l))!=NULL){
		max = sizeof(width_table) / sizeof(struct width_interval) - 1;
		min = 0;
		ucs=unicode(p);
		if (ucs < width_table[0].beg || ucs > width_table[max].end){
			//noop
		}else while (max >= min) {
				mid = (min + max) / 2;
				if (ucs > width_table[mid].end)
					min = mid + 1;
				else if (ucs < width_table[mid].beg)
					max = mid - 1;
				else{
					if(width_table[mid].width<0)
						ret+=2;
					else
						ret+=width_table[mid].width;
					break;
				}
		}
	}
	return ret;
}

const char * unext(const char **s, int *l){
	const char *r=*s;
	if(**s==0||*l<=0){
		return NULL;
	}else if((**s & bb10000000) == bb00000000){
		*s+=1;
		*l-=1;
		return r;
	}else if((**s & bb11100000) == bb11000000){
		*s+=2;
		*l-=2;
		return r;
	}else if((**s & bb11110000) == bb11100000){
		*s+=3;
		*l-=3;
		return r;
	}else if((**s & bb11111000) == bb11110000){
		*s+=4;
		*l-=4;
		return r;
	}
	return NULL;
}

uint32_t unicode(const char *s){
	if(*s==0){
		return 0;
	}else if((*s & bb10000000) == bb00000000){
		return *s;
	}else if((*s & bb11100000) == bb11000000){
		return
		 (((s[0] >> 2) & bb00000111) << 8) |
		 (((s[0] << 6) & bb11000000) << 0) | (((s[1] >> 0) & bb00111111) << 0);
	}else if((*s & bb11110000) == bb11100000){
		return
		 (((s[0] << 4) & bb11110000) << 8) | (((s[1] >> 2) & bb00001111) << 8) |
		 (((s[1] << 6) & bb11000000) << 0) | (((s[1] << 0) & bb00111111) << 0);
	}else if((*s & bb11111000) == bb11110000){
		return
		 (((s[0] << 2) & bb00011100) << 16) | (((s[1] >> 4) & bb00000011) << 16) |
		 (((s[1] << 4) & bb11110000) << 8) | (((s[2] << 2) & bb11110000) << 8) |
		 (((s[2] << 6) & bb11000000) << 0) | (((s[3] << 0) & bb00111111) << 0);
	}
	return 0;
}
