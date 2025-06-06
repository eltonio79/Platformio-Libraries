/*******************************************************/
/**  Autogenerated cart trees for us_phrasing    */
/*******************************************************/

#include "include/cst_string.h"
#include "include/cst_cart.h"
#include "include/cst_regex.h"
#include "lang/cmu_indic_lang/cmu_indic_phrasing_cart.h"
extern const cst_cart cmu_indic_phrasing_cart;


static const cst_cart_node cmu_indic_phrasing_cart_nodes[] = {
{ 0, CST_CART_OP_IS, CTNODE_cmu_indic_phrasing_NO_0000, (cst_val *)&val_0000},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 1, CST_CART_OP_IS, CTNODE_cmu_indic_phrasing_NO_0002, (cst_val *)&val_0002},
{ 2, CST_CART_OP_IS, CTNODE_cmu_indic_phrasing_NO_0003, (cst_val *)&val_0003},
{ 3, CST_CART_OP_IS, CTNODE_cmu_indic_phrasing_NO_0004, (cst_val *)&val_0004},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 4, CST_CART_OP_IS, CTNODE_cmu_indic_phrasing_NO_0006, (cst_val *)&val_0004},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0005 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 5, CST_CART_OP_IS, CTNODE_cmu_indic_phrasing_NO_0010, (cst_val *)&val_0002},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 4, CST_CART_OP_IS, CTNODE_cmu_indic_phrasing_NO_0012, (cst_val *)&val_0004},
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0001 },
{ 255, CST_CART_OP_NONE, 0, (cst_val *)&val_0005 },
{ 255, CST_CART_OP_NONE, 0, 0}};



static const char * const cmu_indic_phrasing_feat_table[] = {
"R:Token.parent.n.name",
"R:Token.n.name",
"R:Token.parent.punc",
"R:Token.parent.break",
"break",
"n.name",
NULL };

const cst_cart cmu_indic_phrasing_cart = {
  cmu_indic_phrasing_cart_nodes,
  cmu_indic_phrasing_feat_table
};
