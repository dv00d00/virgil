/**
 * Copyright (C) 2014 Virgil Security Inc.
 *
 * Lead Maintainer: Virgil Security Inc. <support@virgilsecurity.com>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 *     (1) Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *
 *     (2) Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the documentation and/or other materials provided with the
 *     distribution.
 *
 *     (3) Neither the name of the copyright holder nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AS3_VIRGIL_CHUNK_CIPHER_HPP
#define AS3_VIRGIL_CHUNK_CIPHER_HPP

#include <virgil/service/VirgilChunkCipher.h>
using virgil::service::VirgilChunkCipher;

#include "as3_utils.hpp"

AS3_DECL_THROWABLE_CONSTRUCTOR(VirgilChunkCipher)
AS3_IMPL_DESTRUCTOR(VirgilChunkCipher)

AS3_DECL_FUNC(_wrap_VirgilChunkCipher_startEncryption, "(asSelf:int, asPreferredChunkSize:uint):uint") {
    AS3_TO_C_PTR(VirgilChunkCipher, asSelf, cSelf);
    AS3_TO_C_UINT(asPreferredChunkSize, cPreferredChunkSize);
AS3_THROWABLE_SECTION_START
    size_t cAdjustedChunkSize = cSelf->startEncryption(cPreferredChunkSize);
    AS3_RETURN_C_UINT(cAdjustedChunkSize);
AS3_THROWABLE_SECTION_END
}

AS3_DECL_FUNC(_wrap_VirgilChunkCipher_startDecryptionWithKey, "(asSelf:int, asCertificateId:ByteArray, "
        "asPrivateKey:ByteArray, asPrivateKeyPassword:ByteArray = null):uint") {
    AS3_TO_C_PTR(VirgilChunkCipher, asSelf, cSelf);
    AS3_TO_C_BYTE_ARRAY(asCertificateId, cCertificateId);
    AS3_TO_C_BYTE_ARRAY(asPrivateKey, cPrivateKey);
    AS3_TO_C_BYTE_ARRAY_OPT(asPrivateKeyPassword, cPrivateKeyPassword);
AS3_THROWABLE_SECTION_START
    size_t cAdjustedChunkSize = cSelf->startDecryptionWithKey(cCertificateId, cPrivateKey, cPrivateKeyPassword);
    AS3_RETURN_C_UINT(cAdjustedChunkSize);
AS3_THROWABLE_SECTION_END
}

AS3_DECL_FUNC(_wrap_VirgilChunkCipher_startDecryptionWithPassword, "(asSelf:int, asPassword:ByteArray):uint") {
    AS3_TO_C_PTR(VirgilChunkCipher, asSelf, cSelf);
    AS3_TO_C_BYTE_ARRAY(asPassword, cPassword);
AS3_THROWABLE_SECTION_START
    size_t cAdjustedChunkSize = cSelf->startDecryptionWithPassword(cPassword);
    AS3_RETURN_C_UINT(cAdjustedChunkSize);
AS3_THROWABLE_SECTION_END
}

AS3_DECL_FUNC(_wrap_VirgilChunkCipher_process, "(asSelf:int, asData:ByteArray):ByteArray") {
    AS3_TO_C_PTR(VirgilChunkCipher, asSelf, cSelf);
    AS3_TO_C_BYTE_ARRAY(asData, cData);
AS3_THROWABLE_SECTION_START
    VirgilByteArray cProcessedData = cSelf->process(cData);
    AS3_RETURN_C_BYTE_ARRAY(cProcessedData);
AS3_THROWABLE_SECTION_END
}

AS3_DECL_FUNC(_wrap_VirgilChunkCipher_finish, "(asSelf:int):void") {
    AS3_TO_C_PTR(VirgilChunkCipher, asSelf, cSelf);
AS3_THROWABLE_SECTION_START
    cSelf->finish();
AS3_THROWABLE_SECTION_END
    AS3_RETURN_VOID();
}

#endif /* AS3_VIRGIL_CHUNK_CIPHER_HPP */
