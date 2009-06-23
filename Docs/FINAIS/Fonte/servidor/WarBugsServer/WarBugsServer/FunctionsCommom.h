#pragma once
#ifndef _FUNCTIONS_COMMOM_H_
#define _FUNCTIONS_COMMOM_H_

#include <stdlib.h>
#include <vcclr.h>

/*Transforma a porra do tipo string do windows em coisa de macho!*/
static char * toChar(System::String^ str)
{
	char * target;

	pin_ptr<const wchar_t> wch = PtrToStringChars( str );

	size_t i;

	int len = (( str->Length+1) * 2);

	target = new char[ len ];
				
	wcstombs_s(&i, target, (size_t)len, wch, (size_t)len );

	return target;
}

#endif