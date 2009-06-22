/*
* Classe CObject
*
* Autor: Eder Figueiredo
*
* Objetivo: Objeto base para todas as outras classes
*
*/

//Define a criação da classe
#ifndef _COBJECT_CPP_
#define _COBJECT_CPP_

#include "CWarBugObject.h"

int CWarBugObject::getID()
{
	return(_id);
}
void CWarBugObject::setID(int newID)
{
	_id = newID;
}
int CWarBugObject::getSceneID()
{
	return(_sceneId);
}
void CWarBugObject::setSceneID(int newID)
{
	_sceneId = newID;
}
// -------------------------------------------------------------------------------------------------------------------
CObjectCount::CObjectCount()
{
	_objCount = 0;
	_bufferSize = 0;
	_buffer = new int[1];
}
int CObjectCount::giveID()
{
    int idToReturn;
    if(_bufferSize > 0)
    {
		idToReturn = _buffer[0];
        int *tempBuffer;
        if(_bufferSize == 1)
        {
			tempBuffer = NULL;
		}
        else
        {
			tempBuffer = new int[_bufferSize-1];
		}
        for(int i = 0; i < _bufferSize-1; i = i + 1)
        {
			tempBuffer[i] = _buffer[i+1];        
		}
        _buffer = NULL;
        _buffer = tempBuffer;
        _bufferSize = _bufferSize-1;
	}
    else
    {
		_objCount = _objCount + 1;
        idToReturn = _objCount - 1;
    }
    return(idToReturn);
}
void CObjectCount::removeID(int ID)
{
    if(_bufferSize == 0)
    {
		_buffer = new int[1];
        _buffer[0] = ID;
        _bufferSize = 1;
    }
    else
    {
		int *tempBuffer = new int[_bufferSize+1];
        for(int i = _bufferSize-1; i >= 0; i = i - 1)
        {
			tempBuffer[i] = _buffer[i];
		}
        tempBuffer[_bufferSize] = ID;
		_buffer = NULL;
        _buffer = tempBuffer;
        _bufferSize = _bufferSize+1;
	}
}
int CObjectCount::objectCount()
{ 
	return(_objCount);
}
#endif