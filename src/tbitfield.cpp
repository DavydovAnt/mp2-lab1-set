// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	BitLen = len;
	MemLen = ((len / 32) + 1);
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) {
		pMem[i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen - 1; i++) {
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return(n / 32);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return pow(2, (n % 32));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int num;
	num = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	pMem[num] = pMem[num] | mask;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] &= ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	int num = GetMemIndex(n);
	TELEM mask = GetMemMask(n);
	return pMem[num] & mask;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int ost = (BitLen % 32) + 1;
	ost = pow(2, (ost));
	if (BitLen != bf.BitLen) return false;
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i])return false;
	}
	if (((pMem[MemLen]) % ost) != ((bf.pMem[MemLen]) % ost)) return false;
	return true;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int ost = (BitLen % 32) + 1;
	ost = pow(2, (ost));
	if (BitLen != bf.BitLen) return true;
	for (int i = 0; i < MemLen; i++) {
		if (pMem[i] != bf.pMem[i])return true;
	}
	if (((pMem[MemLen]) % ost) != ((bf.pMem[MemLen]) % ost)) return true;
	return false;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{

}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int ost;
	int maxBitLen;
	if (BitLen > bf.BitLen) {
		maxBitLen = BitLen;
		ost = (bf.BitLen % 32) + 1;
		ost = pow(2, (ost));
		bf.pMem[MemLen] %= ost;
	}
	else
	{
		maxBitLen = bf.BitLen;
		ost = (BitLen % 32) + 1;
		ost = pow(2, (ost));
		pMem[MemLen] %= ost;
	}
	TBitField temp(maxBitLen);
	for (int i = 0; i < MemLen; i++) {
		temp.pMem[i] = pMem[i] & bf.pMem[i];
	}
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(BitLen);
	for (int i = 0; i < MemLen; i++) {
		res.pMem[i] = ~pMem[i];
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int i;
	for (i = 0; i < bf.BitLen; i++)
	{
		if (bf.GetBit(i) != 0) { ostr << 1; }
		else ostr << 0;
	}
	return ostr;
}

