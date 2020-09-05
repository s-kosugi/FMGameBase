#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	memory.h													*/
/*  @brief		:	ÉÅÉÇÉää÷åWÉ}ÉNÉç											*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2018/09/18													*/
/*																				*/
/*==============================================================================*/

#ifndef NEW
	#ifdef DEBUG
	#define NEW				new( _NORMAL_BLOCK, __FILE__, __LINE__ )
	#else
	#define NEW				new
	#endif
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)			{ if (p!=nullptr) { delete (p);	(p) = nullptr; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)	{ if (p!=nullptr) { delete[] (p);	(p) = nullptr; } }
#endif