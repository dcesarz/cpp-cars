#include <iostream>
#include <string>

namespace Pojazd {
	using std::string;
	class Samochod {
	protected:
		string marka;
		int rokprodukcji;
		double przebieg;
		string color;
		int liczbaDrzwi;
	public:

		Samochod()
		{

		}


		Samochod(string marka, int rokprodukcji, string color, int liczbaDrzwi)
		{
			this->marka = marka;
			this->rokprodukcji = rokprodukcji;
			this->color = color;
			this->liczbaDrzwi = liczbaDrzwi;


		}
		void setprzebieg(double przebieg)
		{
			this->przebieg = przebieg;
		}

		friend std::ostream& operator << (std::ostream& out, Samochod & m);

	};

	class PolskiProdukt
	{
	protected:
		string wojewodztwo; 
		string miasto;
	public:
		friend std::ostream& operator << (std::ostream& out, PolskiProdukt & pp);


	};

	class Porsche : public Samochod
	{
	private:

		int iledoSetki;

	public:
		Porsche(int rokprodukcji, string color, int liczbaDrzwi, int iledoSetki)
		{
			this->marka = "porsche";
			this->rokprodukcji = rokprodukcji;
			this->color = color;
			this->liczbaDrzwi = liczbaDrzwi;
			this->iledoSetki = iledoSetki;
		}

	};

	class Maluch : public Samochod, public PolskiProdukt {
	private:

		int glosnosc;
		bool czyJezdzi;

	public:
		Maluch (string marka, int rokprodukcji, string color, int glosnosc)
		{
			this->marka = marka;
			this->rokprodukcji = rokprodukcji;
			this->color = color;
			this->liczbaDrzwi = 2;
			this->glosnosc = glosnosc;
		}

		void setczyJezdzi(bool czyJezdzi)
		{

			this->czyJezdzi = czyJezdzi;


		}

		void setprzebieg(double przebieg)
		{
			this->przebieg = przebieg;
		}

		Maluch nowyMaluch()
		{
			Maluch m = *this;
			m.color = "bialy";
			m.przebieg = m.przebieg / 2;
			m.czyJezdzi = true;
			return m;
		}
		
		friend std::ostream& operator << (std::ostream& out, Maluch & m);


	};
	
	

	

	std::ostream& operator << (std::ostream& out, PolskiProdukt & pp)
	{
		out << "Wojewodztwo: " << pp.wojewodztwo << std::endl;
		out << "Miasto: " << pp.miasto << std::endl;
		return out;
	}


	std::ostream& operator << (std::ostream& out, Samochod & s) {
		out << "DANE POJAZDU: " << std::endl;
		out << "Marka: " << s.marka << std::endl;
		out << "Rok Produkcji: " << s.rokprodukcji << std::endl;
		out << "Przebieg: " << s.przebieg << std::endl;
		out << "Kolor: " << s.color << std::endl;
		out << "Liczba drzwi: " << s.liczbaDrzwi << std::endl;
		return out;
	}

	std::ostream& operator << (std::ostream& out, Maluch &m) {
		Samochod s1 = m;
		out << s1;
		if (m.czyJezdzi) out << "Jezdzi :)" << std::endl;
		out << "glosnosc:" << m.glosnosc << std::endl;
		return out;
	}
}

class Autohandel
{

private:
	std::string nazwa;
	Pojazd::Samochod **listaSamochodow = new Pojazd::Samochod*[100];
	int liczbaSamochodow;
public:

	Autohandel(std::string nazwa) {
		this->nazwa = nazwa;
		liczbaSamochodow = 0;
	}

	void dodajSamochod(Pojazd::Samochod *s)
	{
		int i = liczbaSamochodow;
		listaSamochodow[liczbaSamochodow] = s;
		liczbaSamochodow++;
	}

	void usunSamochod(Pojazd::Samochod * s)
	{
		if (znajdzSamochod(s) >=0)
		{
			listaSamochodow[znajdzSamochod(s)] = listaSamochodow[liczbaSamochodow - 1];
			listaSamochodow[liczbaSamochodow - 1] = nullptr;
			
			liczbaSamochodow--;

		}
		else
		{
			std::cout << "Pojazd nie istnieje" << std::endl;
		}
		//listaSamochodow[i] = nullptr;
	}

	int znajdzSamochod(Pojazd::Samochod *s)
	{
		int i;
		for (i = 0; i < liczbaSamochodow; i++) {
			if (s == listaSamochodow[i]) return i;
		}
		return -1;

	}

	friend std::ostream& operator << (std::ostream& out, Autohandel & ah)
	{
		int i;
		for (int i = 0; i < ah.liczbaSamochodow; i++)
		{
			out << *ah.listaSamochodow[i];
			out << typeid(*ah.listaSamochodow[i]).name() << std::endl;
		}
		return out;
	}

};

int main()
{
	Pojazd::Samochod s1("Audi", 1996, "czarny", 4);
	s1.setprzebieg(123);

	Pojazd::Maluch sm("Maluch", 1990, "czerwony", 34);

	sm.setczyJezdzi(true);
	sm.setprzebieg(324);

	Pojazd::Porsche sp(1990, "czerwony", 5, 23);

	sp.setprzebieg(235);

	Pojazd::Maluch sm2 = sm.nowyMaluch();

	

	Autohandel am("Automoto");
	am.dodajSamochod(&s1);
	am.dodajSamochod(&sm);
	am.dodajSamochod(&sp);
	am.dodajSamochod(&sm2);

	std::cout << am;

	std::cout << "------------------------------------------------------------------" << std::endl;

	am.usunSamochod(&sp);
	std::cout << am;
	
	system("pause");

}
