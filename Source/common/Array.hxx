/*
Copyright (c) 2024 Eugene Kirian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include "Base.hxx"

#define DEFAULT_ARRAY_CAPACITY_VALUE 16
#define DEFAULT_ARRAY_CAPACITY_MULTIPLIER 2

template<typename T>
class Array
{
public:
    Array();
    Array(INT capacity);
    virtual ~Array();

    BOOL Add(CONST T& item);
    BOOL Remove(INT index);
    VOID Clear(VOID);

    CONST INT Count(VOID);

    T& operator[](INT index);

protected:
	VOID Initialize(INT capacity);

    struct
    {
        INT Count;
        INT Capacity;
        T* Items;
        CRITICAL_SECTION Mutex;
    } State;
};

template<typename T>
inline Array<T>::Array()
{
	this->Initialize(DEFAULT_ARRAY_CAPACITY_VALUE);
}

template<typename T>
inline Array<T>::Array(INT capacity)
{
	this->Initialize(capacity > 0 ? capacity : DEFAULT_ARRAY_CAPACITY_VALUE);
}

template<typename T>
inline Array<T>::~Array()
{
    free(this->State.Items);

    DeleteCriticalSection(&this->State.Mutex);
}

template<typename T>
BOOL Array<T>::Add(CONST T& item)
{
    BOOL result = FALSE;

    EnterCriticalSection(&this->State.Mutex);

    if ((this->State.Count + 1) < this->State.Capacity)
    {
        this->State.Items[this->State.Count++] = item;

        result = TRUE;
    }
    else
    {
        CONST INT capacity = this->State.Capacity * DEFAULT_ARRAY_CAPACITY_MULTIPLIER;

        T* ptr = (T*)realloc(this->State.Items, capacity * sizeof(T));

        if (ptr != NULL)
        {
            this->State.Items = ptr;
            this->State.Capacity = capacity;

            ZeroMemory(&this->State.Items[this->State.Count], (this->State.Capacity - this->State.Count) * sizeof(T));

            this->State.Items[this->State.Count++] = item;

            result = TRUE;
        }
    }

    LeaveCriticalSection(&this->State.Mutex);

    return result;
}

template<typename T>
BOOL Array<T>::Remove(INT index)
{
    if (index < 0 || index >= this->State.Count || this->State.Count == 0) { return FALSE; }

    EnterCriticalSection(&this->State.Mutex);

    for (INT x = index; x < (this->State.Count - 1); x++)
    {
        this->State.Items[x] = this->State.Items[x + 1];
    }

    this->State.Count--;

    ZeroMemory(&this->State.Items[this->State.Count], sizeof(T));

    LeaveCriticalSection(&this->State.Mutex);

    return TRUE;
}

template<typename T>
VOID Array<T>::Clear(VOID)
{
    if (this->State.Count == 0) { return; }

    EnterCriticalSection(&this->State.Mutex);

    ZeroMemory(this->State.Items, this->State.Count * sizeof(T));

    this->State.Count = 0;

    LeaveCriticalSection(&this->State.Mutex);
}

template<typename T>
inline CONST INT Array<T>::Count(VOID)
{
    return this->State.Count;
}

template<typename T>
inline T& Array<T>::operator[](INT index)
{
    return this->State.Items[index];
}

template<typename T>
inline VOID Array<T>::Initialize(INT capacity)
{
    this->State.Count = 0;
    this->State.Capacity = capacity;

    CONST UINT size = capacity * sizeof(T);

    this->State.Items = (T*)malloc(size);
    ZeroMemory(this->State.Items, size);

    ZeroMemory(&this->State.Mutex, sizeof(CRITICAL_SECTION));
    InitializeCriticalSection(&this->State.Mutex);
}