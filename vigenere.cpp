//-----------------------------------------------------------------------------
//-- |
//-- Project : Vigenere cipher cracking (KRY project 2012)
//-- Module  : vigenere.cpp
//-- 
//-- Author  : Mikulka Jiri    <xmikul39>
//--
//-- This module implements the Vigenere cipher.
//--
//-----------------------------------------------------------------------------


#include <string>

#include "vigenere.h"

using namespace std;

static string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// function which provides Vigenere cipher encryption
// using key
string
encipher(string & plaintext, string & key)
{
  string ciphertext = "";

  int index = 0;
  for (int i = 0; i < int(plaintext.length()); ++i)
  {
    index  = alphabet.find(plaintext[i]);
    index += alphabet.find(key[i % key.length()]);
    index %= alphabet.length();
    ciphertext += alphabet[index];
  }

  return ciphertext;
}

// function which provides Vigenere cipher decryption
// using key
string
decipher(string & ciphertext, string & key)
{
  string plaintext = "";

  int index = 0;
  for (int i = 0; i < int(ciphertext.length()); ++i)
  {
    index  = alphabet.find(ciphertext[i]);
    index -= alphabet.find(key[i % key.length()]);
    index += alphabet.length();
    index %= alphabet.length();
    plaintext += alphabet[index];
  }

  return plaintext;
}
