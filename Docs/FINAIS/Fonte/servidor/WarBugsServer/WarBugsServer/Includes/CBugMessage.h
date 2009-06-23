/*
	Classse para serializar dados para envio e recebimento via socket
	Baseada na classe dreamMessage.h do livro Programming Multiplayer Games
	@autor Paulo
*/

#include <string>
#include <sstream>


#pragma once

#define MAXPACKAGESIZE 300

class CBugMessage
{
	private:
		int  _readCount;                        // posicao de leitura

	public:
		std::string  _data;							// vetor com os dados

		void    clear(void);

		void    writeByte(char c);
		void    writeShort(short c);
		void    writeInt(int c);
		void    writeFloat(float c);
		void    writeString(char *s);
		void    beginReading(void);
		char    readByte(void);
		short   readShort(void);
		int	    readInt(void);
		float   readFloat(void);
		char  * readString(void);

		int     getSize(void) {return _data.size();}

};