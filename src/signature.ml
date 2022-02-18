module CommonStubs = struct
  type ctxt

  external keygen :
    Fr.Stubs.scalar ->
    Bytes.t ->
    Unsigned.Size_t.t ->
    Bytes.t ->
    Unsigned.Size_t.t ->
    unit = "caml_blst_signature_keygen_stubs"

  external pairing_init : bool -> Bytes.t -> Unsigned.Size_t.t -> ctxt
    = "caml_blst_pairing_init_stubs"

  external pairing_commit : ctxt -> int = "caml_blst_pairing_commit_stubs"

  external pairing_finalverify : ctxt -> bool
    = "caml_blst_pairing_finalverify_stubs"
end

let check_unicity_lst list =
  let hashtbl = Hashtbl.create (List.length list) in
  List.for_all
    (fun x ->
      let res = not (Hashtbl.mem hashtbl x) in
      Hashtbl.add hashtbl x 0 ;
      res)
    list

let with_aggregation_ctxt ciphersuite f =
  let ciphersuite_length = Bytes.length ciphersuite in
  let ctxt =
    CommonStubs.pairing_init
      true
      ciphersuite
      (Unsigned.Size_t.of_int ciphersuite_length)
  in
  f ctxt

type sk = Fr.Stubs.scalar

let sk_size_in_bytes = Fr.size_in_bytes

let sk_of_bytes_exn bytes =
  let buffer = Fr.Stubs.allocate_scalar () in
  if Bytes.length bytes > 32 then
    raise
      (Invalid_argument
         "Input should be maximum 32 bytes, encoded the secret key in little \
          endian")
  else
    let sk = Fr.of_bytes_exn bytes in
    ignore @@ Fr.Stubs.scalar_of_fr buffer sk ;
    buffer

let sk_of_bytes_opt bytes =
  try Some (sk_of_bytes_exn bytes) with Invalid_argument _ -> None

let sk_to_bytes sk =
  let bytes = Bytes.make 32 '\000' in
  ignore @@ Fr.Stubs.scalar_to_bytes_le bytes sk ;
  bytes

let generate_sk ?(key_info = Bytes.empty) ikm =
  let buffer_scalar = Fr.Stubs.allocate_scalar () in
  let key_info_length = Bytes.length key_info in
  let ikm_length = Bytes.length ikm in

  (* https://datatracker.ietf.org/doc/html/draft-irtf-cfrg-bls-signature-04
     Section 2.3 - KeyGen

     For security, IKM MUST be infeasible to guess, e.g., generated by a trusted
     source of randomness. IKM MUST be at least 32 bytes long, but it MAY be
     longer.

     Also, blst_keygen returns a vector of zero (commit
     095a8c53787d6c91b725152ebfbbf33acf05a931) if ikm is less than 32 bytes *)
  if ikm_length < 32 then
    raise
      (Invalid_argument
         "generate_sk: ikm argument must be at least 32 bytes long")
  else
    CommonStubs.keygen
      buffer_scalar
      ikm
      (Unsigned.Size_t.of_int ikm_length)
      key_info
      (Unsigned.Size_t.of_int key_info_length) ;
  buffer_scalar

module MinPk = struct
  module Stubs = struct
    external sk_to_pk : G1.t -> Fr.Stubs.scalar -> int
      = "caml_blst_sk_to_pk_in_g1_stubs"

    external sign : G2.t -> G2.t -> Fr.Stubs.scalar -> int
      = "caml_blst_sign_pk_in_g1_stubs"

    external aggregate_signature :
      CommonStubs.ctxt ->
      G1.t ->
      G2.t ->
      Bytes.t ->
      Unsigned.Size_t.t ->
      Bytes.t ->
      Unsigned.Size_t.t ->
      int
      = "caml_blst_aggregate_signature_pk_in_g1_stubs_bytecode" "caml_blst_aggregate_signature_pk_in_g1_stubs"

    external pairing_chk_n_mul_n_aggr_pk_in_g1 :
      CommonStubs.ctxt ->
      G1.Stubs.affine ->
      bool ->
      G2.Stubs.affine option ->
      bool ->
      Bytes.t ->
      Unsigned.Size_t.t ->
      Bytes.t ->
      Unsigned.Size_t.t ->
      Bytes.t ->
      Unsigned.Size_t.t ->
      int
      = "caml_blst_pairing_chk_n_mul_n_aggr_pk_in_g1_stubs_bytecode" "caml_blst_pairing_chk_n_mul_n_aggr_pk_in_g1_stubs"
  end

  type pk = Bytes.t

  let pk_size_in_bytes = G1.size_in_bytes / 2

  let unsafe_pk_of_bytes pk_bytes = Bytes.copy pk_bytes

  let pk_of_bytes_exn pk_bytes =
    let pk_opt = G1.of_compressed_bytes_opt pk_bytes in
    match pk_opt with
    | None ->
        raise
          (Invalid_argument
             (Printf.sprintf
                "%s is not a valid public key"
                Hex.(show (`Hex (Bytes.to_string pk_bytes)))))
    | Some _ -> Bytes.copy pk_bytes

  let pk_of_bytes_opt pk_bytes =
    let pk_opt = G1.of_compressed_bytes_opt pk_bytes in
    match pk_opt with None -> None | Some _ -> Some (Bytes.copy pk_bytes)

  let pk_to_bytes pk_bytes = Bytes.copy pk_bytes

  let derive_pk sk =
    let buffer_g1 = G1.Stubs.allocate_g1 () in
    ignore @@ Stubs.sk_to_pk buffer_g1 sk ;
    G1.to_compressed_bytes buffer_g1

  type signature = Bytes.t

  let signature_size_in_bytes = G2.size_in_bytes / 2

  let unsafe_signature_of_bytes bytes = Bytes.copy bytes

  let signature_of_bytes_exn bytes =
    let opt = G2.of_compressed_bytes_opt bytes in
    match opt with
    | None ->
        raise
          (Invalid_argument
             (Printf.sprintf
                "%s is not a valid signature"
                Hex.(show (`Hex (Bytes.to_string bytes)))))
    | Some _ -> Bytes.copy bytes

  let signature_of_bytes_opt bytes =
    let opt = G2.of_compressed_bytes_opt bytes in
    match opt with None -> None | Some _ -> Some (Bytes.copy bytes)

  let signature_to_bytes bytes = Bytes.copy bytes

  let core_sign sk message ciphersuite =
    let hash = G2.hash_to_curve message ciphersuite in
    let buffer = G2.Stubs.allocate_g2 () in
    ignore @@ Stubs.sign buffer hash sk ;
    G2.to_compressed_bytes buffer

  let core_verify pk msg signature_bytes ciphersuite =
    with_aggregation_ctxt ciphersuite (fun ctxt ->
        let msg_length = Bytes.length msg in
        let unsafe_signature_affine = G2.Stubs.allocate_g2_affine () in
        let res_signature =
          G2.Stubs.uncompress unsafe_signature_affine signature_bytes
        in
        let unsafe_pk_affine = G1.Stubs.allocate_g1_affine () in
        let res_pk = G1.Stubs.uncompress unsafe_pk_affine pk in
        if res_signature = 0 && res_pk = 0 then
          let res =
            Stubs.pairing_chk_n_mul_n_aggr_pk_in_g1
              ctxt
              unsafe_pk_affine
              (* the pk argument might not be in the subgroup even if the
                 decompression went successfull. `true` means the function must
                 verify the point is in the prime subgroup. IMPORTANT: a test
                 called test_sign_and_verify_with_a_pk_not_in_the_subgroup does
                 exist. We can check the verification is performed correctly
                 because this call returns 3, neaning the point is not in the
                 subgroup. However, even when not verifying the point is in the
                 subgroup, the verification will fail. *)
              true
              (Some unsafe_signature_affine)
              (* the signature argument might not be in the subgroup even if the
                 decompression went successfull. `true` means the function must
                 verify the point is in the prime subgroup. *)
              true
              (* scalar *)
              Bytes.empty
              Unsigned.Size_t.zero
              (* msg *)
              msg
              (Unsigned.Size_t.of_int msg_length)
              (* aug *)
              Bytes.empty
              Unsigned.Size_t.zero
          in
          if res = 0 then (
            ignore @@ CommonStubs.pairing_commit ctxt ;
            CommonStubs.pairing_finalverify ctxt)
          else false
        else false)

  let aggregate_signature_opt signatures =
    let rec aux signatures acc =
      match signatures with
      | [] -> Some acc
      | signature :: signatures -> (
          let signature = G2.of_compressed_bytes_opt signature in
          match signature with
          | None -> None
          | Some signature ->
              let acc = G2.(add signature acc) in
              aux signatures acc)
    in
    let res = aux signatures G2.zero in
    Option.map G2.to_compressed_bytes res

  let core_aggregate_verify pks_with_msgs aggregated_signature ciphersuite =
    let rec aux aggregated_signature pks_with_msgs ctxt =
      match pks_with_msgs with
      | (unsafe_pk_affine, msg) :: rest ->
          let msg_length = Bytes.length msg in
          (* sign the message *)
          let res =
            Stubs.pairing_chk_n_mul_n_aggr_pk_in_g1
              ctxt
              unsafe_pk_affine
              (* the signature argument might not be in the subgroup even if the
                 decompression went successfull. `true` means the function must
                 verify the point is in the prime subgroup. *)
              true
              aggregated_signature
              (* IMPORTANT: does not check signature is a point on the curve and
                 in the subgroup, it is verified by of_compressed_bytes_opt
                 below. *)
              false
              (* scalar *)
              Bytes.empty
              Unsigned.Size_t.zero
              (* msg *)
              msg
              (Unsigned.Size_t.of_int msg_length)
              (* aug *)
              Bytes.empty
              Unsigned.Size_t.zero
          in
          if res = 0 then
            (* signature: must be null except the first one *)
            aux None rest ctxt
          else false
      | [] -> true
    in
    (* IMPORTANT: the verification the aggregated signature is in the subgroup
       is performed here. *)
    let aggregated_signature_opt =
      G2.of_compressed_bytes_opt aggregated_signature
    in
    (* Converts the pk received as bytes in points on the curve. There are no
       checks about points belonging to the subgroup. It is verified when
       calling the auxiliary function. *)
    let pks = List.map fst pks_with_msgs in
    let are_pks_on_curve = ref true in
    let unsafe_pks_affine =
      List.map
        (fun pk_bytes ->
          let pk_affine = G1.Stubs.allocate_g1_affine () in
          let res = G1.Stubs.uncompress pk_affine pk_bytes in
          are_pks_on_curve := res = 0 && !are_pks_on_curve ;
          pk_affine)
        pks
    in
    let pks_with_msgs =
      List.map2
        (fun pk_affine (_, msg) -> (pk_affine, msg))
        unsafe_pks_affine
        pks_with_msgs
    in
    if !are_pks_on_curve then
      match aggregated_signature_opt with
      | None -> false
      | Some aggregated_signature ->
          with_aggregation_ctxt ciphersuite (fun ctxt ->
              let signature_affine = G2.Stubs.allocate_g2_affine () in
              ignore @@ G2.Stubs.to_affine signature_affine aggregated_signature ;
              let res = aux (Some signature_affine) pks_with_msgs ctxt in
              if res then (
                ignore @@ CommonStubs.pairing_commit ctxt ;
                CommonStubs.pairing_finalverify ctxt)
              else false)
    else false

  module Basic = struct
    let ciphersuite =
      Bytes.of_string "BLS_SIG_BLS12381G2_XMD:SHA-256_SSWU_RO_NUL_"

    let ciphersuite_length = Bytes.length ciphersuite

    let sign sk message = core_sign sk message ciphersuite

    let verify pk msg signature = core_verify pk msg signature ciphersuite

    let aggregate_verify pks_with_msgs aggregated_signature =
      let msgs = List.map snd pks_with_msgs in
      if check_unicity_lst msgs then
        core_aggregate_verify pks_with_msgs aggregated_signature ciphersuite
      else raise (Invalid_argument "Messages must be distinct")
  end

  module Aug = struct
    let ciphersuite =
      Bytes.of_string "BLS_SIG_BLS12381G2_XMD:SHA-256_SSWU_RO_AUG_"

    let ciphersuite_length = Bytes.length ciphersuite

    let sign sk msg =
      let pk = derive_pk sk in
      (* Important note: we concatenate with the compressed representation of
         the point! *)
      let msg = Bytes.concat Bytes.empty [pk; msg] in
      core_sign sk msg ciphersuite

    let verify pk msg signature =
      (* Important note: we concatenate with the compressed representation of
         the point! *)
      let msg = Bytes.concat Bytes.empty [pk; msg] in
      core_verify pk msg signature ciphersuite

    let aggregate_verify pks_with_msgs aggregated_signature =
      let pks_with_msgs =
        List.map
          (fun (pk, msg) -> (pk, Bytes.concat Bytes.empty [pk; msg]))
          pks_with_msgs
      in
      core_aggregate_verify pks_with_msgs aggregated_signature ciphersuite
  end

  module Pop = struct
    type proof = Bytes.t

    let sign sk message =
      let ciphersuite =
        Bytes.of_string "BLS_SIG_BLS12381G2_XMD:SHA-256_SSWU_RO_POP_"
      in
      core_sign sk message ciphersuite

    let verify pk msg signature =
      let ciphersuite =
        Bytes.of_string "BLS_SIG_BLS12381G2_XMD:SHA-256_SSWU_RO_POP_"
      in
      core_verify pk msg signature ciphersuite

    let pop_prove sk =
      let ciphersuite =
        Bytes.of_string "BLS_POP_BLS12381G2_XMD:SHA-256_SSWU_RO_POP_"
      in
      let pk = derive_pk sk in
      core_sign sk pk ciphersuite

    let pop_verify pk signature =
      let ciphersuite =
        Bytes.of_string "BLS_POP_BLS12381G2_XMD:SHA-256_SSWU_RO_POP_"
      in
      core_verify pk pk signature ciphersuite

    let aggregate_verify pks_with_pops msg aggregated_signature =
      let pks_bytes = List.map fst pks_with_pops in
      let pks_opts = List.map G1.of_compressed_bytes_opt pks_bytes in
      let pks_are_ok = List.for_all Option.is_some pks_opts in
      if not pks_are_ok then false
      else
        let pks = List.map Option.get pks_opts in
        let aggregated_pk = List.fold_left G1.add G1.zero pks in
        let aggregated_pk = G1.to_compressed_bytes aggregated_pk in
        let signature_check = verify aggregated_pk msg aggregated_signature in
        let pop_checks =
          List.for_all
            (fun (pk, signature) -> pop_verify pk signature)
            pks_with_pops
        in
        pop_checks && signature_check
  end
end

module MinSig = struct
  module Stubs = struct
    external sk_to_pk : G2.t -> Fr.Stubs.scalar -> int
      = "caml_blst_sk_to_pk_in_g2_stubs"

    external sign : G1.t -> G1.t -> Fr.Stubs.scalar -> int
      = "caml_blst_sign_pk_in_g2_stubs"

    external aggregate_signature :
      CommonStubs.ctxt ->
      G2.t ->
      G1.t ->
      Bytes.t ->
      Unsigned.Size_t.t ->
      Bytes.t ->
      Unsigned.Size_t.t ->
      int
      = "caml_blst_aggregate_signature_pk_in_g2_stubs_bytecode" "caml_blst_aggregate_signature_pk_in_g2_stubs"

    external pairing_chk_n_mul_n_aggr_pk_in_g2 :
      CommonStubs.ctxt ->
      G2.Stubs.affine ->
      bool ->
      G1.Stubs.affine option ->
      bool ->
      Bytes.t ->
      Unsigned.Size_t.t ->
      Bytes.t ->
      Unsigned.Size_t.t ->
      Bytes.t ->
      Unsigned.Size_t.t ->
      int
      = "caml_blst_pairing_chk_n_mul_n_aggr_pk_in_g2_stubs_bytecode" "caml_blst_pairing_chk_n_mul_n_aggr_pk_in_g2_stubs"
  end

  type pk = Bytes.t

  let pk_size_in_bytes = G2.size_in_bytes / 2

  let unsafe_pk_of_bytes pk_bytes = Bytes.copy pk_bytes

  let pk_of_bytes_exn pk_bytes =
    let pk_opt = G2.of_compressed_bytes_opt pk_bytes in
    match pk_opt with
    | None ->
        raise
          (Invalid_argument
             (Printf.sprintf
                "%s is not a valid public key"
                Hex.(show (`Hex (Bytes.to_string pk_bytes)))))
    | Some _ -> Bytes.copy pk_bytes

  let pk_of_bytes_opt pk_bytes =
    let pk_opt = G2.of_compressed_bytes_opt pk_bytes in
    match pk_opt with None -> None | Some _ -> Some (Bytes.copy pk_bytes)

  let pk_to_bytes pk_bytes = Bytes.copy pk_bytes

  let derive_pk sk =
    let buffer = G2.Stubs.allocate_g2 () in
    ignore @@ Stubs.sk_to_pk buffer sk ;
    G2.to_compressed_bytes buffer

  type signature = Bytes.t

  let signature_size_in_bytes = G1.size_in_bytes / 2

  let unsafe_signature_of_bytes bytes = Bytes.copy bytes

  let signature_of_bytes_exn bytes =
    let opt = G1.of_compressed_bytes_opt bytes in
    match opt with
    | None ->
        raise
          (Invalid_argument
             (Printf.sprintf
                "%s is not a valid signature"
                Hex.(show (`Hex (Bytes.to_string bytes)))))
    | Some _ -> Bytes.copy bytes

  let signature_of_bytes_opt bytes =
    let opt = G1.of_compressed_bytes_opt bytes in
    match opt with None -> None | Some _ -> Some (Bytes.copy bytes)

  let signature_to_bytes bytes = Bytes.copy bytes

  let core_sign sk message ciphersuite =
    let hash = G1.hash_to_curve message ciphersuite in
    let buffer = G1.Stubs.allocate_g1 () in
    ignore @@ Stubs.sign buffer hash sk ;
    G1.to_compressed_bytes buffer

  let core_verify pk msg signature_bytes ciphersuite =
    with_aggregation_ctxt ciphersuite (fun ctxt ->
        let msg_length = Bytes.length msg in
        let unsafe_signature_affine = G1.Stubs.allocate_g1_affine () in
        let res_signature =
          G1.Stubs.uncompress unsafe_signature_affine signature_bytes
        in
        let unsafe_pk_affine = G2.Stubs.allocate_g2_affine () in
        let res_pk = G2.Stubs.uncompress unsafe_pk_affine pk in
        if res_signature = 0 && res_pk = 0 then
          let res =
            Stubs.pairing_chk_n_mul_n_aggr_pk_in_g2
              ctxt
              unsafe_pk_affine
              (* the pk argument might not be in the subgroup even if the
                 decompression went successfull. `true` means the function must
                 verify the point is in the prime subgroup. IMPORTANT: a test
                 called test_sign_and_verify_with_a_pk_not_in_the_subgroup does
                 exist. We can check the verification is performed correctly
                 because this call returns 3, neaning the point is not in the
                 subgroup. However, even when not verifying the point is in the
                 subgroup, the verification will fail. *)
              true
              (Some unsafe_signature_affine)
              (* the signature argument might not be in the subgroup even if the
                 decompression went successfull. `true` means the function must
                 verify the point is in the prime subgroup. *)
              true
              (* scalar *)
              Bytes.empty
              Unsigned.Size_t.zero
              (* msg *)
              msg
              (Unsigned.Size_t.of_int msg_length)
              (* aug *)
              Bytes.empty
              Unsigned.Size_t.zero
          in
          if res = 0 then (
            ignore @@ CommonStubs.pairing_commit ctxt ;
            CommonStubs.pairing_finalverify ctxt)
          else false
        else false)

  let aggregate_signature_opt signatures =
    let rec aux signatures acc =
      match signatures with
      | [] -> Some acc
      | signature :: signatures -> (
          let signature = G1.of_compressed_bytes_opt signature in
          match signature with
          | None -> None
          | Some signature ->
              let acc = G1.(add signature acc) in
              aux signatures acc)
    in
    let res = aux signatures G1.zero in
    Option.map G1.to_compressed_bytes res

  let core_aggregate_verify pks_with_msgs aggregated_signature ciphersuite =
    let rec aux aggregated_signature pks_with_msgs ctxt =
      match pks_with_msgs with
      | (unsafe_pk_affine, msg) :: rest ->
          let msg_length = Bytes.length msg in
          (* sign the message *)
          let res =
            Stubs.pairing_chk_n_mul_n_aggr_pk_in_g2
              ctxt
              unsafe_pk_affine
              (* the signature argument might not be in the subgroup even if the
                 decompression went successfull. `true` means the function must
                 verify the point is in the prime subgroup. *)
              true
              aggregated_signature
              (* IMPORTANT: does not check signature is a point on the curve and
                 in the subgroup, it is verified by of_compressed_bytes_opt
                 below. *)
              false
              (* scalar *)
              Bytes.empty
              Unsigned.Size_t.zero
              (* msg *)
              msg
              (Unsigned.Size_t.of_int msg_length)
              (* aug *)
              Bytes.empty
              Unsigned.Size_t.zero
          in
          if res = 0 then
            (* signature: must be null except the first one *)
            aux None rest ctxt
          else false
      | [] -> true
    in
    (* IMPORTANT: the verification the aggregated signature is in the subgroup
       is performed here. *)
    let aggregated_signature_opt =
      G1.of_compressed_bytes_opt aggregated_signature
    in
    (* Converts the pk received as bytes in points on the curve. There are no
       checks about points belonging to the subgroup. It is verified when
       calling the auxiliary function. *)
    let pks = List.map fst pks_with_msgs in
    let are_pks_on_curve = ref true in
    let unsafe_pks_affine =
      List.map
        (fun pk_bytes ->
          let pk_affine = G2.Stubs.allocate_g2_affine () in
          let res = G2.Stubs.uncompress pk_affine pk_bytes in
          are_pks_on_curve := res = 0 && !are_pks_on_curve ;
          pk_affine)
        pks
    in
    let pks_with_msgs =
      List.map2
        (fun pk_affine (_, msg) -> (pk_affine, msg))
        unsafe_pks_affine
        pks_with_msgs
    in
    if !are_pks_on_curve then
      match aggregated_signature_opt with
      | None -> false
      | Some aggregated_signature ->
          with_aggregation_ctxt ciphersuite (fun ctxt ->
              let signature_affine = G1.Stubs.allocate_g1_affine () in
              ignore @@ G1.Stubs.to_affine signature_affine aggregated_signature ;
              let res = aux (Some signature_affine) pks_with_msgs ctxt in
              if res then (
                ignore @@ CommonStubs.pairing_commit ctxt ;
                CommonStubs.pairing_finalverify ctxt)
              else false)
    else false

  module Basic = struct
    let ciphersuite =
      Bytes.of_string "BLS_SIG_BLS12381G1_XMD:SHA-256_SSWU_RO_NUL_"

    let ciphersuite_length = Bytes.length ciphersuite

    let sign sk message = core_sign sk message ciphersuite

    let verify pk msg signature = core_verify pk msg signature ciphersuite

    let aggregate_verify pks_with_msgs aggregated_signature =
      let msgs = List.map snd pks_with_msgs in
      if check_unicity_lst msgs then
        core_aggregate_verify pks_with_msgs aggregated_signature ciphersuite
      else raise (Invalid_argument "Messages must be distinct")
  end

  module Aug = struct
    let ciphersuite =
      Bytes.of_string "BLS_SIG_BLS12381G1_XMD:SHA-256_SSWU_RO_AUG_"

    let ciphersuite_length = Bytes.length ciphersuite

    let sign sk msg =
      let pk = derive_pk sk in
      (* Important note: we concatenate with the compressed representation of
         the point! *)
      let msg = Bytes.concat Bytes.empty [pk; msg] in
      core_sign sk msg ciphersuite

    let verify pk msg signature =
      (* Important note: we concatenate with the compressed representation of
         the point! *)
      let msg = Bytes.concat Bytes.empty [pk; msg] in
      core_verify pk msg signature ciphersuite

    let aggregate_verify pks_with_msgs aggregated_signature =
      let pks_with_msgs =
        List.map
          (fun (pk, msg) -> (pk, Bytes.concat Bytes.empty [pk; msg]))
          pks_with_msgs
      in
      core_aggregate_verify pks_with_msgs aggregated_signature ciphersuite
  end

  module Pop = struct
    type proof = Bytes.t

    let sign sk message =
      let ciphersuite =
        Bytes.of_string "BLS_SIG_BLS12381G1_XMD:SHA-256_SSWU_RO_POP_"
      in
      core_sign sk message ciphersuite

    let verify pk msg signature =
      let ciphersuite =
        Bytes.of_string "BLS_SIG_BLS12381G1_XMD:SHA-256_SSWU_RO_POP_"
      in
      core_verify pk msg signature ciphersuite

    let pop_prove sk =
      let ciphersuite =
        Bytes.of_string "BLS_POP_BLS12381G1_XMD:SHA-256_SSWU_RO_POP_"
      in
      let pk = derive_pk sk in
      core_sign sk pk ciphersuite

    let pop_verify pk signature =
      let ciphersuite =
        Bytes.of_string "BLS_POP_BLS12381G1_XMD:SHA-256_SSWU_RO_POP_"
      in
      core_verify pk pk signature ciphersuite

    let aggregate_verify pks_with_pops msg aggregated_signature =
      let pks_bytes = List.map fst pks_with_pops in
      let pks_opts = List.map G2.of_compressed_bytes_opt pks_bytes in
      let pks_are_ok = List.for_all Option.is_some pks_opts in
      if not pks_are_ok then false
      else
        let pks = List.map Option.get pks_opts in
        let aggregated_pk = List.fold_left G2.add G2.zero pks in
        let aggregated_pk = G2.to_compressed_bytes aggregated_pk in
        let signature_check = verify aggregated_pk msg aggregated_signature in
        let pop_checks =
          List.for_all
            (fun (pk, signature) -> pop_verify pk signature)
            pks_with_pops
        in
        pop_checks && signature_check
  end
end
