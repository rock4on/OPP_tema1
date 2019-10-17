#include "pch.h"
#include <iostream>
#include <fstream>


using namespace std;










class nod
{


private:
	int valoare;
	nod* next;
	friend class lista;

public:
	bool is_egal(nod &n)
	{
		if (this == &n) return true;
		else
		{
			return false;
		}
	}


};

class lista
{
public:
	int nr_elemente;
	nod *start;

	lista()
	{
		nr_elemente = 0;
		start = new nod;
		start->next = new nod;
	}

	lista(lista &l)
	{
		nr_elemente = 0;
		start = new nod;
		start->next = new nod;
		copiere(l);
	}

	~lista()
	{

			nod* current = start;
			nod* next;
			int p = 0;
			while (p < nr_elemente) {
				next = current->next;
				delete current;
				current = next;
				p++;
			}
		
		cout << "D" << endl;
	}

	
	void adauga_cap(int el)
	{
		nod *poz = start;
		for (int i = 0; i < nr_elemente; i++)
		{
			poz = poz->next;
		}
		poz->next = new nod;
		poz->valoare = el;
		nr_elemente++;
	}

	int el(int p)
	{
		if (p > nr_elemente - 1) return -9999;
		nod *poz = start;
		for (int i = 0; i < p; i++)
		{
			poz = poz->next;
		}
		return poz->valoare;

	}

	void rm(int p)
	{
		if (p == 0)
		{
			nod *poz = start;
			poz = poz->next;
			start = poz;
			nr_elemente--;
			return;
		}

		nod *poz = start;
		for (int i = 0; i < p - 1; i++)
		{
			poz = poz->next;
		}

		nod *par = poz->next;
		poz->next = par->next;
		delete par;
		
		nr_elemente--;
	}


	void golire()
	{
		for (int i = 0; i < nr_elemente; i++)
		{
			rm(i);
		}
		start->valoare = 0;

	}


	void copiere(lista &m)
	{
		if (start->is_egal(*m.start)) return;
		golire();
		start->valoare = m.start->valoare;
		int i = 1;
		while (m.nr_elemente > i)
		{
			adauga_cap(m.el(i));
			i++;
		}
		
	}
	


	void afisare()
	{
		nod *poz = start;
		for (int i = 0; i <nr_elemente; i++)
		{
			cout << poz->valoare<<" ";
			poz = poz->next;
			
		}
	}


	void swap(nod *n1 ,nod *n2)
	{
		int aux = n1->valoare;
		n1->valoare = n2->valoare;
		n2->valoare = aux;
	}


	void add(lista&l2)
	{
		nod* curent = start;
		for (int i = 1; i < nr_elemente; i++)
		{
			curent = curent->next;
		}
		int s = 0;
		nod* c2 = l2.start;
		if (nr_elemente == 0)
		{
			s = 1;
			curent->valoare = c2->valoare;
			c2 = c2->next;
		}
		for (int i = s; i < l2.nr_elemente; i++)
		{
			curent->next = new nod;
			curent->next->valoare = c2->valoare;
			curent= curent->next;
			c2 = c2->next;
		}
		curent->next = new nod;
		nr_elemente += l2.nr_elemente;
	}


	void sortare()
	{
		bool unsorted = true;
				nod * cur;
		int p;
		while (unsorted) {
			unsorted = false;
			cur = start;
			p = 1;
			while (p<nr_elemente) {
				nod *next = cur->next;
				if (next->valoare < cur->valoare) {
					swap(cur, next);
						unsorted = true;
				}
				p++;
				cur = cur->next;
			}
		}
	}


	void to_multime()
	{
		sortare();
		bool unsorted = true;
		nod * cur;
		int p;
		while (unsorted) {
			unsorted = false;
			cur = start;
			p = 1;
			while (p < nr_elemente) {
				nod *next = cur->next;
				if (next->valoare == cur->valoare) {
					rm(p);
					unsorted = true;
				}
				p++;
				cur = cur->next;
			}
		}



	}

	void intersectie(lista &m)
	{
		to_multime();
		m.to_multime();
		add(m);
		int i = 0,j=0;
		while (i<nr_elemente)
		{
			j = i + 1; int nr = 0;
			while (j<nr_elemente)
			{
				if (el(i) == el(j)) nr++;
				j++;
			}
			if (nr < 1) rm(i);
			else i++;
			
		}
	}

	void scadere(lista &m)
	{
		lista copie=*this;
		to_multime();
		m.to_multime();
		add(m);
		int i = 0, j = 0;
		while (i < nr_elemente)
		{
			j = i + 1;
			while (j < nr_elemente)
			{
				if (el(i) == el(j)) {
					rm(j); rm(i); j = i+1;
				}
				else j++;
			}
			i++;
		}
		intersectie(copie);
	}
	
	lista &operator=(lista &m)
	{
		copiere(m);
		return *this;
	}

	 lista &operator+(lista &m)
	{
		 this->add(m);
		return *this;
	}


};



class multime
{
private:
lista elemente;
int &nr_elemente = elemente.nr_elemente;	

public:
	
	multime()
	{

	}

	multime(multime&m)
	{
		elemente = m.elemente;
	}


	void golire()
	{
		elemente.golire();
		
	}


	

	int af(int p)
	{
		return elemente.el(p);
	}
	void add(int e)
	{
		elemente.adauga_cap(e);
		elemente.to_multime();
	}

	void afisare()
	{
		elemente.afisare();
	}

	void egalare(multime &m)
	{
		elemente=m.elemente;
	}

	multime &operator=(multime &m)
	{
		egalare(m);
		elemente.to_multime();
		return *this;
	}

	multime &operator+(multime &m)
	{
		elemente=elemente + m.elemente;
		elemente.to_multime();
		return *this;
	}

	void intersectie(multime &m)
	{
		elemente.intersectie(m.elemente);
	}

	multime &operator*(multime &m)
	{
		intersectie(m);
		return *this;
	}

	multime &operator -(multime &m)
	{
		elemente.scadere(m.elemente);
		return *this;
	}

};







int main()
{
	ifstream in("C:/Users/andre/source/repos/MULTIME_TEMA12_OOP/in.txt");

	multime m,l;
	int n,c;
	in >> n;
	while (n)
	{
		in >> c;
		m.add(c);
		n--;
	}
	//m.afisare();
	//multime l;
	in >> n;
	while (n)
	{
		in >> c;
		l.add(c);
		n--;
	}
	m.afisare();
	cout << endl;
	
	l.afisare();
	cout<<endl;
	l.add(4);
	m.add(6);
//	l=m + l;
	m.afisare(); cout << endl;
	l.afisare(); cout << endl;
	m=l-m;
	m.afisare();
	return 0;
}
