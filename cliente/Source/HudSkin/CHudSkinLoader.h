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

	//! Pega o caminho de contexto a partir do arquivo de configura��o
	stringc GetContextPathFromFilename( const stringc& filename );

	//! Carregar um arquivo .cfg e armazenar todas as entradas em um mapa de configura��o 
	//! que � retornado. Retorna NULL se o arquivo n�o puder ser aberto. � necess�rio deletar o
	//! mapa de configura��o ap�s o seu uso.
	CHudConfigMap* LoadConfigFromFile( IFileSystem* fileSystem, const stringc& filename );

	//! Carrega a configura��o da Skin de um arquivo. Os nomes das texturas ser�o tratadas
	//! de forma relativa ao arquivo de configura��o.
	SImageGUISkinConfig LoadGUISkinFromFile( IFileSystem* fileSystem, IVideoDriver* driver, const stringc& filename );
}