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

#ifndef AS3_VIRGIL_TICKET_HPP
#define AS3_VIRGIL_TICKET_HPP

#include <virgil/service/data/VirgilTicket.h>
using virgil::service::data::VirgilTicket;

#include <virgil/service/data/VirgilUniqueTicket.h>
using virgil::service::data::VirgilUniqueTicket;

#include <virgil/service/data/VirgilInfoTicket.h>
using virgil::service::data::VirgilInfoTicket;

#include "as3_utils.hpp"
#include "VirgilIdProvider.wrapper.hpp"

AS3_IMPL_DESTRUCTOR(VirgilTicket)
AS3_IMPL_VIRGIL_ID_PROVIDER(VirgilTicket)

AS3_DECL_FUNC(_wrap_VirgilTicket_createFromAsn1, "(asAsn1:ByteArray):int") {
AS3_THROWABLE_SECTION_START
    AS3_TO_C_BYTE_ARRAY(asAsn1, cAsn1);
    VirgilTicket *cTicket = VirgilTicket::createFromAsn1(cAsn1);
    AS3_RETURN_C_PTR(cTicket);
AS3_THROWABLE_SECTION_END
}

AS3_DECL_FUNC(_wrap_VirgilTicket_createFromJson, "(asJson:ByteArray):int") {
AS3_THROWABLE_SECTION_START
    AS3_TO_C_BYTE_ARRAY(asJson, cJson);
    VirgilTicket *cTicket = VirgilTicket::createFromAsn1(cJson);
    AS3_RETURN_C_PTR(cTicket);
AS3_THROWABLE_SECTION_END
}

AS3_DECL_FUNC(_wrap_VirgilTicket_isUniqueTicket, "(asSelf:int):Boolean") {
    AS3_TO_C_PTR(VirgilTicket, asSelf, cSelf);
    bool cBool = cSelf->isUniqueTicket();
    AS3_RETURN_C_BOOL(cBool);
}

AS3_DECL_FUNC(_wrap_VirgilTicket_asUniqueTicket, "(asSelf:int):int") {
AS3_THROWABLE_SECTION_START
    AS3_TO_C_PTR(VirgilTicket, asSelf, cSelf);
    const VirgilTicket& cTicket = cSelf->asUniqueTicket();
    AS3_RETURN_C_PTR(&cTicket);
AS3_THROWABLE_SECTION_END
}

AS3_DECL_FUNC(_wrap_VirgilTicket_isInfoTicket, "(asSelf:int):Boolean") {
    AS3_TO_C_PTR(VirgilTicket, asSelf, cSelf);
    bool cBool = cSelf->isInfoTicket();
    AS3_RETURN_C_BOOL(cBool);
}

AS3_DECL_FUNC(_wrap_VirgilTicket_asInfoTicket, "(asSelf:int):int") {
AS3_THROWABLE_SECTION_START
    AS3_TO_C_PTR(VirgilTicket, asSelf, cSelf);
    const VirgilTicket& cTicket = cSelf->asInfoTicket();
    AS3_RETURN_C_PTR(&cTicket);
AS3_THROWABLE_SECTION_END
}

#endif /* AS3_VIRGIL_TICKET_HPP */
