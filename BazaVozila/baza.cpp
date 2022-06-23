#include "baza.h"

int vozilo::aktivnaVozila = 0;

int vozilo::imena[] = { 0 };

int vozilo::brojAktivnihVozila()
{
	return aktivnaVozila;
}

int vozilo::brojPredOtpisom()
{
	int otpisCounter = 0;
	for (auto test : vozila)
	{
		if (test->kilometriPredOtpis() <= 1000)
		{
			otpisCounter++;
		}
	}
	return otpisCounter;
}

int vozilo::novcanoStanje()
{
	return budzet;
}

void vozilo::otpisi()
{
	for (auto test : vozila)
	{
		test->izbrisiPredOtpis();
	}
}

void vozilo::ispisAktivnihVozila()
{
	sort(vozila.begin(), vozila.end(), usporedba);
	int i = 0;

	for (; i < (vozila.size() - 1); i++)
	{
		std::cout << "(" << vozila[i]->m_tezinaVozila << ", " << vozila[i]->m_prijedeniKilometri << ", " << vozila[i]->m_brojZamjenaMotora << "), ";
	}
	std::cout << "(" << vozila[i]->m_tezinaVozila << ", " << vozila[i]->m_prijedeniKilometri << ", " << vozila[i]->m_brojZamjenaMotora << ").\n";
}

bool vozilo::usporedba(vozilo* v1, vozilo* v2)
{
	return v1->m_prijedeniKilometri > v2->m_prijedeniKilometri;
}

int vozilo::usporedi(vozilo& v)
{
	int counter = 0;
	for (auto voz : vozila)
	{
		if ((voz->tip == v.tip) && (voz->m_prijedeniKilometri > v.m_prijedeniKilometri))
		{
			counter++;
		}
	}
	return counter;
}

int vozilo::ispitajPoslove(std::vector<int>& duljinePuteva, std::vector<int>& brojeviOsoba, std::vector<int>& tereti)
{
	double testBudzet = 0;
	double trosak = 0;
	double zarada = 0;
	bool test = false;
	int counter = 0;
	for (auto v : vozila)
	{
		testBudzet = budzet;
		for (int i = 0; i < duljinePuteva.size(); i++)
		{
			trosak = v->trosakPuta(duljinePuteva[i], brojeviOsoba[i], tereti[i]);
			if (trosak == 0)
			{
				test = true;
				break;
			}
			else
			{
				zarada = v->zarada(duljinePuteva[i], tereti[i]);
				testBudzet = testBudzet - trosak + zarada;
			}
		}
		if (test)
		{
			test = false;
			break;
		}
		else
		{
			if (testBudzet > 0)
			{

				counter++;
			}
		}
	}
	return counter;
}

int vozilo::generirajBroj()
{
	for (int i = 1; i < sizeof(imena); i++)
	{
		if (imena[i] == 0)
		{
			broj = i;
			imena[i] = i;
			return broj;
		}
	}
}

void vozilo::oslobodiBroj()
{
	imena[broj] = 0;
}

double avion::trosakPuta(int duljinaPuta, int brojOsoba, int teret)
{
	if (duljinaPuta <= 0 || teret<0 || teret>m_maxTezinaPrtljaznogProstora)
	{
		return 0;
	}
	double trosak;
	int ukupnaTezina = teret + m_tezinaVozila;

	trosak = gorivoPoUdaljenosti(duljinaPuta) * gorivoPoTezini(ukupnaTezina) / gorivoPoTezini(MIN_TEZINA_VOZILA) * 26.65;
	budzet -= trosak;

	m_prijedeniKilometri += duljinaPuta;

	if ((m_prijedeniKilometri - ((m_motor->m_brojServisa + 1) * SERVIS_AVIONA_KM)) > 0)
	{
		if (m_motor->m_brojServisa < 10)
		{
			m_motor->m_brojServisa++;
			budzet -= CIJENA_SERVISA_AVIONA;
			trosak += CIJENA_SERVISA_AVIONA;
		}
		else
		{
			if (m_brojZamjenaMotora < 3)
			{
				m_motor->m_brojServisa = 0;
				m_prijedeniKilometri = 0;
				m_brojZamjenaMotora++;
				budzet -= CIJENA_MOTORA_AVIONA;
				trosak += CIJENA_MOTORA_AVIONA;
			}
			else
			{
				this->~avion();
			}
		}
	}
	return trosak;
}

double avion::zarada(int duljinaPuta, int kolicinaTereta)
{
	double zarada = duljinaPuta * (10 + 0.8 * kolicinaTereta);
	budzet += zarada;
	return zarada / 3;
}

int avion::kilometriPredOtpis()
{
	double maxBrojKilometara = 44 * SERVIS_AVIONA_KM;
	double trenutniBrojKilometara = (11 * SERVIS_AVIONA_KM * m_brojZamjenaMotora) + m_prijedeniKilometri;
	return maxBrojKilometara - trenutniBrojKilometara;
}

void avion::izbrisiPredOtpis()
{
	if (m_brojZamjenaMotora == 3 && m_motor->m_brojServisa == 10 && m_prijedeniKilometri == KM_ZA_OTPIS_AVIONA)
	{
		this->~avion();
	}
}

double helikopter::trosakPuta(int duljinaPuta, int brojOsoba, int teret)
{
	if (duljinaPuta <= 0 || brojOsoba > m_brojPutnika || brojOsoba < 0 || teret < 0 || teret > m_maxTeret)
	{
		return 0;
	}
	double trosak = 3;
	int ukupnaTezina = brojOsoba * 100 + teret + m_tezinaVozila;
	trosak = gorivoPoUdaljenosti(duljinaPuta) * gorivoPoTezini(ukupnaTezina) / gorivoPoTezini(MIN_TEZINA_VOZILA) * (double)26.65;
	budzet -= trosak;

	m_prijedeniKilometri += duljinaPuta;

	if ((m_prijedeniKilometri - ((m_motor->m_brojServisa + 1) * SERVIS_HELIKOPTERA_KM)) > 0)
	{
		if (m_motor->m_brojServisa < 10)
		{
			m_motor->m_brojServisa++;
			budzet -= CIJENA_SERVISA_HELIKOPTERA;
			trosak += CIJENA_SERVISA_HELIKOPTERA;
		}
		else
		{
			if (m_brojZamjenaMotora < 3)
			{
				m_motor->m_brojServisa = 0;
				m_prijedeniKilometri = 0;
				m_brojZamjenaMotora++;
				budzet -= CIJENA_MOTORA_HELIKOPTERA;
				trosak += CIJENA_MOTORA_HELIKOPTERA;
			}
			else
			{
				this->~helikopter();
			}
		}
	}
	return trosak;
}

double helikopter::zarada(int duljinaPuta, int kolicinaTereta)
{
	double zarada = duljinaPuta * (10 + 0.8 * kolicinaTereta);
	budzet += zarada;
	return zarada;
}

int helikopter::kilometriPredOtpis()
{
	double maxBrojKilometara = 44 * SERVIS_HELIKOPTERA_KM;
	double trenutniBrojKilometara = (11 * SERVIS_HELIKOPTERA_KM * m_brojZamjenaMotora) + m_prijedeniKilometri;
	return maxBrojKilometara - trenutniBrojKilometara;
}
void helikopter::izbrisiPredOtpis()
{
	if (m_brojZamjenaMotora == 3 && m_motor->m_brojServisa == 10 && m_prijedeniKilometri == KM_ZA_OTPIS_HELIKOPTERA)
	{
		this->~helikopter();
	}
}

double gorivoPoUdaljenosti(int duljinaPuta)
{
	return (double)3 * duljinaPuta;
}

double gorivoPoTezini(int tezina)
{
	return ((double)5 * tezina) / (double)100;
}