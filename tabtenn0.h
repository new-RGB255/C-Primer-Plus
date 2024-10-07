#ifndef TABTENN0_H
#define TABTENN0_H
#include<string>
using std::string;

class TableTennisPlayer {
private:
	string firstname;
	string lastname;
	bool hasTable;
public:
	TableTennisPlayer(const string& fn = "none", const string& ln = "none",
		bool ht = false);
	~TableTennisPlayer();
	void Name() const;
	bool HasTable() const { return hasTable; }
	void ResetTable(bool v) { hasTable = v; }
};

class RatedPlayer :public TableTennisPlayer {
private:
	unsigned int rating;
public:
	RatedPlayer(unsigned int r = 0, const string& fn = "none", 
		const string& ln = "none", bool ht = false);
	RatedPlayer(unsigned int r, const TableTennisPlayer& tp);
	~RatedPlayer();
	unsigned int Rating() const { return rating; }
	void ResetRating(unsigned int r) { rating = r; }
};

#endif // !TABTENN0_H
