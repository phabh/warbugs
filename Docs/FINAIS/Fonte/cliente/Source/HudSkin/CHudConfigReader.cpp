#include "CHudConfigReader.h"
#include "IReadFile.h"

CHudConfigReader::CHudConfigReader()
{
	Text = "";
	TextPtr = Text.c_str();
}

CHudConfigReader::CHudConfigReader( const char* filename )
{
	loadFile( filename );
}

CHudConfigReader::CHudConfigReader( std::istream& stream )
{
	loadStream( stream );
}

bool CHudConfigReader::loadStream( std::istream& stream )
{
	char c;
	while ( stream.get(c).good() )
	{
		Text += c;
	}

	TextPtr = Text.c_str();

	return ( Text != "" );
}

bool CHudConfigReader::loadFile( const char* filename )
{
	std::ifstream stream ( filename, std::ios::in );

	bool success = loadStream( stream );

	stream.close();

	return success;
}

bool CHudConfigReader::loadReadFile( io::IReadFile* file )
{
	if ( !file ) 
		return false;

	int size = file->getSize();

	char* buffer = new char[size+1];

	file->read( buffer, size );

	Text = buffer;
	TextPtr = Text.c_str();

	delete buffer;

	return (Text != "");
}

bool CHudConfigReader::nextConfig()
{
	// Reseta valores e nome
	ConfigValue = "";
	ConfigName = "";

	const char* &c = TextPtr;

	do  
	{     
		// Procurar o início de uma atribuição.
		while ( *c == ' ' || *c == '\n' || *c == '\r' || *c == '\t' || *c == '#' )
		{
			// Pular espaços em branco
			while ( *c == ' ' || *c == '\n' || *c == '\r' || *c == '\t' )
			{
				c++;
			}

			// Pular comantários
			if ( *c == '#' )
			{
				// Mover para o final da linha
				while ( *c != 0 && *c != '\n' && *c != '\r' )
					c++;
			}
		}

		// Se alcançou o final do arquivo
		if ( *c == 0 )
			return false;

		// Pegar um nome
		while ( *c != 0 && *c != ' ' && *c != '\t' && *c != '\n' && *c != '\r' && *c != '=' )
		{
			ConfigName += *c;
			c++;
		}

		// Buscar o sinal de =
		while ( *c != 0 && *c != '=' && *c != '\n' && *c != '\r' )
		{
			c++;
		}
	} while ( *c == 0 || *c == '\n' || *c == '\r' );

	// Passar pelo sinal de =
	c++;

	// Pula os espaços em branco depois do sinal de =
	while ( *c == ' ' || *c == '\t' )
	{
		c++;
	}

	std::string tmp = "";

	// Pega o valor
	while ( *c != 0 && *c != '\n' && *c != '\r' && *c != '#' )  // Stop at end of line, end of file, or beginning of a comment
	{
		if ( *c == ' ' || *c == '\t' )
		{
			tmp = "";

			// Pular espaços do valor
			while ( *c == ' ' || *c == '\t' )
			{
				tmp += *c;
				c++;
			}

			// Se não chegou ao final do arquivo
			if ( *c != 0 && *c != '\n' && *c != '\r' && *c != '#' )
				ConfigValue += tmp;

			// Continua o parsing ou aborta se chegar ao final do arquivo
			continue;
		}

		ConfigValue += *c;
		c++;
	}

	return true;
}

const char* CHudConfigReader::getConfigValue() const
{
	return ConfigValue.c_str();
}

const char* CHudConfigReader::getConfigName() const
{
	return ConfigName.c_str();
}