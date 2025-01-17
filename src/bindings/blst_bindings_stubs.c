#include "blst.h"
#include "blst_misc.h"
#define CAML_NAME_SPACE
#include "caml_bls12_381_stubs.h"
#include "ocaml_integers.h"
#include <caml/alloc.h>
#include <caml/custom.h>
#include <caml/fail.h>
#include <caml/memory.h>
#include <caml/mlvalues.h>
#include <stdlib.h>
#include <string.h>

// From ocaml-ctypes:
// https://github.com/ocamllabs/ocaml-ctypes/blob/9048ac78b885cc3debeeb020c56ea91f459a4d33/src/ctypes/ctypes_primitives.h#L110
#if SIZE_MAX == UINT64_MAX
#define ctypes_size_t_val Uint64_val
#define ctypes_copy_size_t integers_copy_uint64
#else
#error "No suitable OCaml type available for representing size_t values"
#endif

// From ocaml/ocaml
// https://github.com/ocaml/ocaml/blob/aca84729327d327eaf6e82f3ae15d0a63953288e/runtime/caml/mlvalues.h#L401
#define Val_none Val_int(0)
#define Some_val(v) Field(v, 0)
#define Tag_some 0
#define Is_none(v) ((v) == Val_none)
#define Is_some(v) Is_block(v)

static int caml_blst_fr_compare(value x, value y) {
  blst_fr *x_c = Blst_fr_val(x);
  blst_fr *y_c = Blst_fr_val(y);
  return (blst_fr_compare(x_c, y_c));
}

static struct custom_operations blst_fr_ops = {"blst_fr",
                                               custom_finalize_default,
                                               caml_blst_fr_compare,
                                               custom_hash_default,
                                               custom_serialize_default,
                                               custom_deserialize_default,
                                               custom_compare_ext_default,
                                               custom_fixed_length_default};

static struct custom_operations blst_scalar_ops = {"blst_scalar",
                                                   custom_finalize_default,
                                                   custom_compare_default,
                                                   custom_hash_default,
                                                   custom_serialize_default,
                                                   custom_deserialize_default,
                                                   custom_compare_ext_default,
                                                   custom_fixed_length_default};

CAMLprim value allocate_scalar_stubs(value unit) {
  CAMLparam1(unit);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_scalar_ops, sizeof(blst_scalar), 0, 1);
  blst_scalar *c = Blst_scalar_val(block);
  memset(c, 0, sizeof(blst_scalar));
  CAMLreturn(block);
}

CAMLprim value caml_blst_fr_from_lendian_stubs(value x, value b) {
  CAMLparam2(x, b);
  blst_fr *x_c = Blst_fr_val(x);
  byte *b_c = Bytes_val(b);
  bool res = blst_fr_from_lendian(x_c, b_c);
  CAMLreturn(Val_bool(res));
}

CAMLprim value caml_blst_lendian_from_fr_stubs(value b, value x) {
  CAMLparam2(b, x);
  blst_fr *x_c = Blst_fr_val(x);
  byte *b_c = Bytes_val(b);
  blst_lendian_from_fr(b_c, x_c);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fr_pow_stubs(value out, value x, value exp,
                                      value exp_nb_bits) {
  CAMLparam4(out, x, exp, exp_nb_bits);
  blst_fr *out_c = Blst_fr_val(out);
  blst_fr *x_c = Blst_fr_val(x);
  byte *exp_c = Bytes_val(exp);
  if (blst_fr_pow(out_c, x_c, exp_c, Int_val(exp_nb_bits)))
    CAMLreturn(CAML_BLS12_381_OUTPUT_INVALID_ARGUMENT);
  else
    CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp12_pow_stubs(value out, value x, value exp,
                                        value exp_nb_bits) {
  CAMLparam4(out, x, exp, exp_nb_bits);
  blst_fp12 *out_c = Blst_fp12_val(out);
  blst_fp12 *x_c = Blst_fp12_val(x);
  byte *exp_c = Bytes_val(exp);
  if (blst_fp12_pow(out_c, x_c, exp_c, Int_val(exp_nb_bits)))
    CAMLreturn(CAML_BLS12_381_OUTPUT_INVALID_ARGUMENT);
  else
    CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fr_is_equal_stubs(value x, value y) {
  CAMLparam2(x, y);
  blst_fr *x_c = Blst_fr_val(x);
  blst_fr *y_c = Blst_fr_val(y);
  CAMLreturn(Val_bool(blst_fr_is_equal(x_c, y_c)));
}

CAMLprim value caml_blst_fr_is_zero_stubs(value x) {
  CAMLparam1(x);
  blst_fr *x_c = Blst_fr_val(x);
  CAMLreturn(Val_bool(blst_fr_is_zero(x_c)));
}

CAMLprim value caml_blst_fr_is_one_stubs(value x) {
  CAMLparam1(x);
  blst_fr *x_c = Blst_fr_val(x);
  CAMLreturn(Val_bool(blst_fr_is_one(x_c)));
}

CAMLprim value callocate_fr_stubs(value unit) {
  CAMLparam1(unit);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_fr_ops, sizeof(blst_fr), 0, 1);
  blst_fr *c = Blst_fr_val(block);
  memset(c, 0, sizeof(blst_fr));
  CAMLreturn(block);
}

CAMLprim value mallocate_fr_stubs(value unit) {
  CAMLparam1(unit);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_fr_ops, sizeof(blst_fr), 0, 1);
  blst_fr *c = Blst_fr_val(block);
  CAMLreturn(block);
}

CAMLprim value caml_blst_fr_add_stubs(value ret, value p1, value p2) {
  CAMLparam3(ret, p1, p2);
  blst_fr_add(Blst_fr_val(ret), Blst_fr_val(p1), Blst_fr_val(p2));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fr_mul_stubs(value ret, value p1, value p2) {
  CAMLparam3(ret, p1, p2);
  blst_fr_mul(Blst_fr_val(ret), Blst_fr_val(p1), Blst_fr_val(p2));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fr_sqr_stubs(value ret, value p1) {
  CAMLparam2(ret, p1);
  blst_fr_sqr(Blst_fr_val(ret), Blst_fr_val(p1));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fr_eucl_inverse_stubs(value ret, value p1) {
  CAMLparam2(ret, p1);
  blst_fr_eucl_inverse(Blst_fr_val(ret), Blst_fr_val(p1));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fr_sub_stubs(value ret, value p1, value p2) {
  CAMLparam3(ret, p1, p2);
  blst_fr_sub(Blst_fr_val(ret), Blst_fr_val(p1), Blst_fr_val(p2));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_scalar_from_fr_stubs(value ret, value p1) {
  CAMLparam2(ret, p1);
  blst_scalar_from_fr(Blst_scalar_val(ret), Blst_fr_val(p1));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fr_from_scalar_stubs(value ret, value p1) {
  CAMLparam2(ret, p1);
  blst_fr_from_scalar(Blst_fr_val(ret), Blst_scalar_val(p1));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_scalar_to_bytes_stubs(value ret, value p1) {
  CAMLparam2(ret, p1);
  blst_lendian_from_scalar(Bytes_val(ret), Blst_scalar_val(p1));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_scalar_of_bytes_stubs(value ret, value p1) {
  CAMLparam2(ret, p1);
  blst_scalar_from_lendian(Blst_scalar_val(ret), Bytes_val(p1));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_check_scalar_stubs(value p1) {
  CAMLparam1(p1);
  bool r = blst_scalar_fr_check(Blst_scalar_val(p1));
  CAMLreturn(Val_bool(r));
}

CAMLprim value caml_blst_fr_memcpy_stubs(value dst, value src) {
  CAMLparam2(dst, src);
  memcpy(Blst_fr_val(dst), Blst_fr_val(src), sizeof(blst_fr));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

static struct custom_operations blst_fp_ops = {"blst_fp",
                                               custom_finalize_default,
                                               custom_compare_default,
                                               custom_hash_default,
                                               custom_serialize_default,
                                               custom_deserialize_default,
                                               custom_compare_ext_default,
                                               custom_fixed_length_default};

CAMLprim value allocate_fp_stubs(value unit) {
  CAMLparam1(unit);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_fp_ops, sizeof(blst_fp), 0, 1);
  blst_fp *c = Blst_fp_val(block);
  memset(c, 0, sizeof(blst_fp));
  CAMLreturn(block);
}

CAMLprim value caml_blst_fp_of_bytes_stubs(value ret, value p1) {
  CAMLparam2(ret, p1);
  blst_fp_from_lendian(Blst_fp_val(ret), Bytes_val(p1));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp_to_bytes_stubs(value ret, value p1) {
  CAMLparam2(ret, p1);
  blst_lendian_from_fp(Bytes_val(ret), Blst_fp_val(p1));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp_add_stubs(value ret, value p1, value p2) {
  CAMLparam3(ret, p1, p2);
  blst_fp_add(Blst_fp_val(ret), Blst_fp_val(p1), Blst_fp_val(p2));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp_mul_stubs(value ret, value p1, value p2) {
  CAMLparam3(ret, p1, p2);
  blst_fp_mul(Blst_fp_val(ret), Blst_fp_val(p1), Blst_fp_val(p2));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp_sqrt_stubs(value ret, value p1) {
  CAMLparam2(ret, p1);
  bool r = blst_fp_sqrt(Blst_fp_val(ret), Blst_fp_val(p1));
  CAMLreturn(Val_bool(r));
}

CAMLprim value caml_blst_fp_cneg_stubs(value buffer, value p, value b) {
  CAMLparam3(buffer, p, b);
  blst_fp_cneg(Blst_fp_val(buffer), Blst_fp_val(p), Bool_val(b));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

static struct custom_operations blst_fp2_ops = {"blst_fp2",
                                                custom_finalize_default,
                                                custom_compare_default,
                                                custom_hash_default,
                                                custom_serialize_default,
                                                custom_deserialize_default,
                                                custom_compare_ext_default,
                                                custom_fixed_length_default};

CAMLprim value allocate_fp2_stubs(value unit) {
  CAMLparam1(unit);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_fp2_ops, sizeof(blst_fp2), 0, 1);
  blst_fp2 *tmp = Blst_fp2_val(block);
  memset(tmp, 0, sizeof(blst_fp2));
  CAMLreturn(block);
}

CAMLprim value caml_blst_fp2_add_stubs(value buffer, value p, value q) {
  CAMLparam3(buffer, p, q);
  blst_fp2_add(Blst_fp2_val(buffer), Blst_fp2_val(p), Blst_fp2_val(q));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp2_mul_stubs(value buffer, value p, value q) {
  CAMLparam3(buffer, p, q);
  blst_fp2_mul(Blst_fp2_val(buffer), Blst_fp2_val(p), Blst_fp2_val(q));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp2_sqrt_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  bool r = blst_fp2_sqrt(Blst_fp2_val(buffer), Blst_fp2_val(p));
  CAMLreturn(Val_bool(r));
}

CAMLprim value caml_blst_fp2_cneg_stubs(value buffer, value p, value b) {
  CAMLparam3(buffer, p, b);
  blst_fp2_cneg(Blst_fp2_val(buffer), Blst_fp2_val(p), Bool_val(b));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp2_assign_stubs(value p, value x1, value x2) {
  CAMLparam3(p, x1, x2);
  blst_fp2 *p_c = Blst_fp2_val(p);
  blst_fp *x1_c = Blst_fp_val(x1);
  blst_fp *x2_c = Blst_fp_val(x2);
  blst_fp2_assign(p_c, x1_c, x2_c);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp2_zero_stubs(value buffer) {
  CAMLparam1(buffer);
  blst_fp2 *buffer_c = Blst_fp2_val(buffer);
  blst_fp2_zero(buffer_c);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp2_one_stubs(value buffer) {
  CAMLparam1(buffer);
  blst_fp2 *buffer_c = Blst_fp2_val(buffer);
  blst_fp2_set_one(buffer_c);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}
CAMLprim value caml_blst_fp2_of_bytes_components_stubs(value buffer, value x1,
                                                       value x2) {
  CAMLparam3(buffer, x1, x2);
  blst_fp2 *buffer_c = Blst_fp2_val(buffer);
  // FIXME: add a check on the length
  blst_fp2_of_bytes_components(buffer_c, Bytes_val(x1), Bytes_val(x2));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp2_to_bytes_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_fp2 *p_c = Blst_fp2_val(p);
  // FIXME: add a check on the length
  byte *out = Bytes_val(buffer);
  blst_fp2_to_bytes(out, p_c);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

static struct custom_operations blst_fp12_ops = {"blst_fp12",
                                                 custom_finalize_default,
                                                 custom_compare_default,
                                                 custom_hash_default,
                                                 custom_serialize_default,
                                                 custom_deserialize_default,
                                                 custom_compare_ext_default,
                                                 custom_fixed_length_default};

CAMLprim value allocate_fp12_stubs(value unit) {
  CAMLparam1(unit);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_fp12_ops, sizeof(blst_fp12), 0, 1);
  blst_fp12 *tmp = Blst_fp12_val(block);
  memset(tmp, 0, sizeof(blst_fp12));
  CAMLreturn(block);
}

CAMLprim value caml_blst_fp12_mul_stubs(value buffer, value p, value q) {
  CAMLparam3(buffer, p, q);
  blst_fp12_mul(Blst_fp12_val(buffer), Blst_fp12_val(p), Blst_fp12_val(q));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp12_is_equal_stubs(value p, value q) {
  CAMLparam2(p, q);
  bool b = blst_fp12_is_equal(Blst_fp12_val(p), Blst_fp12_val(q));
  CAMLreturn(Val_bool(b));
}

CAMLprim value caml_blst_fp12_is_one_stubs(value p) {
  CAMLparam1(p);
  bool b = blst_fp12_is_one(Blst_fp12_val(p));
  CAMLreturn(Val_bool(b));
}

CAMLprim value caml_blst_fp12_inverse_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_fp12_inverse(Blst_fp12_val(buffer), Blst_fp12_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp12_sqr_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_fp12_sqr(Blst_fp12_val(buffer), Blst_fp12_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp12_one_stubs(value buffer) {
  CAMLparam1(buffer);
  blst_fp12 *buffer_c = Blst_fp12_val(buffer);
  blst_fp12_set_one(buffer_c);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp12_to_bytes_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_fp12 *p_c = Blst_fp12_val(p);
  // FIXME: add a check on the length
  blst_fp12_to_bytes(Bytes_val(buffer), p_c);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp12_of_bytes_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_fp12 *buffer_c = Blst_fp12_val(buffer);
  // FIXME: add a check on the length
  blst_fp12_of_bytes(buffer_c, Bytes_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_fp12_in_group_stubs(value x) {
  CAMLparam1(x);
  blst_fp12 *x_c = Blst_fp12_val(x);
  bool r = blst_fp12_in_group(x_c);
  CAMLreturn(Bool_val(r));
}

static struct custom_operations blst_p1_ops = {"blst_p1",
                                               custom_finalize_default,
                                               custom_compare_default,
                                               custom_hash_default,
                                               custom_serialize_default,
                                               custom_deserialize_default,
                                               custom_compare_ext_default,
                                               custom_fixed_length_default};

static struct custom_operations blst_p1_affine_ops = {
    "blst_p1_affine",           custom_finalize_default,
    custom_compare_default,     custom_hash_default,
    custom_serialize_default,   custom_deserialize_default,
    custom_compare_ext_default, custom_fixed_length_default};

CAMLprim value allocate_p1_stubs(value unit) {
  CAMLparam1(unit);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_p1_ops, sizeof(blst_p1), 0, 1);
  blst_p1 *tmp = Blst_p1_val(block);
  memset(tmp, 0, sizeof(blst_p1));
  CAMLreturn(block);
}

CAMLprim value allocate_p1_affine_stubs(value unit) {
  CAMLparam1(unit);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_p1_affine_ops, sizeof(blst_p1_affine), 0, 1);
  blst_p1_affine *tmp = Blst_p1_affine_val(block);
  memset(tmp, 0, sizeof(blst_p1_affine));
  CAMLreturn(block);
}

CAMLprim value caml_blst_p1_to_affine_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_p1_to_affine(Blst_p1_affine_val(buffer), Blst_p1_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p1_from_affine_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_p1_from_affine(Blst_p1_val(buffer), Blst_p1_affine_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p1_double_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_p1_double(Blst_p1_val(buffer), Blst_p1_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p1_add_or_double_stubs(value buffer, value p,
                                                value q) {
  CAMLparam3(buffer, p, q);
  blst_p1_add_or_double(Blst_p1_val(buffer), Blst_p1_val(p), Blst_p1_val(q));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p1_is_inf_stubs(value p) {
  CAMLparam1(p);
  bool r = blst_p1_is_inf(Blst_p1_val(p));
  CAMLreturn(Val_bool(r));
}

CAMLprim value caml_blst_p1_in_g1_stubs(value p) {
  CAMLparam1(p);
  bool r = blst_p1_in_g1(Blst_p1_val(p));
  CAMLreturn(Val_bool(r));
}

CAMLprim value caml_blst_p1_equal_stubs(value p, value q) {
  CAMLparam2(p, q);
  bool r = blst_p1_is_equal(Blst_p1_val(p), Blst_p1_val(q));
  CAMLreturn(Val_bool(r));
}

CAMLprim value caml_blst_p1_cneg_stubs(value p, value b) {
  CAMLparam2(p, b);
  blst_p1_cneg(Blst_p1_val(p), Bool_val(b));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p1_mult_stubs(value buffer, value p, value n,
                                       value size) {
  CAMLparam4(buffer, p, n, size);
  blst_p1_mult(Blst_p1_val(buffer), Blst_p1_val(p), Bytes_val(n),
               ctypes_size_t_val(size));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p1_serialize_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_p1_serialize(Bytes_val(buffer), Blst_p1_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p1_compress_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_p1_compress(Bytes_val(buffer), Blst_p1_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p1_deserialize_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  int r = blst_p1_deserialize(Blst_p1_affine_val(buffer), Bytes_val(p));
  CAMLreturn(Val_int(r));
}

CAMLprim value caml_blst_p1_uncompress_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  int r = blst_p1_uncompress(Blst_p1_affine_val(buffer), Bytes_val(p));
  CAMLreturn(Val_int(r));
}

CAMLprim value caml_blst_p1_hash_to_curve_stubs(value buffer, value msg,
                                                value msg_length, value dst,
                                                value dst_length, value aug,
                                                value aug_length) {
  CAMLparam5(buffer, msg, msg_length, dst, dst_length);
  CAMLxparam2(aug, aug_length);
  blst_hash_to_g1(Blst_p1_val(buffer), Bytes_val(msg),
                  ctypes_size_t_val(msg_length), Bytes_val(dst),
                  ctypes_size_t_val(dst_length), Bytes_val(aug),
                  ctypes_size_t_val(aug_length));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p1_hash_to_curve_stubs_bytecode(value *argv,
                                                         int argn) {
  return caml_blst_p1_hash_to_curve_stubs(argv[0], argv[1], argv[2], argv[3],
                                          argv[4], argv[5], argv[6]);
}

CAMLprim value caml_blst_p1_memcpy_stubs(value dst, value src) {
  CAMLparam2(dst, src);
  memcpy(Blst_p1_val(dst), Blst_p1_val(src), sizeof(blst_p1));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p1_set_coordinates_stubs(value buffer, value x,
                                                  value y) {
  CAMLparam3(buffer, x, y);
  blst_p1 *buffer_c = Blst_p1_val(buffer);
  blst_fp *x_c = Blst_fp_val(x);
  blst_fp *y_c = Blst_fp_val(y);
  blst_p1_set_coordinates(buffer_c, x_c, y_c);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

static struct custom_operations blst_p2_ops = {"blst_p2",
                                               custom_finalize_default,
                                               custom_compare_default,
                                               custom_hash_default,
                                               custom_serialize_default,
                                               custom_deserialize_default,
                                               custom_compare_ext_default,
                                               custom_fixed_length_default};

static struct custom_operations blst_p2_affine_ops = {
    "blst_p2_affine",           custom_finalize_default,
    custom_compare_default,     custom_hash_default,
    custom_serialize_default,   custom_deserialize_default,
    custom_compare_ext_default, custom_fixed_length_default};

CAMLprim value allocate_p2_stubs(value unit) {
  CAMLparam1(unit);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_p2_ops, sizeof(blst_p2), 0, 1);
  blst_p2 *tmp = Blst_p2_val(block);
  memset(tmp, 0, sizeof(blst_p2));
  CAMLreturn(block);
}

CAMLprim value allocate_p2_affine_stubs(value unit) {
  CAMLparam1(unit);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_p2_affine_ops, sizeof(blst_p2_affine), 0, 1);
  blst_p2_affine *tmp = Blst_p2_affine_val(block);
  memset(tmp, 0, sizeof(blst_p2_affine));
  CAMLreturn(block);
}

CAMLprim value caml_blst_p2_to_affine_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_p2_to_affine(Blst_p2_affine_val(buffer), Blst_p2_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p2_from_affine_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_p2_from_affine(Blst_p2_val(buffer), Blst_p2_affine_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p2_double_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_p2_double(Blst_p2_val(buffer), Blst_p2_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p2_add_or_double_stubs(value buffer, value p,
                                                value q) {
  CAMLparam3(buffer, p, q);
  blst_p2_add_or_double(Blst_p2_val(buffer), Blst_p2_val(p), Blst_p2_val(q));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p2_is_inf_stubs(value p) {
  CAMLparam1(p);
  bool r = blst_p2_is_inf(Blst_p2_val(p));
  CAMLreturn(Val_bool(r));
}

CAMLprim value caml_blst_p2_in_g2_stubs(value p) {
  CAMLparam1(p);
  bool r = blst_p2_in_g2(Blst_p2_val(p));
  CAMLreturn(Val_bool(r));
}

CAMLprim value caml_blst_p2_equal_stubs(value p, value q) {
  CAMLparam2(p, q);
  bool r = blst_p2_is_equal(Blst_p2_val(p), Blst_p2_val(q));
  CAMLreturn(Val_bool(r));
}

CAMLprim value caml_blst_p2_cneg_stubs(value p, value b) {
  CAMLparam2(p, b);
  blst_p2_cneg(Blst_p2_val(p), Bool_val(b));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}
CAMLprim value caml_blst_p2_mult_stubs(value buffer, value p, value n,
                                       value size) {
  CAMLparam4(buffer, p, n, size);
  blst_p2_mult(Blst_p2_val(buffer), Blst_p2_val(p), Bytes_val(n),
               ctypes_size_t_val(size));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p2_serialize_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_p2_serialize(Bytes_val(buffer), Blst_p2_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p2_compress_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_p2_compress(Bytes_val(buffer), Blst_p2_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p2_deserialize_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  int r = blst_p2_deserialize(Blst_p2_affine_val(buffer), Bytes_val(p));
  CAMLreturn(Val_int(r));
}

CAMLprim value caml_blst_p2_uncompress_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  int r = blst_p2_uncompress(Blst_p2_affine_val(buffer), Bytes_val(p));
  CAMLreturn(Val_int(r));
}

CAMLprim value caml_blst_p2_hash_to_curve_stubs(value buffer, value msg,
                                                value msg_length, value dst,
                                                value dst_length, value aug,
                                                value aug_length) {
  CAMLparam5(buffer, msg, msg_length, dst, dst_length);
  CAMLxparam2(aug, aug_length);
  blst_hash_to_g2(Blst_p2_val(buffer), Bytes_val(msg),
                  ctypes_size_t_val(msg_length), Bytes_val(dst),
                  ctypes_size_t_val(dst_length), Bytes_val(aug),
                  ctypes_size_t_val(aug_length));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p2_hash_to_curve_stubs_bytecode(value *argv,
                                                         int argn) {
  return caml_blst_p2_hash_to_curve_stubs(argv[0], argv[1], argv[2], argv[3],
                                          argv[4], argv[5], argv[6]);
}

CAMLprim value caml_blst_p2_memcpy_stubs(value dst, value src) {
  CAMLparam2(dst, src);
  memcpy(Blst_p2_val(dst), Blst_p2_val(src), sizeof(blst_p2));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_p2_set_coordinates_stubs(value buffer, value x,
                                                  value y) {
  CAMLparam3(buffer, x, y);
  blst_p2 *buffer_c = Blst_p2_val(buffer);
  blst_fp2 *x_c = Blst_fp2_val(x);
  blst_fp2 *y_c = Blst_fp2_val(y);
  blst_p2_set_coordinates(buffer_c, x_c, y_c);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

// Pairing

CAMLprim value caml_blst_miller_loop_stubs(value buffer, value g2, value g1) {
  CAMLparam3(buffer, g2, g1);
  blst_miller_loop(Blst_fp12_val(buffer), Blst_p2_affine_val(g2),
                   Blst_p1_affine_val(g1));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_miller_loop_list_stubs(value out, value points_array,
                                                value length) {
  CAMLparam3(out, points_array, length);
  blst_fp12 *out_c = Blst_fp12_val(out);
  int length_c = Int_val(length);

  blst_fp12_set_one(out_c);

  blst_fp12 tmp;
  blst_p1_affine tmp_p1;
  blst_p2_affine tmp_p2;

  for (int i = 0; i < length_c; i++) {
    blst_p1_to_affine(&tmp_p1, Blst_p1_val(Field(Field(points_array, i), 0)));
    blst_p2_to_affine(&tmp_p2, Blst_p2_val(Field(Field(points_array, i), 1)));
    blst_miller_loop(&tmp, &tmp_p2, &tmp_p1);
    blst_fp12_mul(out_c, out_c, &tmp);
  }
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_final_exponentiation_stubs(value buffer, value p) {
  CAMLparam2(buffer, p);
  blst_final_exp(Blst_fp12_val(buffer), Blst_fp12_val(p));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

// For signatures
static void finalize_free_pairing(value v) {
  byte *dst = (byte *)blst_pairing_get_dst(Blst_pairing_val(v));
  // See libblst/src/aggregate.c
  if ((uintptr_t)dst != (uintptr_t)42) {
    free(dst);
  }
  free(Blst_pairing_val(v));
}

static struct custom_operations blst_pairing_ops = {
    "blst_pairing",
    finalize_free_pairing,
    custom_compare_default,
    custom_hash_default,
    custom_serialize_default,
    custom_deserialize_default,
    custom_compare_ext_default,
    custom_fixed_length_default};

// Common to both instantiations
CAMLprim value caml_blst_pairing_init_stubs(value check, value dst,
                                            value dst_length) {
  CAMLparam3(check, dst, dst_length);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_fp12_ops, sizeof(blst_pairing *), 0, 1);
  void *p = calloc(1, blst_pairing_sizeof());
  if (p == NULL)
    caml_raise_out_of_memory();
  blst_pairing **d = (blst_pairing **)Data_custom_val(block);
  *d = p;
  blst_pairing_init(Blst_pairing_val(block), Bool_val(check), Bytes_val(dst),
                    ctypes_size_t_val(dst_length));
  CAMLreturn(block);
}

CAMLprim value caml_blst_pairing_commit_stubs(value buffer) {
  CAMLparam1(buffer);
  blst_pairing_commit(Blst_pairing_val(buffer));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_pairing_finalverify_stubs(value buffer) {
  CAMLparam1(buffer);
  bool r = blst_pairing_finalverify(Blst_pairing_val(buffer), NULL);
  CAMLreturn(Val_bool(r));
}

CAMLprim value caml_blst_signature_keygen_stubs(value buffer, value ikm,
                                                value ikm_length,
                                                value key_info,
                                                value key_info_length) {
  CAMLparam5(buffer, ikm, ikm_length, key_info, key_info_length);
  blst_keygen(Blst_scalar_val(buffer), Bytes_val(ikm),
              ctypes_size_t_val(ikm_length), Bytes_val(key_info),
              ctypes_size_t_val(key_info_length));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

// Pk in G1, Signature in G2
CAMLprim value caml_blst_sk_to_pk_in_g1_stubs(value buffer, value scalar) {
  CAMLparam2(buffer, scalar);
  blst_sk_to_pk_in_g1(Blst_p1_val(buffer), Blst_scalar_val(scalar));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_sign_pk_in_g1_stubs(value buffer, value p, value s) {
  CAMLparam3(buffer, p, s);
  blst_sign_pk_in_g1(Blst_p2_val(buffer), Blst_p2_val(p), Blst_scalar_val(s));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_aggregate_signature_pk_in_g1_stubs(
    value buffer, value g1, value g2, value msg, value msg_length, value aug,
    value aug_length) {
  CAMLparam5(buffer, g1, g2, msg, msg_length);
  CAMLxparam2(aug, aug_length);
  int r = blst_pairing_aggregate_pk_in_g1(
      Blst_pairing_val(buffer), Blst_p1_affine_val(g1), Blst_p2_affine_val(g2),
      Bytes_val(msg), ctypes_size_t_val(msg_length), Bytes_val(aug),
      ctypes_size_t_val(aug_length));
  CAMLreturn(Val_int(r));
}

CAMLprim value
caml_blst_aggregate_signature_pk_in_g1_stubs_bytecode(value *argv, int argn) {
  return caml_blst_aggregate_signature_pk_in_g1_stubs(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

CAMLprim value caml_blst_pairing_chk_n_mul_n_aggr_pk_in_g1_stubs(
    value buffer, value pk, value check_pk, value signature,
    value check_signature, value scalar, value nbits, value msg,
    value msg_length, value aug, value aug_length) {
  CAMLparam5(buffer, pk, check_pk, signature, check_signature);
  CAMLxparam5(scalar, nbits, msg, msg_length, aug);
  CAMLxparam1(aug_length);
  blst_p2_affine *signature_c;
  if (Is_none(signature)) {
    signature_c = NULL;
  } else {
    signature_c = Blst_p2_affine_val(Some_val(signature));
  }
  int r = blst_pairing_chk_n_mul_n_aggr_pk_in_g1(
      Blst_pairing_val(buffer), Blst_p1_affine_val(pk), Bool_val(check_pk),
      signature_c, Bool_val(check_signature), Bytes_val(scalar),
      ctypes_size_t_val(nbits), Bytes_val(msg), ctypes_size_t_val(msg_length),
      Bytes_val(aug), ctypes_size_t_val(aug_length));
  CAMLreturn(Val_int(r));
}

CAMLprim value caml_blst_pairing_chk_n_mul_n_aggr_pk_in_g1_stubs_bytecode(
    value *argv, int argn) {
  return caml_blst_pairing_chk_n_mul_n_aggr_pk_in_g1_stubs(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
      argv[8], argv[9], argv[10]);
}

// Pk in G2, signature in G1
CAMLprim value caml_blst_sk_to_pk_in_g2_stubs(value buffer, value scalar) {
  CAMLparam2(buffer, scalar);
  blst_sk_to_pk_in_g2(Blst_p2_val(buffer), Blst_scalar_val(scalar));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_sign_pk_in_g2_stubs(value buffer, value p, value s) {
  CAMLparam3(buffer, p, s);
  blst_sign_pk_in_g2(Blst_p1_val(buffer), Blst_p1_val(p), Blst_scalar_val(s));
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_aggregate_signature_pk_in_g2_stubs(
    value buffer, value g1, value g2, value msg, value msg_length, value aug,
    value aug_length) {
  CAMLparam5(buffer, g1, g2, msg, msg_length);
  CAMLxparam2(aug, aug_length);
  int r = blst_pairing_aggregate_pk_in_g2(
      Blst_pairing_val(buffer), Blst_p2_affine_val(g1), Blst_p1_affine_val(g2),
      Bytes_val(msg), ctypes_size_t_val(msg_length), Bytes_val(aug),
      ctypes_size_t_val(aug_length));
  CAMLreturn(Val_int(r));
}

CAMLprim value
caml_blst_aggregate_signature_pk_in_g2_stubs_bytecode(value *argv, int argn) {
  return caml_blst_aggregate_signature_pk_in_g2_stubs(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6]);
}

CAMLprim value caml_blst_pairing_chk_n_mul_n_aggr_pk_in_g2_stubs(
    value buffer, value pk, value check_pk, value signature,
    value check_signature, value scalar, value nbits, value msg,
    value msg_length, value aug, value aug_length) {
  CAMLparam5(buffer, pk, check_pk, signature, check_signature);
  CAMLxparam5(scalar, nbits, msg, msg_length, aug);
  CAMLxparam1(aug_length);
  blst_p1_affine *signature_c;
  if (Is_none(signature)) {
    signature_c = NULL;
  } else {
    signature_c = Blst_p1_affine_val(Some_val(signature));
  }
  int r = blst_pairing_chk_n_mul_n_aggr_pk_in_g2(
      Blst_pairing_val(buffer), Blst_p2_affine_val(pk), Bool_val(check_pk),
      signature_c, Bool_val(check_signature), Bytes_val(scalar),
      ctypes_size_t_val(nbits), Bytes_val(msg), ctypes_size_t_val(msg_length),
      Bytes_val(aug), ctypes_size_t_val(aug_length));
  CAMLreturn(Val_int(r));
}

CAMLprim value caml_blst_pairing_chk_n_mul_n_aggr_pk_in_g2_stubs_bytecode(
    value *argv, int argn) {
  return caml_blst_pairing_chk_n_mul_n_aggr_pk_in_g2_stubs(
      argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7],
      argv[8], argv[9], argv[10]);
}

// Hypothesis: jacobian_list and scalars are arrays of size *at least* start +
// npoints
CAMLprim value caml_blst_g1_pippenger_stubs(value buffer, value jacobian_list,
                                            value scalars, value start,
                                            value npoints) {
  CAMLparam5(buffer, jacobian_list, scalars, start, npoints);
  size_t npoints_c = ctypes_size_t_val(npoints);
  size_t start_c = ctypes_size_t_val(start);

  blst_p1_affine **addr_ps =
      (blst_p1_affine **)calloc(npoints_c, sizeof(blst_p1_affine *));
  if (addr_ps == NULL) {
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }
  blst_p1_affine *ps =
      (blst_p1_affine *)calloc(npoints_c, sizeof(blst_p1_affine));
  if (ps == NULL) {
    free(addr_ps);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }

  byte **addr_scalars_bs = (byte **)calloc(npoints_c, sizeof(byte *));
  if (addr_scalars_bs == NULL) {
    free(addr_ps);
    free(ps);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }
  byte *scalars_bs = (byte *)calloc(npoints_c * 32, sizeof(byte));
  if (scalars_bs == NULL) {
    free(addr_ps);
    free(ps);
    free(addr_scalars_bs);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }

  blst_scalar scalar;

  for (int i = 0; i < npoints_c; i++) {
    blst_p1_to_affine(ps + i, Blst_p1_val(Field(jacobian_list, start_c + i)));
    blst_scalar_from_fr(&scalar, Blst_fr_val(Field(scalars, start_c + i)));
    blst_lendian_from_scalar(scalars_bs + i * 32, &scalar);
    addr_scalars_bs[i] = scalars_bs + i * 32;
    addr_ps[i] = ps + i;
  }
  void *scratch = calloc(1, blst_p1s_mult_pippenger_scratch_sizeof(npoints_c));
  if (scratch == NULL) {
    free(addr_ps);
    free(ps);
    free(addr_scalars_bs);
    free(scalars_bs);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }

  blst_p1s_mult_pippenger(Blst_p1_val(buffer), addr_ps, npoints_c,
                          addr_scalars_bs, 256, scratch);

  free(addr_ps);
  free(ps);
  free(addr_scalars_bs);
  free(scalars_bs);
  free(scratch);

  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

// Hypothesis: jacobian_list and scalars are arrays of size *at least* start +
// npoints
CAMLprim value caml_blst_g2_pippenger_stubs(value buffer, value jacobian_list,
                                            value scalars, value start,
                                            value npoints) {
  CAMLparam5(buffer, jacobian_list, scalars, start, npoints);
  size_t npoints_c = ctypes_size_t_val(npoints);
  size_t start_c = ctypes_size_t_val(start);

  blst_p2_affine **addr_ps =
      (blst_p2_affine **)calloc(npoints_c, sizeof(blst_p2_affine *));
  if (addr_ps == NULL) {
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }
  blst_p2_affine *ps =
      (blst_p2_affine *)calloc(npoints_c, sizeof(blst_p2_affine));
  if (ps == NULL) {
    free(addr_ps);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }
  *addr_ps = ps;

  byte **addr_scalars_bs = (byte **)calloc(npoints_c, sizeof(byte *));
  if (addr_scalars_bs == NULL) {
    free(addr_ps);
    free(ps);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }
  byte *scalars_bs = (byte *)calloc(npoints_c * 32, sizeof(byte));
  if (scalars_bs == NULL) {
    free(addr_ps);
    free(ps);
    free(addr_scalars_bs);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }
  blst_scalar scalar;

  for (int i = 0; i < npoints_c; i++) {
    blst_p2_to_affine(ps + i, Blst_p2_val(Field(jacobian_list, start_c + i)));
    blst_scalar_from_fr(&scalar, Blst_fr_val(Field(scalars, start_c + i)));
    blst_lendian_from_scalar(scalars_bs + i * 32, &scalar);
    addr_scalars_bs[i] = scalars_bs + i * 32;
    addr_ps[i] = ps + i;
  }

  void *scratch = calloc(1, blst_p2s_mult_pippenger_scratch_sizeof(npoints_c));
  if (scratch == NULL) {
    free(addr_ps);
    free(ps);
    free(addr_scalars_bs);
    free(scalars_bs);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }

  blst_p2s_mult_pippenger(Blst_p2_val(buffer), addr_ps, npoints_c,
                          addr_scalars_bs, 256, scratch);

  free(addr_ps);
  free(ps);
  free(addr_scalars_bs);
  free(scalars_bs);
  free(scratch);

  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

// Hypothesis: fr_array_left and fr_array_right are both *at least* of size
// length
CAMLprim value caml_blst_fr_inner_product_stubs(value buffer,
                                                value fr_array_left,
                                                value fr_array_right,
                                                value length) {
  CAMLparam4(buffer, fr_array_left, fr_array_right, length);
  blst_fr *tmp = (blst_fr *)(calloc(1, sizeof(blst_fr)));
  blst_fr *buffer_c = Blst_fr_val(buffer);
  int length_c = Int_val(length);
  for (int i = 0; i < length_c; i++) {
    blst_fr_mul(tmp, Blst_fr_val(Field(fr_array_left, i)),
                Blst_fr_val(Field(fr_array_right, i)));
    blst_fr_add(buffer_c, tmp, buffer_c);
  }
  free(tmp);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

static struct custom_operations blst_p1_affine_array_ops = {
    "blst_p1_affine_array",     custom_finalize_default,
    custom_compare_default,     custom_hash_default,
    custom_serialize_default,   custom_deserialize_default,
    custom_compare_ext_default, custom_fixed_length_default};

CAMLprim value allocate_p1_affine_array_stubs(value n) {
  CAMLparam1(n);
  int n_c = Int_val(n);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_p1_affine_array_ops,
                            sizeof(blst_p1_affine) * n_c, 0, 1);
  CAMLreturn(block);
}

CAMLprim value caml_blst_p1_affine_array_set_p1_points_stubs(value buffer,
                                                             value l, value n) {
  CAMLparam3(buffer, l, n);
  int n_c = Int_val(n);
  blst_p1_affine *buffer_c = Blst_p1_affine_val(buffer);

  for (int i = 0; i < n_c; i++) {
    blst_p1 *p = Blst_p1_val(Field(l, i));
    blst_p1_to_affine(buffer_c + i, p);
  }
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

// NB: we do not check i is smaller than the array size because it is supposed
// to be done on the caml side
CAMLprim value caml_blst_p1_affine_array_get_stubs(value buffer, value list,
                                                   value i) {
  CAMLparam3(buffer, list, i);
  blst_p1 *buffer_c = Blst_p1_val(buffer);
  blst_p1_affine *list_c = Blst_p1_affine_val(list);
  int i_c = Int_val(i);

  blst_p1_from_affine(buffer_c, list_c + i_c);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

// Hypothesis: affine_list and scalars are arrays of size *at least* start +
// length
CAMLprim value caml_blst_g1_pippenger_contiguous_affine_array_stubs(
    value buffer, value affine_list, value scalars, value start, value len) {
  CAMLparam5(buffer, affine_list, scalars, start, len);
  size_t start_c = ctypes_size_t_val(start);
  size_t len_c = ctypes_size_t_val(len);
  blst_p1_affine *affine_list_c = Blst_p1_affine_val(affine_list);

  blst_p1_affine **addr_ps =
      (blst_p1_affine **)calloc(len_c, sizeof(blst_p1_affine *));
  if (addr_ps == NULL) {
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }

  byte **addr_scalars_bs = (byte **)calloc(len_c, sizeof(byte *));
  if (addr_scalars_bs == NULL) {
    free(addr_ps);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }
  byte *scalars_bs = (byte *)calloc(len_c * 32, sizeof(byte));
  if (scalars_bs == NULL) {
    free(addr_ps);
    free(addr_scalars_bs);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }
  blst_scalar scalar;

  for (int i = 0; i < len_c; i++) {
    blst_scalar_from_fr(&scalar, Blst_fr_val(Field(scalars, start_c + i)));
    blst_lendian_from_scalar(scalars_bs + i * 32, &scalar);
    addr_scalars_bs[i] = scalars_bs + i * 32;
    addr_ps[i] = affine_list_c + start_c + i;
  }

  limb_t *scratch = calloc(1, blst_p1s_mult_pippenger_scratch_sizeof(len_c));
  if (scratch == NULL) {
    free(addr_ps);
    free(addr_scalars_bs);
    free(scalars_bs);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }

  blst_p1s_mult_pippenger(Blst_p1_val(buffer), addr_ps, len_c, addr_scalars_bs,
                          256, scratch);

  free(addr_ps);
  free(addr_scalars_bs);
  free(scalars_bs);
  free(scratch);

  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

static struct custom_operations blst_p2_affine_array_ops = {
    "blst_p2_affine_array",     custom_finalize_default,
    custom_compare_default,     custom_hash_default,
    custom_serialize_default,   custom_deserialize_default,
    custom_compare_ext_default, custom_fixed_length_default};

CAMLprim value allocate_p2_affine_array_stubs(value n) {
  CAMLparam1(n);
  int n_c = Int_val(n);
  CAMLlocal1(block);
  block = caml_alloc_custom(&blst_p2_affine_array_ops,
                            sizeof(blst_p2_affine) * n_c, 0, 1);
  CAMLreturn(block);
}

CAMLprim value caml_blst_p2_affine_array_set_p2_points_stubs(value buffer,
                                                             value l, value n) {
  CAMLparam3(buffer, l, n);
  int n_c = Int_val(n);
  blst_p2_affine *buffer_c = Blst_p2_affine_val(buffer);

  for (int i = 0; i < n_c; i++) {
    blst_p2 *p = Blst_p2_val(Field(l, i));
    blst_p2_to_affine(buffer_c + i, p);
  }
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

// NB: we do not check i is smaller than the array size because it is supposed
// to be done on the caml side
CAMLprim value caml_blst_p2_affine_array_get_stubs(value buffer, value list,
                                                   value i) {
  CAMLparam3(buffer, list, i);
  blst_p2 *buffer_c = Blst_p2_val(buffer);
  blst_p2_affine *list_c = Blst_p2_affine_val(list);
  int i_c = Int_val(i);

  blst_p2_from_affine(buffer_c, list_c + i_c);
  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}

CAMLprim value caml_blst_g2_pippenger_contiguous_affine_array_stubs(
    value buffer, value affine_list, value scalars, value start, value len) {
  CAMLparam5(buffer, affine_list, scalars, start, len);
  size_t start_c = ctypes_size_t_val(start);
  size_t len_c = ctypes_size_t_val(len);

  blst_p2_affine **addr_ps =
      (blst_p2_affine **)calloc(len_c, sizeof(blst_p2_affine *));
  if (addr_ps == NULL) {
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }

  byte **addr_scalars_bs = (byte **)calloc(len_c, sizeof(byte *));
  if (addr_scalars_bs == NULL) {
    free(addr_ps);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }
  byte *scalars_bs = (byte *)calloc(len_c * 32, sizeof(byte));
  if (scalars_bs == NULL) {
    free(addr_ps);
    free(addr_scalars_bs);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }

  blst_scalar scalar;

  for (int i = 0; i < len_c; i++) {
    blst_scalar_from_fr(&scalar, Blst_fr_val(Field(scalars, start_c + i)));
    blst_lendian_from_scalar(scalars_bs + i * 32, &scalar);
    addr_scalars_bs[i] = scalars_bs + i * 32;
    addr_ps[i] = Blst_p2_affine_val(affine_list) + start_c + i;
  }
  limb_t *scratch = calloc(1, blst_p2s_mult_pippenger_scratch_sizeof(len_c));
  if (scratch == NULL) {
    free(addr_ps);
    free(addr_scalars_bs);
    free(scalars_bs);
    CAMLreturn(CAML_BLS12_381_OUTPUT_OUT_OF_MEMORY);
  }

  blst_p2s_mult_pippenger(Blst_p2_val(buffer), addr_ps, len_c, addr_scalars_bs,
                          256, scratch);

  free(addr_ps);
  free(addr_scalars_bs);
  free(scalars_bs);
  free(scratch);

  CAMLreturn(CAML_BLS12_381_OUTPUT_SUCCESS);
}
