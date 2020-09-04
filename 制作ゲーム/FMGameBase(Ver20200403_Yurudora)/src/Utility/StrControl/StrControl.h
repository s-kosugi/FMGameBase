#pragma once

/*==============================================================================*/
/*																				*/
/*	@file title	:	StrControl.h												*/
/*  @brief		:	�����񑀍�													*/
/*	@written	:	s.kosugi													*/
/*	@create		:   2019/04/14													*/
/*																				*/
/*==============================================================================*/


#include<string>

//==========================================================================================
// �����v����
// s : ���̕����� suffix : �����v���܂܂�邩�ǂ����𔻒肵����������
// return : ��v true  �s��v false
//==========================================================================================
inline bool Ends_With(const std::string& s, const std::string& suffix) {
	if (s.size() < suffix.size()) return false;
	return std::equal(std::rbegin(suffix), std::rend(suffix), std::rbegin(s));
};
