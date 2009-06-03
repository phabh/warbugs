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

	//! Cria um leitor de configuração. Chamar o loadFile ou loadStream para fazer o parse de configuração.
	CHudConfigReader();

	//! Cria um leitor de configuração lendo de um arquivo.
	CHudConfigReader( const char* filename );

	//! Cria um leitor de configuração lendo de uma stream.
	CHudConfigReader( std::istream& stream );

	//! Carrega o arquivo de configuração de uma stream. 
	bool loadStream( std::istream& stream );

	//! Carrega um arquivo de configuração.
	bool loadFile( const char* filename );

	//! Carrega um arquivo de configuração de um arquivo irrlicht.
	bool loadReadFile( IReadFile* file );

	//! Mover para a próxima atribuição. Pode ser chamado antes de getConfigValue() e getConfigName().
	bool nextConfig();

	//! Retorna o valor de uma atribuição.
	const char* getConfigValue() const;

	//! Retorna o nome da variável que está sendo atribuída.
	const char* getConfigName() const;

private:

	std::string Text;
	const char* TextPtr; // ponteiro para um char na string

	std::string ConfigValue;
	std::string ConfigName;
};