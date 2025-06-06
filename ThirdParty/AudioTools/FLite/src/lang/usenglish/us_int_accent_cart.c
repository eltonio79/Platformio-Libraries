/*************************************************************************/
/*                                                                       */
/*                   Carnegie Mellon University and                      */
/*                Centre for Speech Technology Research                  */
/*                     University of Edinburgh, UK                       */
/*                       Copyright (c) 1998-2001                         */
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
/*  THE UNIVERSITY OF EDINBURGH, CARNEGIE MELLON UNIVERSITY AND THE      */
/*  CONTRIBUTORS TO THIS WORK DISCLAIM ALL WARRANTIES WITH REGARD TO     */
/*  THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY   */
/*  AND FITNESS, IN NO EVENT SHALL THE UNIVERSITY OF EDINBURGH, CARNEGIE */
/*  MELLON UNIVERSITY NOR THE CONTRIBUTORS BE LIABLE FOR ANY SPECIAL,    */
/*  INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER          */
/*  RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN  AN ACTION   */
/*  OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF     */
/*  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.       */
/*                                                                       */
/*************************************************************************/
/*             Author:  Alan W Black (awb@cs.cmu.edu)                    */
/*               Date:  January 2001                                     */
/*************************************************************************/
/*                                                                       */
/*  Derived directly from the accent model cart tree in University of    */
/*  Edinburgh's Festival Speech Synthesis Systems                        */
/*    file:  festival/lib/tobi.scm:f2b_int_accent_cart_tree              */
/*  which was in turn was trained from Boston University FM Radio Data   */
/*  Corpus                                                               */
/*                                                                       */
/*************************************************************************/
/*******************************************************/
/**  Autogenerated cart trees for us_int_accent    */
/*******************************************************/

#include "include/cst_string.h"
#include "include/cst_cart.h"
#include "include/cst_regex.h"
#include "lang/usenglish/us_int_accent_cart.h"

extern const cst_cart us_int_accent_cart;

static const cst_cart_node us_int_accent_cart_nodes[] = {
{ 0, CST_CART_OP_IS, CTNODE_NO_0000, (cst_val *)&val_0000},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 1, CST_CART_OP_IS, CTNODE_NO_0002, (cst_val *)&val_0000},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 2, CST_CART_OP_IS, CTNODE_NO_0004, (cst_val *)&val_0000},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 3, CST_CART_OP_IS, CTNODE_NO_0006, (cst_val *)&val_0003},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 4, CST_CART_OP_IS, CTNODE_NO_0008, (cst_val *)&val_0004},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 4, CST_CART_OP_IS, CTNODE_NO_0010, (cst_val *)&val_0005},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 5, CST_CART_OP_IS, CTNODE_NO_0012, (cst_val *)&val_0003},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 4, CST_CART_OP_IS, CTNODE_NO_0014, (cst_val *)&val_0006},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 4, CST_CART_OP_IS, CTNODE_NO_0016, (cst_val *)&val_0007},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 4, CST_CART_OP_IS, CTNODE_NO_0018, (cst_val *)&val_0008},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 4, CST_CART_OP_IS, CTNODE_NO_0020, (cst_val *)&val_0009},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 6, CST_CART_OP_IS, CTNODE_NO_0022, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 7, CST_CART_OP_IS, CTNODE_NO_0024, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 4, CST_CART_OP_IS, CTNODE_NO_0026, (cst_val *)&val_0011},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 8, CST_CART_OP_IS, CTNODE_NO_0028, (cst_val *)&val_0012},
{ 9, CST_CART_OP_IS, CTNODE_NO_0029, (cst_val *)&val_0000},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 10, CST_CART_OP_IS, CTNODE_NO_0032, (cst_val *)&val_0013},
{ 11, CST_CART_OP_IS, CTNODE_NO_0033, (cst_val *)&val_0006},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 12, CST_CART_OP_IS, CTNODE_NO_0035, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 13, CST_CART_OP_IS, CTNODE_NO_0037, (cst_val *)&val_0006},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 9, CST_CART_OP_IS, CTNODE_NO_0039, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 14, CST_CART_OP_IS, CTNODE_NO_0041, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 8, CST_CART_OP_IS, CTNODE_NO_0043, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 3, CST_CART_OP_IS, CTNODE_NO_0046, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 5, CST_CART_OP_IS, CTNODE_NO_0048, (cst_val *)&val_0013},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 10, CST_CART_OP_IS, CTNODE_NO_0050, (cst_val *)&val_0012},
{ 7, CST_CART_OP_IS, CTNODE_NO_0051, (cst_val *)&val_0014},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 15, CST_CART_OP_IS, CTNODE_NO_0054, (cst_val *)&val_0015},
{ 14, CST_CART_OP_IS, CTNODE_NO_0055, (cst_val *)&val_0010},
{ 7, CST_CART_OP_IS, CTNODE_NO_0056, (cst_val *)&val_0006},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 12, CST_CART_OP_IS, CTNODE_NO_0058, (cst_val *)&val_0015},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 7, CST_CART_OP_IS, CTNODE_NO_0060, (cst_val *)&val_0014},
{ 12, CST_CART_OP_IS, CTNODE_NO_0061, (cst_val *)&val_0013},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 16, CST_CART_OP_IS, CTNODE_NO_0065, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 13, CST_CART_OP_IS, CTNODE_NO_0068, (cst_val *)&val_0010},
{ 9, CST_CART_OP_IS, CTNODE_NO_0069, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0016 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 9, CST_CART_OP_IS, CTNODE_NO_0072, (cst_val *)&val_0000},
{ 3, CST_CART_OP_IS, CTNODE_NO_0073, (cst_val *)&val_0012},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 8, CST_CART_OP_IS, CTNODE_NO_0075, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 14, CST_CART_OP_IS, CTNODE_NO_0077, (cst_val *)&val_0010},
{ 10, CST_CART_OP_IS, CTNODE_NO_0078, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 12, CST_CART_OP_IS, CTNODE_NO_0082, (cst_val *)&val_0013},
{ 17, CST_CART_OP_IS, CTNODE_NO_0083, (cst_val *)&val_0010},
{ 10, CST_CART_OP_IS, CTNODE_NO_0084, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0016 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 12, CST_CART_OP_IS, CTNODE_NO_0088, (cst_val *)&val_0017},
{ 7, CST_CART_OP_IS, CTNODE_NO_0089, (cst_val *)&val_0014},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 11, CST_CART_OP_IS, CTNODE_NO_0092, (cst_val *)&val_0006},
{ 15, CST_CART_OP_IS, CTNODE_NO_0093, (cst_val *)&val_0013},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 15, CST_CART_OP_IS, CTNODE_NO_0095, (cst_val *)&val_0012},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 10, CST_CART_OP_IS, CTNODE_NO_0097, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 7, CST_CART_OP_IS, CTNODE_NO_0099, (cst_val *)&val_0014},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0018 },
{ 5, CST_CART_OP_IS, CTNODE_NO_0102, (cst_val *)&val_0015},
{ 8, CST_CART_OP_IS, CTNODE_NO_0103, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 10, CST_CART_OP_IS, CTNODE_NO_0105, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0016 },
{ 11, CST_CART_OP_IS, CTNODE_NO_0108, (cst_val *)&val_0004},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 9, CST_CART_OP_IS, CTNODE_NO_0110, (cst_val *)&val_0012},
{ 10, CST_CART_OP_IS, CTNODE_NO_0111, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 15, CST_CART_OP_IS, CTNODE_NO_0114, (cst_val *)&val_0019},
{ 14, CST_CART_OP_IS, CTNODE_NO_0115, (cst_val *)&val_0010},
{ 13, CST_CART_OP_IS, CTNODE_NO_0116, (cst_val *)&val_0014},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0018 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 13, CST_CART_OP_IS, CTNODE_NO_0120, (cst_val *)&val_0005},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 17, CST_CART_OP_IS, CTNODE_NO_0122, (cst_val *)&val_0012},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 3, CST_CART_OP_IS, CTNODE_NO_0124, (cst_val *)&val_0013},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 8, CST_CART_OP_IS, CTNODE_NO_0126, (cst_val *)&val_0010},
{ 16, CST_CART_OP_IS, CTNODE_NO_0127, (cst_val *)&val_0000},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 3, CST_CART_OP_IS, CTNODE_NO_0129, (cst_val *)&val_0012},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 10, CST_CART_OP_IS, CTNODE_NO_0131, (cst_val *)&val_0010},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 3, CST_CART_OP_IS, CTNODE_NO_0133, (cst_val *)&val_0000},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 7, CST_CART_OP_IS, CTNODE_NO_0136, (cst_val *)&val_0006},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0016 },
{ 15, CST_CART_OP_IS, CTNODE_NO_0138, (cst_val *)&val_0020},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0018 },
{ 12, CST_CART_OP_IS, CTNODE_NO_0140, (cst_val *)&val_0015},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 15, CST_CART_OP_IS, CTNODE_NO_0142, (cst_val *)&val_0013},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0018 },
{ 14, CST_CART_OP_IS, CTNODE_NO_0144, (cst_val *)&val_0010},
{ 15, CST_CART_OP_IS, CTNODE_NO_0145, (cst_val *)&val_0012},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0002 },
{ 255, CST_CART_OP_NONE, 0, 0}};



static const char * const us_int_accent_feat_table[] = {
"R:SylStructure.parent.R:Token.parent.EMPH",
"n.R:SylStructure.parent.R:Token.parent.EMPH",
"p.R:SylStructure.parent.R:Token.parent.EMPH",
"ssyl_in",
"R:SylStructure.parent.gpos",
"ssyl_out",
"stress",
"R:SylStructure.parent.R:Word.p.gpos",
"p.syl_break",
"syl_break",
"p.p.syl_break",
"R:SylStructure.parent.R:Word.p.p.gpos",
"syl_out",
"R:SylStructure.parent.R:Word.n.gpos",
"n.stress",
"syl_in",
"n.syl_break",
"n.n.syl_break",
NULL };

const cst_cart us_int_accent_cart = {
  us_int_accent_cart_nodes,
  us_int_accent_feat_table
};
