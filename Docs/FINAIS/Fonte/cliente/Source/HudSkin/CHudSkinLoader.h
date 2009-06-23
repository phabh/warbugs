#pragma once

#include "CHudImageSkin.h"
#include "irrString.h"

class CHudConfigMap;

namespace irr
{
	namespace io
	{
		class IFileSystem;
	}

	namespace video
	{
		class IVideoDriver;
	}

	using namespace core;
	using namespace gui;
	using namespace io;
	using namespace video;

	//! Pega o caminho de contexto a partir do arquivo de configuração
	stringc GetContextPathFromFilename( const stringc& filename );

	//! Carregar um arquivo .cfg e armazenar todas as entradas em um mapa de configuração 
	//! que é retornado. Retorna NULL se o arquivo não puder ser aberto. É necessário deletar o
	//! mapa de configuração após o seu uso.
	CHudConfigMap* LoadConfigFromFile( IFileSystem* fileSystem, const stringc& filename );

	//! Carrega a configuração da Skin de um arquivo. Os nomes das texturas serão tratadas
	//! de forma relativa ao arquivo de configuração.
	SImageGUISkinConfig LoadGUISkinFromFile( IFileSystem* fileSystem, IVideoDriver* driver, const stringc& filename );
}