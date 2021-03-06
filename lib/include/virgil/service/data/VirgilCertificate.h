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

#ifndef VIRGIL_DATA_VIRGIL_CERTIFICATE_H
#define VIRGIL_DATA_VIRGIL_CERTIFICATE_H

#include <virgil/service/data/VirgilIdProvider.h>
using virgil::service::data::VirgilIdProvider;

#include <virgil/VirgilByteArray.h>
using virgil::VirgilByteArray;

#include <virgil/service/data/VirgilCertificateId.h>
using virgil::service::data::VirgilCertificateId;

namespace virgil { namespace service { namespace data {

/**
 * @brief This class describes Virgil Security certificate object.
 */
class VirgilCertificate : public VirgilIdProvider<VirgilCertificateId> {
public:
    /**
     * @brief Creates certificate object with underlying public key.
     * @note If publicKey is empty it can be restored with @see fromAsn1() and @see fromJson()
     */
    explicit VirgilCertificate(const VirgilByteArray& publicKey = VirgilByteArray());
    /**
     * @brief Polymorphic destructor.
     */
    virtual ~VirgilCertificate() throw();
    /**
     * @name Accessors
     */
    ///@{
    /**
     * @brief Returns certificate's public key.
     */
    VirgilByteArray publicKey() const;
    /**
     * @name VirgilAsn1Compatible implementation
     *
     * Marshalling format:
     *     VirgilCertificate ::= SEQUENCE {
     *         id VirgilCertificateId,
     *         publicKey OCTET STRING
     *     }
     *     VirgilCertificateId ::= SEQUENCE {
     *         accountId UTF8String,
     *         certificateId UTF8String
     *     }
     */
    ///@{
    virtual size_t asn1Write(VirgilAsn1Writer& asn1Writer, size_t childWrittenBytes = 0) const;
    virtual void asn1Read(VirgilAsn1Reader& asn1Reader);
    ///@}
    /**
     * @name VirgilJsonCompatible implementation
     *
     * Marshalling format:
     *    {
     *        "id" : {
     *            "account_id" : "UTF8String",
     *            "certificate_id" : "UTF8String"
     *        },
     *        "public_key" : "UTF8String"
     *    }
     */
    ///@{
    virtual Json::Value jsonWrite(Json::Value& childObject) const;
    virtual Json::Value jsonRead(const Json::Value& parentValue);
    ///@}
private:
    VirgilByteArray publicKey_;
};

}}}

#endif /* VIRGIL_DATA_VIRGIL_CERTIFICATE_H */
