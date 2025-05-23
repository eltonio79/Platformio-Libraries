/*************************************************************************/
/*                                                                       */
/*                  Language Technologies Institute                      */
/*                     Carnegie Mellon University                        */
/*                      Copyright (c) 1999-2000                          */
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
/*               Date:  April 2001                                       */
/*************************************************************************/
/*                                                                       */
/*  A simple diphone voice defintion			                 */
/*                                                                       */
/*************************************************************************/

#include <string.h>
#include "flite.h"
#include "include/cst_diphone.h"
#include "lang/usenglish/usenglish.h"
#include "lang/cmulex/cmu_lex.h"

extern cst_diphone_db cmu_us_kal16_db;

cst_voice *cmu_us_kal16_diphone = NULL;

cst_voice *register_cmu_us_kal16(const char *voxdir)
{
    cst_voice *v;
    cst_lexicon *lex;

    if (cmu_us_kal16_diphone)
        return cmu_us_kal16_diphone;  /* Already registered */

    v = new_voice();
    v->name = "kal16";

    /* Sets up language specific parameters in the cmu_us_kal16. */
    usenglish_init(v);

    feat_set_string(v->features,"name","cmu_us_kal16");

    feat_set_float(v->features,"int_f0_target_mean",95.0);
    feat_set_float(v->features,"int_f0_target_stddev",11.0);

    feat_set_float(v->features,"duration_stretch",1.1); 

    /* Lexicon */
    lex = cmu_lex_init();
    feat_set(v->features,"lexicon",lexicon_val(lex));
    feat_set(v->features,"postlex_func",uttfunc_val(lex->postlex));

    /* Waveform synthesis */
    feat_set(v->features,"wave_synth_func",uttfunc_val(&diphone_synth));
    feat_set(v->features,"diphone_db",diphone_db_val(&cmu_us_kal16_db));
    feat_set_int(v->features,"sample_rate",cmu_us_kal16_db.sts->sample_rate);
/*    feat_set_string(v->features,"join_type","simple_join"); */
    feat_set_string(v->features,"join_type","modified_lpc");
    feat_set_string(v->features,"resynth_type","fixed");

    cmu_us_kal16_diphone = v;

    return cmu_us_kal16_diphone;
}

void unregister_cmu_us_kal16(cst_voice *vox)
{
    if (vox != cmu_us_kal16_diphone)
	return;
    delete_voice(vox);
    cmu_us_kal16_diphone = NULL;
}

