#pragma once

class CClientLoyalty
{
private:
	int _aranha;
	int _besouro;
	int _escorpiao;
	int _louvadeus;
	int _vespa;
public:
	CClientLoyalty(void);
	CClientLoyalty(int spider, int beetle, int scorpion, int mantis, int wasp);
	CClientLoyalty(CClientLoyalty * base);
	int getSpiderLoyalty();
	int getBeetleLoyalty();
	int getScorpionLoyalty();
	int getMantisLoyalty();
	int getWaspLoyalty();
};
