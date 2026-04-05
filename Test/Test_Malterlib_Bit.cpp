// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include <Mib/Container/BitArray>
#include <Mib/Container/BitArrayHierarchical>
#include <Mib/Container/BitArrayPowerTwo>
#include <Mib/Test/Performance>
#include <Mib/Time/PerfTimeMeasure>

// gc_HighestBitSet: 0-indexed highest bit position, returns -1 for zero
static_assert(NMib::gc_HighestBitSet<0> == -1);
static_assert(NMib::gc_HighestBitSet<1> == 0);
static_assert(NMib::gc_HighestBitSet<2> == 1);
static_assert(NMib::gc_HighestBitSet<3> == 1);
static_assert(NMib::gc_HighestBitSet<4> == 2);
static_assert(NMib::gc_HighestBitSet<7> == 2);
static_assert(NMib::gc_HighestBitSet<8> == 3);
static_assert(NMib::gc_HighestBitSet<16> == 4);
static_assert(NMib::gc_HighestBitSet<255> == 7);
static_assert(NMib::gc_HighestBitSet<256> == 8);
static_assert(NMib::gc_HighestBitSet<0x08000000> == 27);

// cIsPowerOfTwo concept
static_assert(!NMib::cIsPowerOfTwo<0>);
static_assert(NMib::cIsPowerOfTwo<1>);
static_assert(NMib::cIsPowerOfTwo<2>);
static_assert(!NMib::cIsPowerOfTwo<3>);
static_assert(NMib::cIsPowerOfTwo<4>);
static_assert(!NMib::cIsPowerOfTwo<5>);
static_assert(!NMib::cIsPowerOfTwo<6>);
static_assert(!NMib::cIsPowerOfTwo<7>);
static_assert(NMib::cIsPowerOfTwo<8>);
static_assert(!NMib::cIsPowerOfTwo<9>);
static_assert(NMib::cIsPowerOfTwo<16>);
static_assert(NMib::cIsPowerOfTwo<64>);
static_assert(NMib::cIsPowerOfTwo<256>);
static_assert(NMib::cIsPowerOfTwo<1024>);
static_assert(!NMib::cIsPowerOfTwo<15>);
static_assert(!NMib::cIsPowerOfTwo<17>);

// fg_MinPowerOfTwo: smallest non-negative integer such that 2^result >= value (for powers of two)
// For non-powers-of-two it returns floor(log2(value))
static_assert(NMib::fg_MinPowerOfTwo(0) == 0);
static_assert(NMib::fg_MinPowerOfTwo(1) == 0);
static_assert(NMib::fg_MinPowerOfTwo(2) == 1);
static_assert(NMib::fg_MinPowerOfTwo(3) == 1);
static_assert(NMib::fg_MinPowerOfTwo(4) == 2);
static_assert(NMib::fg_MinPowerOfTwo(5) == 2);
static_assert(NMib::fg_MinPowerOfTwo(7) == 2);
static_assert(NMib::fg_MinPowerOfTwo(8) == 3);
static_assert(NMib::fg_MinPowerOfTwo(15) == 3);
static_assert(NMib::fg_MinPowerOfTwo(16) == 4);
static_assert(NMib::fg_MinPowerOfTwo(31) == 4);
static_assert(NMib::fg_MinPowerOfTwo(32) == 5);
static_assert(NMib::fg_MinPowerOfTwo(63) == 5);
static_assert(NMib::fg_MinPowerOfTwo(64) == 6);
static_assert(NMib::fg_MinPowerOfTwo(127) == 6);
static_assert(NMib::fg_MinPowerOfTwo(128) == 7);
static_assert(NMib::fg_MinPowerOfTwo(255) == 7);
static_assert(NMib::fg_MinPowerOfTwo(256) == 8);
static_assert(NMib::fg_MinPowerOfTwo(1024) == 10);
static_assert(NMib::fg_MinPowerOfTwo(65536) == 16);

// fg_IsPowerOfTwo
static_assert(NMib::fg_IsPowerOfTwo(1));
static_assert(NMib::fg_IsPowerOfTwo(2));
static_assert(!NMib::fg_IsPowerOfTwo(3));
static_assert(NMib::fg_IsPowerOfTwo(4));
static_assert(!NMib::fg_IsPowerOfTwo(5));
static_assert(NMib::fg_IsPowerOfTwo(8));
static_assert(!NMib::fg_IsPowerOfTwo(0));
static_assert(!NMib::fg_IsPowerOfTwo(-1));
static_assert(NMib::fg_IsPowerOfTwo(1024));
static_assert(!NMib::fg_IsPowerOfTwo(1023));

// fg_RoundPowerOfTwoUp
static_assert(NMib::fg_RoundPowerOfTwoUp(1) == 1);
static_assert(NMib::fg_RoundPowerOfTwoUp(2) == 2);
static_assert(NMib::fg_RoundPowerOfTwoUp(3) == 4);
static_assert(NMib::fg_RoundPowerOfTwoUp(4) == 4);
static_assert(NMib::fg_RoundPowerOfTwoUp(5) == 8);
static_assert(NMib::fg_RoundPowerOfTwoUp(7) == 8);
static_assert(NMib::fg_RoundPowerOfTwoUp(8) == 8);
static_assert(NMib::fg_RoundPowerOfTwoUp(9) == 16);
static_assert(NMib::fg_RoundPowerOfTwoUp(15) == 16);
static_assert(NMib::fg_RoundPowerOfTwoUp(16) == 16);
static_assert(NMib::fg_RoundPowerOfTwoUp(17) == 32);
static_assert(NMib::fg_RoundPowerOfTwoUp(127) == 128);
static_assert(NMib::fg_RoundPowerOfTwoUp(128) == 128);
static_assert(NMib::fg_RoundPowerOfTwoUp(129) == 256);
static_assert(NMib::fg_RoundPowerOfTwoUp(255) == 256);
static_assert(NMib::fg_RoundPowerOfTwoUp(256) == 256);
static_assert(NMib::fg_RoundPowerOfTwoUp(1000) == 1024);
static_assert(NMib::fg_RoundPowerOfTwoUp(1024) == 1024);

// fg_RoundPowerOfTwoDown
static_assert(NMib::fg_RoundPowerOfTwoDown(1) == 1);
static_assert(NMib::fg_RoundPowerOfTwoDown(2) == 2);
static_assert(NMib::fg_RoundPowerOfTwoDown(3) == 2);
static_assert(NMib::fg_RoundPowerOfTwoDown(4) == 4);
static_assert(NMib::fg_RoundPowerOfTwoDown(5) == 4);
static_assert(NMib::fg_RoundPowerOfTwoDown(7) == 4);
static_assert(NMib::fg_RoundPowerOfTwoDown(8) == 8);
static_assert(NMib::fg_RoundPowerOfTwoDown(9) == 8);
static_assert(NMib::fg_RoundPowerOfTwoDown(15) == 8);
static_assert(NMib::fg_RoundPowerOfTwoDown(16) == 16);
static_assert(NMib::fg_RoundPowerOfTwoDown(17) == 16);
static_assert(NMib::fg_RoundPowerOfTwoDown(127) == 64);
static_assert(NMib::fg_RoundPowerOfTwoDown(128) == 128);
static_assert(NMib::fg_RoundPowerOfTwoDown(129) == 128);
static_assert(NMib::fg_RoundPowerOfTwoDown(255) == 128);
static_assert(NMib::fg_RoundPowerOfTwoDown(256) == 256);
static_assert(NMib::fg_RoundPowerOfTwoDown(1000) == 512);
static_assert(NMib::fg_RoundPowerOfTwoDown(1024) == 1024);

static_assert(NMib::gc_LowestBitSet<3> == 0);
static_assert(NMib::gc_LowestBitSet<2> == 1);
static_assert(NMib::gc_LowestBitSet<1 << 5> == 5);
static_assert(NMib::gc_LowestBitSet<1 << 10> == 10);
static_assert(NMib::gc_LowestBitSet<1 << 15> == 15);
static_assert(NMib::gc_LowestBitSet<1 << 20> == 20);
static_assert(NMib::gc_LowestBitSet<1 << 25> == 25);
static_assert(NMib::gc_LowestBitSet<1 << 30> == 30);
static_assert(NMib::gc_LowestBitSet<1u << 31> == 31);

#if DMibPBits_mint > 32
static_assert(NMib::gc_LowestBitSet<umint(1) << 35> == 35);
static_assert(NMib::gc_LowestBitSet<umint(1) << 40> == 40);
static_assert(NMib::gc_LowestBitSet<umint(1) << 45> == 45);
static_assert(NMib::gc_LowestBitSet<umint(1) << 50> == 50);
static_assert(NMib::gc_LowestBitSet<umint(1) << 55> == 55);
static_assert(NMib::gc_LowestBitSet<umint(1) << 60> == 60);
static_assert(NMib::gc_LowestBitSet<umint(1) << 63> == 63);
#endif

namespace NMib
{

}


namespace
{

	template <typename t_CFunctor>
	static inline_never void fs_CallFunctor(t_CFunctor _Functor)
	{
		_Functor();
	}

	template <typename t_CInteger>
	static void fs_TestMinPowerOfTwo(const ch8 *_pName)
	{
		DMibTestPath(_pName);

		// fg_MinPowerOfTwo(0) == 0
		DMibTest(DMibExpr(NMib::fg_MinPowerOfTwo(t_CInteger(0))) == DMibExpr(t_CInteger(0)));

		// fg_MinPowerOfTwo(1) == 0 (2^0 = 1 >= 1)
		DMibTest(DMibExpr(NMib::fg_MinPowerOfTwo(t_CInteger(1))) == DMibExpr(t_CInteger(0)));

		// Test all powers of two within the type's range
		for (t_CInteger i = 1; i < t_CInteger(sizeof(t_CInteger) * 8 - 1); ++i)
		{
			t_CInteger PowerOfTwo = t_CInteger(1) << i;
			DMibTest(DMibExpr(NMib::fg_MinPowerOfTwo(PowerOfTwo)) == DMibExpr(i)) (ETestFlag_Aggregated);
		}

		// Test power-of-two + 1 (should return same as the power)
		for (t_CInteger i = 2; i < t_CInteger(sizeof(t_CInteger) * 8 - 1); ++i)
		{
			t_CInteger PowerOfTwoPlusOne = (t_CInteger(1) << i) + t_CInteger(1);
			DMibTest(DMibExpr(NMib::fg_MinPowerOfTwo(PowerOfTwoPlusOne)) == DMibExpr(i)) (ETestFlag_Aggregated);
		}

		// Test power-of-two - 1 (should return one less than the power)
		for (t_CInteger i = 2; i < t_CInteger(sizeof(t_CInteger) * 8 - 1); ++i)
		{
			t_CInteger PowerOfTwoMinusOne = (t_CInteger(1) << i) - t_CInteger(1);
			DMibTest(DMibExpr(NMib::fg_MinPowerOfTwo(PowerOfTwoMinusOne)) == DMibExpr(i - t_CInteger(1))) (ETestFlag_Aggregated);
		}
	}

	template <typename t_CInteger>
	static void fs_TestHighestBitSet(const ch8 *_pName)
	{
		DMibTestPath(_pName);

		NMib::NTime::CPrefCyclesTimeMeasureMin MalterlibTime;
		const umint nLoops = 10000;

#ifndef DMibClangAnalyzerWorkaround
		t_CInteger Number = NMib::NStr::CStr(NMib::NStr::CStr::CFormat("{}") << 0x50).f_ToInt();
#else
		t_CInteger Number = 0x50;
#endif
		uint32 Result = 0;
		auto Lambda = [&] ()
		{
			uint32 Temp = Result;
			MalterlibTime.f_Start();
			for (umint i = 0; i < nLoops; ++i)
			{
				NMib::NAtomic::fg_MemoryFence(NMib::NAtomic::gc_MemoryOrder_Acquire);
				Temp += NMib::fg_GetHighestBitSet(Number);
			}
			MalterlibTime.f_Stop();
			Result = Temp;
		};
		for (umint i = 0; i < 100; ++i)
			fs_CallFunctor(Lambda);
		MalterlibTime /= nLoops;
		umint ExpectedCycles = 10*sizeof(t_CInteger);
		DMibTest(DMibExpr(Result) == DMibExpr(6*100*nLoops)) (ETestFlag_NoValues);
		if (NMib::NTest::fg_GroupActive("Performance"))
			DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
	}

	template <typename t_CInteger>
	static void fs_TestHighestBitSetNoZero(const ch8 *_pName)
	{
		DMibTestPath(_pName);
		NMib::NTime::CPrefCyclesTimeMeasureMin MalterlibTime;
		const umint nLoops = 10000;
		t_CInteger Number = NMib::NStr::CStr(NMib::NStr::CStr::CFormat("{}") << 0x50).f_ToInt();
		uint32 Result = 0;
		auto Lambda = [&] ()
		{
			uint32 Temp = Result;
			MalterlibTime.f_Start();
			for (umint i = 0; i < nLoops; ++i)
			{
				NMib::NAtomic::fg_MemoryFence(NMib::NAtomic::gc_MemoryOrder_Acquire);
				Temp += NMib::fg_GetHighestBitSetNoZero(Number);
			}
			MalterlibTime.f_Stop();
			Result = Temp;
		};
		for (umint i = 0; i < 100; ++i)
			fs_CallFunctor(Lambda);
		MalterlibTime /= nLoops;
		umint ExpectedCycles = 10*sizeof(t_CInteger);
		DMibTest(DMibExpr(Result) == DMibExpr(6*100*nLoops)) (ETestFlag_NoValues);
		if (NMib::NTest::fg_GroupActive("Performance"))
			DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
	}

	template <typename t_CInteger>
	static void fs_TestLowestBitSet(const ch8 *_pName)
	{
		DMibTestPath(_pName);
		NMib::NTime::CPrefCyclesTimeMeasureMin MalterlibTime;
		const umint nLoops = 10000;
		enum
		{
			ENumBits = sizeof(t_CInteger) * 8
		};
		t_CInteger Number = t_CInteger(NMib::NStr::CStr(NMib::NStr::CStr::CFormat("{}") << 0x55).f_ToInt()) << (ENumBits - 8);
		uint32 Result = 0;
		auto Lambda = [&] ()
		{
			uint32 Temp = Result;
			MalterlibTime.f_Start();
			for (umint i = 0; i < nLoops; ++i)
			{
				NMib::NAtomic::fg_MemoryFence(NMib::NAtomic::gc_MemoryOrder_Acquire);
				Temp += NMib::fg_GetLowestBitSet(Number);
			}
			MalterlibTime.f_Stop();
			Result = Temp;
		};
		for (umint i = 0; i < 100; ++i)
			fs_CallFunctor(Lambda);
		MalterlibTime /= nLoops;
		umint ExpectedCycles = 10*sizeof(t_CInteger);
		DMibTest(DMibExpr(Result) == DMibExpr((ENumBits-8)*100*nLoops)) (ETestFlag_NoValues);
		if (NMib::NTest::fg_GroupActive("Performance"))
			DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
	}



	template <typename t_CInteger>
	static void fs_TestLowestBitSetNoZero(const ch8 *_pName)
	{
		DMibTestPath(_pName);
		NMib::NTime::CPrefCyclesTimeMeasureMin MalterlibTime;
		const umint nLoops = 10000;
		enum
		{
			ENumBits = sizeof(t_CInteger) * 8
		};
		t_CInteger Number = t_CInteger(NMib::NStr::CStr(NMib::NStr::CStr::CFormat("{}") << 0x55).f_ToInt()) << (ENumBits - 8);
		uint32 Result = 0;
		auto Lambda = [&] ()
		{
			uint32 Temp = Result;
			MalterlibTime.f_Start();
			for (umint i = 0; i < nLoops; ++i)
			{
				NMib::NAtomic::fg_MemoryFence(NMib::NAtomic::gc_MemoryOrder_Acquire);
				Temp += NMib::fg_GetLowestBitSetNoZero(Number);
			}
			MalterlibTime.f_Stop();
			Result = Temp;
		};
		for (umint i = 0; i < 100; ++i)
			fs_CallFunctor(Lambda);
		MalterlibTime /= nLoops;
		umint ExpectedCycles = 10*sizeof(t_CInteger);
		DMibTest(DMibExpr(Result) == DMibExpr((ENumBits-8)*100*nLoops)) (ETestFlag_NoValues);
		if (NMib::NTest::fg_GroupActive("Performance"))
			DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
	}




	template <typename t_CInteger>
	static void fs_TestNumBitsSet(const ch8 *_pName)
	{
		DMibTestPath(_pName);
		NMib::NTime::CPrefCyclesTimeMeasureMin MalterlibTime;
		const umint nLoops = 10000;
		t_CInteger Number = 0;
		umint nBytes = sizeof(Number);
		for (umint i = 0; i < nBytes; ++i)
		{
			Number |= t_CInteger(NMib::NStr::CStr(NMib::NStr::CStr::CFormat("{}") << 0x55).f_ToInt()) << (i * 8);
		}
		uint32 Result = 0;
		auto Lambda = [&] ()
		{
			uint32 Temp = Result;
			MalterlibTime.f_Start();
			for (umint i = 0; i < nLoops; ++i)
			{
				NMib::NAtomic::fg_MemoryFence(NMib::NAtomic::gc_MemoryOrder_Acquire);
				Temp += NMib::fg_NumBitsSet(Number);
			}
			MalterlibTime.f_Stop();
			Result = Temp;
		};
		for (umint i = 0; i < 100; ++i)
			fs_CallFunctor(Lambda);
		MalterlibTime /= nLoops;
		umint ExpectedCycles = 10*sizeof(t_CInteger);
		DMibTest(DMibExpr(Result) == DMibExpr(4*nBytes*100*nLoops)) (ETestFlag_NoValues);
		if (NMib::NTest::fg_GroupActive("Performance"))
			DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
	}

	template <template <umint t_nBits> class t_TCBitArray>
	struct TCTestBitArray
	{
		static void fs_DoTests()
		{
			const aint nBitsAligned = sizeof(umint) * sizeof(umint) * 8 * 8;
			const aint nBitsUnaligned = sizeof(umint) * sizeof(umint) * 8 * 8 - 1;
			using CBitArrayAligned = typename t_TCBitArray<nBitsAligned>::CType;
			using CBitArrayUnaligned = typename t_TCBitArray<nBitsUnaligned>::CType;
			{
				DMibTestPath("FindFreeBitAndSet");
				using CBitArrayAligned = CBitArrayAligned;
				using CBitArrayUnaligned = CBitArrayUnaligned;
				{
					DMibTestPath("Aligned");
					NMib::NTest::CTestPerformance Pref(1.0);

					{
						NMib::NTest::CTestPerformanceMeasure MalterlibMeasure("Malterlib");
						const umint nBits = nBitsAligned;
						CBitArrayAligned TestBits;
						for (aint i = 0; i < 10; ++i)
						{
							TestBits.f_Clear();
							MalterlibMeasure.f_Start();
							for (umint i = 0; i < nBits-1; ++i)
								TestBits.f_FindFreeBitAndSet();
							MalterlibMeasure.f_Stop(nBits-1);
							DMibTest(DMibExpr(TestBits.f_FindFreeBitAndSet()) == DMibExpr(nBits - 1)) (ETestFlag_Aggregated);
							DMibTest(DMibExpr(TestBits.f_FindFreeBitAndSet()) < DMibExpr(0)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(333, false);
							TestBits.f_SetBit(555, false);
							DMibTest(DMibExpr(TestBits.f_FindFreeBitAndSet()) == DMibExpr(333)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(555, true);
							DMibTest(DMibExpr(TestBits.f_FindFreeBitAndSet()) < DMibExpr(0) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							TestBits.template f_SetBit<false>(555);
							DMibTest(DMibExpr(TestBits.f_FindFreeBitAndSet()) == DMibExpr(555) && DMibExpr("Static set")) (ETestFlag_Aggregated);

							MalterlibMeasure.f_NewRepetition();
						}
						Pref.f_Add(MalterlibMeasure);
					}

					DMibTest(DMibExpr(Pref));
				}
				{
					DMibTestPath("Unaligned");
					NMib::NTime::CPrefCyclesTimeMeasureMin MalterlibTime;
					const umint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = 0; i < 10; ++i)
					{
						TestBits.f_Clear();
						MalterlibTime.f_Start();
						for (umint i = 0; i < nBits-1; ++i)
							TestBits.f_FindFreeBitAndSet();
						MalterlibTime.f_Stop();
						DMibTest(DMibExpr(TestBits.f_FindFreeBitAndSet()) == DMibExpr(nBits - 1)) (ETestFlag_Aggregated);
						DMibTest(DMibExpr(TestBits.f_FindFreeBitAndSet()) < DMibExpr(0)) (ETestFlag_Aggregated);
						TestBits.f_SetBit(333, false);
						TestBits.f_SetBit(555, false);
						DMibTest(DMibExpr(TestBits.f_FindFreeBitAndSet()) == DMibExpr(333)) (ETestFlag_Aggregated);
						TestBits.f_SetBit(555, true);
						DMibTest(DMibExpr(TestBits.f_FindFreeBitAndSet()) < DMibExpr(0) && DMibExpr("Static set")) (ETestFlag_Aggregated);
						TestBits.template f_SetBit<false>(555);
						DMibTest(DMibExpr(TestBits.f_FindFreeBitAndSet()) == DMibExpr(555) && DMibExpr("Static set")) (ETestFlag_Aggregated);
					}
					MalterlibTime /= nBits - 1;
					umint ExpectedCycles = (nBits*10)/(sizeof(void *)*2);
					if (NMib::NTest::fg_GroupActive("Performance"))
						DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
				};
			}
			{
				DMibTestPath("FindFreeBitReverseAndSet");
				using CBitArrayAligned = CBitArrayAligned;
				using CBitArrayUnaligned = CBitArrayUnaligned;
				{
					DMibTestPath("Aligned");
					NMib::NTest::CTestPerformance Pref(1.0);

					{
						NMib::NTest::CTestPerformanceMeasure MalterlibMeasure("Malterlib");
						const umint nBits = nBitsAligned;
						CBitArrayAligned TestBits;
						for (aint i = 0; i < 10; ++i)
						{
							TestBits.f_Clear();
							MalterlibMeasure.f_Start();
							for (umint i = 0; i < nBits-1; ++i)
								TestBits.f_FindFreeBitReverseAndSet();
							MalterlibMeasure.f_Stop(nBits-1);
							DMibTest(DMibExpr(TestBits.f_FindFreeBitReverseAndSet()) == DMibExpr(0)) (ETestFlag_Aggregated);
							DMibTest(DMibExpr(TestBits.f_FindFreeBitReverseAndSet()) < DMibExpr(0)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(555, false);
							TestBits.f_SetBit(333, false);
							DMibTest(DMibExpr(TestBits.f_FindFreeBitReverseAndSet()) == DMibExpr(555)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(333, true);
							DMibTest(DMibExpr(TestBits.f_FindFreeBitReverseAndSet()) < DMibExpr(0) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							TestBits.template f_SetBit<false>(555);
							DMibTest(DMibExpr(TestBits.f_FindFreeBitReverseAndSet()) == DMibExpr(555) && DMibExpr("Static set")) (ETestFlag_Aggregated);

							MalterlibMeasure.f_NewRepetition();
						}
						Pref.f_Add(MalterlibMeasure);
					}

					DMibTest(DMibExpr(Pref));
				}
				{
					DMibTestPath("Unaligned");
					NMib::NTime::CPrefCyclesTimeMeasureMin MalterlibTime;
					const umint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = 0; i < 10; ++i)
					{
						TestBits.f_Clear();
						MalterlibTime.f_Start();
						for (umint i = 0; i < nBits-1; ++i)
							TestBits.f_FindFreeBitReverseAndSet();
						MalterlibTime.f_Stop();
						DMibTest(DMibExpr(TestBits.f_FindFreeBitReverseAndSet()) == DMibExpr(0)) (ETestFlag_Aggregated);
						DMibTest(DMibExpr(TestBits.f_FindFreeBitReverseAndSet()) < DMibExpr(0)) (ETestFlag_Aggregated);
						TestBits.f_SetBit(333, false);
						TestBits.f_SetBit(555, false);
						DMibTest(DMibExpr(TestBits.f_FindFreeBitReverseAndSet()) == DMibExpr(555)) (ETestFlag_Aggregated);
						TestBits.f_SetBit(333, true);
						DMibTest(DMibExpr(TestBits.f_FindFreeBitReverseAndSet()) < DMibExpr(0) && DMibExpr("Static set")) (ETestFlag_Aggregated);
						TestBits.template f_SetBit<false>(555);
						DMibTest(DMibExpr(TestBits.f_FindFreeBitReverseAndSet()) == DMibExpr(555) && DMibExpr("Static set")) (ETestFlag_Aggregated);
					}
					MalterlibTime /= nBits - 1;
					umint ExpectedCycles = (nBits*10)/(sizeof(void *)*2);
					if (NMib::NTest::fg_GroupActive("Performance"))
						DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
				}
			}
			{
				DMibTestPath("FindUpperBound");
				using CBitArrayAligned = CBitArrayAligned;
				using CBitArrayUnaligned = CBitArrayUnaligned;
				{
					DMibTestPath("Aligned");
					const aint nBits = nBitsAligned;
					CBitArrayAligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						TestBits.f_SetBit(i, true);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(0)) == DMibExpr(i)) (ETestFlag_Aggregated);
						TestBits.f_SetBit(i, false);

						TestBits.template f_SetBit<true>(i);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(0)) == DMibExpr(i) && DMibExpr("Static set")) (ETestFlag_Aggregated);
						TestBits.template f_SetBit<false>(i);
					}
				}
				{
					DMibTestPath("Unaligned");
					const aint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						TestBits.f_SetBit(i, true);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(0)) == DMibExpr(i)) (ETestFlag_Aggregated);
						TestBits.f_SetBit(i, false);

						TestBits.template f_SetBit<true>(i);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(0)) == DMibExpr(i) && DMibExpr("Static set")) (ETestFlag_Aggregated);
						TestBits.template f_SetBit<false>(i);
					}
				}
			}
			{
				DMibTestPath("FindUpperBoundStart");
				using CBitArrayAligned = CBitArrayAligned;
				using CBitArrayUnaligned = CBitArrayUnaligned;
				{
					DMibTestPath("Aligned");
					const aint nBits = nBitsAligned;
					CBitArrayAligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						umint Start = NMib::fg_Max(0, smint(i)-3);

						TestBits.f_SetBit(i, true);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(Start)) == DMibExpr(i)) (ETestFlag_Aggregated);
						TestBits.f_SetBit(i, false);

						TestBits.template f_SetBit<true>(i);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(Start)) == DMibExpr(i) && DMibExpr("Static set")) (ETestFlag_Aggregated);
						TestBits.template f_SetBit<false>(i);
					}
				}
				{
					DMibTestPath("Unaligned");
					const aint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						umint Start = NMib::fg_Max(0, smint(i)-3);
						TestBits.f_SetBit(i, true);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(Start)) == DMibExpr(i)) (ETestFlag_Aggregated);
						TestBits.f_SetBit(i, false);

						TestBits.template f_SetBit<true>(i);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(Start)) == DMibExpr(i) && DMibExpr("Static set")) (ETestFlag_Aggregated);
						TestBits.template f_SetBit<false>(i);
					}
				}
			}
			{
				DMibTestPath("EnumFreeBits");
				using CBitArrayAligned = CBitArrayAligned;
				using CBitArrayUnaligned = CBitArrayUnaligned;
				{
					DMibTestPath("Aligned");
					const aint nBits = nBitsAligned;
					CBitArrayAligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						{
							TestBits.f_SetBit(i, true);

							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, 0
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr(nBits - 1)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(i, false);
						}
						{
							TestBits.template f_SetBit<true>(i);

							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, 0
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr(nBits - 1) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							TestBits.template f_SetBit<false>(i);
						}
					}
				}
				{
					DMibTestPath("Unaligned");
					const aint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						{
							TestBits.f_SetBit(i, true);
							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, 0
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr(nBits - 1)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(i, false);
						}
						{
							TestBits.template f_SetBit<true>(i);
							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, 0
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr(nBits - 1) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							TestBits.template f_SetBit<false>(i);
						}
					}
				}
			}
			{
				DMibTestPath("EnumFreeBitsMiddle");
				using CBitArrayAligned = CBitArrayAligned;
				using CBitArrayUnaligned = CBitArrayUnaligned;
				{
					DMibTestPath("Aligned");
					const aint nBits = nBitsAligned;
					CBitArrayAligned TestBits;
					for (aint i = nBits/2; i < nBits; ++i)
					{
						{
							TestBits.f_SetBit(i, true);

							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, nBits/2
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr((nBits - nBits/2) - 1)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(i, false);
						}
						{
							TestBits.template f_SetBit<true>(i);

							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, nBits/2
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr((nBits - nBits/2) - 1) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							TestBits.template f_SetBit<false>(i);
						}
					}
				}
				{
					DMibTestPath("Unaligned");
					const aint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = nBits/2; i < nBits; ++i)
					{
						{
							TestBits.f_SetBit(i, true);
							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, nBits/2
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr((nBits - nBits/2) - 1)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(i, false);
						}
						{
							TestBits.template f_SetBit<true>(i);
							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, nBits/2
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr((nBits - nBits/2) - 1) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							TestBits.template f_SetBit<false>(i);
						}
					}
				}
			}
			{
				DMibTestPath("EnumFreeBitsMiddleEnd");
				using CBitArrayAligned = CBitArrayAligned;
				using CBitArrayUnaligned = CBitArrayUnaligned;
				{
					DMibTestPath("Aligned");
					const aint nBits = nBitsAligned;
					CBitArrayAligned TestBits;
					for (aint i = nBits/3; i < nBits/2; ++i)
					{
						{
							TestBits.f_SetBit(i, true);

							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, nBits/3
									, nBits/2
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr((nBits/2 - nBits/3) - 1)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(i, false);
						}
						{
							TestBits.template f_SetBit<true>(i);

							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, nBits/3
									, nBits/2
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr((nBits/2 - nBits/3) - 1) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							TestBits.template f_SetBit<false>(i);
						}
					}
				}
				{
					DMibTestPath("Unaligned");
					const aint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = nBits/3; i < nBits/2; ++i)
					{
						{
							TestBits.f_SetBit(i, true);
							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, nBits/3
									, nBits/2
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr((nBits/2 - nBits/3) - 1)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(i, false);
						}
						{
							TestBits.template f_SetBit<true>(i);
							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, nBits/3
									, nBits/2
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr((nBits/2 - nBits/3) - 1) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							TestBits.template f_SetBit<false>(i);
						}
					}
				}
			}
			{
				DMibTestPath("EnumFreeBitRanges");
				using CBitArrayAligned = CBitArrayAligned;
				using CBitArrayUnaligned = CBitArrayUnaligned;
				{
					DMibTestPath("Aligned");
					const aint nBits = nBitsAligned;
					CBitArrayAligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						{
							TestBits.f_SetBit(i, true);

							aint nFound = 0;
							aint nRanges = 0;
							TestBits.f_EnumFreeBitRanges
								(
									[&](umint _Bit, umint _nBits) -> bool
									{
										nFound += _nBits;
										++nRanges;
										return true;
									}
									, 0
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr(nBits - 1)) (ETestFlag_Aggregated);
							if (i == 0 || i == nBits - 1)
								DMibTest(DMibExpr(nRanges) == DMibExpr(1)) (ETestFlag_Aggregated);
							else
								DMibTest(DMibExpr(nRanges) == DMibExpr(2)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(i, false);
						}
						{
							TestBits.template f_SetBit<true>(i);

							aint nFound = 0;
							aint nRanges = 0;
							TestBits.f_EnumFreeBitRanges
								(
									[&](umint _Bit, umint _nBits) -> bool
									{
										nFound += _nBits;
										++nRanges;
										return true;
									}
									, 0
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr(nBits - 1) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							if (i == 0 || i == nBits - 1)
								DMibTest(DMibExpr(nRanges) == DMibExpr(1) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							else
								DMibTest(DMibExpr(nRanges) == DMibExpr(2) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							TestBits.template f_SetBit<false>(i);
						}
					}
				}
				{
					DMibTestPath("Unaligned");
					const aint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						{
							TestBits.f_SetBit(i, true);
							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, 0
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr(nBits - 1)) (ETestFlag_Aggregated);
							TestBits.f_SetBit(i, false);
						}
						{
							TestBits.template f_SetBit<true>(i);
							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bool
									{
										++nFound;
										return true;
									}
									, 0
								)
							;
							DMibTest(DMibExpr(nFound) == DMibExpr(nBits - 1) && DMibExpr("Static set")) (ETestFlag_Aggregated);
							TestBits.template f_SetBit<false>(i);
						}
					}
				}
			}
		}
	};

	template <template <umint t_nBits> class t_TCBitArray>
	struct TCTestBitArrayPowerOfTwo
	{
		static void fs_DoTests()
		{
			const aint nBitsAligned = sizeof(umint) * sizeof(umint) * 8 * 8;
			const aint nBitsUnaligned = sizeof(umint) * sizeof(umint) * 8 * 8 - 1;
			using CBitArrayAligned = typename t_TCBitArray<nBitsAligned>::CType;
			using CBitArrayUnaligned = typename t_TCBitArray<nBitsUnaligned>::CType;
			{
				DMibTestPath("PowerTwo");
				{
					DMibTestPath("FindAndSetFreeBit");
					{
						DMibTestPath("Aligned");
						[[maybe_unused]] const aint nBits = nBitsAligned;
						CBitArrayAligned TestBits;

						umint Bit = TestBits.f_FindFreeBitAndSet(3);
						DMibTest(DMibExpr(TestBits.f_GetBit(3, Bit)) == DMibExpr(true)) (ETestFlag_Aggregated);
					}
					{
						DMibTestPath("Unaligned");
						NMib::NTime::CPrefCyclesTimeMeasureMin MalterlibTime;
						[[maybe_unused]] const aint nBits = nBitsUnaligned;
						CBitArrayUnaligned TestBits;
						umint Bit = TestBits.f_FindFreeBitAndSet(3);
						DMibTest(DMibExpr(TestBits.f_GetBit(3, Bit)) == DMibExpr(true)) (ETestFlag_Aggregated);
					}
				}
			};
		}
	};

	class CBitOperations_Tests : public NMib::NTest::CTest
	{
	public:

		template <umint t_nBits>
		struct TCNormalBitArray
		{
			using CType = NMib::NContainer::TCBitArray<t_nBits>;
		};

		template <umint t_nBits>
		struct TCHierarchicalBitArray
		{
			using CType = NMib::NContainer::TCBitArrayHierarchical<t_nBits>;
		};

		template <umint t_nBits>
		struct TCPowerOfTwoBitArray
		{
			using CType = NMib::NContainer::TCBitArrayPowerTwo<t_nBits>;
		};

		void f_DoTests()
		{
			DMibTestSuite("Bit vector power of two")
			{
				TCTestBitArrayPowerOfTwo<TCPowerOfTwoBitArray>::fs_DoTests();
				TCTestBitArray<TCPowerOfTwoBitArray>::fs_DoTests();
			};
			DMibTestSuite("Bit vector")
			{
				TCTestBitArray<TCNormalBitArray>::fs_DoTests();
			};
			DMibTestSuite("Bit vector hierarchical")
			{
				TCTestBitArray<TCHierarchicalBitArray>::fs_DoTests();
			};
			DMibTestSuite("HighestBitSet")
			{
				fs_TestHighestBitSet<int8>("int8");
				fs_TestHighestBitSet<uint8>("uint8");
				fs_TestHighestBitSet<int16>("int16");
				fs_TestHighestBitSet<uint16>("uint16");
				fs_TestHighestBitSet<int32>("int32");
				fs_TestHighestBitSet<uint32>("uint32");
				fs_TestHighestBitSet<int64>("int64");
				fs_TestHighestBitSet<uint64>("uint64");
				fs_TestHighestBitSet<int128>("int128");
				fs_TestHighestBitSet<uint128>("uint128");
				fs_TestHighestBitSet<int256>("int256");
				fs_TestHighestBitSet<uint256>("uint256");
				fs_TestHighestBitSet<int512>("int512");
				fs_TestHighestBitSet<uint512>("uint512");
			};
			DMibTestSuite("HighestBitSetNoZero")
			{
				fs_TestHighestBitSetNoZero<int8>("int8");
				fs_TestHighestBitSetNoZero<uint8>("uint8");
				fs_TestHighestBitSetNoZero<int16>("int16");
				fs_TestHighestBitSetNoZero<uint16>("uint16");
				fs_TestHighestBitSetNoZero<int32>("int32");
				fs_TestHighestBitSetNoZero<uint32>("uint32");
				fs_TestHighestBitSetNoZero<int64>("int64");
				fs_TestHighestBitSetNoZero<uint64>("uint64");
				fs_TestHighestBitSetNoZero<int128>("int128");
				fs_TestHighestBitSetNoZero<uint128>("uint128");
				fs_TestHighestBitSetNoZero<int256>("int256");
				fs_TestHighestBitSetNoZero<uint256>("uint256");
				fs_TestHighestBitSetNoZero<int512>("int512");
				fs_TestHighestBitSetNoZero<uint512>("uint512");
			};
			DMibTestSuite("LowestBitSet")
			{
				fs_TestLowestBitSet<int8>("int8");
				fs_TestLowestBitSet<uint8>("uint8");
				fs_TestLowestBitSet<int16>("int16");
				fs_TestLowestBitSet<uint16>("uint16");
				fs_TestLowestBitSet<int32>("int32");
				fs_TestLowestBitSet<uint32>("uint32");
				fs_TestLowestBitSet<int64>("int64");
				fs_TestLowestBitSet<uint64>("uint64");
				fs_TestLowestBitSet<int128>("int128");
				fs_TestLowestBitSet<uint128>("uint128");
				fs_TestLowestBitSet<int256>("int256");
				fs_TestLowestBitSet<uint256>("uint256");
				fs_TestLowestBitSet<int512>("int512");
				fs_TestLowestBitSet<uint512>("uint512");
			};
			DMibTestSuite("LowestBitSetNoZero")
			{
				fs_TestLowestBitSetNoZero<int8>("int8");
				fs_TestLowestBitSetNoZero<uint8>("uint8");
				fs_TestLowestBitSetNoZero<int16>("int16");
				fs_TestLowestBitSetNoZero<uint16>("uint16");
				fs_TestLowestBitSetNoZero<int32>("int32");
				fs_TestLowestBitSetNoZero<uint32>("uint32");
				fs_TestLowestBitSetNoZero<int64>("int64");
				fs_TestLowestBitSetNoZero<uint64>("uint64");
				fs_TestLowestBitSetNoZero<int128>("int128");
				fs_TestLowestBitSetNoZero<uint128>("uint128");
				fs_TestLowestBitSetNoZero<int256>("int256");
				fs_TestLowestBitSetNoZero<uint256>("uint256");
				fs_TestLowestBitSetNoZero<int512>("int512");
				fs_TestLowestBitSetNoZero<uint512>("uint512");
			};
			DMibTestSuite("MinPowerOfTwo")
			{
				fs_TestMinPowerOfTwo<uint8>("uint8");
				fs_TestMinPowerOfTwo<uint16>("uint16");
				fs_TestMinPowerOfTwo<uint32>("uint32");
				fs_TestMinPowerOfTwo<uint64>("uint64");
			};
			DMibTestSuite("NumBitsSet")
			{
				fs_TestNumBitsSet<int8>("int8");
				fs_TestNumBitsSet<uint8>("uint8");
				fs_TestNumBitsSet<int16>("int16");
				fs_TestNumBitsSet<uint16>("uint16");
				fs_TestNumBitsSet<int32>("int32");
				fs_TestNumBitsSet<uint32>("uint32");
				fs_TestNumBitsSet<int64>("int64");
				fs_TestNumBitsSet<uint64>("uint64");
				fs_TestNumBitsSet<int128>("int128");
				fs_TestNumBitsSet<uint128>("uint128");
				fs_TestNumBitsSet<int256>("int256");
				fs_TestNumBitsSet<uint256>("uint256");
				fs_TestNumBitsSet<int512>("int512");
				fs_TestNumBitsSet<uint512>("uint512");
			};
		}
	};

	DMibTestRegister(CBitOperations_Tests, Malterlib::Bit);
}
