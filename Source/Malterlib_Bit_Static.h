// Copyright © 2015 Hansoft AB 
// Distributed under the MIT license, see license text in LICENSE.Malterlib
 
#pragma once

#define DMibBit(d_Bit) (1 << (d_Bit))
#define DMibBitTyped(d_Bit, d_Type) (d_Type(1) << (d_Bit))
#define DMibBitRange(d_BitStart, d_BitEnd) ((((1 << (d_BitEnd)) - 1) | (1 << (d_BitEnd))) ^ ((1 << (d_BitStart)) - 1))
#define DMibBitRangeTyped(d_BitStart, d_BitEnd, d_Type) ((((d_Type(1) << (d_BitEnd)) - d_Type(1)) | (d_Type(1) << (d_BitEnd))) ^ ((d_Type(1) << (d_BitStart)) - d_Type(1)))
#define DMibBitRangeOne(d_BitStart, d_BitEnd, d_One) ((((d_One << (d_BitEnd)) - d_One) | (d_One << (d_BitEnd))) ^ ((d_One << (d_BitStart)) - d_One))

#ifndef DMibPNoShortCuts
#	define DBit(_Bit) DMibBit(_Bit)
#	define DBitTyped(_Bit, _Type) DMibBitTyped(_Bit, _Type)
#	define DBitRange(_BitStart, _BitEnd) DMibBitRange(_BitStart, _BitEnd)
#endif

