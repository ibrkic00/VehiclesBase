#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define MIN_TEZINA_VOZILA 13000

#define SERVIS_HELIKOPTERA_KM 26000
#define CIJENA_SERVISA_HELIKOPTERA 72000
#define CIJENA_MOTORA_HELIKOPTERA 720000
#define KM_ZA_OTPIS_HELIKOPTERA 1144000

#define SERVIS_AVIONA_KM 200000
#define CIJENA_SERVISA_AVIONA 350000
#define CIJENA_MOTORA_AVIONA 1200000
#define KM_ZA_OTPIS_AVIONA 8800000

struct motor
{
	// variables
	int m_brojServisa;
	std::string m_modelMotora;
};

class vozilo
{
protected:
	// protected variables
	static int aktivnaVozila;
	static int imena[100];

	int tip;
	int broj;
	int m_brojZamjenaMotora;
	int m_tezinaVozila;
	int m_prijedeniKilometri;
	std::string m_oznakaVozila;

	motor* m_motor;

public:
	//public variables
	static double budzet;
	static std::vector<vozilo*> vozila;

	// default constructor
	vozilo()
	{
		aktivnaVozila++;
		m_motor = new motor();
		m_brojZamjenaMotora = 0;
		m_tezinaVozila = MIN_TEZINA_VOZILA;
		m_prijedeniKilometri = 0;
		m_oznakaVozila = "voz" + std::to_string(generirajBroj());
		m_motor->m_brojServisa = 0;
		m_motor->m_modelMotora = "generic";
		std::cout << "Vozilo " << m_oznakaVozila << " je kreirano.\n";
		vozila.push_back(this);
	}

	//constructor
	vozilo(int tezinaVozila, int prijedeniKilometri, int brojZamjenaMotora,
		int brojServisa, std::string modelMotora, std::string jedinstvenaOznaka)
	{
		aktivnaVozila++;
		broj = generirajBroj();
		m_motor = new motor();
		m_tezinaVozila = tezinaVozila;
		m_prijedeniKilometri = prijedeniKilometri;
		m_brojZamjenaMotora = brojZamjenaMotora;
		m_oznakaVozila = jedinstvenaOznaka;
		m_motor->m_brojServisa = brojServisa;
		m_motor->m_modelMotora = modelMotora;
		std::cout << "Vozilo " << m_oznakaVozila << " je kreirano.\n";
		vozila.push_back(this);
	}

	// copy constructor
	vozilo(const vozilo& v)
	{
		aktivnaVozila++;
		m_motor = new motor();
		m_tezinaVozila = v.m_tezinaVozila;
		m_prijedeniKilometri = v.m_prijedeniKilometri;
		m_brojZamjenaMotora = v.m_brojZamjenaMotora;
		m_oznakaVozila = "voz" + std::to_string(generirajBroj());
		m_motor->m_brojServisa = v.m_motor->m_brojServisa;
		m_motor->m_modelMotora = v.m_motor->m_modelMotora;
		std::cout << "Vozilo " << m_oznakaVozila << " je kreirano cp.\n";
		vozila.push_back(this);
	}

	// destructor
	~vozilo() {
		aktivnaVozila--;
		delete m_motor;
		std::cout << "Vozilo je otpusteno iz sluzbe.\n";
		oslobodiBroj();
		vozila.erase(std::remove(vozila.begin(), vozila.end(), this), vozila.end());
	};

	// methods
	static int brojAktivnihVozila();
	static int brojPredOtpisom();
	static int novcanoStanje();
	static void otpisi();
	static void ispisAktivnihVozila();
	static bool usporedba(vozilo* v1, vozilo* v2);
	static int usporedi(vozilo& v);
	static int ispitajPoslove(std::vector<int>& duljinePuteva, std::vector<int>& brojeviOsoba, std::vector<int>& tereti);

	int generirajBroj();
	void oslobodiBroj();

	// virtal methods
	virtual double trosakPuta(int duljinaPuta, int brojOsoba, int teret) = 0;
	virtual double zarada(int duljinaPuta, int kolicinaTereta) = 0;
	virtual int kilometriPredOtpis() = 0;
	virtual void izbrisiPredOtpis() = 0;
};

class avion :public vozilo
{
private:
	// variables
	int m_maxTezinaPrtljaznogProstora;
	std::string m_model;

public:
	// default constructor
	avion() : vozilo()
	{
		tip = 1;
		m_model = "NekiAvion";
		m_maxTezinaPrtljaznogProstora = 5000;
		std::cout << "Avion " << m_model << " je kreiran.\n";
	};

	// constructor
	avion(int tezinaVozila, int prijedeniKilometri, int brojZamjenaMotora, std::string jedinstvenaOznaka, int brojServisa,
		std::string modelMotora, std::string model, int maxTezinaPrtljaznogProstora) :
		vozilo(tezinaVozila, prijedeniKilometri, brojZamjenaMotora, brojServisa, modelMotora, jedinstvenaOznaka)
	{
		tip = 1;
		m_model = model;
		m_maxTezinaPrtljaznogProstora = maxTezinaPrtljaznogProstora;
		std::cout << "Avion " << m_model << " je kreiran.\n";
	}

	// copy constructor
	avion(const avion& a) : vozilo(a)
	{
		tip = 1;
		m_model = a.m_model;
		m_maxTezinaPrtljaznogProstora = a.m_maxTezinaPrtljaznogProstora;
		std::cout << "Avion " << m_model << " je kreiran cp.\n";
	}

	// destructor
	~avion()
	{
		std::cout << "Avion je otpusten iz sluzbe.\n";
	};

	// methods
	double trosakPuta(int duljinaPuta, int brojOsoba, int teret) override;
	double zarada(int duljinaPuta, int kolicinaTereta) override;
	int kilometriPredOtpis() override;
	void izbrisiPredOtpis() override;
};

class helikopter :public vozilo
{
private:
	// variables
	int m_maxTeret;
	int m_brojPutnika;
	std::string m_model;

public:
	// default constructor
	helikopter() : vozilo()
	{
		tip = 2;
		m_model = "NekiHelikopter";
		m_maxTeret = 500;
		m_brojPutnika = 4;
		std::cout << "Helikopter " << m_model << " je kreiran.\n";
	};

	// constructor
	helikopter(int tezinaVozila, int prijedeniKilometri, int brojZamjenaMotora, std::string jedinstvenaOznaka, int brojServisa,
		std::string modelMotora, std::string model, int maxTeret, int brojPutnika) :
		vozilo(tezinaVozila, prijedeniKilometri, brojZamjenaMotora, brojServisa, modelMotora, jedinstvenaOznaka)
	{
		tip = 2;
		m_model = model;
		m_maxTeret = maxTeret;
		m_brojPutnika = brojPutnika;
		std::cout << "Helikopter " << m_model << " je kreiran.\n";
	}

	// copy constructor
	helikopter(const helikopter& h) : vozilo(h)
	{
		tip = 2;
		m_model = h.m_model;
		m_maxTeret = h.m_maxTeret;
		m_brojPutnika = h.m_brojPutnika;
		std::cout << "Helikopter " << m_model << " je kreiran cp.\n";
	}

	// destructor
	~helikopter()
	{
		std::cout << "Helikopter je otpusten iz sluzbe.\n";
	}

	// methods
	double trosakPuta(int duljinaPuta, int brojOsoba, int teret) override;
	double zarada(int duljinaPuta, int kolicinaTereta) override;
	int kilometriPredOtpis() override;
	void izbrisiPredOtpis() override;
};

double gorivoPoUdaljenosti(int duljinaPuta);

double gorivoPoTezini(int tezina);
