#include "string_utils.h"

wchar_t* MBCS2Unicode(wchar_t * buff, const char * str)
{
	wchar_t * wp = buff;
	char * p = (char *)str;
	while (*p)
	{
		if (*p & 0x80)
		{
			*wp = *(wchar_t *)p;
			p++;
		}
		else {
			*wp = (wchar_t)*p;
		}
		wp++;
		p++;
	}
	*wp = 0x0000;
	return buff;
}

char * Unicode2MBCS(char * buff, const wchar_t * str)
{
	wchar_t * wp = (wchar_t *)str;
	char * p = buff, *tmp;
	while (*wp) {
		tmp = (char *)wp;
		if (*wp & 0xFF00) {
			*p = *tmp;
			p++; tmp++;
			*p = *tmp;
			p++;
		}
		else {
			*p = *tmp;
			p++;
		}
		wp++;
	}
	*p = 0x00;
	return buff;
}


std::wstring str2wstr(std::string str)
{
	size_t len = str.size();
	wchar_t * b = (wchar_t *)malloc((len + 1) * sizeof(wchar_t));
	MBCS2Unicode(b, str.c_str());
	std::wstring r(b);
	free(b);
	return r;
}