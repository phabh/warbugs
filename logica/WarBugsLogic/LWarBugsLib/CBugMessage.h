/*
	Classse para serializar dados para envio e recebimento via socket
	Baseada na classe dreamMessage.h do livro Programming Multiplayer Games
	@autor Paulo
*/

#pragma once

class CBugMessage
{
	private:
		bool _overFlow;							// verifica se ouve estouro de memória
		int  _maxSize;							// tamanho máximo
		int  _size;                             // tamanho corrente
		int  _readCount;                        // posicao de leitura

		char *getNewPoint(int length);          

	public:
		char  * _data;							// vetor com os dados

		void    init(char *d, int length);

		void    clear(void);
		void    write(void *d, int length);

		void    writeByte(char c);
		void    writeShort(short c);
		void    writeInt(int c);
		void    writeFloat(float c);
		void    writeString(char *s);
		void    beginReading(void);
		void    beginReading(int s);
		char  * read(int s);
		char    readByte(void);
		short   readShort(void);
		int	    readInt(void);
		float   readFloat(void);
		char  * readString(void);

		bool    getOverFlow(void) {return _overFlow;}

		int     getSize(void) {return _size;}
		void    setSize(int s) {_size = s;}
};