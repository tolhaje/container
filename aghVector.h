#ifndef AGHVECTOR_H
	#define AGHVECTOR_H
	
	#include "aghContainer.h"
	using namespace std;

template <typename TYPE>
class aghVector : public aghContainer<TYPE> {
	
	private:
	
TYPE* tab; //< wskaznik do tablicy
int amount; //< liczba elementow w tablicy
int capacity; //< calkowita ilosc zaalokowanej pamieci

	public:
	
/**
 * \brief konstruktor domyslny
 * 
 * alokuje zawsze 10 el. wiecej by uniknac fragmentowania pamieci i czestych alokacji
 * \param _size - jak duza ma byc tablica
 */	
aghVector(int _size = 0);

/**
 * \brief konstruktor kopiujacy
 */
aghVector(const aghContainer<TYPE> &pattern);

/**
 * \brief destruktor
 */
~aghVector();


/**
 * \brief op. przypisania
 * \param pattern - przyjmuje ref. do obiektu
 * \return zwraca referencje do obiektu ktoremu przypisywalismy
 */
aghVector<TYPE>& operator=(const aghVector<TYPE> &pattern);

/**
 * \brief wstawia element na zadana pozycje
 * \param _index - gdzie wstawic
 * \param &_val - wartosc do wstawienia
 * \return true - udalo sie wstawic, false - porazka
 */
bool insert(int _index, TYPE const &_val);

/**
 * \brief zwraca referencje do obiektu na miejscu _index
 * \param _index - zadane miejsce w tablicy
 * \return referencja do obiektu na miejscu index
 */
TYPE& at(int _index) const;

/**
 * \brief zwraca liczbe elementow w pojemniku
 * \return wielkosc pojemnika
 */
int size(void) const { return this->amount; }

/**
 * \brief kasuje zadany element
 * \param _index - kasuje element na miejscu _index
 * \return czy udalo sie usunac
 */
bool remove(int _index);
///////


};

//----------------------------------------------------------------------

template <typename TYPE>
aghVector<TYPE>::aghVector(int _size)
: amount(_size), capacity(_size+10)
{
this->tab  = new TYPE[_size+10];
if(this->tab == NULL) throw aghException(0,"Memory allocation error!");
}
//----------------------------------------------------------------------
template <typename TYPE>
aghVector<TYPE>::aghVector(const aghContainer<TYPE> &pattern)
: amount(pattern.size() ), capacity(amount+10)
{
this->tab = new TYPE [pattern.size()+10];
if(this->tab == NULL) throw aghException(0,"Memory allocation error!");

for(int i=0; i<pattern.size(); i++)
	this->at(i)=pattern.at(i) ;
}

//----------------------------------------------------------------------
template <typename TYPE>
aghVector<TYPE>& aghVector<TYPE>::operator=(const aghVector<TYPE>  &right)
{
if( &right == this ); //sprawdza czy nie przypisujemy a=a,zeby nie tracic danych
else
	{
	if(!(this->isEmpty())) this->clear();
	for(int i=0; this->size()<right.size(); i++)
		this->append(right[i]);	
	}
return *this;
}

//------------------------------------------------------------------------
template <typename TYPE>
aghVector<TYPE>::~aghVector()
{
delete [] tab;
this->tab      = NULL;
this->capacity = 0;
this->amount   = 0;
}

//----------------------------------------------------------------------
template <typename TYPE>
bool aghVector<TYPE>::remove(int _index)
//funkcja usuwa element i aktualizuje liczbe elementow
{
if(_index < 0 || _index >= this->size() ) return false;
	
	for(int i=_index; i+1<this->size(); ++i) //przesuwa elementy na wolne miejsce
		this->at(i) = this->at(i+1);
		
this->amount--;
return true; 

}

//----------------------------------------------------------------------

template <typename TYPE>
bool aghVector<TYPE>::insert(int _index, TYPE const &_val)
{

if( _index < 0 ) return false;
if( _index >= this->capacity || this->capacity == this->size() )
{   //gdy brakuje miejsca realokacja tablicy
	aghVector<TYPE> temp( this->size() );

	for(int i=0; i<this->size(); ++i)
	  temp.at(i) = this->at(i);

int tt;
	if(_index>= this->capacity) tt=_index;	
	else tt=this->size();

	delete [] this->tab; 
	*this= aghVector<TYPE>(tt+1); //inicjalizacja konstruktorem

	for(int i=0, k=0; i<temp.size(); ++i, ++k)
	{ //przekopiowuje na i-te miejsce z temp. tablicy z miejsca k
	  //gdy znajdzie wstawiany index zostawia tam luke
		if(i==_index)
		{
			k--;
			continue;
		}
		this->at(i)=temp.at(k);
	}

}
else
{
	for(int i=this->size()-1; i>_index-1; i--)
		this->at(i+1) = this->at(i);
}

(*this)[_index] = _val;
this->amount++;

return true;
}

//----------------------------------------------------------------------

template <typename TYPE>
TYPE& aghVector<TYPE>::at(int _index) const
{
if(_index < 0 || _index > this->capacity-1) throw aghException(-1,"Index out of range!");
else return tab[ _index ];
}
#endif
