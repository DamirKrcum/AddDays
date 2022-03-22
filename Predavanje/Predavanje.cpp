// Zadatak sa predavanja sa optimizacijom za iteriranje za broj dana veci od 365

#include <iostream>
#include <ctime>
using namespace std;
int brojac = 1;
class Datum {
private:
	int _dan, _mjesec, _godina;

	bool PrijestupnaGodina(int godina) {
		return	godina % 4 == 0 && godina % 100 != 0 || godina % 400 == 0;
	}
	int PosljednjiDanUMjesecu(int mjesec, int godina) {
		if (mjesec == 2)
			return 28 + PrijestupnaGodina(godina);
		if (mjesec == 4 || mjesec == 6 || mjesec == 9 || mjesec == 11)
			return 30;
		return 31;
	}
	bool ValidanDatum(int dan, int mjesec, int godina) {
		if (dan < 1 || dan > PosljednjiDanUMjesecu(mjesec, godina) || mjesec < 1 || mjesec>12 || godina < 1900)
			return false;
		return true;
	}
	void SetDatum(int dan, int mjesec, int godina) {
		_dan = dan;
		_mjesec = mjesec;
		_godina = godina;
	}
	tm GetTrenutniDatum() {
		tm datum;
		time_t trenutnoVrijeme = time(nullptr);
		localtime_s(&datum, &trenutnoVrijeme);
		return datum;
	}
	void SetDanasnjiDatum() {
		tm danas = GetTrenutniDatum();
		SetDatum(danas.tm_mday, danas.tm_mon + 1, danas.tm_year + 1900);
	}


public:


	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		if (ValidanDatum(dan, mjesec, godina)) {
			SetDatum(dan, mjesec, godina);
		}
		else
			SetDanasnjiDatum();
	}
	void Ispis() {
		cout << _dan << "." << _mjesec << "." << _godina << "." << endl;
	}
	void AddDays(int brojDana)
	{
		while (brojDana > 0)
		{
			int danaDoKrajaMjeseca = PosljednjiDanUMjesecu(_mjesec, _godina) - _dan + 1;
			while (brojDana >= 365) {

				brojDana -= 365;
				if (PrijestupnaGodina(_godina)) {
					brojDana -= 1;
				}
				_godina++;
				brojac++; // broji iteracije za povecanje godine

			}
			if (brojDana >= danaDoKrajaMjeseca) {
				_dan = 1;
				_mjesec++;
				if (_mjesec > 12) {
					_mjesec = 1;
					_godina++;
				}
				brojDana -= danaDoKrajaMjeseca;
			}
			else {
				_dan += brojDana;
				brojDana = 0;
			}

		}
	}
};
int main()
{
	int numOfDays = 10000;
	Datum Danas(22, 3, 2022);
	Danas.Ispis();
	Danas.AddDays(numOfDays);
	Danas.Ispis();
	cout << "Prolazak kroz optimizaciju: " << brojac << ". Dana: " << numOfDays << endl;

}

