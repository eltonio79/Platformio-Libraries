/*************************************************************************/
/*                                                                       */
/*                  Language Technologies Institute                      */
/*                     Carnegie Mellon University                        */
/*                        Copyright (c) 1999                             */
/*                        All Rights Reserved.                           */
/*                                                                       */
/*  Permission is hereby granted, free of charge, to use and distribute  */
/*  this software and its documentation without restriction, including   */
/*  without limitation the rights to use, copy, modify, merge, publish,  */
/*  distribute, sublicense, and/or sell copies of this work, and to      */
/*  permit persons to whom this work is furnished to do so, subject to   */
/*  the following conditions:                                            */
/*   1. The code must retain the above copyright notice, this list of    */
/*      conditions and the following disclaimer.                         */
/*   2. Any modifications must be clearly marked as such.                */
/*   3. Original authors' names are not deleted.                         */
/*   4. The authors' names are not used to endorse or promote products   */
/*      derived from this software without specific prior written        */
/*      permission.                                                      */
/*                                                                       */
/*  CARNEGIE MELLON UNIVERSITY AND THE CONTRIBUTORS TO THIS WORK         */
/*  DISCLAIM ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING      */
/*  ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT   */
/*  SHALL CARNEGIE MELLON UNIVERSITY NOR THE CONTRIBUTORS BE LIABLE      */
/*  FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES    */
/*  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN   */
/*  AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,          */
/*  ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF       */
/*  THIS SOFTWARE.                                                       */
/*                                                                       */
/*************************************************************************/
/*             Author:  Alan W Black (awb@cs.cmu.edu)                    */
/*               Date:  December 1999                                    */
/*************************************************************************/
/*                                                                       */
/*  Light weight run-time speech synthesis system, public API            */
/*                                                                       */
/*************************************************************************/
#ifndef _FLITE_H__
#define _FLITE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "include/cst_string.h"
#include "include/cst_regex.h"
#include "include/cst_val.h"
#include "include/cst_features.h"
#include "include/cst_item.h"
#include "include/cst_relation.h"
#include "include/cst_utterance.h"
#include "include/cst_wave.h"
#include "include/cst_track.h"

#include "include/cst_cart.h"
#include "include/cst_phoneset.h"
#include "include/cst_voice.h"
#include "include/cst_audio.h"

#include "include/cst_utt_utils.h"
#include "include/cst_lexicon.h"
#include "include/cst_synth.h"
#include "include/cst_units.h"
#include "include/cst_tokenstream.h"

#ifdef WIN32
/* For Visual Studio 2012 global variable definitions */
#define GLOBALVARDEF __declspec(dllexport)
#else
#define GLOBALVARDEF
#endif
 extern GLOBALVARDEF cst_val *flite_voice_list;
 extern GLOBALVARDEF cst_lang flite_lang_list[20];
 extern GLOBALVARDEF int flite_lang_list_length;

/* Public functions */
int flite_init();

/* General top level functions */
cst_voice *flite_voice_select(const char *name);
cst_voice *flite_voice_load(const char *voice_filename);
int flite_voice_dump(cst_voice *voice, const char *voice_filename);
float flite_file_to_speech(const char *filename, 
			   cst_voice *voice,
			   const char *outtype);
float flite_text_to_speech(const char *text, 
			   cst_voice *voice,
			   const char *outtype);
float flite_phones_to_speech(const char *text, 
			     cst_voice *voice,
			     const char *outtype);
float flite_ssml_file_to_speech(const char *filename,
                                cst_voice *voice,
                                const char *outtype);
float flite_ssml_text_to_speech(const char *text,
                                cst_voice *voice,
                                const char *outtype);
int flite_voice_add_lex_addenda(cst_voice *v, const cst_string *lexfile);

/* Lower lever user functions */
cst_wave *flite_text_to_wave(const char *text,cst_voice *voice);
cst_utterance *flite_synth_text(const char *text,cst_voice *voice);
cst_utterance *flite_synth_phones(const char *phones,cst_voice *voice);

float flite_ts_to_speech(cst_tokenstream *ts, 
                         cst_voice *voice,
                         const char *outtype);
cst_utterance *flite_do_synth(cst_utterance *u,
                              cst_voice *voice,
                              cst_uttfunc synth);
float flite_process_output(cst_utterance *u,
                           const char *outtype,
                           int append);

/* for voices with external voxdata */
int flite_mmap_clunit_voxdata(const char *voxdir, cst_voice *voice);
int flite_munmap_clunit_voxdata(cst_voice *voice);

/* flite public export wrappers for features access */
int flite_get_param_int(const cst_features *f, const char *name,int def);
float flite_get_param_float(const cst_features *f, const char *name, float def);
const char *flite_get_param_string(const cst_features *f, const char *name, const char *def);
const cst_val *flite_get_param_val(const cst_features *f, const char *name, cst_val *def);
void flite_feat_set_int(cst_features *f, const char *name, int v);
void flite_feat_set_float(cst_features *f, const char *name, float v);
void flite_feat_set_string(cst_features *f, const char *name, const char *v);
void flite_feat_set(cst_features *f, const char *name,const cst_val *v);
int flite_feat_remove(cst_features *f, const char *name);

const char *flite_ffeature_string(const cst_item *item,const char *featpath);
int flite_ffeature_int(const cst_item *item,const char *featpath);
float flite_ffeature_float(const cst_item *item,const char *featpath);
const cst_val *flite_ffeature(const cst_item *item,const char *featpath);
cst_item* flite_path_to_item(const cst_item *item,const char *featpath);

/* These functions are *not* thread-safe, they are designed to be called */
/* before the initial synthesis occurs */
int flite_add_voice(cst_voice *voice);
int flite_add_lang(const char *langname,
                   void (*lang_init)(cst_voice *vox),
                   cst_lexicon *(*lex_init)());
/* These are init functions for generic grapheme based voices */
void utf8_grapheme_lang_init(cst_voice *v);
cst_lexicon *utf8_grapheme_lex_init(void);

#ifdef __cplusplus
}  /* extern "C" */
#endif /* __cplusplus */

#endif
