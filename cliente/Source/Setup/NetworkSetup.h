#pragma once

#include <string>

//-----------------------------------------------------------------------------------------
// CONSTANTES
//-----------------------------------------------------------------------------------------

const std::string SERVERHOST = "127.0.0.1";//"warbugs.ddns.com.br";/*"189.61.169.212"; "10.16.11.31";*/ // IP do servidor
const int SERVERPORT = 30003;          // Porta do servidor

const int PACKAGESIZE = 1400; // Tamanho do pacote de mensagens

//-----------------------------------------------------------------------------------------
// MENSAGENS
//-----------------------------------------------------------------------------------------

/*Identificador de Mensagens*/
enum TYPE_MESSAGE 
{
	DISCONNECT = 0,
	PING,
	END_FRAME,
	LOGIN_OK = 33,
	LOGIN_FAIL,
	SHOW_PERSONAGENS,
	CREATE_PLAYER_OK,
	CREATE_PLAYER_FAIL,
	DELETE_PLAYER_OK,
	DELETE_PLAYER_FAIL,
	START_GAME_FAIL,
	ENTER_CENARIO,
	ADD_PERSONAGEM,
	ADD_BOLSA,
	UPDATE_POSITION,
	UPDATE_ESTADO,
	UPDATE_ATACK,
	UPDATE_TARGET,
	OPENED_BOLSA,
	OPEN_FAIL,
	CLOSED_BOLSA,
	CLOSE_BOLSA_FAIL,
	UPDATE_EQUIP,
	SHOW_DAMAGE,
	SHOW_FULL_STATUS,
	CHAT,
	REMOVE_ITEM,
	ADD_ITEM,
	PRICE_ITEM,
	CHANGE_BUFFS,
	CHANGE_MONEY,
	CHANGE_BONUS,
	UPDATE_PVPPNIVEL,
	UPDATE_DIRVEL,
	ADD_QUEST,
	UPDATE_QUEST,
	QUEST_OK,
	UPDATE_BOLSA,
	SHOW_SHOP_PAGE,
	SHOW_ITEM_ATTRIBUTES,
	UPDATE_XP,
	SHOT,
	REMOVE_PERSONAGEM,
	UPDATE_LEVEL,
	REMOVE_BOLSA,
	ENEMY_REBORN,
	SCENE_FULL,
	NO_LOYALTY,
	DOUBLE_LOGIN,
	PORTAL_FAIL,
	INVENTORY_FULL,
	LOGIN_REQUEST,
	PERSONAGENS_REQUEST,
	CREATE_PERSONAGEM,
	DELETE_PERSONAGEM,
	START_GAME,
	SEND_POSITION,
	SEND_ESTADO,
	SEND_ATACK,
	OPEN_BOLSA,
	CLOSE_BOLSA,
	SEND_EQUIP,
	SEND_TARGET,
	USE_ITEM,
	DROP_ITEM,
	SEND_MESSAGE,
	SEND_ITEM,
	GET_ITEM_BOLSA,
	INSERT_ITEM_BOLSA,
	START_SHOT,
	REQUEST_FULL_STATUS,
	SEND_BONUS_POINTS,
	ACCEPT_QUEST,
	START_SHOP,
	REQUEST_SHOP_PAGE,
	BUY_ITEM,
	REQUEST_PRICE_ITEM,
	SELL_ITEM,
	TRADE_REQUEST,
	TRADE_REQUEST_ACCEPTED,
	TRADE_REQUEST_REFUSED,
	TRADE_CHANGED,
	TRADE_ACCEPTED,
	TRADE_REFUSED,
	TRADE_CONCLUDE,
	GET_ITEM_ATTRIBUTES,
	ENTER_PORTAL
};