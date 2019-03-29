#pragma once

#include "list.h"
#include "../structure_iterator.h"
#include "../array/array.h"
#include <Windows.h>
#include <Psapi.h>

namespace structures
{

	/// <summary> Zoznam implementovany polom. </summary>
	/// <typeparam name = "T"> Typ dat ukladanych v zozname. </typepram>
	template<typename T>
	class ArrayList : public List<T>
	{
	public:
		/// <summary> Konstruktor. </summary>
		ArrayList();

		/// <summary> Kopirovaci konstruktor. </summary>
		/// <param name = "other"> ArrayList, z ktoreho sa prevezmu vlastnosti. </param>
		ArrayList(const ArrayList<T>& other);

		/// <summary> Destruktor. </summary>
		~ArrayList();

		/// <summary> Operacia klonovania. Vytvori a vrati duplikat zoznamu. </summary>
		/// <returns> Ukazovatel na klon struktury. </returns>
		Structure* clone() const override;

		/// <summary> Vrati pocet prvkov v zozname. </summary>
		/// <returns> Pocet prvkov v zozname. </returns>
		size_t size() const override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		List<T>& operator=(const List<T>& other) override;

		/// <summary> Operator priradenia. </summary>
		/// <param name = "other"> Zoznam, z ktoreho ma prebrat vlastnosti. </param>
		/// <returns> Adresa, na ktorej sa tento zoznam nachadza po priradeni. </returns>
		ArrayList<T>& operator=(const ArrayList<T>& other);

		/// <summary> Vrati adresou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Adresa prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T& operator[](const int index) override;

		/// <summary> Vrati hodnotou prvok na indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Hodnota prvku na danom indexe. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		const T operator[](const int index) const override;

		/// <summary> Prida prvok do zoznamu. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		void add(const T& data) override;

		/// <summary> Vlozi prvok do zoznamu na dany index. </summary>
		/// <param name = "data"> Pridavany prvok. </param>
		/// <param name = "index"> Index prvku. </param>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		/// <remarks> Ak je ako index zadana hodnota poctu prvkov (teda prvy neplatny index), metoda insert sa sprava ako metoda add. </remarks>
		void insert(const T& data, const int index) override;

		/// <summary> Odstrani prvy vyskyt prvku zo zoznamu. </summary>
		/// <param name = "data"> Odstranovany prvok. </param>
		/// <returns> true, ak sa podarilo prvok zo zoznamu odobrat, false inak. </returns>
		bool tryRemove(const T& data) override;

		/// <summary> Odstrani zo zoznamu prvok na danom indexe. </summary>
		/// <param name = "index"> Index prvku. </param>
		/// <returns> Odstraneny prvok. </returns>
		/// <exception cref="std::out_of_range"> Vyhodena, ak index nepatri do zoznamu. </exception>  
		T removeAt(const int index) override;

		/// <summary> Vrati index prveho vyskytu prvku v zozname. </summary>
		/// <param name = "data"> Prvok, ktoreho index sa hlada. </param>
		/// <returns> Index prveho vyskytu prvku v zozname, ak sa prvok v zozname nenachadza, vrati -1. </returns>
		int getIndexOf(const T& data) override;

		/// <summary> Vymaze zoznam. </summary>
		void clear() override;

		/// <summary> Vrati skutocny iterator na zaciatok struktury </summary>
		/// <returns> Iterator na zaciatok struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getBeginIterator() const override;

		/// <summary> Vrati skutocny iterator na koniec struktury </summary>
		/// <returns> Iterator na koniec struktury. </returns>
		/// <remarks> Zabezpecuje polymorfizmus. </remarks>
		Iterator<T>* getEndIterator() const override;

		/*/// <summary> Vrati teoreticky maximalny pocet prvkov, ktore je mozne do kontajnera ulozit (vzhladom na dostupnu pamat). </summary>
		/// <returns> Maximalny pocet prvkov v strukture. </returns>
		/// <remarks> Na ziskanie informacii o pamati je mozne vyuzit funkciu GetProcessMemoryInfo. </remarks>
		size_t max_size() const;*/

		/// <summary> Zabezpeci, aby mal zoznam danu kapacitu. Ak taku kapacitu zoznam uz ma, nespravi nic. </summary>
		/// <param name = "capacity"> Pozadovana kapacita zoznamu. </param>
		/// <remarks> Nemeni pocet prvkov v zozname. </remarks>
		void reserve(size_t capacity);

		/// <summary> Vrati aktualnu kapacitu zoznamu. </summary>
		/// <returns> Aktualna kapacita zoznamu. </returns>
		size_t capacity() const;

		/// <summary> Fyzicky odstrani (dealokuje) nepotrebne miesto v zozname. </summary>
		/// <remarks> Po volani tejto funkcie plati: size() == capacity(). </remarks>
		void shrink_to_fit();
	private:
		/// <summary> Pole s datami. </summary>
		Array<T>* array_;
		/// <summary> Pocet prvkov v zozname. </summary>
		size_t size_;
	private:
		/// <summary> Rozsiri kapacitu zoznamu. </summary>
		void enlarge();

		/// <summary> Iterator pre ArrayList. </summary>
		class ArrayListIterator : public Iterator<T>
		{
		public:
			/// <summary> Konstruktor. </summary>
			/// <param name = "arrayList"> Zoznam, cez ktory iteruje. </param>
			/// <param name = "position"> Pozicia, na ktorej zacina. </param>
			ArrayListIterator(const ArrayList<T>* arrayList, int position);

			/// <summary> Destruktor. </summary>
			~ArrayListIterator();

			/// <summary> Operator priradenia. Priradi do seba hodnotu druheho iteratora. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> Vrati seba po priradeni. </returns>
			Iterator<T>& operator= (const Iterator<T>& other) override;

			/// <summary> Porovna sa s druhym iteratorom na nerovnost. </summary>
			/// <param name = "other"> Druhy iterator. </param>
			/// <returns> True, ak sa iteratory nerovnaju, false inak. </returns>
			bool operator!=(const Iterator<T>& other) override;

			/// <summary> Vrati data, na ktore aktualne ukazuje iterator. </summary>
			/// <returns> Data, na ktore aktualne ukazuje iterator. </returns>
			const T operator*() override;

			/// <summary> Posunie iterator na dalsi prvok v strukture. </summary>
			/// <returns> Iterator na dalsi prvok v strukture. </returns>
			/// <remarks> Zvycajne vrati seba. Ak vrati iny iterator, povodny bude automaticky zruseny. </remarks>
			Iterator<T>& operator++() override;
		private:
			/// <summary> Zoznam, cez ktory iteruje. </summary>
			const ArrayList<T>* arrayList_;
			/// <summary> Aktualna pozicia v zozname. </summary>
			int position_;
		};
	};

	template<typename T>
	inline ArrayList<T>::ArrayList() :
		List(),
		array_(new Array<T>(4)),
		size_(0)
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayList(const ArrayList<T>& other) :
		List(),
		array_(new Array<T>(*other.array_)),
		size_(other.size_)
	{
	}

	template<typename T>
	inline ArrayList<T>::~ArrayList()
	{
		delete array_;
		array_ = nullptr;
		size_ = 0;
	}

	template<typename T>
	inline Structure * ArrayList<T>::clone() const
	{
		return new ArrayList<T>(*this);
	}

	template<typename T>
	inline size_t ArrayList<T>::size() const
	{
		return size_;
	}

	template<typename T>
	inline List<T>& ArrayList<T>::operator=(const List<T>& other)
	{
		if (this != &other)
		{
			*this = dynamic_cast<const ArrayList<T>&>(other);
		}
		return *this;
	}

	template<typename T>
	inline ArrayList<T>& ArrayList<T>::operator=(const ArrayList<T>& other)
	{
		if (this != &other)
		{
			delete array_;
			size_ = other.size_;
			array_ = new Array<T>(size_);
			Array<T>::copy(*other.array_, 0, *array_, 0, size_);
		}
		return *this;
	}

	template<typename T>
	inline T & ArrayList<T>::operator[](const int index)
	{
		if (index >= 0 && index < size_)
		{
			return (*array_)[index];
		}
		else
		{
			throw std::out_of_range("BAD INDEX!");
		}

	}

	template<typename T>
	inline const T ArrayList<T>::operator[](const int index) const
	{
		if (index >= 0 && index < size_)
		{
			return (*array_)[index];
		}
		else
		{
			throw std::out_of_range("BAD INDEX!");
		}
	}

	template<typename T>
	inline void ArrayList<T>::add(const T & data)
	{
		if (size_ == array_->size())
		{
			enlarge();
		}
		(*array_)[size_++] = data;
	}

	template<typename T>
	inline void ArrayList<T>::insert(const T & data, const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_ + 1, "Invalid index");
		if (size_ == index)
		{
			add(data);
		}
		else
		{
			if (size_ == array_->size())
			{
				enlarge();
			}
			Array<T>::copy(*array_, index, *array_, index + 1, size_ - index);
			(*array_)[index] = data;
			++size_;
		}
	}

	template<typename T>
	inline bool ArrayList<T>::tryRemove(const T & data)
	{
		int index = getIndexOf(data);
		if (index != -1)
		{
			removeAt(index);
			return true;
		}
		return false;
	}

	template<typename T>
	inline T ArrayList<T>::removeAt(const int index)
	{
		DSRoutines::rangeCheckExcept(index, size_, "Invalid index");
		T kopia = (*array_)[index];
		if (index < size_ - 1)
		{
			Array<T>::copy(*array_, index + 1, *array_, index, size_ - index - 1);
		}
		--size_;
		return kopia;
	}

	template<typename T>
	inline int ArrayList<T>::getIndexOf(const T & data)
	{
		for (int i = 0; i < size_; i++)
		{
			if (data == (*array_)[i])
			{
				return i;
			}
		}
		return -1;
	}

	template<typename T>
	inline void ArrayList<T>::clear()
	{
		size_ = 0;
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getBeginIterator() const
	{
		return new ArrayListIterator(this, 0);
	}

	template<typename T>
	inline Iterator<T>* ArrayList<T>::getEndIterator() const
	{
		return new ArrayListIterator(this, size_);
	}

	/*template<typename T>
	inline size_t ArrayList<T>::max_size() const
	{
		return GetProcessMemoryInfo();
	}*/

	template<typename T>
	inline void ArrayList<T>::reserve(size_t capacity)
	{
		if (array_->size() < capacity)
		{
			Array<T>* nove = new Array<T>(capacity); //vytvor nove pole
			Array<T>::copy(*array_, 0, *nove, 0, size_); //kopiruj
			delete array_; //zahod
			array_ = nove; //aktualizuj referenciu
		}
	}

	template<typename T>
	inline size_t ArrayList<T>::capacity() const
	{
		return array_->size();
	}

	template<typename T>
	inline void ArrayList<T>::shrink_to_fit()
	{
		Array<T>* nove = new Array<T>(size_); //vytvor nove pole
		Array<T>::copy(*array_, 0, *nove, 0, size_); //kopiruj
		delete array_; //zahod
		array_ = nove; //aktualizuj referenciu
	}

	template<typename T>
	inline void ArrayList<T>::enlarge()
	{
		Array<T>* nove = new Array<T>(size_ + 4); //vytvor nove pole
		Array<T>::copy(*array_, 0, *nove, 0, size_); //kopiruj
		delete array_; //zahod
		array_ = nove; //aktualizuj referenciu
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::ArrayListIterator(const ArrayList<T>* arrayList, int position) :
		arrayList_(arrayList),
		position_(position)
	{
	}

	template<typename T>
	inline ArrayList<T>::ArrayListIterator::~ArrayListIterator()
	{
		position_ = 0;
		arrayList_ = nullptr;
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator=(const Iterator<T>& other)
	{
		const ArrayListIterator& otherALI = dynamic_cast<const ArrayListIterator&>(other);

		position_ = otherALI.position_;
		arrayList_ = otherALI.arrayList_;
		return *this;
	}

	template<typename T>
	inline bool ArrayList<T>::ArrayListIterator::operator!=(const Iterator<T>& other)
	{
		const ArrayListIterator& otherALI = dynamic_cast<const ArrayListIterator&>(other);
		return position_ != otherALI.position_ || arrayList_ != otherALI.arrayList_;
	}

	template<typename T>
	inline const T ArrayList<T>::ArrayListIterator::operator*()
	{
		return (*arrayList_)[position_];
	}

	template<typename T>
	inline Iterator<T>& ArrayList<T>::ArrayListIterator::operator++()
	{
		position_++;
		return *this;
	}

}