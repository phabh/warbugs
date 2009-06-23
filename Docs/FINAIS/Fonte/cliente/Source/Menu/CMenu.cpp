#include "CMenu.h"

TypeMenuID CMenu::run()
{
	ITimer *cronometroMS = _dispGrafico->getTimer(); 

	u32 tempoInicial,
		tempoCorrido;

	updateHuds();

	while(_dispGrafico->run())
	{
		tempoInicial = cronometroMS->getRealTime(); // Milisegundos

		if(_myID == MN_JOGO)
		{
			receivePackages();
		}

		if (_dispGrafico->isWindowActive())
		{
			_gerEventos->endEventProcess(); // Desativa a escuta de eventos para desenhar.

			_gerVideo->beginScene(true, true, SColor(255, 255, 255, 255));
			_gerCena->drawAll(); 
			_gerHud->drawAll();
			graphicsDrawAddOn();
			_gerVideo->endScene();

			readCommands();

			updateGraphics();

			if(!_menuFlag[HUDUPDATED])
			{
				// Se o HUD não estiver atualizado
				updateHuds();
			}

			if(_nextID != _myID)
			{
				// Solicitou troca de Menu
				break;
			}
			else
			{
				tempoCorrido = cronometroMS->getRealTime() - tempoInicial;

				if(tempoCorrido < 33) // 30ms = 1000/30
					_dispGrafico->sleep(33 - tempoCorrido); // Adormece para manter o FPS
			}

			// Ativa a escuta de eventos. SEMPRE deve ser a última linha do while.
			_gerEventos->startEventProcess(); 
		}
	}
	_dispAudio->stopAllSounds();

	return _nextID;
}

//-----------------------------------------------------------------------------------------------------------------

void CMenu::addNewBtn( IGUIButton *&ptrBtn, rect<s32> posicao, IGUIElement *parent, s32 id, const wchar_t *texto, const wchar_t *dica, bool isTexturedBtn, bool isPushBtn, int idImageUp, int idImagePressed)
{
	ptrBtn = _gerHud->addButton( posicao, parent, id, texto, dica );
	ptrBtn->setIsPushButton(isPushBtn);
	ptrBtn->setPressed(false);

	if(isTexturedBtn)
	{
		if(idImageUp >= 0)
			ptrBtn->setImage(_gerVideo->getTexture(pathTexture2D[idImageUp]));

		if(idImagePressed >= 0)
			ptrBtn->setPressedImage(_gerVideo->getTexture(pathUsedTexture2D[idImagePressed]));
	}
	ptrBtn->setUseAlphaChannel(true);
}

//-----------------------------------------------------------------------------------------------------------------

void CMenu::addNewText( IGUIStaticText *&ptrTexto, const wchar_t *texto, rect<s32> posicao, bool hasBorder, bool isWrap, bool fillBg, IGUIElement *parent, s32 id, EGUI_ALIGNMENT horizontal, EGUI_ALIGNMENT vertical )
{
	ptrTexto = _gerHud->addStaticText(texto, posicao, hasBorder, isWrap, parent, id, fillBg);
	ptrTexto->setTextAlignment(horizontal, vertical);
}

//-----------------------------------------------------------------------------------------------------------------

void CMenu::addNewWindow( IGUIWindow *&ptrWindow, rect<s32> posicao, bool modal, const wchar_t *titulo, IGUIElement *parent, int id)
{
	ptrWindow = _gerHud->addWindow(posicao, modal, titulo, parent, id); 
	ptrWindow->getCloseButton()->setEnabled(false); 
	ptrWindow->getCloseButton()->setToolTipText(L""); 
	ptrWindow->getCloseButton()->setVisible(false);
}

//-----------------------------------------------------------------------------------------------------------------
