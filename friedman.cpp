//-----------------------------------------------------------------------------
//-- |
//-- Project : Vigenere cipher cracking (KRY project 2012)
//-- Module  : friedman.cpp
//-- 
//-- Author  : Mikulka Jiri    <xmikul39>
//--
//-- This module implements the Friedman test (together with index of 
//-- coincidence)
//--
//-----------------------------------------------------------------------------
#include <string>

#include "friedman.h"

using namespace std;

// kp based on letter frequinces in english
// http://pages.central.edu/emp/LintonT/classes/spring01/cryptography/letterfreq.html
// kp = sum_i=A^Z (p_i^2)
float kp = 0.0654966995;
static float kr = 1.0 / 26.0;

// counting index of coincidence from letters frenquencies
// and the string length
float
index_of_coincidence(map<int,int> & freqs, int str_length)
{
  float sum = 0.0;
  for (int i = 'A'; i <= 'Z'; ++i) sum += freqs[i] * (freqs[i] - 1.0);
  return sum / (str_length * (str_length - 1.0));
}

// counting letters frequencies in given string
map<int,int>
letters_freq(string & str)
{
  map<int,int> freqs;
  for (int i = 'A'; i <= 'Z'; ++i) freqs[i] = 0;

  for (string::iterator iter = str.begin(); iter != str.end(); ++iter)
    freqs[*iter] += 1;

  return freqs;
}

// friedman test for english ciphertext
// (using kp for english text)
float
friedman_test(string & str)
{
  map<int,int> freqs = letters_freq(str);
  float ko = index_of_coincidence(freqs, str.length());
  return (kp-kr)/(ko-kr);
}
