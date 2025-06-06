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
/*               Date:  August 2000                                      */
/*************************************************************************/
/*                                                                       */
/*  Waveforms                                                            */
/*                                                                       */
/*************************************************************************/
#ifndef _CST_TRACK_H__
#define _CST_TRACK_H__

#include "include/cst_file.h"
#include "include/cst_error.h"
#include "include/cst_alloc.h"
#include "include/cst_endian.h"
#include "include/cst_file.h"
#include "include/cst_val.h"

typedef struct  cst_track_struct {
    const char *type;
    int num_frames;
    int num_channels;
    float *times;
    float **frames;
} cst_track;

cst_track *new_track();
void delete_track(cst_track *val);

float track_frame_shift(cst_track *t, int frame);
void cst_track_resize(cst_track *t,int num_frames, int num_channels);
cst_track *cst_track_copy(const cst_track *t);

int cst_track_save_est(cst_track *t, const char *filename);
int cst_track_save_est_binary(cst_track *t, const char *filename);
int cst_track_load_est(cst_track *t, const char *filename);

CST_VAL_USER_TYPE_DCLS(track,cst_track)

#endif
