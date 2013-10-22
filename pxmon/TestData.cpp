/////////////////////////////////////////////////////////////////////////////
//
// TESTDATA.CPP : test data
//
// Copyright (c) 2006-2013, Thomas A. Rieck, All Rights Reserved
//

#include "Common.h"
#include "TestData.h"
#include "Exception.h"

#define PUSH_DATA(i,r)	\
	do { \
		TData data(i, r); \
		m_testData.push_back(data); \
	} while (0);

/////////////////////////////////////////////////////////////////////////////
TData::TData(const string& inst, const string& regs) : instruction(inst)
{
	setRegisters(regs);
}

/////////////////////////////////////////////////////////////////////////////
TData::TData(const TData& tdata)
{
	*this = tdata;
}

/////////////////////////////////////////////////////////////////////////////
TData& TData::operator = (const TData& rhs)
{
	if (this != &rhs) {
		instruction = rhs.instruction;
		memcpy(registers, rhs.registers, sizeof(word) * CPU::NREGS);
	}

	return *this;
}

/////////////////////////////////////////////////////////////////////////////
void TData::setRegisters(const string& sregs)
{
	word* pregs = registers;
	const char* psregs = sregs.c_str();

	if (sregs.length() != 4 * CPU::NREGS)
		throw Exception("bad test data: \"%s\".", sregs.c_str());

	string sreg;
	for (int i = 0; i < CPU::NREGS; ++i, ++pregs, psregs += 4) {
		sreg = string(psregs, 4);
		if (1 != sscanf(sreg.c_str(), "%hx", pregs))
			throw Exception("bad test data: \"%s\".", sregs.c_str());		
	}
}

/////////////////////////////////////////////////////////////////////////////
TestData::TestData()
{
	// register string format is :
	// AAAABBBBCCCCDDDDXXXXSSSSIIIIFFFF

	PUSH_DATA("mov al, $01\n", "00010000000000000000000000030000");
	PUSH_DATA("mov bl, $01\n", "00010001000000000000000000030000");
	PUSH_DATA("mov cl, $01\n", "00010001000100000000000000030000");
	PUSH_DATA("mov dl, $01\n", "00010001000100010000000000030000");
	
	/*
	PUSH_DATA("adc al, al\n", "00020000000000000000000000020000");
	PUSH_DATA("adc ah, ah\n", "00020000000000000000000000020002");
	PUSH_DATA("adc bl, bl\n", "00020000000000000000000000020002");
	PUSH_DATA("adc bh, bh\n", "00020000000000000000000000020002");
	PUSH_DATA("adc cl, cl\n", "00020000000000000000000000020002");
	PUSH_DATA("adc ch, ch\n", "00020000000000000000000000020002");
	PUSH_DATA("adc dl, dl\n", "00020000000000000000000000020002");
	PUSH_DATA("adc dh, dh\n", "00020000000000000000000000020002");
	*/

	reset();
}

/////////////////////////////////////////////////////////////////////////////
TestData::~TestData()
{
}

/////////////////////////////////////////////////////////////////////////////
TestData* TestData::create()
{
	return new TestData();
}

/////////////////////////////////////////////////////////////////////////////
const TData* TestData::next()
{
	if (m_it == m_testData.end())
		return NULL;

	return &*m_it++;
}

/////////////////////////////////////////////////////////////////////////////
bool TestData::hasMore() const
{
	return m_it != m_testData.end();
}

/////////////////////////////////////////////////////////////////////////////
void TestData::reset()
{
	m_it = m_testData.begin();
}


