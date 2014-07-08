//-----------------------------------------------------------------------------
//-- |
//-- Project : Vigenere cipher cracking (KRY project 2012)
//-- Module  : key.h
//-- 
//-- Author  : Mikulka Jiri    <xmikul39>
//--
//-- This module implements guessing of the key based on Friedman and 
//-- Kasiski tests.
//--
//-----------------------------------------------------------------------------

int get_real_key_length(std::string & str, float friedman, int kasiski);
std::string get_key(std::string & str, int key_len);
