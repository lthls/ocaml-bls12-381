(*****************************************************************************)
(*                                                                           *)
(* Copyright (c) 2020-2021 Danny Willems <be.danny.willems@gmail.com>        *)
(*                                                                           *)
(* Permission is hereby granted, free of charge, to any person obtaining a   *)
(* copy of this software and associated documentation files (the "Software"),*)
(* to deal in the Software without restriction, including without limitation *)
(* the rights to use, copy, modify, merge, publish, distribute, sublicense,  *)
(* and/or sell copies of the Software, and to permit persons to whom the     *)
(* Software is furnished to do so, subject to the following conditions:      *)
(*                                                                           *)
(* The above copyright notice and this permission notice shall be included   *)
(* in all copies or substantial portions of the Software.                    *)
(*                                                                           *)
(* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR*)
(* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,  *)
(* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL   *)
(* THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER*)
(* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING   *)
(* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER       *)
(* DEALINGS IN THE SOFTWARE.                                                 *)
(*                                                                           *)
(*****************************************************************************)

module G1_stubs = Rustc_bls12_381_bindings.G1 (Rustc_bls12_381_stubs)

module Stubs = struct
  let size_in_bytes = 96

  let empty () = Bytes.make size_in_bytes '\000'

  let check_bytes bs =
    G1_stubs.uncompressed_check_bytes (Ctypes.ocaml_bytes_start bs)

  let check_compressed_bytes bs =
    G1_stubs.compressed_check_bytes (Ctypes.ocaml_bytes_start bs)

  let compressed_of_uncompressed bs =
    let res = Bytes.make (size_in_bytes / 2) '\000' in
    G1_stubs.compressed_of_uncompressed
      (Ctypes.ocaml_bytes_start res)
      (Ctypes.ocaml_bytes_start bs) ;
    res

  let uncompressed_of_compressed_unsafe bs =
    let res = empty () in
    G1_stubs.uncompressed_of_compressed_unsafe
      (Ctypes.ocaml_bytes_start res)
      (Ctypes.ocaml_bytes_start bs) ;
    res

  let is_zero bs = G1_stubs.is_zero (Ctypes.ocaml_bytes_start bs)

  let zero () =
    let bs = empty () in
    G1_stubs.zero (Ctypes.ocaml_bytes_start bs) ;
    bs

  let one () =
    let bs = empty () in
    G1_stubs.one (Ctypes.ocaml_bytes_start bs) ;
    bs

  let random () =
    let bs = empty () in
    G1_stubs.random (Ctypes.ocaml_bytes_start bs) ;
    bs

  let add x y =
    let buffer = empty () in
    G1_stubs.add
      (Ctypes.ocaml_bytes_start buffer)
      (Ctypes.ocaml_bytes_start x)
      (Ctypes.ocaml_bytes_start y) ;
    buffer

  let mul x y =
    let buffer = empty () in
    G1_stubs.mul
      (Ctypes.ocaml_bytes_start buffer)
      (Ctypes.ocaml_bytes_start x)
      (Ctypes.ocaml_bytes_start y) ;
    buffer

  let eq x y =
    G1_stubs.eq (Ctypes.ocaml_bytes_start x) (Ctypes.ocaml_bytes_start y)

  let negate x =
    let buffer = empty () in
    G1_stubs.negate
      (Ctypes.ocaml_bytes_start buffer)
      (Ctypes.ocaml_bytes_start x) ;
    buffer

  let double x =
    let buffer = empty () in
    G1_stubs.double
      (Ctypes.ocaml_bytes_start buffer)
      (Ctypes.ocaml_bytes_start x) ;
    buffer

  let build_from_components x y =
    let buffer = empty () in
    let res =
      G1_stubs.build_from_components
        (Ctypes.ocaml_bytes_start buffer)
        (Ctypes.ocaml_bytes_start x)
        (Ctypes.ocaml_bytes_start y)
    in
    if res = false then None else Some buffer
end

include Bls12_381_gen.G1.Make (Fr) (Stubs)
