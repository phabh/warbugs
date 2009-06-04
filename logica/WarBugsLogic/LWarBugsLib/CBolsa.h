#pragma once
#include <iostream>
using namespace std;
#include "Enumerators.h"
#include "CItem.h"

typedef SCelula<CItem> SElemento;

class CBolsa : public C3DObject
{
private:
	SElemento *_first;
	int _size;
	bool _open;

public:
	CBolsa(void);
	CBolsa(CItem * item);

	bool isOpen();
	bool isEmpty();
	int size();
	void setOpen(bool isopen);
	void addItem(CItem *item);
	CItem *removeItemAt(int pos);
	CItem *removeItem(int ID);
	CItem *removeSceneItem(int sceneID);
	//CItem *removeItem(CItem *item);
	CItem *getItem(int IDItem);
	CItem *getSceneItem(int sceneID);
	CItem *getElementAt(int index);

	bool haveItem(int ID);
};
