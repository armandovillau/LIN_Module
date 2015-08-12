/*******************************************************************************/
/**
\file       MemAlloc_Cfg.c
\brief      Memowy Allocation configuration
\author     Francisco Martinez
\version    1.0
\date       08/07/2015
*/
/*******************************************************************************/

#include "MemAlloc_Cfg.h"

extern const T_ULONG _heap_addr;
extern const T_ULONG _heap_end;


const MemAllocConfigType MemAllocConfig = 
{
	(void*)&_heap_addr,
	(void*)&_heap_end	
};