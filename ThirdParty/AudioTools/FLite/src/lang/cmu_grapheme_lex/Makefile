###########################################################################
##                                                                       ##
##                  Language Technologies Institute                      ##
##                     Carnegie Mellon University                        ##
##                        Copyright (c) 2013                             ##
##                        All Rights Reserved.                           ##
##                                                                       ##
##  Permission is hereby granted, free of charge, to use and distribute  ##
##  this software and its documentation without restriction, including   ##
##  without limitation the rights to use, copy, modify, merge, publish,  ##
##  distribute, sublicense, and/or sell copies of this work, and to      ##
##  permit persons to whom this work is furnished to do so, subject to   ##
##  the following conditions:                                            ##
##   1. The code must retain the above copyright notice, this list of    ##
##      conditions and the following disclaimer.                         ##
##   2. Any modifications must be clearly marked as such.                ##
##   3. Original authors' names are not deleted.                         ##
##   4. The authors' names are not used to endorse or promote products   ##
##      derived from this software without specific prior written        ##
##      permission.                                                      ##
##                                                                       ##
##  CARNEGIE MELLON UNIVERSITY AND THE CONTRIBUTORS TO THIS WORK         ##
##  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      ##
##  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   ##
##  SHALL CARNEGIE MELLON UNIVERSITY NOR THE CONTRIBUTORS BE LIABLE      ##
##  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    ##
##  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   ##
##  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          ##
##  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       ##
##  THIS SOFTWARE.                                                       ##
##                                                                       ##
###########################################################################
##                                                                       ##
##  grapheme lexicon and letter to sound rules                           ##
##                                                                       ##
###########################################################################
TOP=../..
DIRNAME=lang/cmu_grapheme_lex
BUILD_DIRS = 
ALL_DIRS= 
H = cmu_grapheme_lex.h
SRCS = cmu_grapheme_lex.c grapheme_unitran_tables.c
SCRIPTS = 
OBJS = $(SRCS:.c=.o)
SCM=
FILES = Makefile $(SCM) $(SRCS) $(H) $(SCRIPTS)
LIBNAME = flite_cmu_grapheme_lex
LOCAL_INCLUDES = 

ALL = 

include $(TOP)/config/common_make_rules

mapping:
	${ESTDIR}/../festival/bin/festival -b ${TOP}/tools/make_ug.scm ${FESTVOXDIR}/src/grapheme/unicode_sampa_mapping.scm '(doit)'


