#pragma once

#include <string>
#include <fstream>

namespace irr
{
	namespace io
	{
		class IReadFile;
	}
}

using namespace irr;
using namespace io;

class CHudConfigReader
{

public:

	//! Cria um leitor de configura��o. Chamar o loadFile ou loadStream para fazer o parse de configura��o.
	CHudConfigReader();

	//! Cria um leitor de configura��o lendo de um arquivo.
	CHudConfigReader( const char* filename );

	//! Cria um leitor de configura��o lendo de uma stream.
	CHudConfigReader( std::istream& stream );

	//! Carrega o arquivo de configura��o de uma stream. 
	bool loadStream( std::istream& stream );

	//! Carrega um arquivo de configura��o.
	bool loadFile( const char* filename );

	//! Carrega um arquivo de configura��o de um arquivo irrlicht.
	bool loadReadFile( IReadFile* file );

	//! Mover para a pr�xima atribui��o. Pode ser chamado antes de getConfigValue() e getConfigName().
	bool nextConfig();

	//! Retorna o valor de uma atribui��o.
	const char* getConfigValue() const;

	//! Retorna o nome da vari�vel que est� sendo atribu�da.
	const char* getConfigName() const;

private:

	std::string Text;
	const char* TextPtr; // ponteiro para um char na string

	std::string ConfigValue;
	std::string ConfigName;
};