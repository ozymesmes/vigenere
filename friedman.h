//-----------------------------------------------------------------------------
//-- |
//-- Project : Vigenere cipher cracking (KRY project 2012)
//-- Module  : friedman.h
//-- 
//-- Author  : Mikulka Jiri    <xmikul39>
//--
//-- This module implements the Friedman test (together with index of 
//-- coincidence)
//--
//-----------------------------------------------------------------------------

#include <map>

float friedman_test(std::string & str);
float index_of_coincidence(std::map<int,int> & freqs, int str_length);
std::map<int,int> letters_freq(std::string & str);


