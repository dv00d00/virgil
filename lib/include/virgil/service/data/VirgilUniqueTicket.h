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

#ifndef VIRGIL_SERVICE_DATA_VIRGIL_UNIQUE_TICKET_H
#define VIRGIL_SERVICE_DATA_VIRGIL_UNIQUE_TICKET_H

#include <virgil/service/data/VirgilTicket.h>
using virgil::service::data::VirgilTicket;

#include <virgil/service/data/VirgilUniqueTicketType.h>

#include <virgil/VirgilByteArray.h>
using virgil::VirgilByteArray;

namespace virgil { namespace service { namespace data {

/**
 * @brief This class describes Virgil Security ticket that contains information about any unique identifier.
 *
 * The purpose of this ticket to describe unique identifiers as email, phone number, etc.
 */
class VirgilUniqueTicket : public VirgilTicket {
public:
    /**
     * @brief Returns class name.
     */
     static std::string ClassName();
public:
    /**
     * @brief Configures ticket with type VirgilUniqueTicketType_None and with empty value.
     * @note Use this constructor only in conjuction with demarshalling methods.
     * @see fromAsn1()
     * @see fromJson()
     */
    VirgilUniqueTicket();
    /**
     * @brief Configures ticket with specific type and value.
     */
    VirgilUniqueTicket(VirgilUniqueTicketType type, const VirgilByteArray& value);
    /**
     * @brief Polymorphic destructor.
     */
    virtual ~VirgilUniqueTicket() throw();
    /**
     * @return true.
     */
    virtual bool isUniqueTicket() const;
    /**
     * @name Accessors
     */
    ///@{
    /**
     * @return Unique identifier.
     */
    VirgilByteArray value() const;
    /**
     * @return ticket's type.
     */
    VirgilUniqueTicketType type() const;
    ///@}
    /**
     * @name VirgilAsn1Compatible implementation
     *
     * Marshalling format:
     *     {
     *         className UTF8String,
     *         type UTF8String,
     *         value OCTET STRING
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
     *        "class_name" : "UTF8String",
     *        "type" : "UTF8String",
     *        "value" : "Base64String"
     *    }
     */
    ///@{
    virtual Json::Value jsonWrite(Json::Value& childObject) const;
    virtual Json::Value jsonRead(const Json::Value& parentValue);
    ///@}
protected:
    /**
     * @brief Returns class name.
     */
    virtual std::string className() const;
private:
    VirgilUniqueTicketType type_;
    VirgilByteArray value_;
};

}}}

#endif /* VIRGIL_SERVICE_DATA_VIRGIL_UNIQUE_TICKET_H */
