/*************************************************************************/
/*                                                                       */
/*                  Language Technologies Institute                      */
/*                     Carnegie Mellon University                        */
/*                         Copyright (c) 2001                            */
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
/*               Date:  January 2001                                     */
/*************************************************************************/
/*  Feature functions used by various cart trees etc                     */
/*  These have been create as needed, and as some of the trees are       */
/*  from University of Edinburgh's Festival system their names and       */
/*  semantics follow them                                                */
/*************************************************************************/

#include "include/cst_hrg.h"
#include "include/cst_phoneset.h"
#include "include/cst_regex.h"
#include "include/cst_ffeatures.h"
#include "lang/usenglish/us_ffeatures.h"

static const cst_val *gpos(const cst_item *word);

DEF_STATIC_CONST_VAL_STRING(val_string_numeric,"numeric");
DEF_STATIC_CONST_VAL_STRING(val_string_number,"number");
DEF_STATIC_CONST_VAL_STRING(val_string_month,"month");
DEF_STATIC_CONST_VAL_STRING(val_string_day,"day");
DEF_STATIC_CONST_VAL_STRING(val_string_other,"_other_");
DEF_STATIC_CONST_VAL_STRING(val_string_a,"a");
DEF_STATIC_CONST_VAL_STRING(val_string_flight,"flight");
DEF_STATIC_CONST_VAL_STRING(val_string_to,"to");

DEF_STATIC_CONST_VAL_STRING(val_string_content,"content");

static const cst_val *gpos(const cst_item *word)
{
    /* Guess at part of speech (function/content) */
    const char *w;
    int s,t;

    w = item_feat_string(word,"name");

    for (s=0; us_gpos[s]; s++)
    {
	for (t=1; us_gpos[s][t]; t++)
	    if (cst_streq(w,val_string(us_gpos[s][t])))
		return us_gpos[s][0];
    }

    return (cst_val *)&val_string_content;
}

static const cst_val *num_digits(const cst_item *token)
{   
    const char *name = item_feat_string(token,"name");

    return val_int_n(cst_strlen(name));
}

static const cst_val *month_range(const cst_item *token)
{   
    int v = item_feat_int(token,"name");

    if ((v > 0) && ( v < 32))
	return VAL_STRING_1;	
    else
	return VAL_STRING_0;	
}

static const cst_val *token_pos_guess(const cst_item *token)
{   
    const char *name = item_feat_string(token,"name");
    char *dc = cst_downcase(name);
    const cst_val *r;

    if (cst_regex_match(cst_rx_digits,dc))
	r = &val_string_numeric;
    else if ((cst_regex_match(cst_rx_double,dc)) ||
	(cst_regex_match(cst_rx_double,dc)))
	r = &val_string_number;
    else if (cst_streq(dc,"jan") ||
	cst_streq(dc,"january") ||
	cst_streq(dc,"feb") ||
	cst_streq(dc,"february") ||
	cst_streq(dc,"mar") ||
	cst_streq(dc,"march") ||
	cst_streq(dc,"apr") ||
	cst_streq(dc,"april") ||
	cst_streq(dc,"may") ||
	cst_streq(dc,"jun") ||
	cst_streq(dc,"june") ||
	cst_streq(dc,"jul") ||
	cst_streq(dc,"july") ||
	cst_streq(dc,"aug") ||
	cst_streq(dc,"august") ||
	cst_streq(dc,"sep") ||
	cst_streq(dc,"sept") ||
	cst_streq(dc,"september") ||
	cst_streq(dc,"oct") ||
	cst_streq(dc,"october") ||
	cst_streq(dc,"nov") ||
	cst_streq(dc,"november") ||
	cst_streq(dc,"dec") ||
	cst_streq(dc,"december"))
	r = &val_string_month;
    else if (cst_streq(dc,"sun") ||
	cst_streq(dc,"sunday") ||
	cst_streq(dc,"mon") ||
	cst_streq(dc,"monday") ||
	cst_streq(dc,"tue") ||
	cst_streq(dc,"tues") ||
	cst_streq(dc,"tuesday") ||
	cst_streq(dc,"wed") ||
	cst_streq(dc,"wednesday") ||
	cst_streq(dc,"thu") ||
	cst_streq(dc,"thurs") ||
	cst_streq(dc,"thursday") ||
	cst_streq(dc,"fri") ||
	cst_streq(dc,"friday") ||
	cst_streq(dc,"sat") ||
	cst_streq(dc,"saturday"))
	r = &val_string_day;
   /* ignoring the "token_most_common" condition, does get used */
    else if (cst_streq(dc,"a"))
	r =  &val_string_a;
    else if (cst_streq(dc,"flight"))
	r =  &val_string_flight;
    else if (cst_streq(dc,"to"))
	r =  &val_string_to;
    else
	r =  &val_string_other;
    cst_free(dc);
    return r;
}

const cst_val *content_words_in(const cst_item *p)
{
    const cst_item *s;
    int i=0;
    p=item_as(p,"Word");
    s=item_as(path_to_item(p,"R:SylStructure.R:Phrase.parent.daughter1"),"Word");
    for (;s && !item_equal(p,s);s=item_next(s))
    {
        if (cst_streq(ffeature_string(s,"gpos"),"content"))
        {i++;}
    }
    return val_string_n(i);
}

const cst_val *content_words_out(const cst_item *p)
{
    const cst_item *s;
    int i=0;
    p=item_as(p,"Word");
    s=item_as(path_to_item(p,"R:SylStructure.R:Phrase.parent.daughtern"),"Word");
#if 1 /* fix by uratec */
  for (;s && !item_equal(p,s);s=item_prev(s))
    {
      if (cst_streq(ffeature_string(s,"gpos"),"content"))
        {i++;}
    }
#else
    for (;s && !item_equal(p,s);p=item_next(p))
    {
        if (cst_streq(ffeature_string(p,"gpos"),"content"))
        {i++;}
    }
    if(cst_streq(ffeature_string(s,"gpos"), "content")){i++;}
#endif
    return val_string_n(i);
}

const cst_val *cg_content_words_in_phrase(const cst_item *p)
{
	return float_val(ffeature_float(p,"R:SylStructure.parent.parent.R:Word.content_words_in") + 
                         ffeature_float(p,"R:SylStructure.parent.parent.R:Word.content_words_out")) ;
}


void us_ff_register(cst_features *ffunctions)
{

    /* The language independent ones */
    basic_ff_register(ffunctions);

    ff_register(ffunctions, "gpos",gpos);
    ff_register(ffunctions, "num_digits",num_digits);
    ff_register(ffunctions, "month_range",month_range);
    ff_register(ffunctions, "token_pos_guess",token_pos_guess);
    ff_register(ffunctions, "content_words_in",content_words_in);
    ff_register(ffunctions, "content_words_out",content_words_out);
    ff_register(ffunctions, "lisp_cg_content_words_in_phrase",cg_content_words_in_phrase);

}
