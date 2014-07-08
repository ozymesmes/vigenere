#-----------------------------------------------------------------------------
#-- |
#-- Project : Vigenere cipher cracking (KRY project 2012)
#-- Module  : Makefile
#-- 
#-- Author  : Mikulka Jiri    <xmikul39>
#--
#-- Makefile for the project.
#--
#-----------------------------------------------------------------------------

CC=g++
CFLAGS=-c -Wall -Wwrite-strings -Winline -Wshadow -D_GNU_SOURCE -Wextra -pedantic -O2 -pg
LDFLAGS=
SOURCES=main.cpp kasiski.cpp friedman.cpp key.cpp vigenere.cpp
HEADERS=kasiski.h friedman.h key.h vigenere.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=kry
LOGIN=xmikul39
DOC=doc

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *~ *.o $(EXECUTABLE) $(DOC).aux $(DOC).log *.dvi *.log *.ps

doc:
	latex $(DOC).tex
	latex $(DOC).tex
	dvips $(DOC).dvi
	ps2pdf $(DOC).ps

archive: doc clean
	tar cvf $(LOGIN).tar $(SOURCES) $(HEADERS) $(DOC).pdf Makefile 
