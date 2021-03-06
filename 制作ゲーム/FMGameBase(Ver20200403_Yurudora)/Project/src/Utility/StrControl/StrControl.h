#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	StrControl.h												*/
/*  @brief		:	文字列操作													*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/14													*/
/*																				*/
/*==============================================================================*/


#include<string>

//==========================================================================================
// 後方一致検索
// s : 元の文字列 suffix : 後方一致が含まれるかどうかを判定したい文字列
// return : 一致 true  不一致 false
//==========================================================================================
inline bool Ends_With(const std::string& s, const std::string& suffix) {
	if (s.size() < suffix.size()) return false;
	return std::equal(std::rbegin(suffix), std::rend(suffix), std::rbegin(s));
};
