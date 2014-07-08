//-----------------------------------------------------------------------------
//-- |
//-- Project : Vigenere cipher cracking (KRY project 2012)
//-- Module  : key.cpp
//-- 
//-- Author  : Mikulka Jiri    <xmikul39>
//--
//-- This module implements guessing of the key based on Friedman and 
//-- Kasiski tests.
//--
//-----------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#include "key.h"
#include "kasiski.h"
#include "friedman.h"

#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

using namespace std;

extern float kp;
extern float kr;
static float eps = 0.010;

int alphabet_len = 'z' - 'a' + 1;

// letters frequencies in standard english text
static float letfreq[] = {
  0.08167, 0.01492, 0.02782, 0.04253, 0.12702, // A B C D E
  0.02228, 0.02015, 0.06094, 0.06966, 0.00153, // F G H I J
  0.00772, 0.04025, 0.02406, 0.06749, 0.07507, // K L M N O
  0.01929, 0.00095, 0.05987, 0.06327, 0.09056, // P Q R S T
  0.02758, 0.00978, 0.02360, 0.00150, 0.01974, 0.00074}; // U V W X Y Z

// count average ic from vector of ics
static float
ic_avg( vector<float> & m, int i)
{
    float sum = 0.0;
    for (vector<float>::iterator x = m.begin(); x != m.end(); ++x) sum += *x;
    return sum / float(i);
}

// count ic for specific substring of the given string
static void
substr_ic(string & str, vector<float> & m, int i)
{
    for (int j = 0; j < i; ++j)
    {
      string tmp = "";
      for (size_t k = j; k < str.length(); k += i) tmp += str[k];
      map<int,int> tmp_freq = letters_freq(tmp);
      m.push_back(index_of_coincidence(tmp_freq, tmp.length()));
    }
}

// try to guess the real length of the password
// using knowledge of results of friedman and kasiski tests
int
get_real_key_length(string & str, float friedman, int kasiski)
{
  // this is moreless maximal value for the cycle
  int max = ceil(10 * (friedman + kasiski));

  // the idea of getting the real length of the password
  // is based on repeating (or cycling) the keyword of length `n`
  // which means that average value of i ics for all substrings in
  // step i should be close to the kp ~= 0.065 (for english text)
  // after another i steps (2*i step), the same value should be hit
  // (all other steps should provide ic close to the random text
  // kr ~= 0.038)
  // when the real length is hit twice (twise just for asuring)
  // the loop is finished
  map< int, vector<int> > pos_len;
  for (int i = 1; i <= max; ++i)
  {
    vector<float> m;
    substr_ic(str, m, i);
    double val = fabs(ic_avg(m, i) - kp);
    if      (val >= 0 * eps && val < 1 * eps && pos_len[0].size() < 4) pos_len[0].push_back(i);
    else if (val >= 1 * eps && val < 2 * eps && pos_len[1].size() < 4) pos_len[1].push_back(i);
    else if (val >= 2 * eps && val < 3 * eps && pos_len[2].size() < 4) pos_len[2].push_back(i);
  }

  int key_len = multi_gcd(pos_len[0]);
  if (key_len == 0) key_len = multi_gcd(pos_len[1]);
  if (key_len == 0) key_len = multi_gcd(pos_len[2]);

  return key_len;
}

// for the key len i, break i monoalphabetic substitution ciphers
// and get j-letter of the key
string
get_key(string & str, int key_len)
{
  string key = "";
  
  for (int i = 0; i < key_len; ++i)
  {
    string ci = "";
    for (size_t j = i; j < str.length(); j += key_len) ci += str[j];

    map<int,int> f = letters_freq(ci);

    vector<double> guess;
    for (int g = 0; g < alphabet_len; ++g)
    {
      double sum = 0;
      for (int x = 0; x < alphabet_len; ++x) sum += letfreq[x] * f['A' + (x+g) % alphabet_len];
      sum /= double(ci.length());
      guess.push_back(fabs(sum - kp));
    }
    key += 'a' + int(min_element(guess.begin(), guess.end()) - guess.begin());
  }

  return key;
}
