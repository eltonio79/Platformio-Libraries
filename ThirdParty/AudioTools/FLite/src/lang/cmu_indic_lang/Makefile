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
##  indic general functions/models                                       ##
##                                                                       ##
###########################################################################
TOP=../..
DIRNAME=lang/cmu_indic_lang
BUILD_DIRS = 
ALL_DIRS= 
H = cmu_indic_lang.h cmu_indic_phrasing_cart.h \
    indic_num_table.h indic_eng_num_table.h \
    indic_hin_num_table.h \
    indic_kan_num_table.h \
    indic_mar_num_table.h \
    indic_guj_num_table.h \
    indic_tam_num_table.h \
    indic_tel_num_table.h \
    indic_san_num_table.h \
    indic_pan_num_table.h
SRCS = cmu_indic_lang.c cmu_indic_phoneset.c cmu_indic_phrasing_cart.c
SCRIPTS = 
OBJS = $(SRCS:.c=.o)
SCM=
FILES = Makefile $(SCM) $(SRCS) $(H) $(SCRIPTS)
LIBNAME = flite_cmu_indic_lang
LOCAL_INCLUDES = 

ALL = 

include $(TOP)/config/common_make_rules

