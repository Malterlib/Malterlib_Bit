// Copyright © 2026 Unborken AB
// Distributed under the MIT license, see license text in LICENSE.Malterlib

#pragma once

namespace NMib
{
	template <typename tf_CType>
	constexpr inline_small tf_CType fg_RotateLeft(tf_CType _Data, aint _nBits) noexcept
	{
		return (_Data << _nBits) | (_Data >> ((sizeof(_Data) << 3) - _nBits));
	}

	template <typename tf_CType>
	constexpr inline_small tf_CType fg_RotateRight(tf_CType _Data, aint _nBits) noexcept
	{
		return (_Data >> _nBits) | (_Data << ((sizeof(_Data) << 3) - _nBits));
	}

#ifdef DMibPRotateLeft8
	template <>
	constexpr inline_small uint8 fg_RotateLeft<uint8>(uint8 _Data, aint _nBits) noexcept
	{
		return DMibPRotateLeft8(_Data, _nBits);
	}

	template <>
	constexpr inline_small int8 fg_RotateLeft<int8>(int8 _Data, aint _nBits) noexcept
	{
		return DMibPRotateLeft8(_Data, _nBits);
	}
#endif

#ifdef DMibPRotateLeft16
	template <>
	constexpr inline_small uint16 fg_RotateLeft<uint16>(uint16 _Data, aint _nBits) noexcept
	{
		return DMibPRotateLeft16(_Data, _nBits);
	}

	template <>
	constexpr inline_small int16 fg_RotateLeft<int16>(int16 _Data, aint _nBits) noexcept
	{
		return DMibPRotateLeft16(_Data, _nBits);
	}
#endif

#ifdef DMibPRotateLeft32
	template <>
	constexpr inline_small uint32 fg_RotateLeft<uint32>(uint32 _Data, aint _nBits) noexcept
	{
		return DMibPRotateLeft32(_Data, _nBits);
	}

	template <>
	constexpr inline_small int32 fg_RotateLeft<int32>(int32 _Data, aint _nBits) noexcept
	{
		return DMibPRotateLeft32(_Data, _nBits);
	}
#endif

#ifdef DMibPRotateLeft64
	template <>
	constexpr inline_small uint64 fg_RotateLeft<uint64>(uint64 _Data, aint _nBits) noexcept
	{
		return DMibPRotateLeft64(_Data, _nBits);
	}

	template <>
	constexpr inline_small int64 fg_RotateLeft<int64>(int64 _Data, aint _nBits) noexcept
	{
		return DMibPRotateLeft64(_Data, _nBits);
	}
#endif

#ifdef DMibPRotateRight8
	template <>
	constexpr inline_small uint8 fg_RotateRight<uint8>(uint8 _Data, aint _nBits) noexcept
	{
		return DMibPRotateRight8(_Data, _nBits);
	}

	template <>
	constexpr inline_small int8 fg_RotateRight<int8>(int8 _Data, aint _nBits) noexcept
	{
		return DMibPRotateRight8(_Data, _nBits);
	}
#endif

#ifdef DMibPRotateRight16
	template <>
	constexpr inline_small uint16 fg_RotateRight<uint16>(uint16 _Data, aint _nBits) noexcept
	{
		return DMibPRotateRight16(_Data, _nBits);
	}

	template <>
	constexpr inline_small int16 fg_RotateRight<int16>(int16 _Data, aint _nBits) noexcept
	{
		return DMibPRotateRight16(_Data, _nBits);
	}
#endif

#ifdef DMibPRotateRight32
	template <>
	constexpr inline_small uint32 fg_RotateRight<uint32>(uint32 _Data, aint _nBits) noexcept
	{
		return DMibPRotateRight32(_Data, _nBits);
	}

	template <>
	constexpr inline_small int32 fg_RotateRight<int32>(int32 _Data, aint _nBits) noexcept
	{
		return DMibPRotateRight32(_Data, _nBits);
	}
#endif

#ifdef DMibPRotateRight64
	template <>
	constexpr inline_small uint64 fg_RotateRight<uint64>(uint64 _Data, aint _nBits) noexcept
	{
		return DMibPRotateRight64(_Data, _nBits);
	}

	template <>
	constexpr inline_small int64 fg_RotateRight<int64>(int64 _Data, aint _nBits) noexcept
	{
		return DMibPRotateRight64(_Data, _nBits);
	}
#endif
}
