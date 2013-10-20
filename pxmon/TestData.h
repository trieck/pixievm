/////////////////////////////////////////////////////////////////////////////
//
// TESTDATA.H : test data
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "CPU.H"

#ifndef __TESTDATA_H__
#define __TESTDATA_H__

/////////////////////////////////////////////////////////////////////////////
struct TData {
	TData(const string& inst, const string& regs);
	TData(const TData& tdata);
	TData& operator = (const TData& rhs);
	void setRegisters(const string& regs);
	string instruction;					// instruction for assembly
	word registers[CPU::NREGS];	// register state after execution
};

/////////////////////////////////////////////////////////////////////////////
class TestData {
// Construction / Destruction
private:
	TestData();
public:
	~TestData();

// Interface
	const TData* next();
	void reset();
	bool hasMore() const;
	static TestData *create();
	
// Implementation
private:
	typedef vector<TData> TDataVec;
	TDataVec m_testData;
	TDataVec::const_iterator m_it;
};
/////////////////////////////////////////////////////////////////////////////

#endif // __TESTDATA_H__
