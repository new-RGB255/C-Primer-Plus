#include<iostream>
#include "tabtenn0.h"

TableTennisPlayer::TableTennisPlayer(const string& fn,
	const string& ln, bool ht)
	:firstname(fn), lastname(ln), hasTable(ht) {}

TableTennisPlayer::~TableTennisPlayer(){}

void TableTennisPlayer::Name() const {
	std::cout << lastname << ", " << firstname;
}
/*


*/
RatedPlayer::RatedPlayer(unsigned int r, const string& fn,
	const string& ln, bool ht) :TableTennisPlayer(fn, ln, ht), rating(r) {}

RatedPlayer::RatedPlayer(unsigned int r, const TableTennisPlayer& tp) 
	:rating(r), TableTennisPlayer(tp) {}

RatedPlayer::~RatedPlayer(){}

