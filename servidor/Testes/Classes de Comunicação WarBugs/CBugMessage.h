#pragma once

class CBugMessage
{
	private:
		bool _overFlow;
		int  _maxSize;
		int  _size;
		int  _readCount;

		char *getNewPoint(int length);

	public:
		char  * _data;

		void    init(char *d, int length);

		void    clear(void);
		void    write(void *d, int length);

		void    writeByte(char c);
		void    writeShort(short c);
		void    writeLong(long c);
		void    writeFloat(float c);
		void    writeString(char *s);
		void    beginReading(void);
		void    beginReading(int s);
		char  * read(int s);
		char    readByte(void);
		short   readShort(void);
		long    readLong(void);
		float   readFloat(void);
		char  * readString(void);

		bool    getOverFlow(void) {return _overFlow;}

		int     getSize(void) {return _size;}
		void    setSize(int s) {_size = s;}
};