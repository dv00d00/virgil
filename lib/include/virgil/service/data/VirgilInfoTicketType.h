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

#ifndef VIRGIL_SERVICE_DATA_VIRGIL_INFO_TICKET_TYPE_H
#define VIRGIL_SERVICE_DATA_VIRGIL_INFO_TICKET_TYPE_H

#include <string>

/**
 * @brief VirgilInfoTicket types
 */
typedef enum {
    VirgilInfoTicketType_None = 0,
    VirgilInfoTicketType_FirstName,
    VirgilInfoTicketType_LastName,
    VirgilInfoTicketType_MiddleName,
    VirgilInfoTicketType_Nickname,
    VirgilInfoTicketType_BirthDate
} VirgilInfoTicketType;

/**
 * @brief Convert VirgilInfoTicketType to it string representation.
 */
std::string virgil_info_ticket_type_to_string(VirgilInfoTicketType type);
/**
 * @brief Convert VirgilInfoTicketType string representation to the type.
 */
VirgilInfoTicketType virgil_info_ticket_type_from_string(const std::string type);


#endif /* VIRGIL_SERVICE_DATA_VIRGIL_INFO_TICKET_TYPE_H */
