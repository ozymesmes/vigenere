//-----------------------------------------------------------------------------
//-- |
//-- Project : Vigenere cipher cracking (KRY project 2012)
//-- Module  : main.cpp
//-- 
//-- Author  : Mikulka Jiri    <xmikul39>
//--
//-- This module implements the main function of the program.
//--
//-----------------------------------------------------------------------------

#include <iostream>

#include "friedman.h"
#include "kasiski.h"
#include "key.h"
#include "vigenere.h"

using namespace std;

// reading the ciphertext from stdin
void
read_input (string & str)
{
  string line;
  while (cin)
  {
    getline(cin,line);
    str += line;
  }
}

// removing all non-alphabetic symbols from the input string
// transforming all latters to uppercase
void
clear_input (string & str)
{
  string::iterator it = str.begin();
  while (it != str.end())
  {
    if (!isalpha(*it))
    {
      str.erase(it);
      continue;
    }
    *it = toupper(*it);
    it++;
  }
}

// main function of the program
int
main (int argc __attribute__ ((__unused__)), char ** argv __attribute__ ((__unused__)))
{
  string ciphertext;

  // read and clear the ciphertext
  read_input (ciphertext);
  clear_input (ciphertext);

  // count friedman and kasiski test
  float friedman = friedman_test(ciphertext);
  int kasiski = kasiski_test(ciphertext);

  // guess the real length of the password using results of the
  // friedman and kasiski tests
  int key_length = get_real_key_length(ciphertext, friedman, kasiski);
  string key = get_key(ciphertext, key_length);

  // print results of the cracking
  cout << friedman << ";" << kasiski << ";" << key_length << ";" << key << endl;

  return 0;
}
