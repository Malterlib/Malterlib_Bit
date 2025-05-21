// Copyright © 2015 Hansoft AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib
 
#pragma once

#include <Mib/Core/Core>
#ifdef DCompiler_MSVCWorkaround
#include <type_traits>
#endif

namespace NMib::NNumeric
{
	template <typename t_CUpper, typename t_CLower>
	struct TCInt;
}

namespace NMib
{
	/**	\namespace NMib::NBit
		\brief Bit namespace
		 
		Contains helpers for bit 
	 */

	struct CBitAutoConvert
	{
		template <typename tf_CType>
		constexpr operator tf_CType() const
		{
			using CIntType = NTraits::TCUnsigned<NTraits::TCIntFromSize<sizeof(tf_CType)>>;

			return tf_CType(CIntType(1) << m_Bit);
		}

		mint m_Bit;
	};

	constexpr CBitAutoConvert fg_Bit(mint _Bit)
	{
		return CBitAutoConvert{.m_Bit = _Bit};
	}

	template <typename tf_CType>
	constexpr tf_CType fg_Bit(mint _Bit, tf_CType _One)
	{
		return _One << _Bit;
	}

	struct CBitRangeAutoConvert
	{
		template <typename tf_CType>
		constexpr operator tf_CType() const
		{
			using CIntType = NTraits::TCUnsigned<NTraits::TCIntFromSize<sizeof(tf_CType)>>;

			return tf_CType
				(
					(
						(
							(CIntType(1) << m_BitEnd)
							- CIntType(1)
						)
						| (CIntType(1) << m_BitEnd)
					)
					^
					(
						(CIntType(1) << m_BitStart)
						- CIntType(1)
					)
				)
			;
		}

		mint m_BitStart;
		mint m_BitEnd;
	};

	constexpr CBitRangeAutoConvert fg_BitRange(mint _BitStart, mint _BitEnd)
	{
		return CBitRangeAutoConvert{.m_BitStart = _BitStart, .m_BitEnd = _BitEnd};
	}

	template <typename tf_CType>
	constexpr tf_CType fg_BitRange(uaint _BitStart, uaint _BitEnd)
	{
		using CUnsigned = NTraits::TCUnsigned<tf_CType>;

		return
			(
				(
					(CUnsigned(1) << _BitEnd)
					- CUnsigned(1)
				)
				| (CUnsigned(1) << _BitEnd)
			)
			^
			(
				(CUnsigned(1) << _BitStart)
				- CUnsigned(1)
			)
		;
	}

	template <typename t_CInt>
	NTraits::TCSmallerType<t_CInt> fg_GetLower(t_CInt const &_Integer);

	template <typename t_CInt>
	NTraits::TCSmallerType<t_CInt> fg_GetUpper(t_CInt const &_Integer);

	template <typename t_CUpper, typename t_CLower>
	typename NNumeric::TCInt<t_CUpper, t_CLower>::CLower const &fg_GetLower(NNumeric::TCInt<t_CUpper, t_CLower> const &_Integer);

	template <typename t_CUpper, typename t_CLower>
	typename NNumeric::TCInt<t_CUpper, t_CLower>::CUpper const &fg_GetUpper(NNumeric::TCInt<t_CUpper, t_CLower> const &_Integer);


	template <typename tf_CInt>
	constexpr int32 fg_GetLowestBitSet(tf_CInt const &_Number);

	template <typename tf_CInt>
	constexpr int32 fg_GetLowestBitSetNoZero(tf_CInt const &_Number);

	template <typename tf_CInt>
	constexpr int32 fg_GetHighestBitSet(tf_CInt const &_Number);
	
	template <typename tf_CInt>
	constexpr int32 fg_GetHighestBitSetNoZero(tf_CInt const &_Number);
	
	namespace NPrivate
	{
		template <mint t_CurrentNumber, mint t_Bit = 0>
		class TCGetLowestBitSetStaticHelper
		{
		public:
			enum
			{
				ENumBits = (t_CurrentNumber & 1) ? t_Bit : TCGetLowestBitSetStaticHelper<(t_CurrentNumber >> 1), t_Bit + 1>::ENumBits
			};
		};

		template <mint t_Bit>
		class TCGetLowestBitSetStaticHelper<0, t_Bit>
		{
		public:
			enum
			{
				ENumBits = -1
			};
		};
	}

	template <mint t_CurrentNumber>
	constexpr inline mint gc_LowestBitSet = NPrivate::TCGetLowestBitSetStaticHelper<t_CurrentNumber>::ENumBits;

	namespace NPrivate
	{

		template <mint t_Dummy = 0>
		class TCGetLowestBitSet_Helpers
		{
		public:
			constexpr static const int8 ms_LogTable256[] 
			{
				-1, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				7, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				6, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				5, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
				4, 0, 1, 0, 2, 0, 1, 0, 3, 0, 1, 0, 2, 0, 1, 0, 
			};
		};

		template <typename t_CInt>
		class TCGetLowestBitSetGeneric
		{
		public:
			using CType = t_CInt;
			enum
			{
				EDefaultImplementation = 1
			};
			constexpr static inline_small int32 fs_GetLowestBitSet(t_CInt const &_Number)
			{
				using CUnsigned = NMib::NTraits::TCUnsigned<t_CInt>;
				mint nBytes = sizeof(CUnsigned);
				CUnsigned Number = _Number;
				int const Shift = sizeof(t_CInt) == 1 ? 0 : 8;
				for (mint i = 0; i < nBytes; ++i, Number >>= Shift)
				{
					CUnsigned Current = Number & CUnsigned(0xff);
					if (Current != 0)
					{
						return i * 8 + TCGetLowestBitSet_Helpers<>::ms_LogTable256[mint(Current)];
					}
				}
				return -1;
			}
		};

		template <typename t_CInt, bool t_SupportZero>
		struct TCGetLowestBitSet : public TCGetLowestBitSetGeneric<t_CInt>
		{
		};

		template <typename t_CInt>
		class TCGetLowestBitSet<t_CInt, 0> : public TCGetLowestBitSet<t_CInt, 1>
		{
		public:
		};

		template <mint t_nBytes, typename t_CType, bool t_bSupportZero>
		class TCHelper_GetLowestBitSetChooseBySize
		{
		public:
			using CGetter = TCGetLowestBitSet<t_CType, t_bSupportZero>;
		};

		template <mint t_nBytes, typename t_CType>
		class TCHelper_GetLowestBitSetChooseBySize<t_nBytes, t_CType, 0>
		{
		public:
			using CGetter = TCGetLowestBitSet<t_CType, 1>;
		};

#ifdef DMibPGetLowestBitSet32
		template <>
		class TCGetLowestBitSet<uint32, true>
		{
		public:
			using CType = uint32;
			enum
			{
				EDefaultImplementation = 0
			};
			constexpr static inline_small int32 fs_GetLowestBitSet(uint32 const &_Number)
			{
#ifdef DCompiler_MSVC_Workaround
				if_consteval
				{
					return TCGetLowestBitSetGeneric<uint32>::fs_GetLowestBitSet(_Number);
				}
				else
#endif
				{
					return DMibPGetLowestBitSet32(_Number);
				}
			}
		};

		template <>
		class TCGetLowestBitSet<int32, true> : public TCGetLowestBitSet<uint32, true>
		{
		};

		template <typename t_CType>
		class TCHelper_GetLowestBitSetChooseBySize<sizeof(uint8), t_CType, true>
		{
		public:
			using CGetter = TCGetLowestBitSet<uint32, true>;
		};

		template <typename t_CType>
		class TCHelper_GetLowestBitSetChooseBySize<sizeof(uint16), t_CType, true>
		{
		public:
			using CGetter = TCGetLowestBitSet<uint32, true>;
		};

		template <typename t_CType>
		class TCHelper_GetLowestBitSetChooseBySize<sizeof(uint32), t_CType, true>
		{
		public:
			using CGetter = TCGetLowestBitSet<uint32, true>;
		};
#else
		template <>
		class TCGetLowestBitSet<uint8, 1>
		{
		public:
			using CType = uint8;
			enum
			{
				EDefaultImplementation = 1
			};
			constexpr static inline_small int32 fs_GetLowestBitSet(CType const &_Number)
			{
				return TCGetLowestBitSet_Helpers<>::ms_LogTable256[_Number];
			}
		};

		template <typename t_CType>
		class TCHelper_GetLowestBitSetChooseBySize<sizeof(uint8), t_CType, true>
		{
		public:
			using CGetter = TCGetLowestBitSet<uint8, true>;
		};


#endif

	#ifdef DMibPGetLowestBitSet32NoZero
		template <>
		class TCGetLowestBitSet<uint32, false>
		{
		public:
			using CType = uint32;
			enum
			{
				EDefaultImplementation = 0
			};
			constexpr static inline_small int32 fs_GetLowestBitSet(uint32 const &_Number)
			{
#ifdef DCompiler_MSVC_Workaround
				if_consteval
				{
					return TCGetLowestBitSetGeneric<uint32>::fs_GetLowestBitSet(_Number);
				}
				else
#endif
				{
					return DMibPGetLowestBitSet32NoZero(_Number);
				}
			}
		};

		template <>
		class TCGetLowestBitSet<int32, false> : public TCGetLowestBitSet<uint32, false>
		{
		};

		template <typename t_CType>
		class TCHelper_GetLowestBitSetChooseBySize<sizeof(uint8), t_CType, false>
		{
		public:
			using CGetter = TCGetLowestBitSet<uint32, false>;
		};

		template <typename t_CType>
		class TCHelper_GetLowestBitSetChooseBySize<sizeof(uint16), t_CType, false>
		{
		public:
			using CGetter = TCGetLowestBitSet<uint32, false>;
		};

		template <typename t_CType>
		class TCHelper_GetLowestBitSetChooseBySize<sizeof(uint32), t_CType, false>
		{
		public:
			using CGetter = TCGetLowestBitSet<uint32, false>;
		};

	#endif


	#ifdef DMibPGetLowestBitSet64
		template <>
		class TCGetLowestBitSet<uint64, true>
		{
		public:
			using CType = uint64;
			enum
			{
				EDefaultImplementation = 0
			};
			constexpr static inline_small int32 fs_GetLowestBitSet(uint64 const &_Number)
			{
#ifdef DCompiler_MSVC_Workaround
				if_consteval
				{
					return TCGetLowestBitSetGeneric<uint64>::fs_GetLowestBitSet(_Number);
				}
				else
#endif
				{
					return DMibPGetLowestBitSet64(_Number);
				}
			}
		};

		template <>
		class TCGetLowestBitSet<int64, true> : public TCGetLowestBitSet<uint64, true>
		{
		};

		template <typename t_CType>
		class TCHelper_GetLowestBitSetChooseBySize<sizeof(uint64), t_CType, true>
		{
		public:
			using CGetter = TCGetLowestBitSet<uint64, true>;
		};

	#endif

	#ifdef DMibPGetLowestBitSet64NoZero
		template <>
		class TCGetLowestBitSet<uint64, false>
		{
		public:
			using CType = uint64;
			enum
			{
				EDefaultImplementation = 0
			};
			constexpr static inline_small int32 fs_GetLowestBitSet(uint64 const &_Number)
			{
#ifdef DCompiler_MSVC_Workaround
				if_consteval
				{
					return TCGetLowestBitSetGeneric<uint64>::fs_GetLowestBitSet(_Number);
				}
				else
#endif
				{
					return DMibPGetLowestBitSet64NoZero(_Number);
				}
			}
		};

		template <>
		class TCGetLowestBitSet<int64, false> : public TCGetLowestBitSet<uint64, false>
		{
		};

		template <typename t_CType>
		class TCHelper_GetLowestBitSetChooseBySize<sizeof(uint64), t_CType, false>
		{
		public:
			using CGetter = TCGetLowestBitSet<uint64, false>;
		};

	#endif

		template <typename tf_CInt>
		constexpr inline_small TCEnableIf<!TCGetLowestBitSet<tf_CInt, true>::EDefaultImplementation, int32> fg_GetLowestBitSetHelper(tf_CInt const &_Number)
		{
			return NPrivate::TCGetLowestBitSet<tf_CInt, true>::fs_GetLowestBitSet(_Number);
		}

		template <typename tf_CInt>
		constexpr inline_small TCEnableIf<TCGetLowestBitSet<tf_CInt, true>::EDefaultImplementation && NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>, int32> fg_GetLowestBitSetHelper(tf_CInt const &_Number)
		{
			// Static branch
			using CGetter = typename NPrivate::TCHelper_GetLowestBitSetChooseBySize<sizeof(tf_CInt), tf_CInt, true>::CGetter;
			return CGetter::fs_GetLowestBitSet(_Number);
		}

		template <typename tf_CInt>
		constexpr inline_small TCEnableIf<TCGetLowestBitSet<tf_CInt, true>::EDefaultImplementation && !NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>, int32> fg_GetLowestBitSetHelper(tf_CInt const &_Number)
		{
			enum
			{
				EToShift = sizeof(_Number)*4
			};
			// Static branch
			if constexpr (NMib::NTraits::cIsFundamental<tf_CInt>)
			{
				decltype(auto) Lower = fg_GetLower(_Number);
				if (Lower)
					return fg_GetLowestBitSet(Lower);
				decltype(auto) Upper = fg_GetUpper(_Number);
				int32 Ret = fg_GetLowestBitSet(Upper);
				if (Ret < 0)
					return -1;
				return Ret + EToShift;
			}
			else
			{
				decltype(auto) Lower = fg_GetLower(_Number);
				int32 Ret = fg_GetLowestBitSet(Lower);
				if (Ret >= 0)
					return Ret;

				decltype(auto) Upper = fg_GetUpper(_Number);
				Ret = fg_GetLowestBitSet(Upper);
				if (Ret < 0)
					return -1;
				return Ret + EToShift;
			}
		}

		template <typename tf_CInt>
		constexpr inline_small TCEnableIf<!TCGetLowestBitSet<tf_CInt, true>::EDefaultImplementation, int32> fg_GetLowestBitSetHelperNoZero(tf_CInt const &_Number)
		{
			return NPrivate::TCGetLowestBitSet<tf_CInt, false>::fs_GetLowestBitSet(_Number);
		}

		template <typename tf_CInt>
		constexpr inline_small auto fg_GetLowestBitSetHelperNoZero(tf_CInt const &_Number)
			-> TCEnableIf<TCGetLowestBitSet<tf_CInt, true>::EDefaultImplementation && NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>, int32>
		{
			// Static branch
			using CGetter = typename NPrivate::TCHelper_GetLowestBitSetChooseBySize<sizeof(tf_CInt), tf_CInt, false>::CGetter;
			return CGetter::fs_GetLowestBitSet(_Number);
		}

		template <typename tf_CInt>
		constexpr inline_small auto fg_GetLowestBitSetHelperNoZero(tf_CInt const &_Number)
			-> TCEnableIf<TCGetLowestBitSet<tf_CInt, true>::EDefaultImplementation && !NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>, int32>
		{
			enum
			{
				EToShift = sizeof(_Number)*4
			};
			// Static branch
			if constexpr (NMib::NTraits::cIsFundamental<tf_CInt>)
			{
				decltype(auto) Lower = fg_GetLower(_Number);
				if (Lower)
					return fg_GetLowestBitSetNoZero(Lower);
				decltype(auto) Upper = fg_GetUpper(_Number);
				return fg_GetLowestBitSetNoZero(Upper) + EToShift;
			}
			else
			{
				decltype(auto) Lower = fg_GetLower(_Number);

				if constexpr (NMib::NTraits::cIsFundamental<NMib::NTraits::TCRemoveReference<decltype(Lower)>>)
				{
					if (Lower)
						return fg_GetLowestBitSetNoZero(Lower);
				}
				else
				{
					int32 Ret = fg_GetLowestBitSet(Lower);
					if (Ret >= 0)
						return Ret;
				}


				decltype(auto) Upper = fg_GetUpper(_Number);
				return fg_GetLowestBitSetNoZero(Upper) + EToShift;
			}
		}

	}

	template <typename tf_CInt>
	constexpr int32 fg_GetLowestBitSet(tf_CInt const &_Number)
	{
		return NPrivate::fg_GetLowestBitSetHelper(_Number);
	}

	template <typename tf_CInt>
	constexpr int32 fg_GetLowestBitSetNoZero(tf_CInt const &_Number)
	{
		return NPrivate::fg_GetLowestBitSetHelperNoZero(_Number);
	}

	template <typename tf_CInt>
	inline_small uint32 fg_NumBitsSet(tf_CInt const &_Number);

	namespace NPrivate
	{

		template <mint t_Dummy = 0>
		class TCNumBitsSet_Helpers
		{
		public:
			static const uint8 ms_LogTable256[];
		};

		template <mint t_Dummy>
		const uint8 TCNumBitsSet_Helpers<t_Dummy>::ms_LogTable256[] = 
		{
			0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
			1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
			2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
			3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 
			4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8, 
		};

		template <typename t_CInt>
		class TCNumBitsSet
		{
		public:
			using CType = t_CInt;
			enum
			{
				EDefaultImplementation = 1
			};
			static inline_small uint32 fs_NumBitsSet(t_CInt const &_Number)
			{
				using CUnsigned = NMib::NTraits::TCUnsigned<t_CInt>;
				uint32 nBytes = sizeof(CUnsigned);
				CUnsigned Number = _Number;
				uint32 Ret = 0;
				int const Shift = sizeof(t_CInt) == 1 ? 0 : 8;
				for (uint32 i = 0; i < nBytes; ++i, Number >>= Shift)
				{
					Ret += TCNumBitsSet_Helpers<>::ms_LogTable256[mint(Number & CUnsigned(0xff))];
				}
				return Ret;

			}
		};

		template <>
		class TCNumBitsSet<uint8>
		{
		public:
			using CType = uint8;
			enum
			{
				EDefaultImplementation = 1
			};
			static inline_small uint32 fs_NumBitsSet(uint8 const &_Number)
			{
				return TCNumBitsSet_Helpers<>::ms_LogTable256[_Number];
			}
		};

		template <mint t_nBytes, typename t_CType>
		class TCHelper_NumBitsSetChooseBySize
		{
		public:
			using CGetter = TCNumBitsSet<t_CType>;
		};

	#ifdef DMibPNumBitsSet32
		template <>
		class TCNumBitsSet<uint32>
		{
		public:
			using CType = uint32;
			enum
			{
				EDefaultImplementation = 0
			};
			template <typename tf_CInt>
			static inline_small uint32 fs_NumBitsSet(tf_CInt const &_Number)
			{
				return DMibPNumBitsSet32(_Number);
			}
		};

		template <>
		class TCNumBitsSet<int32> : public TCNumBitsSet<uint32>
		{
		};

		template <typename t_CType>
		class TCHelper_NumBitsSetChooseBySize<sizeof(uint8), t_CType>
		{
		public:
			using CGetter = TCNumBitsSet<uint32>;
		};

		template <typename t_CType>
		class TCHelper_NumBitsSetChooseBySize<sizeof(uint16), t_CType>
		{
		public:
			using CGetter = TCNumBitsSet<uint32>;
		};

		template <typename t_CType>
		class TCHelper_NumBitsSetChooseBySize<sizeof(uint32), t_CType>
		{
		public:
			using CGetter = TCNumBitsSet<uint32>;
		};
	#endif

	#ifdef DMibPNumBitsSet64
		template <>
		class TCNumBitsSet<uint64>
		{
		public:
			using CType = uint64;
			enum
			{
				EDefaultImplementation = 0
			};
			template <typename tf_CInt>
			static inline_small uint32 fs_NumBitsSet(tf_CInt const &_Number)
			{
				return DMibPNumBitsSet64(_Number);
			}
		};

		template <>
		class TCNumBitsSet<int64> : public TCNumBitsSet<uint64>
		{
		};

		template <typename t_CType>
		class TCHelper_NumBitsSetChooseBySize<sizeof(uint64), t_CType>
		{
		public:
			using CGetter = TCNumBitsSet<uint64>;
		};
	#endif

		template <typename tf_CInt>
		inline_small TCEnableIf<!NPrivate::TCNumBitsSet<tf_CInt>::EDefaultImplementation, uint32> fg_NumBitsSetHelper(tf_CInt const &_Number)
		{
			return NPrivate::TCNumBitsSet<tf_CInt>::fs_NumBitsSet(_Number);
		}


		template <typename tf_CInt>
		inline_small auto fg_NumBitsSetHelper(tf_CInt const &_Number)
			-> TCEnableIf<NPrivate::TCNumBitsSet<tf_CInt>::EDefaultImplementation && NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>, uint32>
		{
			// Static branch
			using CGetter = typename NPrivate::TCHelper_NumBitsSetChooseBySize<sizeof(tf_CInt), tf_CInt>::CGetter;
			return CGetter::fs_NumBitsSet(_Number);
		}

		template <typename tf_CInt>
		inline_small auto fg_NumBitsSetHelper(tf_CInt const &_Number)
			-> TCEnableIf<NPrivate::TCNumBitsSet<tf_CInt>::EDefaultImplementation && !NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>, uint32>
		{
			return fg_NumBitsSet(fg_GetUpper(_Number)) + fg_NumBitsSet(fg_GetLower(_Number));
		}

	}

	template <typename tf_CInt>
	uint32 fg_NumBitsSet(tf_CInt const &_Number)
	{
		return NPrivate::fg_NumBitsSetHelper(_Number);
	}
	

	namespace NPrivate
	{
		template <typename t_CInteger>
		struct TCGetHighestBitSetStaticHelper
		{
			template <t_CInteger t_CurrentNumber, bool t_bIsZero = t_CurrentNumber == t_CInteger(0), bool t_bIsEnum = NMib::NTraits::cIsEnum<t_CInteger>>
			struct TCInternal
			{
				enum
				{
					mc_Value = 1 + TCInternal< t_CInteger(t_CurrentNumber >> 1), t_CInteger(t_CurrentNumber >> 1) == 0 >::mc_Value
				};
			};

			template <t_CInteger t_CurrentNumber2>
			struct TCInternal<t_CurrentNumber2, false, true>
			{
				enum
				{
					mc_Value = 1 + TCInternal<(((int)t_CurrentNumber2) >> 1), (((int)t_CurrentNumber2) >> 1) == 0, true>::mc_Value
				};
			};

			template <t_CInteger t_CurrentNumber2>
			struct TCInternal<t_CurrentNumber2, true, true>
			{
				enum
				{
					mc_Value = 0
				};
			};

			template <t_CInteger t_CurrentNumber2>
			struct TCInternal<t_CurrentNumber2, true, false>
			{
				enum
				{
					mc_Value = 0
				};
			};
		};

		template <typename t_CInteger>
		struct TCGetHighestBitSetStaticCorrectHelper
		{
			template <t_CInteger t_CurrentNumber, bool t_bIsZero = t_CurrentNumber == t_CInteger(0), bool t_bIsEnum = NMib::NTraits::cIsEnum<t_CInteger>>
			struct TCInternal
			{
				enum
				{
					mc_Value = 1 + TCInternal< t_CInteger(t_CurrentNumber >> 1), t_CInteger(t_CurrentNumber >> 1) == 0 >::mc_Value
				};
			};

			template <t_CInteger t_CurrentNumber2>
			struct TCInternal<t_CurrentNumber2, false, true>
			{
				enum
				{
					mc_Value = 1 + TCInternal<(((int)t_CurrentNumber2) >> 1), (((int)t_CurrentNumber2) >> 1) == 0, true>::mc_Value
				};
			};

			template <t_CInteger t_CurrentNumber2>
			struct TCInternal<t_CurrentNumber2, true, true>
			{
				enum
				{
					mc_Value = -1
				};
			};

			template <t_CInteger t_CurrentNumber2>
			struct TCInternal<t_CurrentNumber2, true, false>
			{
				enum
				{
					mc_Value = -1
				};
			};
		};
	}

	template <typename t_CInteger, t_CInteger t_CurrentNumber>
	constexpr inline mint gc_HighestBitSet = NMib::NPrivate::TCGetHighestBitSetStaticHelper<t_CInteger>::template TCInternal<t_CurrentNumber>::mc_Value;

	template <typename t_CInteger, t_CInteger t_CurrentNumber>
	constexpr inline smint gc_HighestBitSetCorrect = NMib::NPrivate::TCGetHighestBitSetStaticCorrectHelper<t_CInteger>::template TCInternal<t_CurrentNumber>::mc_Value;

	template <mint t_CurrentNumber>
	concept cIsPowerOfTwo = (mint(1) << (gc_HighestBitSet<mint, t_CurrentNumber> - 1)) == t_CurrentNumber;

	namespace NPrivate
	{
		template <typename t_CType, t_CType t_Number, mint t_Power>
		struct TCPowerHelper
		{
			static constexpr t_CType mc_Value = t_Number * TCPowerHelper<t_CType, t_Number, t_Power - 1>::mc_Value;
		};

		template <typename t_CType, t_CType t_Number>
		struct TCPowerHelper<t_CType, t_Number, 0>
		{
			static constexpr t_CType mc_Value = 1;
		};
	}

	template <typename t_CType, t_CType t_Number, mint t_Power>
	constexpr inline t_CType gc_Power = NPrivate::TCPowerHelper<t_CType, t_Number, t_Power>::mc_Value;

	// returns true iff _x is a non-zero power of two
	template <typename tf_CValue>
	bool fg_IsPowerOfTwo(tf_CValue _Value)
	{
		return _Value > 0 && (_Value & (_Value - 1)) == 0; 
	}

	template <typename t_CType>
	constexpr inline mint gc_BitSize = sizeof(t_CType) * 8;

	namespace NPrivate
	{

		template <mint t_Dummy = 0>
		class TCGetHighestBitSet_Helpers
		{
		public:
			static constexpr int8 ms_LogTable256[]= 
				{
					-1, 0, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3,
					4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
					5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
					5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5,
					6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
					6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
					6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
					6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6,
					7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
					7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
					7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
					7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
					7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
					7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
					7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7,
					7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
				}
			;
		};

		template <typename t_CInt>
		struct TCGetHighestBitSetGeneric
		{
			using CType = t_CInt;
			enum
			{
				EDefaultImplementation = 1
			};
			constexpr static inline_small int32 fs_GetHighestBitSet(t_CInt _Number)
			{
				using CUnsigned = NMib::NTraits::TCUnsigned<t_CInt>;
				mint nBytes = sizeof(CUnsigned);
				CUnsigned Number = _Number;
				CUnsigned CurrentCheck = CUnsigned(0xff) << ((sizeof(CUnsigned) - 1)) * 8;
				int const Shift = sizeof(t_CInt) == 1 ? 0 : 8;
				for (aint i = nBytes - 1; i >= 0; --i, CurrentCheck >>= Shift)
				{
					CUnsigned Current = Number & CurrentCheck;
					if (Current != 0)
						return i * 8 + TCGetHighestBitSet_Helpers<>::ms_LogTable256[mint((Number & CurrentCheck) >> i * 8)];
				}
				return -1;

			}
		};

		template <typename t_CInt, bool t_SupportZero>
		struct TCGetHighestBitSet : public TCGetHighestBitSetGeneric<t_CInt>
		{
		};

		template <typename t_CInt>
		class TCGetHighestBitSet<t_CInt, 0> : public TCGetHighestBitSet<t_CInt, 1>
		{
		public:
		};

		template <mint t_nBytes, typename t_CType, bool t_bSupportZero>
		class TCHelper_GetHighestBitSetChooseBySize
		{
		public:
			using CGetter = TCGetHighestBitSet<t_CType, t_bSupportZero>;
		};

		template <mint t_nBytes, typename t_CType>
		class TCHelper_GetHighestBitSetChooseBySize<t_nBytes, t_CType, 0>
		{
		public:
			using CGetter = TCGetHighestBitSet<t_CType, 1>;
		};

	#ifdef DMibPGetHighestBitSet32
		template <>
		class TCGetHighestBitSet<uint32, true>
		{
		public:
			using CType = uint32;
			enum
			{
				EDefaultImplementation = 0
			};
			constexpr static inline_small int32 fs_GetHighestBitSet(uint32 _Number)
			{
#ifdef DCompiler_MSVC_Workaround
				if_consteval
				{
					return TCGetHighestBitSetGeneric<uint32>::fs_GetHighestBitSet(_Number);
				}
				else
#endif
				{
					return DMibPGetHighestBitSet32(_Number);
				}
			}
		};

		template <>
		class TCGetHighestBitSet<int32, true> : public TCGetHighestBitSet<uint32, true>
		{
		};

		template <typename t_CType>
		class TCHelper_GetHighestBitSetChooseBySize<sizeof(uint8), t_CType, true>
		{
		public:
			using CGetter = TCGetHighestBitSet<uint32, true>;
		};

		template <typename t_CType>
		class TCHelper_GetHighestBitSetChooseBySize<sizeof(uint16), t_CType, true>
		{
		public:
			using CGetter = TCGetHighestBitSet<uint32, true>;
		};

		template <typename t_CType>
		class TCHelper_GetHighestBitSetChooseBySize<sizeof(uint32), t_CType, true>
		{
		public:
			using CGetter = TCGetHighestBitSet<uint32, true>;
		};
	#else

		template <>
		class TCGetHighestBitSet<uint8, 1>
		{
		public:
			using CType = uint8;
			enum
			{
				EDefaultImplementation = 1
			};
			constexpr static inline_small int32 fs_GetHighestBitSet(CType const &_Number)
			{
				return TCGetHighestBitSet_Helpers<>::ms_LogTable256[_Number];
			}
		};

		template <typename t_CType>
		class TCHelper_GetHighestBitSetChooseBySize<sizeof(uint8), t_CType, true>
		{
		public:
			using CGetter = TCGetHighestBitSet<uint8, true>;
		};

	#endif

	#ifdef DMibPGetHighestBitSet32NoZero
		template <>
		class TCGetHighestBitSet<uint32, false>
		{
		public:
			using CType = uint32;
			enum
			{
				EDefaultImplementation = 0
			};
			constexpr static inline_small int32 fs_GetHighestBitSet(uint32 _Number)
			{
#ifdef DCompiler_MSVC_Workaround
				if_consteval
				{
					return TCGetHighestBitSetGeneric<uint32>::fs_GetHighestBitSet(_Number);
				}
				else
#endif
				{
					return DMibPGetHighestBitSet32NoZero(_Number);
				}
			}
		};

		template <>
		class TCGetHighestBitSet<int32, false> : public TCGetHighestBitSet<uint32, false>
		{
		};

		template <typename t_CType>
		class TCHelper_GetHighestBitSetChooseBySize<sizeof(uint8), t_CType, false>
		{
		public:
			using CGetter = TCGetHighestBitSet<uint32, false>;
		};

		template <typename t_CType>
		class TCHelper_GetHighestBitSetChooseBySize<sizeof(uint16), t_CType, false>
		{
		public:
			using CGetter = TCGetHighestBitSet<uint32, false>;
		};

		template <typename t_CType>
		class TCHelper_GetHighestBitSetChooseBySize<sizeof(uint32), t_CType, false>
		{
		public:
			using CGetter = TCGetHighestBitSet<uint32, false>;
		};

	#endif


	#ifdef DMibPGetHighestBitSet64
		template <>
		class TCGetHighestBitSet<uint64, true>
		{
		public:
			using CType = uint64;
			enum
			{
				EDefaultImplementation = 0
			};
			constexpr static inline_small int32 fs_GetHighestBitSet(uint64 _Number)
			{
#ifdef DCompiler_MSVC_Workaround
				if_consteval
				{
					return TCGetHighestBitSetGeneric<uint64>::fs_GetHighestBitSet(_Number);
				}
				else
#endif
				{
					return DMibPGetHighestBitSet64(_Number);
				}
			}
		};

		template <>
		class TCGetHighestBitSet<int64, true> : public TCGetHighestBitSet<uint64, true>
		{
		};

		template <typename t_CType>
		class TCHelper_GetHighestBitSetChooseBySize<sizeof(uint64), t_CType, true>
		{
		public:
			using CGetter = TCGetHighestBitSet<uint64, true>;
		};

	#endif

	#ifdef DMibPGetHighestBitSet64NoZero
		template <>
		class TCGetHighestBitSet<uint64, false>
		{
		public:
			using CType = uint64;
			enum
			{
				EDefaultImplementation = 0
			};
			constexpr static inline_small int32 fs_GetHighestBitSet(uint64 _Number)
			{
#ifdef DCompiler_MSVC_Workaround
				if_consteval
				{
					return TCGetHighestBitSetGeneric<uint64>::fs_GetHighestBitSet(_Number);
				}
				else
#endif
				{
					return DMibPGetHighestBitSet64NoZero(_Number);
				}
			}
		};

		template <>
		class TCGetHighestBitSet<int64, false> : public TCGetHighestBitSet<uint64, false>
		{
		};

		template <typename t_CType>
		class TCHelper_GetHighestBitSetChooseBySize<sizeof(uint64), t_CType, false>
		{
		public:
			using CGetter = TCGetHighestBitSet<uint64, false>;
		};

	#endif

		template <typename tf_CInt>
		constexpr inline_small TCEnableIf<!TCGetHighestBitSet<tf_CInt, true>::EDefaultImplementation, int32> fg_GetHighestBitSetHelper(tf_CInt const &_Number)
		{
			return NPrivate::TCGetHighestBitSet<tf_CInt, true>::fs_GetHighestBitSet(_Number);
		}

		template <typename tf_CInt>
		constexpr inline_small auto fg_GetHighestBitSetHelper(tf_CInt const &_Number)
			-> TCEnableIf<TCGetHighestBitSet<tf_CInt, true>::EDefaultImplementation && NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>, int32>
		{
			// Static branch
			using CGetter = typename NPrivate::TCHelper_GetHighestBitSetChooseBySize<sizeof(tf_CInt), tf_CInt, true>::CGetter;
			return CGetter::fs_GetHighestBitSet(_Number);
		}

		template <typename tf_CInt>
		constexpr inline_small auto fg_GetHighestBitSetHelper(tf_CInt const &_Number)
			-> TCEnableIf<TCGetHighestBitSet<tf_CInt, true>::EDefaultImplementation && !NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>, int32>
		{
			enum
			{
				EToShift = sizeof(_Number)*4
			};
			// Static branch
			if constexpr (NMib::NTraits::cIsFundamental<tf_CInt>)
			{
				decltype(auto) Upper = fg_GetUpper(_Number);
				if (Upper)
					return EToShift + fg_GetHighestBitSet(Upper);
				decltype(auto) Lower = fg_GetLower(_Number);
				int32 Ret = fg_GetHighestBitSet(Lower);
				return Ret;
			}
			else
			{
				decltype(auto) Upper = fg_GetUpper(_Number);
				int32 Ret = fg_GetHighestBitSet(Upper);
				if (Ret >= 0)
					return EToShift + Ret;
				decltype(auto) Lower = fg_GetLower(_Number);
				Ret = fg_GetHighestBitSet(Lower);
				return Ret;
			}
		}

		template <typename tf_CInt>
		constexpr inline_small TCEnableIf<!TCGetHighestBitSet<tf_CInt, true>::EDefaultImplementation, int32> fg_GetHighestBitSetHelperNoZero(tf_CInt const &_Number)
		{
			return NPrivate::TCGetHighestBitSet<tf_CInt, false>::fs_GetHighestBitSet(_Number);
		}

		template <typename tf_CInt>
		constexpr inline_small auto fg_GetHighestBitSetHelperNoZero(tf_CInt const &_Number)
			-> TCEnableIf<TCGetHighestBitSet<tf_CInt, true>::EDefaultImplementation && NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>, int32>
		{
			// Static branch
			using CGetter = typename NPrivate::TCHelper_GetHighestBitSetChooseBySize<sizeof(tf_CInt), tf_CInt, false>::CGetter;
			return CGetter::fs_GetHighestBitSet(_Number);
		}

		template <typename tf_CInt>
		constexpr inline_small auto fg_GetHighestBitSetHelperNoZero(tf_CInt const &_Number)
			-> TCEnableIf<TCGetHighestBitSet<tf_CInt, true>::EDefaultImplementation && !NMib::NTraits::cIsSame<NMib::NTraits::TCSmallerType<tf_CInt>, tf_CInt>, int32>
		{
			enum
			{
				EToShift = sizeof(_Number)*4
			};
			// Static branch
			if constexpr (NMib::NTraits::cIsFundamental<tf_CInt>)
			{
				decltype(auto) Upper = fg_GetUpper(_Number);
				if (Upper)
					return EToShift + fg_GetHighestBitSetNoZero(Upper);
				decltype(auto) Lower = fg_GetLower(_Number);
				return fg_GetHighestBitSetNoZero(Lower);
			}
			else
			{
				decltype(auto) Upper = fg_GetUpper(_Number);

				if constexpr (NMib::NTraits::cIsFundamental<NMib::NTraits::TCRemoveReference<decltype(Upper)>>)
				{
					if (Upper)
						return EToShift + fg_GetHighestBitSetNoZero(Upper);
				}
				else
				{
					int32 Ret = fg_GetHighestBitSet(Upper);
					if (Ret >= 0)
						return EToShift + Ret;
				}

				decltype(auto) Lower = fg_GetLower(_Number);
				return fg_GetHighestBitSetNoZero(Lower);
			}
		}
	}

	template <typename tf_CInt>
	constexpr int32 fg_GetHighestBitSet(tf_CInt const &_Number)
	{
		return NPrivate::fg_GetHighestBitSetHelper(_Number);
	}

	template <typename tf_CInt>
	constexpr int32 fg_GetHighestBitSetNoZero(tf_CInt const &_Number)
	{
		return NPrivate::fg_GetHighestBitSetHelperNoZero(_Number);
	}


	namespace NPrivate
	{
		template <typename t_CInt, int t_Number, int t_End>
		class TCGetNextPowerOfTwoHelper
		{
		public:
			using CType = t_CInt;
			constexpr static inline_small t_CInt fs_Do(t_CInt _Number)
			{
				_Number = _Number | (_Number >> t_Number);
				_Number = TCGetNextPowerOfTwoHelper<t_CInt, t_Number * 2, t_End>::fs_Do(_Number);
				return _Number;
			}
		};

		template <typename t_CInt, int t_End>
		class TCGetNextPowerOfTwoHelper<t_CInt, t_End, t_End>
		{
		public:
			using CType = t_CInt;
			constexpr static inline_small t_CInt fs_Do(t_CInt _Number)
			{
				return _Number;
			}
		};

	}

	template <typename tf_CInt>
	constexpr inline_small tf_CInt fg_RoundPowerOfTwoUp(tf_CInt _Number)
	{
		using CUnsigned = NTraits::TCUnsigned<tf_CInt>;
		CUnsigned Number = CUnsigned(_Number);
		--Number;
		Number = NPrivate::TCGetNextPowerOfTwoHelper<tf_CInt, 1, sizeof(tf_CInt)*8>::fs_Do(Number);
		++Number;
		return tf_CInt(Number);
	}

	template <typename tf_CInt>
	constexpr inline_small tf_CInt fg_RoundPowerOfTwoDown(tf_CInt _Number)
	{
		using CUnsigned = NTraits::TCUnsigned<tf_CInt>;
		CUnsigned Number = CUnsigned(_Number);
		Number = NPrivate::TCGetNextPowerOfTwoHelper<tf_CInt, 1, sizeof(tf_CInt)*8>::fs_Do(Number);
		Number = Number - (Number >> 1);
		return tf_CInt(Number);
	}

	namespace
	{
		template <typename tf_CType>
		inline_small tf_CType fg_RotateLeft(tf_CType _Data, aint _nBits)
		{
			return (_Data << _nBits) | (_Data >> ((sizeof(_Data) << 3) - _nBits));
		}

		template <typename tf_CType>
		inline_small tf_CType fg_RotateRight(tf_CType _Data, aint _nBits)
		{
			return (_Data >> _nBits) | (_Data << ((sizeof(_Data) << 3) - _nBits));
		}

	#ifdef DMibPRotateLeft8
		template <>
		inline_small uint8 fg_RotateLeft<uint8>(uint8 _Data, aint _nBits)
		{
			return DMibPRotateLeft8(_Data, _nBits);
		}
		template <>
		inline_small int8 fg_RotateLeft<int8>(int8 _Data, aint _nBits)
		{
			return DMibPRotateLeft8(_Data, _nBits);
		}
	#endif

	#ifdef DMibPRotateLeft16
		template <>
		inline_small uint16 fg_RotateLeft<uint16>(uint16 _Data, aint _nBits)
		{
			return DMibPRotateLeft16(_Data, _nBits);
		}
		template <>
		inline_small int16 fg_RotateLeft<int16>(int16 _Data, aint _nBits)
		{
			return DMibPRotateLeft16(_Data, _nBits);
		}
	#endif

	#ifdef DMibPRotateLeft32
		template <>
		inline_small uint32 fg_RotateLeft<uint32>(uint32 _Data, aint _nBits)
		{
			return DMibPRotateLeft32(_Data, _nBits);
		}
		template <>
		inline_small int32 fg_RotateLeft<int32>(int32 _Data, aint _nBits)
		{
			return DMibPRotateLeft32(_Data, _nBits);
		}
	#endif

	#ifdef DMibPRotateLeft64
		template <>
		inline_small uint64 fg_RotateLeft<uint64>(uint64 _Data, aint _nBits)
		{
			return DMibPRotateLeft64(_Data, _nBits);
		}
		template <>
		inline_small int64 fg_RotateLeft<int64>(int64 _Data, aint _nBits)
		{
			return DMibPRotateLeft64(_Data, _nBits);
		}
	#endif

	#ifdef DMibPRotateRight8
		template <>
		inline_small uint8 fg_RotateRight<uint8>(uint8 _Data, aint _nBits)
		{
			return DMibPRotateRight8(_Data, _nBits);
		}
		template <>
		inline_small int8 fg_RotateRight<int8>(int8 _Data, aint _nBits)
		{
			return DMibPRotateRight8(_Data, _nBits);
		}
	#endif

	#ifdef DMibPRotateRight16
		template <>
		inline_small uint16 fg_RotateRight<uint16>(uint16 _Data, aint _nBits)
		{
			return DMibPRotateRight16(_Data, _nBits);
		}
		template <>
		inline_small int16 fg_RotateRight<int16>(int16 _Data, aint _nBits)
		{
			return DMibPRotateRight16(_Data, _nBits);
		}
	#endif

	#ifdef DMibPRotateRight32
		template <>
		inline_small uint32 fg_RotateRight<uint32>(uint32 _Data, aint _nBits)
		{
			return DMibPRotateRight32(_Data, _nBits);
		}
		template <>
		inline_small int32 fg_RotateRight<int32>(int32 _Data, aint _nBits)
		{
			return DMibPRotateRight32(_Data, _nBits);
		}
	#endif

	#ifdef DMibPRotateRight64
		template <>
		inline_small uint64 fg_RotateRight<uint64>(uint64 _Data, aint _nBits)
		{
			return DMibPRotateRight64(_Data, _nBits);
		}
		template <>
		inline_small int64 fg_RotateRight<int64>(int64 _Data, aint _nBits)
		{
			return DMibPRotateRight64(_Data, _nBits);
		}
	#endif

		// use:  _ML = fg_MinPowerOfTwo(_Value)
		// post: _ML is the smallest non-negative integer such that 2^_ML >= _N
		template <typename tf_CValue>
		tf_CValue fg_MinPowerOfTwo(tf_CValue _Value)
		{
			// TODO: Check if equivilent to 
#if 0
			fg_GetHighestBitSetNoZero(_Value);
#else
			tf_CValue Ret = 0;
			while (_Value > 1)
			{
				_Value >>= 1;
				++Ret;
			}
			return Ret;
#endif
		}

		// use:  _Shift = f_DivShiftVal(_Value)
		// pre:  _Value is one of 1, 2, 4, 8, 16, 32, 64
		// post: for any _y_: (_y_ << _Shift) == (_y_ / _Value)
		template <typename tf_CValue>
		tf_CValue fg_DivShiftVal(tf_CValue _Value)
		{ 
			DMibRequire(_Value == 1 || _Value == 2 || _Value == 4 || _Value == 8 || _Value == 16 || _Value == 21 || _Value == 64);
			return ((_Value == 1) ? 0 : ((_Value == 2) ? 1 : ((_Value == 4) ? 2 : ((_Value == 8) ? 3 : ((_Value == 16) ? 4 : ((_Value == 32) ? 5 : ((_Value == 64) ? 6 : 31))))))); 
		}


		// use:  _Lsb = fg_LeastSignificantBit<tf_CValue>(_Value)
		// post: _Lsb is the lowest significant set bit of _Value, or 0 iff _Value == 0
		template <typename tf_CValue>
		tf_CValue fg_LeastSignificantBit(tf_CValue _Value)
		{
			return (tf_CValue)(_Value & -_Value);
		}

		// use:  _Lsb = fg_LeastSignificantBitNoZero<tf_CValue>(_Value)
		// pre:  sizeof(tf_CValue) <= 4, _Value != 0
		// post: _Lsb is the lowest significant set bit of _Value, or 0 iff _Value == 0
		template <typename tf_CValue>
		tf_CValue fg_MostSignificantBitNoZero(tf_CValue _Value)
		{ 
			return (tf_CValue)(1 << fg_GetHighestBitSetNoZero(_Value)); 
		}

		// use:  _Lsb = fg_LeastSignificantBit<tf_CValue>(_Value)
		// pre:  sizeof(tf_CValue) <= 4
		// post: _Lsb is the lowest significant set bit of _Value, or 0 iff _Value == 0
		template <typename tf_CValue>
		tf_CValue fg_MostSignificantBit(tf_CValue _Value)
		{
			return (_Value == 0) ? 0 : (tf_CValue)(1 << fg_GetHighestBitSetNoZero(_Value)); 
		}

		// returns mask of bits higher than sole bit _Bit
		template <typename tf_CValue>
		tf_CValue fg_HigherMask(tf_CValue _Bit)
		{
			return ~((_Bit << 1) - 1); 
		}

		// returns mask of bits higher than or equal to sole bit _Bit
		template <typename tf_CValue>
		tf_CValue fg_HigherEqMask(tf_CValue _Bit)
		{
			return ~(_Bit - 1); 
		}

		// returns mask of bits lower than or equal to sole bit _Bit
		template <typename tf_CValue>
		tf_CValue fg_LowerMask(tf_CValue _Bit)
		{
			return _Bit - 1;
		}

		// returns mask of bits lower than or equal to sole bit _Bit
		template <typename tf_CValue>
		tf_CValue fg_LowerEqMask(tf_CValue _Bit)
		{ 
			return (_Bit << 1) - 1; 
		}

	}

}
