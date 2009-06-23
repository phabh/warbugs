#include "CMenuJogo.h"

//-----------------------------------------------------------------------------------------------------------------

void CMenuJogo::receivePackages()
{
	int retorno = SUCESSO;
	bool fim = false;

	do
	{
		retorno = _gameCore->receberPacote();

		switch (retorno)
		{

		case FINAL_PACOTES:	fim = true;	break;
		case ERRO_SAIR: fim = true; _nextID = MN_LOGIN; break;

		};

	}while(!fim);
}

//-----------------------------------------------------------------------------------------------------------------

CMenuJogo::CMenuJogo()
{
}

//-----------------------------------------------------------------------------------------------------------------

bool CMenuJogo::start(CGameCore *gameCore)
{
	_gameCore = gameCore;

	_gameCore->getAllManagers(_dispGrafico, _dispAudio, _gerEventos, _gerCena, _gerVideo, _gerHud, _gameConfig);

	_gameCore->playMusic(pathBackgroundSound[MM_JOGO]);

	_myID = _nextID = MN_JOGO;

	for(int i=0; i<NUMFLAGSMENU; i++)
		_menuFlag[i] = false;

	_menuFlag[OBJSELECTED] = false;
	_menuFlag[HUDUPDATED]  = false;
	_menuFlag[ALERTON]     = false;

	_menuCamera = gameCore->createCamera( vector3df(0,0,0), vector3df(0,0,100), vector3df(0,0,0), 0, 179.0f,true/*, false*/);
	_gameCore->createLight(_menuCamera, vector3df(0,0,0), 1200.0f);

	_gameCore->camRotVert = _gameCore->camRotHor = 0.0;

	_gameCore->enviarPacote(START_GAME, _gameCore->_myUserID, _gameCore->_myCharID);

	int retorno = PING_REQUEST;

	while(retorno == PING_REQUEST)
		retorno = _gameCore->receberPacote();

	if(retorno == ERRO_SAIR)
		_nextID = MN_LOGIN; // Desconecta e volta para a tela de login

	receivePackages();

	maxH = _gameCore->sHeight;
	maxW = _gameCore->sWidth;
	minH = 0;
	minW = 0;
	midH = maxH/2;
	midW = maxW/2;

	return (true);
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuJogo::updateHuds()
{
	int idTipo = 0; // TIRAR

	_gerHud->clear();

	//_font->draw(temp, rect<s32>(130,10,300,50), SColor(255,255,255,255));


	// Criar janela de mini mapa
	addNewWindow(mapWindow, rect<s32>(maxW-255, minH+5, maxW-5, minH+255), false, L"Minimap");

	// Criar janela de inventário do jogador
	addNewWindow(invWindow, rect<s32>(midW-132, midH-120, midW+132, midH+120), false, L"Inventory");

	// Criar janela de status do jogador
	addNewWindow(statWindow, rect<s32>(minW, minH+400, minW+150, minH+480), false, L"Status");

	// Criar janela de configurações do jogo
	addNewWindow(cfgWindow, rect<s32>(midW-100, midH-100, midW+100, midH+100), false, L"Config");

	// Criar janela de shop
	addNewWindow(shopWindow, rect<s32>(midW-255, midH-130, midW+255, midH+130), false, L"Shop");

	// Criar janela de trade
	addNewWindow(tradeWindow, rect<s32>(midW-90, midH-100, midW+90, midH+100), false, L"Trade");

	// Criar janela de trade
	addNewWindow(bagWindow, rect<s32>(midW-255, midH-130, midW+255, midH+130), false, L"Bag");

	// Criar janela de alerta
	addNewWindow(alertWindow, rect<s32>(0, 600-200, 800/4, 600), false, L"Alert");

	addNewBtn(  hudBtn[0], rect<s32>( midW-170, maxH-45, midW-130, maxH-5), 0, 400, 0, L"Inventory", true, false, H_INVENTARIO, H_INVENTARIO);
	addNewBtn(  hudBtn[1], rect<s32>( midW-120, maxH-45, midW-80, maxH-5), 0, 401, 0, L"Trade", true, false, H_TRADE, H_TRADE);
	addNewBtn(  hudBtn[2], rect<s32>( midW-70, maxH-45, midW-30, maxH-5), 0, 402, 0, L"Shop", true, false, H_SHOP, H_SHOP);

	addNewBtn(  hudBtn[6], rect<s32>( midW-20, maxH-45, midW+20, maxH-5), 0, 406, 0, L"Alert", true, false, H_ALERT, H_ALERT);
	
	addNewBtn(  hudBtn[3], rect<s32>( midW+30, maxH-45, midW+70, maxH-5), 0, 403, 0, L"Status", true, false, H_STATUS, H_STATUS);
	addNewBtn(  hudBtn[4], rect<s32>( midW+80, maxH-45, midW+120, maxH-5), 0, 404, 0, L"Config", true, false, H_CONFIG, H_CONFIG);
	addNewBtn(  hudBtn[5], rect<s32>( midW+130, maxH-45, midW+170, maxH-5), 0, 405, 0, L"Exit", true, false, H_EXIT, H_EXIT);
	
	// background da hud de luas no topo da tela
	bgMoon = _gerHud->addImage(_gerVideo->getTexture("recursos/huds/tx2d_topbg.png"), position2d<s32>(midW-128, 0));
	
	addNewBtn(  hudBtn[7], rect<s32>( midW-112, minH+5, midW-60, minH+57), 0, 407, 0, L"War/Peace", true, true, H_PEACEMODE, H_WARMODE);

	addNewBtn(  hudBtn[10], rect<s32>( midW-45, minH, midW+45, minH+90), 0, 410, 0, L"current moon", true, false, H_MOON_BESOURO, H_MOON_BESOURO);
	//imgMoon = _gerHud->addImage(_gerVideo->getTexture("recursos/huds/tx2d_moon_ty.png"), position2d<s32>(midW-45, minH), true, 0, -1, L"Current Moon");
	addNewBtn(  hudBtn[9], rect<s32>( midW+60, minH+5, midW+112, minH+57), 0, 409, 0, L"Quest", true, true, H_QUEST_NONE, H_QUEST_NONE);
	
	//addNewBtn(  hudBtn[8], rect<s32>( minW+310, maxH-190, minW+350, maxH-160), 0, 408, L"Send", 0, false);

	chatInput = _gerHud->addEditBox(L"", rect<s32>(minW+5, maxH-182, minW+200, maxH-160), true, 0, 409 );
	chatInput->setMax(43);

	chatPlayers = _gerHud->addListBox(rect<s32>(minW+205, maxH-182, minW+320, maxH-160), 0, 410, true);
	chatPlayers->addItem(L"Todos");
	chatPlayers->addItem(L"Player22222");

	// Esconde o chat input inicialmente
	chatPlayers->setVisible(false);
	//hudBtn[8]->setVisible(false);
	chatInput->setVisible(false);

	gameMessages = _gerHud->addListBox(rect<s32>(minW+5, maxH-150, minW+320, maxH-5), 0, 411, true);
	gameMessages->insertItem(0, L"Servidor: Seja bem vindo! :)", -1);
	gameMessages->setItemOverrideColor(0, SColor(255, 0, 150, 0));
	gameMessages->insertItem(0, L"PLAYERXXX: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", -1);
	gameMessages->setItemOverrideColor(0, SColor(255, 150, 0, 0));

	

	if(_menuFlag[MAPAON])
	{
		// 0 = id cenario
		_gerHud->addImage(_gerVideo->getTexture(pathTexture2D[H_MOLDURA]), position2d<s32>(0,0), true, mapWindow);
		_gerHud->addImage(_gerVideo->getTexture(pathMapCenario[0]), position2d<s32>(25,25), true, mapWindow);
		meOnMap = _gerHud->addImage(_gerVideo->getTexture(pathMe), position2d<s32>(125,125), true, mapWindow);
	}

	if(_menuFlag[INVENTARIOON])
	{
		// Itens do jogador
		addNewBtn(  slotInv[0], rect<s32>(25, 45, 65, 85), invWindow, 500, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInv[1], rect<s32>(80, 45, 120, 85), invWindow, 501, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInv[2], rect<s32>(135, 45, 175, 85), invWindow, 502, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInv[3], rect<s32>(25, 95, 65, 135), invWindow, 503, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInv[4], rect<s32>(80, 95, 120, 135), invWindow, 504, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInv[5], rect<s32>(135, 95, 175, 135), invWindow, 505, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInv[6], rect<s32>(25, 145, 65, 185), invWindow, 506, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInv[7], rect<s32>(80, 145, 120, 185), invWindow, 507, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInv[8], rect<s32>(135, 145, 175, 185), invWindow, 508, 0, 0, true, true, idTipo, idTipo);

		// Equipamentos do jogador
		addNewBtn(  slotInv[9], rect<s32>(200, 45, 240, 85), invWindow, 509, 0, 0, true, true, idTipo, idTipo);
		addNewBtn( slotInv[10], rect<s32>(200, 95, 240, 135), invWindow, 510, 0, 0, true, true, idTipo, idTipo);

		// Dinheiro do jogador
		addNewText(cashInvBag, L"$" +( const wchar_t)999999, rect<s32>(185, 155, 255, 175), false, false, true, invWindow, 511, EGUIA_LOWERRIGHT, EGUIA_CENTER);

		// Botões do inventário (drop / roleta)
		addNewBtn(  invBtn[0], rect<s32>(25, 200, 65, 235), invWindow, 512, 0, 0, true, true, H_DROP, H_DROP);
		addNewBtn(  invBtn[1], rect<s32>(80, 200, 120, 235), invWindow, 513, 0, 0, true, true, H_ROLETA, H_ROLETA);

		// Close Window
		addNewBtn(  invBtn[2], rect<s32>(235, 5, 260, 30), invWindow, 514, 0, 0, true, true, H_CLOSE_WINDOW, H_CLOSE_WINDOW);
	}

	if(_menuFlag[BOLSAON])
	{
		// Itens da bolsa
		addNewBtn(  slotBag[0], rect<s32>(60, 45, 100, 85), bagWindow, 600, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotBag[1], rect<s32>(115, 45, 155, 85), bagWindow, 601, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotBag[2], rect<s32>(170, 45, 210, 85), bagWindow, 602, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotBag[3], rect<s32>(60, 95, 100, 135), bagWindow, 603, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotBag[4], rect<s32>(115, 95, 155, 135), bagWindow, 604, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotBag[5], rect<s32>(170, 95, 210, 135), bagWindow, 605, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotBag[6], rect<s32>(60, 145, 100, 185), bagWindow, 606, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotBag[7], rect<s32>(115, 145, 155, 185), bagWindow, 607, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotBag[8], rect<s32>(170, 145, 210, 185), bagWindow, 608, 0, 0, true, true, idTipo, idTipo);

		// Itens do jogador
		addNewBtn(  slotInvBag[0], rect<s32>(270, 45, 310, 85), bagWindow, 610, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvBag[1], rect<s32>(325, 45, 365, 85), bagWindow, 611, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvBag[2], rect<s32>(380, 45, 420, 85), bagWindow, 612, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvBag[3], rect<s32>(270, 95, 310, 135), bagWindow, 613, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvBag[4], rect<s32>(325, 95, 365, 135), bagWindow, 614, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvBag[5], rect<s32>(380, 95, 420, 135), bagWindow, 615, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvBag[6], rect<s32>(270, 145, 310, 185), bagWindow, 616, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvBag[7], rect<s32>(325, 145, 365, 185), bagWindow, 617, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvBag[8], rect<s32>(380, 145, 420, 185), bagWindow, 618, 0, 0, true, true, idTipo, idTipo);

		// Equipamentos do jogador
		addNewBtn(  slotInvBag[9], rect<s32>(445, 45, 485, 85), bagWindow, 619, 0, 0, true, true, idTipo, idTipo);
		addNewBtn( slotInvBag[10], rect<s32>(445, 95, 485, 135), bagWindow, 620, 0, 0, true, true, idTipo, idTipo);

		// Dinheiro do jogador
		addNewText(cashInvBag, L"9999", rect<s32>(430, 155, 500, 175), false, false, true, bagWindow, 621, EGUIA_LOWERRIGHT, EGUIA_CENTER);

		// Botões do inventário (drop / roleta)
		addNewBtn(  bagBtn[0], rect<s32>(270, 200, 310, 235), bagWindow, 622, 0, 0, true, false, idTipo, idTipo);
		addNewBtn(  bagBtn[1], rect<s32>(325, 200, 365, 235), bagWindow, 623, 0, 0, true, false, idTipo, idTipo);

		// Close Window
		addNewBtn(  bagBtn[2], rect<s32>(480, 5, 505, 30), bagWindow, 624, 0, 0, true, true, H_CLOSE_WINDOW, H_CLOSE_WINDOW);
	}

	if(_menuFlag[SHOPON])
	{
		// Itens do vendedor
		addNewBtn(  slotShop[0], rect<s32>(60, 45, 100, 85), shopWindow, 700, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotShop[1], rect<s32>(115, 45, 155, 85), shopWindow, 701, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotShop[2], rect<s32>(170, 45, 210, 85), shopWindow, 702, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotShop[3], rect<s32>(60, 95, 100, 135), shopWindow, 703, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotShop[4], rect<s32>(115, 95, 155, 135), shopWindow, 704, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotShop[5], rect<s32>(170, 95, 210, 135), shopWindow, 705, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotShop[6], rect<s32>(60, 145, 100, 185), shopWindow, 706, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotShop[7], rect<s32>(115, 145, 155, 185), shopWindow, 707, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotShop[8], rect<s32>(170, 145, 210, 185), shopWindow, 708, 0, 0, true, true, idTipo, idTipo);

		// Itens do jogador
		addNewBtn(  slotInvShop[0], rect<s32>(270, 45, 310, 85), shopWindow, 710, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvShop[1], rect<s32>(325, 45, 365, 85), shopWindow, 711, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvShop[2], rect<s32>(380, 45, 420, 85), shopWindow, 712, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvShop[3], rect<s32>(270, 95, 310, 135), shopWindow, 713, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvShop[4], rect<s32>(325, 95, 365, 135), shopWindow, 714, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvShop[5], rect<s32>(380, 95, 420, 135), shopWindow, 715, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvShop[6], rect<s32>(270, 145, 310, 185), shopWindow, 716, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvShop[7], rect<s32>(325, 145, 365, 185), shopWindow, 717, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvShop[8], rect<s32>(380, 145, 420, 185), shopWindow, 718, 0, 0, true, true, idTipo, idTipo);

		// Equipamentos do jogador
		addNewBtn(  slotInvShop[9], rect<s32>(445, 45, 485, 85), shopWindow, 719, 0, 0, true, true, idTipo, idTipo);
		addNewBtn(  slotInvShop[10], rect<s32>(445, 95, 485, 135), shopWindow, 720, 0, 0, true, true, idTipo, idTipo);

		// Page Up Shop
		addNewBtn(  shopBtn[0], rect<s32>(20, 95, 50, 125), shopWindow, 721, 0, 0, true, false, H_LEFT_MINI, H_LEFT_MINI);

		// Page Down Shop
		addNewBtn(  shopBtn[1], rect<s32>(220, 95, 250, 125), shopWindow, 722, 0, 0, true, false, H_RIGHT_MINI, H_RIGHT_MINI);

		// Jogador Comprar
		addNewBtn(  shopBtn[2], rect<s32>(60, 200, 100, 235), shopWindow, 723, 0, 0, true, false, idTipo, idTipo);

		// Botões do inventário (drop / roleta)
		addNewBtn(  shopBtn[3], rect<s32>(270, 200, 310, 235), shopWindow, 724, 0, 0, true, false, idTipo, idTipo);
		addNewBtn(  shopBtn[4], rect<s32>(325, 200, 365, 235), shopWindow, 725, 0, 0, true, false, idTipo, idTipo);

		// Jogador Vender
		addNewBtn(  shopBtn[5], rect<s32>(380, 200, 420, 235), shopWindow, 726, 0, 0, true, false, idTipo, idTipo);

		// Close Window
		addNewBtn(  shopBtn[6], rect<s32>(480, 5, 505, 30), shopWindow, 727, 0, 0, true, true, H_CLOSE_WINDOW, H_CLOSE_WINDOW);

		// Dinheiro do jogador
		addNewText(cashInvBag, L"99999", rect<s32>(430, 155, 500, 175), false, false, true, shopWindow, 728, EGUIA_LOWERRIGHT, EGUIA_CENTER);

		// Preço do Item para vender ao NPC
		addNewText(cashToSell, L"9999", rect<s32>(430, 205, 500, 225), false, false, true, shopWindow, 729, EGUIA_LOWERRIGHT, EGUIA_CENTER);

		// Preço do item para comprar do NPC
		addNewText(cashToBuy, L"9999", rect<s32>(125, 205, 195, 225), false, false, true, shopWindow, 730, EGUIA_LOWERRIGHT, EGUIA_CENTER);
	}

	if(_menuFlag[TRADEON])
	{
		// Item repassado pelo alvo
		addNewBtn(  slotTrade[0], rect<s32>(30, 35, 70, 75), tradeWindow, 800, 0, L"Item to receive", true, true, idTipo, idTipo);

		// Item que você quer repassar
		addNewBtn(  slotTrade[1], rect<s32>(105, 35, 145, 75), tradeWindow, 801, 0, L"Item to send", true, true, idTipo, idTipo);

		// Dinheiro repassado pelo alvo
		addNewText(cashTradeRecv, L"9999", rect<s32>(25, 115, 75, 135), false, false, true, tradeWindow, 806, EGUIA_LOWERRIGHT, EGUIA_CENTER);

		// Dinheiro que você quer repassar
		addNewText(cashTradeSend, L"9999", rect<s32>(100, 115, 150, 135), false, false, true, tradeWindow, 807, EGUIA_LOWERRIGHT, EGUIA_CENTER);

		// Botões para modificar dinheiro enviado
		addNewBtn(  tradeBtn[0], rect<s32>(100, 95, 115, 110), tradeWindow, 808, L"+", L"Add seed");//, true, true, idTipo, idTipo);
		addNewBtn(  tradeBtn[1], rect<s32>(135, 95, 150, 110), tradeWindow, 809, L"-", L"Sub seed");//, true, true, idTipo, idTipo);

		// Botões para identificar o status da troca
		addNewBtn(  tradeBtn[2], rect<s32>(30, 145, 70, 180), tradeWindow, 810, 0, L"Locked/Unlocked by the other");//, true, true, idTipo, idTipo);
		addNewBtn(  tradeBtn[3], rect<s32>(110, 145, 150, 180), tradeWindow, 811, 0, L"Lock/Unlock my deal");//, true, true, idTipo, idTipo);

		// Botão para fechar janela de Shop
		addNewBtn(  tradeBtn[4], rect<s32>(150, 5, 175, 30), tradeWindow, 812, 0, 0, true, true, H_CLOSE_WINDOW, H_CLOSE_WINDOW);
	}

	if(_menuFlag[CONFIGON])
	{
		// Volume
		addNewText(cfgCaption[0], L"Volume:", rect<s32>(minW+10, minH+50, minW+60, minH+70), false, false, false, cfgWindow, 900, EGUIA_UPPERLEFT, EGUIA_CENTER);
		cfgVolume = _gerHud->addScrollBar(true, rect<s32>(minW+70, minH+55, minW+200, minH+65), cfgWindow, 901);

		// Contorno
		cfgContorno = _gerHud->addCheckBox(_gameCore->showContorno, rect<s32>(minW+10, minH+80, minW+200, minH+100), cfgWindow, 902, L"Apply mesh contour");
	}

	if(_menuFlag[STATUSON])
	{
		// Status expandido
	}

	if(_menuFlag[ALERTON])
	{
	}

	statusBg = _gerHud->addImage(_gerVideo->getTexture("recursos/huds/tx2d_status_bg.png"), position2d<s32>(2, 2), true);

	// Desenha Status fixo
	barPV = new CHudProgressBar(_gerHud->getRootGUIElement(), _gerHud, rect<s32>(130, 60, 270, 72), 1200);
	barPV->setProgress(0.1);
	barPV->setFillColor(SColor(255, 100, 255, 0));
	barPV->setToolTipText(L"pontos de vida");
	barPV->setAutomaticText(L"10/100");

	barPP = new CHudProgressBar(_gerHud->getRootGUIElement(), _gerHud, rect<s32>(130, 80, 270, 92), 1201);
	barPP->setProgress(0.3);
	barPP->setFillColor(SColor(255, 255, 100, 100));
	barPP->setToolTipText(L"pontos de poder");
	barPP->setAutomaticText(L"30/100");

	barXP = new CHudProgressBar(_gerHud->getRootGUIElement(), _gerHud, rect<s32>(130, 100 ,270, 112), 1202);
	barXP->setProgress(0.5);
	barXP->setFillColor(SColor(255, 100, 100, 255));
	barXP->setToolTipText(L"pontos de experiência");
	barXP->setAutomaticText(L"50/100");

	barMP = new CHudProgressBar(_gerHud->getRootGUIElement(), _gerHud, rect<s32>(130, 120, 270, 132), 1203);
	barMP->setProgress(0.9);
	barMP->setFillColor(SColor(255, 255, 255, 100));
	barMP->setToolTipText(L"tempo de carga");
	barMP->setAutomaticText(L"90/100");

	statusFace = _gerHud->addImage(_gerVideo->getTexture("recursos/huds/tx2d_face_besouro.png"), position2d<s32>(10,10), true);

	// Cria Roleta
	_roleta = new CHudRoleta( 
		rect<s32>(maxW-200, maxH-200, maxW, maxH),
		_gerHud,						
		_gerHud->getRootGUIElement(),
		_gerVideo->getTexture("recursos/huds/tx2d_roleta_mask.png"), // fundo
		_gerVideo->getTexture("recursos/huds/tx2d_poder1_besouro.png"),
		_gerVideo->getTexture("recursos/huds/tx2d_poder2_besouro.png"),
		_gerVideo->getTexture("recursos/huds/tx2d_poder3_besouro.png"),
		_gerVideo->getTexture("recursos/huds/tx2d_rol_polpa_form.png"),
		_gerVideo->getTexture("recursos/huds/tx2d_rol_polpa_cupim.png"),
		_gerVideo->getTexture("recursos/huds/tx2d_rol_none.png"),
		_gerVideo->getTexture("recursos/huds/tx2d_face_formiga.png") // alvo
		);

	for (u32 i=0; i<EGDC_COUNT ; ++i)
	{
		SColor col = _gerHud->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
		col.setAlpha(200);
		_gerHud->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
	}

	for(int i=0; i<NUMFLAGSMENU; i++)
		_menuFlag[i] = false;

	_menuFlag[MAPAON] = true;
	_menuFlag[HUDUPDATED] = true;
	//_menuFlag[CHATON] = false;


	invWindow->setVisible(_menuFlag[INVENTARIOON]);
	shopWindow->setVisible(_menuFlag[SHOPON]);
	tradeWindow->setVisible(_menuFlag[TRADEON]);
	statWindow->setVisible(_menuFlag[STATUSON]);
	cfgWindow->setVisible(_menuFlag[CONFIGON]);
	mapWindow->setVisible(_menuFlag[MAPAON]);
	alertWindow->setVisible(_menuFlag[ALERTON]);
	bagWindow->setVisible(_menuFlag[BOLSAON]);
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuJogo::readCommands()
{		
	// captura o elemento de hud em foco
	IGUIElement *focusedElement = _gerHud->getFocus();

	

	temp = L"";
	temp += (int)_gerVideo->getFPS();

	_dispGrafico->setWindowCaption(temp.c_str());

	if(_gerEventos->isMouseButtonDoubleClicked(MBLEFT))
	{
		// Duplo-clique no botão esquerdo do mouse
		/*
		_idInimigo = -1;
		_nodoSelecionado = _gerCena->getSceneCollisionManager()->getSceneNodeFromScreenCoordinatesBB(_dispGrafico->getCursorControl()->getPosition());

		_idInimigo = _nodoSelecionado->getID();

		if(_idInimigo > 0)
		{
		_combate = true;
		_targetPosition = _nodoSelecionado->getPosition();
		cout << "\nCombate TRUE.\n";
		cout << "\nAlvo X: " << _targetPosition.X << "\nAlvo Y: " << _targetPosition.Y << "\nAlvo Z: " << _targetPosition.Z << endl;
		}
		else
		{
		_combate = false;
		cout << "\nCombate FALSE.\n";

		_material.Lighting = false;

		_posClick = _dispGrafico->getCursorControl()->getPosition();
		_raio = _gerCena->getSceneCollisionManager()->getRayFromScreenCoordinates(_posClick, _menuCamera);


		if(_gerCena->getSceneCollisionManager()->getCollisionPoint(_raio, _gameCore->_sceneTris, _targetPosition, _trianguloCapt))
		{
		//_targetPosition = desiredPosition;
		_gerVideo->setTransform(ETS_WORLD, matrix4());
		_gerVideo->setMaterial(_material);
		_gerVideo->draw3DTriangle(_trianguloCapt, SColor(0,255,0,0));
		} 
		else
		_targetPosition = _gameCore->_myPlayerChar->_modelo->getPosition();

		cout << "\nAlvo X: " << _targetPosition.X << "\nAlvo Y: " << _targetPosition.Y << "\nAlvo Z: " << _targetPosition.Z << endl;
		}*/
	}

	// Click com o botão esquerdo do mouse
	if(_gerEventos->isMouseButtonReleased(MBLEFT))
	{	
		// Click esquerdo em um botão
		if(_gerEventos->getEventCallerByElement(EGET_BUTTON_CLICKED))
		{
			switch(_gerEventos->getEventCallerByID())
			{

			case 400: // Btn inv
				_menuFlag[INVENTARIOON] = !_menuFlag[INVENTARIOON];
				invWindow->setVisible(_menuFlag[INVENTARIOON]);
				break;

			case 401: // Btn trade
				_menuFlag[TRADEON] = !_menuFlag[TRADEON];
				tradeWindow->setVisible(_menuFlag[TRADEON]);
				break;

			case 402: // Btn shop
				_menuFlag[SHOPON] = !_menuFlag[SHOPON];
				shopWindow->setVisible(_menuFlag[SHOPON]);
				break;

			case 403: // Btn status
				_menuFlag[STATUSON] = !_menuFlag[STATUSON];
				statWindow->setVisible(_menuFlag[STATUSON]);
				break;

			case 406: // Btn alert
				_menuFlag[ALERTON] = !_menuFlag[ALERTON];
				alertWindow->setVisible(_menuFlag[ALERTON]);
				break;

			case 404: // Btn Config
				_menuFlag[CONFIGON] = !_menuFlag[CONFIGON];
				cfgWindow->setVisible(_menuFlag[CONFIGON]);
				break;

			case 405: // Btn Exit
				_nextID = MN_CREDITOS;
				break;

			case 407: // Btn War/Peace
				//_gameCore->_myCharPlayer->_combatMode = !_gameCore->_myCharPlayer->_combatMode;
				break;

			case 514: // Btn Close Inv
				_menuFlag[INVENTARIOON] = !_menuFlag[INVENTARIOON];
				invWindow->setVisible(_menuFlag[INVENTARIOON]);
				break;

			case 624: // Btn Close bag
				_menuFlag[BOLSAON] = !_menuFlag[BOLSAON];
				bagWindow->setVisible(_menuFlag[BOLSAON]);
				break;

			case 812: // Btn Close trade
				_menuFlag[TRADEON] = !_menuFlag[TRADEON];
				tradeWindow->setVisible(_menuFlag[TRADEON]);
				break;
			};

			if(_nextID != MN_JOGO)
				return;
		}

		// Click esquerdo em outro elemento
		else
		{
			// Não é clique em botão
		}
	}


	if(_gerEventos->wheelMoved())
	{
		// Giro do scroll do mouse
		_roleta->move(_gerEventos->getDeltaMouseWheelPosition());
	}

	if(_gerEventos->isKeyPressed(KEY_RETURN))
	{
		// Ignora o elemento de hud em foco para iniciar o modo chat
		_gerHud->setFocus(NULL);
	}

	if(_gerEventos->isKeyReleased(KEY_RETURN))
	{
		// Habilitar | Desabilitar modo Chat
		if(_menuFlag[CHATON])
		{
			// Desativar modo Chat.
			// envia msg de chat
			// tira o foco
			focusedElement = NULL;
			_gerHud->setFocus(focusedElement);
			chatInput->setText(L""); // limpa input
			//hudBtn[8]->setVisible(false);
			chatPlayers->setVisible(false);
			chatInput->setVisible(false);
		}
		else
		{
			// Ativar modo Chat.
			// muda o foco para o input do chat
			_gerHud->setFocus(chatInput);
			focusedElement = chatInput;
			chatInput->setText(L""); // limpa input
			//hudBtn[8]->setVisible(true);
			chatPlayers->setVisible(true);
			chatInput->setVisible(true);
		}

		// troca o valor da flag
		_menuFlag[CHATON] = !_menuFlag[CHATON];
	}

	// Se o modo chat estiver desabilitado, leia as outras teclas
	if(!_menuFlag[CHATON])
	{
		if(_gerEventos->isKeyReleased(KEY_KEY_B))
		{
			// Mostrar | Esconder janela de bolsa
			_menuFlag[BOLSAON] = !_menuFlag[BOLSAON];
			bagWindow->setVisible(_menuFlag[BOLSAON]);
		}

		if(_gerEventos->isKeyReleased(KEY_KEY_I))
		{
			// Mostrar | Esconder janela de inventario
			_menuFlag[INVENTARIOON] = !_menuFlag[INVENTARIOON];
			invWindow->setVisible(_menuFlag[INVENTARIOON]);
		}

		if(_gerEventos->isKeyReleased(KEY_KEY_Z))
		{
			// Mostrar | Esconder janela de status extendido
			_menuFlag[STATUSON] = !_menuFlag[STATUSON];
			statWindow->setVisible(_menuFlag[STATUSON]);
		}

		if(_gerEventos->isKeyReleased(KEY_KEY_M))
		{
			// Habilitar | Desabilitar janela de minimapa
			_menuFlag[MAPAON] = !_menuFlag[MAPAON];
			mapWindow->setVisible(_menuFlag[MAPAON]);
		}

		if(_gerEventos->isKeyReleased(KEY_KEY_F))
		{
			// Habilitar | Desabilitar janela de config
			_menuFlag[CONFIGON] = !_menuFlag[CONFIGON];
			cfgWindow->setVisible(_menuFlag[CONFIGON]);
		}

		if(_gerEventos->isKeyReleased(KEY_KEY_R))
		{
			// Habilitar | Desabilitar janela de config
			_menuFlag[ALERTON] = !_menuFlag[ALERTON];
			alertWindow->setVisible(_menuFlag[ALERTON]);
		}


		if(_gerEventos->isKeyReleased(KEY_TAB))
		{
			// Habilitar | Desabilitar modo combate
			//_gameCore->_myCharPlayer->_combatMode = !_gameCore->_myCharPlayer->_combatMode
			hudBtn[7]->setPressed( !hudBtn[7]->isPressed() );
		}

		if(_gerEventos->isKeyReleased(KEY_KEY_T))
		{
			// Habilitar | Desabilitar negociação de troca com o alvo
			//if(!_gameCore->_myPlayerChar->_combatMode)
			//{
			// Não trocar em modo combate ativado
			_menuFlag[TRADEON] = !_menuFlag[TRADEON];
			tradeWindow->setVisible(_menuFlag[TRADEON]);
			//}
		}


		if(_gerEventos->isKeyDown(KEY_KEY_W))
		{
			//float x = cos(((direcao+90)*PI)/180)*velocidade;
			//float z = -sin(((direcao+90)*PI)/180)*velocidade;
			_gameCore->_myPlayerChar->_modelo->setPosition(_gameCore->_myPlayerChar->_modelo->getPosition() + 
				
				vector3df(
				cos(((_gameCore->_myPlayerChar->_direcao+90)*PI)/180)*_gameCore->_myPlayerChar->_velAnim,
				0,
				-sin(((_gameCore->_myPlayerChar->_direcao+90)*PI)/180)*_gameCore->_myPlayerChar->_velAnim));

			_newPosition = true;
		}

		if(_gerEventos->isKeyDown(KEY_KEY_S))
		{
			//float x = cos(((direcao+180+90)*PI)/180)*velocidade;
			//float z = -sin(((direcao+180+90)*PI)/180)*velocidade;

			_gameCore->_myPlayerChar->_modelo->setPosition(_gameCore->_myPlayerChar->_modelo->getPosition() + 
				vector3df(cos(((_gameCore->_myPlayerChar->_direcao+180+90)*PI)/180)*_gameCore->_myPlayerChar->_velAnim,
				0,
				-sin(((_gameCore->_myPlayerChar->_direcao+180)*PI)/180+90)*_gameCore->_myPlayerChar->_velAnim));
			_newPosition = true;
		}

		if(_gerEventos->isKeyDown(KEY_KEY_Q))
		{
			_gameCore->_myPlayerChar->_modelo->setPosition(_gameCore->_myPlayerChar->_modelo->getPosition() + 
				vector3df(cos(((_gameCore->_myPlayerChar->_direcao)*PI)/180)*_gameCore->_myPlayerChar->_velAnim,
				0,
				-sin(((_gameCore->_myPlayerChar->_direcao)*PI)/180)*_gameCore->_myPlayerChar->_velAnim));

			_newPosition = true;
		}

		if(_gerEventos->isKeyDown(KEY_KEY_E))
		{
			_gameCore->_myPlayerChar->_modelo->setPosition(_gameCore->_myPlayerChar->_modelo->getPosition() + 
				vector3df(cos(((_gameCore->_myPlayerChar->_direcao+180)*PI)/180)*_gameCore->_myPlayerChar->_velAnim,
				0,
				-sin(((_gameCore->_myPlayerChar->_direcao+180)*PI)/180)*_gameCore->_myPlayerChar->_velAnim));

			_newPosition = true;
		}

		if(_gerEventos->isKeyDown(KEY_KEY_A))
		{
			_gameCore->_myPlayerChar->_direcao-=1;
			_gameCore->_myPlayerChar->_modelo->setRotation(vector3df(0.f, _gameCore->_myPlayerChar->_direcao, 0.f));
		}

		if(_gerEventos->isKeyDown(KEY_KEY_D))
		{
			_gameCore->_myPlayerChar->_direcao+=1;
			_gameCore->_myPlayerChar->_modelo->setRotation(vector3df(0.f, _gameCore->_myPlayerChar->_direcao, 0.f));
		}
	}

	// Rotações da câmera

	if(_gerEventos->isKeyDown(KEY_NUMPAD2))
	{
		// Gira a câmera para baixo
		if(_gameCore->camRotVert < 50)
			_gameCore->camRotVert += 2;
	}

	if(_gerEventos->isKeyDown(KEY_NUMPAD8))
	{
		// Gira a câmera para cima
		if(_gameCore->camRotVert > 0)
			_gameCore->camRotVert -= 2;
	}

	if(_gerEventos->isKeyDown(KEY_NUMPAD4))
	{
		// Gira a câmera para a esquerda
		_gameCore->camRotHor += 2;
		if(_gameCore->camRotHor >= 360.0)
			_gameCore->camRotHor -= 360.0;
	}

	if(_gerEventos->isKeyDown(KEY_NUMPAD6))
	{
		// Gira a câmera para a direita
		_gameCore->camRotHor -= 2;
		if(_gameCore->camRotHor < 0.0)
			_gameCore->camRotHor += 360.0;
	}

	// Reestabelece o elemento de Hud em foco
	_gerHud->setFocus(focusedElement);
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuJogo::updateGraphics()
{	
	//_gameCore->_myPlayerChar->_modelo->setPosition(_gameCore->upd3DPosition(_gameCore->_myPlayerChar->_modelo->getPosition().X, _gameCore->_myPlayerChar->_modelo->getPosition().Z));
		
	_gameCore->_emptyCam->setPosition(_gameCore->_myPlayerChar->_modelo->getPosition());

	_gameCore->_emptyCam->setRotation(_gameCore->rotacaoResultante(0, _gameCore->camRotHor, _gameCore->camRotVert));


	//_toonShader->apply(_modelo[0],"recursos/texturas/besouro1.jpg");

	if(_newPosition)
	{
		//meOnMap->setRelativePosition(meOnMap->getRelativePosition() + position2d<s32>(1,1));
		_newPosition = false;
	}

	_roleta->update();
}

//-----------------------------------------------------------------------------------------------------------------

void CMenuJogo::graphicsDrawAddOn() 
{
	//_gameCore->boneMao->updateAbsolutePositionOfAllChildren();
	//_gameCore->boneCabeca->updateAbsolutePositionOfAllChildren();
	_gameCore->maca->updateAbsolutePosition();
	_gameCore->capacete->updateAbsolutePosition();
	


	_gerVideo->setTransform(ETS_WORLD, matrix4());
	_gerVideo->setMaterial(_material);
	_gerVideo->draw3DTriangle(_trianguloCapt, SColor(0,255,0,0));

	if(_gameCore->showContorno)
	{
		_gameCore->contourAll(_gerCena->getRootSceneNode());
	}
}

//-----------------------------------------------------------------------------------------------------------------
