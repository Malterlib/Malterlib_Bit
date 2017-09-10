// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#include <Mib/Container/BitArray>
#include <Mib/Container/BitArrayHierarchical>
#include <Mib/Container/BitArrayPowerTwo>
#include <Mib/Test/Performance>

DMibStaticCheck((NMib::TCHighestBitSetCorrect<int, 3>::mc_Value == 1));
DMibStaticCheck((NMib::TCHighestBitSet<int, 3>::mc_Value == 2));
DMibStaticCheck((NMib::TCHighestBitSet<int, 0x08000000>::mc_Value == 28));
DMibStaticCheck((NMib::TCHighestBitSetCorrect<int, 0x08000000>::mc_Value == 27));

DMibStaticCheck(NMib::TCLowestBitSet<3>::mc_Value == 0);
DMibStaticCheck(NMib::TCLowestBitSet<2>::mc_Value == 1);
DMibStaticCheck(NMib::TCLowestBitSet<1 << 5>::mc_Value == 5);
DMibStaticCheck(NMib::TCLowestBitSet<1 << 10>::mc_Value == 10);
DMibStaticCheck(NMib::TCLowestBitSet<1 << 15>::mc_Value == 15);
DMibStaticCheck(NMib::TCLowestBitSet<1 << 20>::mc_Value == 20);
DMibStaticCheck(NMib::TCLowestBitSet<1 << 25>::mc_Value == 25);
DMibStaticCheck(NMib::TCLowestBitSet<1 << 30>::mc_Value == 30);
DMibStaticCheck(NMib::TCLowestBitSet<1u << 31>::mc_Value == 31);

#if DMibPBits_mint > 32
DMibStaticCheck(NMib::TCLowestBitSet<mint(1) << 35>::mc_Value == 35);
DMibStaticCheck(NMib::TCLowestBitSet<mint(1) << 40>::mc_Value == 40);
DMibStaticCheck(NMib::TCLowestBitSet<mint(1) << 45>::mc_Value == 45);
DMibStaticCheck(NMib::TCLowestBitSet<mint(1) << 50>::mc_Value == 50);
DMibStaticCheck(NMib::TCLowestBitSet<mint(1) << 55>::mc_Value == 55);
DMibStaticCheck(NMib::TCLowestBitSet<mint(1) << 60>::mc_Value == 60);
DMibStaticCheck(NMib::TCLowestBitSet<mint(1) << 63>::mc_Value == 63);
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
	static void fs_TestHighestBitSet(const ch8 *_pName)
	{
		DMibTestSuite(_pName)
		{
			NMib::NTime::CCyclesMin MalterlibTime;
			const mint nLoops = 10000;
			t_CInteger Number = NMib::NStr::CStr(NMib::NStr::CStr::CFormat("{}") << 0x50).f_ToInt();
			uint32 Result = 0;
			auto Lambda = [&] ()
			{	
				uint32 Temp = Result;
				MalterlibTime.f_Start();
				for (mint i = 0; i < nLoops; ++i)
				{
					NMib::NAtomic::fg_MemoryFence(NMib::NAtomic::EMemoryOrder_Acquire);
					Temp += NMib::fg_GetHighestBitSet(Number);
				}
				MalterlibTime.f_Stop();
				Result = Temp;
			};
			for (mint i = 0; i < 100; ++i)
				fs_CallFunctor(Lambda);
			MalterlibTime /= nLoops;
			mint ExpectedCycles = 10*sizeof(t_CInteger);
			DMibTest(DMibExpr(Result) == DMibExpr(6*100*nLoops)) (ETestFlag_NoValues);
			if (NMib::NTest::fg_GroupActive("Performance"))
				DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
		};
	}

	template <typename t_CInteger>
	static void fs_TestHighestBitSetNoZero(const ch8 *_pName)
	{
		DMibTestSuite(_pName)
		{
			NMib::NTime::CCyclesMin MalterlibTime;
			const mint nLoops = 10000;
			t_CInteger Number = NMib::NStr::CStr(NMib::NStr::CStr::CFormat("{}") << 0x50).f_ToInt();
			uint32 Result = 0;
			auto Lambda = [&] ()
			{	
				uint32 Temp = Result;
				MalterlibTime.f_Start();
				for (mint i = 0; i < nLoops; ++i)
				{
					NMib::NAtomic::fg_MemoryFence(NMib::NAtomic::EMemoryOrder_Acquire);
					Temp += NMib::fg_GetHighestBitSetNoZero(Number);
				}
				MalterlibTime.f_Stop();
				Result = Temp;
			};
			for (mint i = 0; i < 100; ++i)
				fs_CallFunctor(Lambda);
			MalterlibTime /= nLoops;
			mint ExpectedCycles = 10*sizeof(t_CInteger);
			DMibTest(DMibExpr(Result) == DMibExpr(6*100*nLoops)) (ETestFlag_NoValues);
			if (NMib::NTest::fg_GroupActive("Performance"))
				DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
		};
	}

	template <typename t_CInteger>
	static void fs_TestLowestBitSet(const ch8 *_pName)
	{
		DMibTestSuite(_pName)
		{
			NMib::NTime::CCyclesMin MalterlibTime;
			const mint nLoops = 10000;
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
				for (mint i = 0; i < nLoops; ++i)
				{
					NMib::NAtomic::fg_MemoryFence(NMib::NAtomic::EMemoryOrder_Acquire);
					Temp += NMib::fg_GetLowestBitSet(Number);
				}
				MalterlibTime.f_Stop();
				Result = Temp;
			};
			for (mint i = 0; i < 100; ++i)
				fs_CallFunctor(Lambda);
			MalterlibTime /= nLoops;
			mint ExpectedCycles = 10*sizeof(t_CInteger);
			DMibTest(DMibExpr(Result) == DMibExpr((ENumBits-8)*100*nLoops)) (ETestFlag_NoValues);
			if (NMib::NTest::fg_GroupActive("Performance"))
				DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
		};
	}



	template <typename t_CInteger>
	static void fs_TestLowestBitSetNoZero(const ch8 *_pName)
	{
		DMibTestSuite(_pName)
		{
			NMib::NTime::CCyclesMin MalterlibTime;
			const mint nLoops = 10000;
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
				for (mint i = 0; i < nLoops; ++i)
				{
					NMib::NAtomic::fg_MemoryFence(NMib::NAtomic::EMemoryOrder_Acquire);
					Temp += NMib::fg_GetLowestBitSetNoZero(Number);
				}
				MalterlibTime.f_Stop();
				Result = Temp;
			};
			for (mint i = 0; i < 100; ++i)
				fs_CallFunctor(Lambda);
			MalterlibTime /= nLoops;
			mint ExpectedCycles = 10*sizeof(t_CInteger);
			DMibTest(DMibExpr(Result) == DMibExpr((ENumBits-8)*100*nLoops)) (ETestFlag_NoValues);
			if (NMib::NTest::fg_GroupActive("Performance"))
				DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
		};
	}




	template <typename t_CInteger>
	static void fs_TestNumBitsSet(const ch8 *_pName)
	{
		DMibTestSuite(_pName)
		{
			NMib::NTime::CCyclesMin MalterlibTime;
			const mint nLoops = 10000;
			t_CInteger Number = 0;
			mint nBytes = sizeof(Number);
			for (mint i = 0; i < nBytes; ++i)
			{
				Number |= t_CInteger(NMib::NStr::CStr(NMib::NStr::CStr::CFormat("{}") << 0x55).f_ToInt()) << (i * 8);
			}
			uint32 Result = 0;
			auto Lambda = [&] ()
			{	
				uint32 Temp = Result;
				MalterlibTime.f_Start();
				for (mint i = 0; i < nLoops; ++i)
				{
					NMib::NAtomic::fg_MemoryFence(NMib::NAtomic::EMemoryOrder_Acquire);
					Temp += NMib::fg_NumBitsSet(Number);
				}
				MalterlibTime.f_Stop();
				Result = Temp;
			};
			for (mint i = 0; i < 100; ++i)
				fs_CallFunctor(Lambda);
			MalterlibTime /= nLoops;
			mint ExpectedCycles = 10*sizeof(t_CInteger);
			DMibTest(DMibExpr(Result) == DMibExpr(4*nBytes*100*nLoops)) (ETestFlag_NoValues);
			if (NMib::NTest::fg_GroupActive("Performance"))
				DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
		};
	}

	template <template <mint t_nBits> class t_TCBitArray>
	struct TCTestBitArray
	{

		static void fs_DoTests()
		{
			
			const aint nBitsAligned = sizeof(mint) * sizeof(mint) * 8 * 8;
			const aint nBitsUnaligned = sizeof(mint) * sizeof(mint) * 8 * 8 - 1;
			typedef typename t_TCBitArray<nBitsAligned>::CType CBitArrayAligned;
			typedef typename t_TCBitArray<nBitsUnaligned>::CType CBitArrayUnaligned;
			DMibTestCategory("FindFreeBitAndSet")
			{
				typedef CBitArrayAligned CBitArrayAligned;
				typedef CBitArrayUnaligned CBitArrayUnaligned;
				DMibTestSuite("Aligned")
				{
					NMib::NTest::CTestPerformance Pref(1.0);

					{
						NMib::NTest::CTestPerformanceMeasure MalterlibMeasure("Malterlib");
						const mint nBits = nBitsAligned;
						CBitArrayAligned TestBits;
						for (aint i = 0; i < 10; ++i)
						{
							TestBits.f_Clear();
							MalterlibMeasure.f_Start();
							for (mint i = 0; i < nBits-1; ++i)
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
				};
				DMibTestSuite("Unaligned")
				{
					NMib::NTime::CCyclesMin MalterlibTime;
					const mint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = 0; i < 10; ++i)
					{
						TestBits.f_Clear();
						MalterlibTime.f_Start();
						for (mint i = 0; i < nBits-1; ++i)
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
					mint ExpectedCycles = (nBits*10)/(sizeof(void *)*2);
					if (NMib::NTest::fg_GroupActive("Performance"))
						DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
				};
			};
			DMibTestCategory("FindFreeBitReverseAndSet")
			{
				typedef CBitArrayAligned CBitArrayAligned;
				typedef CBitArrayUnaligned CBitArrayUnaligned;
				DMibTestSuite("Aligned")
				{
					NMib::NTest::CTestPerformance Pref(1.0);

					{
						NMib::NTest::CTestPerformanceMeasure MalterlibMeasure("Malterlib");
						const mint nBits = nBitsAligned;
						CBitArrayAligned TestBits;
						for (aint i = 0; i < 10; ++i)
						{
							TestBits.f_Clear();
							MalterlibMeasure.f_Start();
							for (mint i = 0; i < nBits-1; ++i)
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
				};
				DMibTestSuite("Unaligned")
				{
					NMib::NTime::CCyclesMin MalterlibTime;
					const mint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = 0; i < 10; ++i)
					{
						TestBits.f_Clear();
						MalterlibTime.f_Start();
						for (mint i = 0; i < nBits-1; ++i)
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
					mint ExpectedCycles = (nBits*10)/(sizeof(void *)*2);
					if (NMib::NTest::fg_GroupActive("Performance"))
						DMibTest(DMibExpr(MalterlibTime.f_GetCycles()) < DMibExpr(ExpectedCycles));
				};
			};
			DMibTestCategory("FindUpperBound")
			{
				typedef CBitArrayAligned CBitArrayAligned;
				typedef CBitArrayUnaligned CBitArrayUnaligned;
				DMibTestSuite("Aligned")
				{
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
				};
				DMibTestSuite("Unaligned")
				{
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
				};
			};
			DMibTestCategory("FindUpperBoundStart")
			{
				typedef CBitArrayAligned CBitArrayAligned;
				typedef CBitArrayUnaligned CBitArrayUnaligned;
				DMibTestSuite("Aligned")
				{
					const aint nBits = nBitsAligned;
					CBitArrayAligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						mint Start = NMib::fg_Max(0, smint(i)-3);

						TestBits.f_SetBit(i, true);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(Start)) == DMibExpr(i)) (ETestFlag_Aggregated);
						TestBits.f_SetBit(i, false);

						TestBits.template f_SetBit<true>(i);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(Start)) == DMibExpr(i) && DMibExpr("Static set")) (ETestFlag_Aggregated);
						TestBits.template f_SetBit<false>(i);
					}
				};
				DMibTestSuite("Unaligned")
				{
					const aint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						mint Start = NMib::fg_Max(0, smint(i)-3);
						TestBits.f_SetBit(i, true);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(Start)) == DMibExpr(i)) (ETestFlag_Aggregated);
						TestBits.f_SetBit(i, false);

						TestBits.template f_SetBit<true>(i);
						DMibTest(DMibExpr(TestBits.f_FindUpperBound(Start)) == DMibExpr(i) && DMibExpr("Static set")) (ETestFlag_Aggregated);
						TestBits.template f_SetBit<false>(i);
					}
				};
			};
			DMibTestCategory("EnumFreeBits")
			{
				typedef CBitArrayAligned CBitArrayAligned;
				typedef CBitArrayUnaligned CBitArrayUnaligned;
				DMibTestSuite("Aligned")
				{
					const aint nBits = nBitsAligned;
					CBitArrayAligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						{
							TestBits.f_SetBit(i, true);

							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bint
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
									[&](aint _Bit) -> bint
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
				};
				DMibTestSuite("Unaligned")
				{
					const aint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = 0; i < nBits; ++i)
					{
						{
							TestBits.f_SetBit(i, true);
							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bint
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
									[&](aint _Bit) -> bint
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
				};
			};
			DMibTestCategory("EnumFreeBitsMiddle")
			{
				typedef CBitArrayAligned CBitArrayAligned;
				typedef CBitArrayUnaligned CBitArrayUnaligned;
				DMibTestSuite("Aligned")
				{
					const aint nBits = nBitsAligned;
					CBitArrayAligned TestBits;
					for (aint i = nBits/2; i < nBits; ++i)
					{
						{
							TestBits.f_SetBit(i, true);

							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bint
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
									[&](aint _Bit) -> bint
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
				};
				DMibTestSuite("Unaligned")
				{
					const aint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = nBits/2; i < nBits; ++i)
					{
						{
							TestBits.f_SetBit(i, true);
							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bint
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
									[&](aint _Bit) -> bint
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
				};
			};
			DMibTestCategory("EnumFreeBitsMiddleEnd")
			{
				typedef CBitArrayAligned CBitArrayAligned;
				typedef CBitArrayUnaligned CBitArrayUnaligned;
				DMibTestSuite("Aligned")
				{
					const aint nBits = nBitsAligned;
					CBitArrayAligned TestBits;
					for (aint i = nBits/3; i < nBits/2; ++i)
					{
						{
							TestBits.f_SetBit(i, true);

							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bint
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
									[&](aint _Bit) -> bint
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
				};
				DMibTestSuite("Unaligned")
				{
					const aint nBits = nBitsUnaligned;
					CBitArrayUnaligned TestBits;
					for (aint i = nBits/3; i < nBits/2; ++i)
					{
						{
							TestBits.f_SetBit(i, true);
							aint nFound = 0;
							TestBits.f_EnumFreeBits
								(
									[&](aint _Bit) -> bint
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
									[&](aint _Bit) -> bint
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
				};
			};
			DMibTestCategory("EnumFreeBitRanges")
			{
				typedef CBitArrayAligned CBitArrayAligned;
				typedef CBitArrayUnaligned CBitArrayUnaligned;
				DMibTestSuite("Aligned")
				{
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
									[&](mint _Bit, mint _nBits) -> bool
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
									[&](mint _Bit, mint _nBits) -> bool
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
				};
				DMibTestSuite("Unaligned")
				{
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
				};
			};
		}

	};

	template <template <mint t_nBits> class t_TCBitArray>
	struct TCTestBitArrayPowerOfTwo
	{

		static void fs_DoTests()
		{
			
			const aint nBitsAligned = sizeof(mint) * sizeof(mint) * 8 * 8;
			const aint nBitsUnaligned = sizeof(mint) * sizeof(mint) * 8 * 8 - 1;
			typedef typename t_TCBitArray<nBitsAligned>::CType CBitArrayAligned;
			typedef typename t_TCBitArray<nBitsUnaligned>::CType CBitArrayUnaligned;
			DMibTestCategory("PowerTwo")
			{
				DMibTestCategory("FindAndSetFreeBit")
				{
					DMibTestSuite("Aligned")
					{
						[[maybe_unused]] const aint nBits = nBitsAligned;
						CBitArrayAligned TestBits;

						mint Bit = TestBits.f_FindFreeBitAndSet(3);
						DMibTest(DMibExpr(TestBits.f_GetBit(3, Bit)) == DMibExpr(true)) (ETestFlag_Aggregated);
					};
					DMibTestSuite("Unaligned")
					{
						NMib::NTime::CCyclesMin MalterlibTime;
						[[maybe_unused]] const aint nBits = nBitsUnaligned;
						CBitArrayUnaligned TestBits;
						mint Bit = TestBits.f_FindFreeBitAndSet(3);
						DMibTest(DMibExpr(TestBits.f_GetBit(3, Bit)) == DMibExpr(true)) (ETestFlag_Aggregated);
					};
				};
			};
		}

	};

	class CBitOperations_Tests : public NMib::NTest::CTest
	{
	public:

		template <mint t_nBits>
		struct TCNormalBitArray
		{
			typedef NMib::NContainer::TCBitArray<t_nBits> CType;
		};
		template <mint t_nBits>
		struct TCHierarchicalBitArray
		{
			typedef NMib::NContainer::TCBitArrayHierarchical<t_nBits> CType;
		};
		template <mint t_nBits>
		struct TCPowerOfTwoBitArray
		{
			typedef NMib::NContainer::TCBitArrayPowerTwo<t_nBits> CType;
		};

		
		void f_DoTests()
		{
			DMibTestCategory("Bit vector power of two")
			{
				TCTestBitArrayPowerOfTwo<TCPowerOfTwoBitArray>::fs_DoTests();
				TCTestBitArray<TCPowerOfTwoBitArray>::fs_DoTests();
			};

			DMibTestCategory("Bit vector")
			{
				TCTestBitArray<TCNormalBitArray>::fs_DoTests();
			};

			DMibTestCategory("Bit vector hierarchical")
			{
				TCTestBitArray<TCHierarchicalBitArray>::fs_DoTests();
			};


			DMibTestCategory("HighestBitSet")
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
			DMibTestCategory("HighestBitSetNoZero")
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
			DMibTestCategory("LowestBitSet")
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
			DMibTestCategory("LowestBitSetNoZero")
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
			DMibTestCategory("NumBitsSet")
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
