#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	StrControl.h												*/
/*  @brief		:	•¶š—ñ‘€ì													*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/14													*/
/*																				*/
/*==============================================================================*/


#include<string>

//==========================================================================================
// Œã•ûˆê’vŒŸõ
// s : Œ³‚Ì•¶š—ñ suffix : Œã•ûˆê’v‚ªŠÜ‚Ü‚ê‚é‚©‚Ç‚¤‚©‚ğ”»’è‚µ‚½‚¢•¶š—ñ
// return : ˆê’v true  •sˆê’v false
//==========================================================================================
inline bool Ends_With(const std::string& s, const std::string& suffix) {
	if (s.size() < suffix.size()) return false;
	return std::equal(std::rbegin(suffix), std::rend(suffix), std::rbegin(s));
};
