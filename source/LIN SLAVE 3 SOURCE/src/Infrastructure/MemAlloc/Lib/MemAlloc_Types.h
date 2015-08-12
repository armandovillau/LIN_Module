/*******************************************************************************/
/**
\file       MemAlloc_Types.h
\brief      Memowy Allocation header file
\author     Francisco Martinez
\version    1.0
\date       08/07/2015
*/
/*******************************************************************************/
#ifndef __MEMALLOC_TYPES_H
#define  __MEMALLOC_TYPES_H

#include "typedefs.h"

typedef struct
{
	void *MemAllocHeapStartAddr;
	void *MemAllocHeapEndAddr;
}MemAllocConfigType;

#endif /* __MEMALLOC_TYPES_H */