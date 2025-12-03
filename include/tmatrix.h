// ННГУ, ИИТММ, Курс "Алгоритмы и структуры данных"
//
// Copyright (c) Сысоев А.В.
//
//

#ifndef __TDynamicMatrix_H__
#define __TDynamicMatrix_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Динамический вектор - 
// шаблонный вектор на динамической памяти
template<typename T>
class TDynamicVector
{
protected:
  size_t sz;
  T* pMem;
public:
  TDynamicVector(size_t size = 1) : sz(size)
  {
    if (sz == 0)
      throw out_of_range("Vector size should be greater than zero");
    if (sz >= MAX_VECTOR_SIZE)
        throw out_of_range("Vector size should be less than MAX_VECTOR_SIZE");
    pMem = new T[sz]();// {}; // У типа T д.б. констуктор по умолчанию
  }
  TDynamicVector(T* arr, size_t s) : sz(s)
  {
    if (sz > MAX_VECTOR_SIZE)
       throw out_of_range("Vector size should be less than MAX_VECTOR_SIZE");
    assert(arr != nullptr && "TDynamicVector ctor requires non-nullptr arg");
    pMem = new T[sz];
    std::copy(arr, arr + sz, pMem);
  }
  TDynamicVector(const TDynamicVector& v)
  {
      pMem = new T[v.sz]();
      sz = v.sz;
      for (int i = 0; i<v.sz; i++){
          pMem[i] = v.pMem[i];
      }
  }
  TDynamicVector(TDynamicVector&& v) noexcept
  {
      sz = v.sz;
      pMem = v.pMem;
      v.sz = 0;
      v.pMem = nullptr;
  }
  ~TDynamicVector()
  {
      sz = 0;
      delete[] pMem;
  }
  TDynamicVector& operator=(const TDynamicVector& v)
  {
      if (this != &v) {
          if (v.sz != sz) {
              delete[] pMem;
              sz = v.sz;
              pMem = new T[sz]();
          }
          for (int i = 0; i < sz; i++) {
              pMem[i] = v.pMem[i];
          }
      }
      return *this;
  }
  TDynamicVector& operator=(TDynamicVector&& v) noexcept
  {
      if (this != &v) {
          sz = v.sz;
          pMem = v.pMem;
          v.sz = 0;
          v.pMem = nullptr;
      }
      return *this;
  }

  size_t size() const noexcept { return sz; }

  // индексация
  T& operator [](size_t ind)
  {
      if (ind >= sz || ind < 0)throw out_of_range("");
      return pMem[ind];
  }
  const T& operator[](size_t ind) const
  {
      return &pMem[ind];
  }
  // индексация с контролем
  T& at(size_t ind)
  {
      if (0 <= ind < sz) {
          return &pMem[ind];
      }
  }
  const T& at(size_t ind) const
  {
      if (0 <= ind < sz) {
          return &pMem[ind];
      }
  }

  // сравнение
  bool operator==(const TDynamicVector& v) const noexcept
  {
      if (sz == v.sz) {
          for (int i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) { return 0; }
          }
          return 1;
      }
      return 0;
  }
  bool operator!=(const TDynamicVector& v) const noexcept
  {
      if (sz == v.sz) {
          for (int i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) { return 1; }
          }
          return 0;
      }
      return 1;
  }

  // скалярные операции
  TDynamicVector operator+(T val)
  {
      TDynamicVector x;
      x = *this;
      for (int i = 0; i < x.sz; i++) {
          x.pMem[i] += val;
      }
      return x;
  }
  TDynamicVector operator-(T val)
  {
      TDynamicVector x;
      x = *this;
      for (int i = 0; i < x.sz; i++) {
          x.pMem[i] -= val;
      }
      return x;
  }
  TDynamicVector operator*(T val)
  {
      TDynamicVector x;
      x = *this;
      for (int i = 0; i < x.sz; i++) {
          x.pMem[i] *= val;
      }
      return x;
  }

  // векторные операции
  TDynamicVector operator+(const TDynamicVector& v)
  {
      if (sz != v.sz)throw out_of_range("vectors_with_not_equal_size");
      TDynamicVector x;
      x = *this;
      for (int i = 0; i < x.sz; i++) {
          x.pMem[i] += v.pMem[i];
      }
      return x;
  }
  TDynamicVector operator-(const TDynamicVector& v)
  {
      if (sz != v.sz)throw out_of_range("vectors_with_not_equal_size");
      TDynamicVector x;
      x = *this;
      for (int i = 0; i < x.sz; i++) {
          x.pMem[i] -= v.pMem[i];
      }
      return x;
  }
  T operator*(const TDynamicVector& v) noexcept(noexcept(T()))
  {
      if (sz != v.sz)throw out_of_range("vectors_with_not_equal_size");
      TDynamicVector x;
      x = *this;
      for (int i = 0; i < x.sz; i++) {
          x.pMem[i] *= v.pMem[i];
      }
      T y = 0;
      for (int i = 0; i < x.sz; i++) {
          y += x.pMem[i];
      }
      return y;
  }
  friend void swap(TDynamicVector& lhs, TDynamicVector& rhs) noexcept
  {
    std::swap(lhs.sz, rhs.sz);
    std::swap(lhs.pMem, rhs.pMem);
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      istr >> v.pMem[i]; // требуется оператор>> для типа T
    return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicVector& v)
  {
    for (size_t i = 0; i < v.sz; i++)
      ostr << v.pMem[i] << ' '; // требуется оператор<< для типа T
    return ostr;
  }
};


// Динамическая матрица - 
// шаблонная матрица на динамической памяти
template<typename T>
class TDynamicMatrix : private TDynamicVector<TDynamicVector<T>>
{
  using TDynamicVector<TDynamicVector<T>>::pMem;
  using TDynamicVector<TDynamicVector<T>>::sz;
public:
  TDynamicMatrix(size_t s = 1) : TDynamicVector<TDynamicVector<T>>(s)
  {
    if (s >= MAX_MATRIX_SIZE || s < 0)
      throw out_of_range("Matrix size should be less than MAX_Matrix_SIZE");
    for (size_t i = 0; i < sz; i++)
      pMem[i] = TDynamicVector<T>(sz);
  }

  using TDynamicVector<TDynamicVector<T>>::operator[];

  // сравнение
  bool operator==(const TDynamicMatrix& v) const noexcept
  {
      if (sz == v.sz) {
          for (int i = 0; i < sz; i++) {
              if (pMem[i] != v.pMem[i]) { return 0; }
          }
          return 1;
      }
      return 0;
  }
  bool operator!=(const TDynamicMatrix& v) const noexcept
  {
      return !(sz == v.sz);
  }

  // матрично-скалярные операции
  TDynamicMatrix operator*(const T& val)
  {
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              pMem[i][j] *= val;
          }
      }
  }

  // матрично-векторные операции
  TDynamicVector<T> operator*(const TDynamicVector<T>& v)
  {
      TDynamicVector<T> x(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              x.pMem[i] += pMem[i][j] * v.pMem[j];
          }
      }
      return x;
  }

  // матрично-матричные операции
  TDynamicMatrix operator+(const TDynamicMatrix& m)
  {
      if (sz != m.sz)throw out_of_range("Matrix_with_not_equal_size");
      TDynamicMatrix x(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              x.pMem[i][j] = pMem[i][j] + m.pMem[i][j];
          }
      }
      return x;
  }
  TDynamicMatrix operator-(const TDynamicMatrix& m)
  {
      if (sz != m.sz)throw out_of_range("Matrix_with_not_equal_size");
      TDynamicMatrix x(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              x.pMem[i][j] = pMem[i][j] - m.pMem[i][j];
          }
      }
      return x;
  }
  TDynamicMatrix operator*(const TDynamicMatrix& m)
  {
      if (sz != m.sz)throw out_of_range("Matrix_with_not_equal_size");
      TDynamicMatrix<T> x(sz);
      for (int i = 0; i < sz; i++) {
          for (int j = 0; j < sz; j++) {
              for (int k = 0; k < sz; k++) {
                  x.pMem[i][j] += pMem[i][k] * m.pMem[k][j];
              }
          }
      }
      return x;
  }

  // ввод/вывод
  friend istream& operator>>(istream& istr, TDynamicMatrix& v)
  {
      istr << v.sz;
      std::istr.ignore();
      for (int i = 0; i < v.sz; i++) {
          for (int j = 0; j < v.sz; j++) {
              istr << v.pMem[i][j];
              std::istr.ignore();
          }
          std::istr.ignore();
      }
      return istr;
  }
  friend ostream& operator<<(ostream& ostr, const TDynamicMatrix& v)
  {
      ostr << v.sz;
      ostr << "\n";
      for (int i = 0; i < v.sz; i++) {
          for (int j = 0; j < v.sz; j++) {
              ostr << v.pMem[i][j] << " ";
          }
          ostr << "\n";
      }
      return ostr;
  }
};

#endif
