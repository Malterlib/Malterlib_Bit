// Copyright © Unbroken AB
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#pragma once

#define DMibBit(d_Bit) (1 << (d_Bit))
#define DMibBitTyped(d_Bit, d_Type) (d_Type(1) << (d_Bit))
#define DMibBitRange(d_BitStart, d_BitEnd) ((((1 << (d_BitEnd)) - 1) | (1 << (d_BitEnd))) ^ ((1 << (d_BitStart)) - 1))
#define DMibBitRangeTyped(d_BitStart, d_BitEnd, d_Type) ((((d_Type(1) << (d_BitEnd)) - d_Type(1)) | (d_Type(1) << (d_BitEnd))) ^ ((d_Type(1) << (d_BitStart)) - d_Type(1)))
#define DMibBitRangeOne(d_BitStart, d_BitEnd, d_One) ((((d_One << (d_BitEnd)) - d_One) | (d_One << (d_BitEnd))) ^ ((d_One << (d_BitStart)) - d_One))

#ifndef DMibPNoShortCuts
#	define DBit(d_Bit) DMibBit(d_Bit)
#	define DBitTyped(d_Bit, d_Type) DMibBitTyped(d_Bit, d_Type)
#	define DBitRange(d_BitStart, d_BitEnd) DMibBitRange(d_BitStart, d_BitEnd)
#endif
