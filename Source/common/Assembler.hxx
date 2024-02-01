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

#include "Array.hxx"

class Assembler;
typedef Assembler* LPASSEMBLER;

class AssemblerState;
typedef AssemblerState* LPASSEMBLERSTATE;

class AssemblerDelegate;
typedef AssemblerDelegate* LPASSEMBLERDELEGATE;

class AssemblerDelegateState;
typedef AssemblerDelegateState* LPASSEMBLERDELEGATESTATE;

struct AssemblerItem
{
    LPVOID Agent;
    LPASSEMBLERDELEGATE Delegate;
    LPVOID Value;
};

class AssemblerState
{
public:
	AssemblerState();
	virtual ~AssemblerState();

    Array<AssemblerItem> Items;

    CRITICAL_SECTION Mutex;
};

class Assembler
{
public:
    Assembler();
    virtual ~Assembler();

    BOOL Agent(LPVOID value, REFIID riid, LPVOID* agent);
    LPVOID Agent(LPVOID value, REFIID riid);

    BOOL Initialize(LPVOID agent, LPASSEMBLERDELEGATE delegate, LPVOID value);

    BOOL IsAgent(LPVOID agent, REFIID riid);
    BOOL IsValue(LPVOID value, REFIID riid);

    BOOL RemoveAgent(LPVOID agent, REFIID riid);
    BOOL RemoveDelegate(LPASSEMBLERDELEGATE delegate);
    BOOL RemoveValue(LPVOID value, REFIID riid);

    BOOL Value(LPVOID agent, REFIID riid, LPVOID* value);
    LPVOID Value(LPVOID agent, REFIID riid);

protected:
    LPASSEMBLERSTATE State;
};

struct AssemblerDelegateItem
{
    LPVOID Agent;
    IID IID;
    LPVOID Value;
};

class AssemblerDelegateState
{
public:
	AssemblerDelegateState();
	virtual ~AssemblerDelegateState();

	LPASSEMBLER Assembler;

    Array<AssemblerDelegateItem> Items;

    CRITICAL_SECTION Mutex;
};

class AssemblerDelegate
{
public:
    AssemblerDelegate(LPASSEMBLER assembler);
    virtual ~AssemblerDelegate();

    BOOL Agent(LPVOID value, REFIID riid, LPVOID* agent);
    LPVOID Agent(LPVOID value, REFIID riid);

    BOOL Initialize(LPVOID value, REFIID riid, LPVOID agent);

    BOOL IsAgent(LPVOID agent, REFIID riid);
    BOOL IsValue(LPVOID value, REFIID riid);

    BOOL Remove(LPVOID agent, REFIID riid, LPVOID value);
    BOOL RemoveAgent(LPVOID agent, REFIID riid);
    BOOL RemoveValue(LPVOID value, REFIID riid);

    BOOL Value(LPVOID agent, REFIID riid, LPVOID* value);
    LPVOID Value(LPVOID agent, REFIID riid);

protected:
    LPASSEMBLERDELEGATESTATE State;
};

template<typename T, typename TT>
inline TT Assemble(LPASSEMBLER assembler, LPASSEMBLERDELEGATE delegate, REFIID riid, TT value)
{
    return delegate->IsAgent(value, riid) ? (TT)delegate->Agent(value, riid) : (new T(assembler, delegate, riid, (TT)value));
}

#define AssembleAgent(T, A, D, V)((I##T*)(Assemble<T, I##T*>(A, D, IID_I##T, (I##T*)V)))

#define AcquireAgent(ID, V)(this->State.Delegate->Agent(*V, ID, V))
#define ActivateAgent(T, V) AssembleAgent(T, this->State.Assembler, this->State.Delegate, V);
#define ActivateAgentDelegate(T, V) AssembleAgent(T, this->State.Assembler, (new AssemblerDelegate(this->State.Assembler)), V);

#define AccessAgentValue(T, V)((I##T*)this->State.Assembler->Value(V, IID_I##T))
#define AttemptAccessAgentValue(T, V) if (this->State.Assembler->IsAgent(V, IID_I##T)) { V = AccessAgentValue(T, V); }

#define AgentConstructorParameters(T)   \
    LPASSEMBLER assembler, LPASSEMBLERDELEGATE delegate, REFIID riid, I##T* value

#define AgentStateStruct(T)             \
    struct                              \
    {                                   \
        IID ID;                         \
        LPASSEMBLER Assembler;          \
        LPASSEMBLERDELEGATE Delegate;   \
        I##T* Self;                     \
    } State;

#define AgentConstructor()                                                      \
    this->State.Assembler = assembler;                                          \
    this->State.ID = riid;                                                      \
    this->State.Delegate = delegate;                                            \
    this->State.Self = value;                                                   \
                                                                                \
    this->State.Assembler->Initialize(this, this->State.Delegate, value);       \
    this->State.Delegate->Initialize(value, riid, this);

#define AgentDestructor()                                                               \
    this->State.Delegate->Remove(this->State.Self, this->State.ID, this->State.Self);   \
    this->State.Assembler->RemoveAgent(this, this->State.ID);