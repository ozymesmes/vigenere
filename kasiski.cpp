//-----------------------------------------------------------------------------
//-- |
//-- Project : Vigenere cipher cracking (KRY project 2012)
//-- Module  : kasiski.cpp
//--
//-- Author  : Mikulka Jiri    <xmikul39>
//--
//-- This module implements the Kasiski test.
//--
//-----------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "kasiski.h"

using namespace std;

static const int FROM = 3;
static const int TO = 6;

// count greatest common divisor of 2 numbers
static int
gcd(int u, int v)
{
    if (v) return gcd(v, u % v);
    else return u < 0 ? -u : u;
}

// count GCD of list of numbers
int
multi_gcd(vector<int> & num)
{
    if      (num.size() == 0) return 0;
    else if (num.size() == 1) return num[0];
    else if (num.size() == 2) return gcd(num[0], num[1]);

    num[1] = gcd(num[0], num[1]);
    num.erase(num.begin());
    return multi_gcd(num);
}

// find all n-grams (FROM-grams ... TO-grams) in linear time (!)
static void
find_ngrams(string & str, map<string, vector<int> > & tgs, int from, int to)
{
    int length = str.length();
    for (int i = 0; i < length; ++i)
    {
        // from each position in str count all n-grams (if possible)
        for (int j = from; j <= to; ++j)
        {
            if (i+j > length) continue;
            string sub = str.substr(i, j);
            tgs[sub].push_back(i);
        }
    }

    // ignore those n-grams which are irrelevant due to insufficient
    // number of occurrences
    map<string, vector<int> >::iterator rem = tgs.begin();
    while (rem != tgs.end())
    {
        if (rem->second.size() < 3) tgs.erase(rem++);
        else ++rem;
    }

    for(map<string, vector<int> >::iterator it = tgs.begin(); it != tgs.end(); ++it)
    {
        int size = it->second.size();

        // count differences between occurences
        for (int i = size - 1; i > 0; --i)
            it->second[i] -= it->second[i-1];
        it->second.erase(it->second.begin());

        // count GCD for the n-grams
        int mgcd = multi_gcd(it->second);

        // save {"n-gram": [gcd, freq]}
        it->second.clear();
        it->second.push_back(mgcd);
        it->second.push_back(size);
    }
}

// try to get the key len
static int
get_key_len (map<string, vector<int> > & tgs)
{
    int key_len = 0;

    // take (6-3) best (most frequented ngrams)
    for (int step = 0; step < (TO-FROM); ++step)
    {
        // find ngram with the maximal frequency
        int max_size = 0;
        for (map<string, vector<int> >::iterator it = tgs.begin(); it != tgs.end(); ++it)
            if (it->second.at(1) > max_size) max_size = it->second.at(1);

        // find & erase all ngrams with the counted maximal frequency
        vector<int> max_gcd;
        map<string, vector<int> >::iterator rem = tgs.begin();
        while (rem != tgs.end())
        {
            if (rem->second.at(1) == max_size)
            {
                max_gcd.push_back(rem->second.at(0));
                tgs.erase(rem++);
            }
            else ++rem;
        }

        // count GCD for all ngrams with the same number of occurences
        int tmp_gcd = multi_gcd(max_gcd);
        // if key_len is invalid, then use counted GCD
        // or if can get better result with the latest gcd than we have
        // counted in previous loops
        if (key_len == 0 || gcd(key_len, tmp_gcd) < tmp_gcd) key_len = tmp_gcd;
    }

    return key_len;
}

// kasiski test
int
kasiski_test (string & str)
{
    map<string, vector<int> > ngrams;
    find_ngrams(str, ngrams, FROM, TO);
    return get_key_len(ngrams);
}
