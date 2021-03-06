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

#include <virgil/crypto/asn1/VirgilAsn1Writer.h>
using virgil::crypto::asn1::VirgilAsn1Writer;

#include <virgil/VirgilByteArray.h>
using virgil::VirgilByteArray;

#include <virgil/crypto/PolarsslException.h>
#include <virgil/crypto/VirgilCryptoException.h>
using virgil::crypto::VirgilCryptoException;

#include <cstddef>
#include <climits>
#include <cstring>
#include <algorithm>
#include <stdexcept>
#include <polarssl/asn1write.h>

static const size_t kBufLenDefault = 2048;

static const size_t kAsn1TagValueSize = 1;
static const size_t kAsn1LengthValueSize = 3;
static const size_t kAsn1IntegerValueSize = kAsn1TagValueSize + kAsn1LengthValueSize + 8;

#define RETURN_POINTER_DIFF_AFTER_INVOCATION(pointer,invocation) \
do { \
    unsigned char *before = pointer; \
    invocation; \
    unsigned char *after = pointer; \
    return (ptrdiff_t)(before - after); \
} while(0);

VirgilAsn1Writer::VirgilAsn1Writer() : p_(0), start_(0), buf_(0), bufLen_(0) {
    this->reset();
}

VirgilAsn1Writer::~VirgilAsn1Writer() throw() {
    dispose();
}

void VirgilAsn1Writer::reset() {
    dispose();
    relocateBuffer(kBufLenDefault);
}

VirgilByteArray VirgilAsn1Writer::finish() {
    checkState();
    VirgilByteArray result = VIRGIL_BYTE_ARRAY_FROM_PTR_AND_LEN(p_, bufLen_ - (p_ - start_));
    dispose();
    return result;
}

size_t VirgilAsn1Writer::writeInteger(int value) {
    checkState();
    ensureBufferEnough(kAsn1IntegerValueSize);
    RETURN_POINTER_DIFF_AFTER_INVOCATION(p_,
        POLARSSL_ERROR_HANDLER(
            ::asn1_write_int(&p_, start_, value)
        )
    );
}

size_t VirgilAsn1Writer::writeNull() {
    checkState();
    ensureBufferEnough(kAsn1TagValueSize);
    RETURN_POINTER_DIFF_AFTER_INVOCATION(p_,
        POLARSSL_ERROR_HANDLER(
            ::asn1_write_null(&p_, start_)
        )
    );
}

size_t VirgilAsn1Writer::writeOctetString(const VirgilByteArray& data) {
    checkState();
    ensureBufferEnough(kAsn1TagValueSize + kAsn1LengthValueSize + data.size());
    RETURN_POINTER_DIFF_AFTER_INVOCATION(p_,
        POLARSSL_ERROR_HANDLER(
            ::asn1_write_octet_string(&p_, start_, VIRGIL_BYTE_ARRAY_TO_PTR_AND_LEN(data))
        )
    );
}

size_t VirgilAsn1Writer::writeUTF8String(const VirgilByteArray& data) {
    checkState();
    ensureBufferEnough(kAsn1TagValueSize + kAsn1LengthValueSize + data.size());
    RETURN_POINTER_DIFF_AFTER_INVOCATION(p_,
        {
            POLARSSL_ERROR_HANDLER(
                ::asn1_write_raw_buffer(&p_, start_, VIRGIL_BYTE_ARRAY_TO_PTR_AND_LEN(data))
            );
            POLARSSL_ERROR_HANDLER(
                ::asn1_write_len(&p_, start_, data.size())
            );
            POLARSSL_ERROR_HANDLER(
                ::asn1_write_tag(&p_, start_, ASN1_UTF8_STRING)
            );
        }
    );
}

size_t VirgilAsn1Writer::writeContextTag(unsigned char tag, size_t len) {
    if (tag > 0x1F) {
        throw VirgilCryptoException("Tag value is too big, MAX value is 31.");
    }
    checkState();
    ensureBufferEnough(kAsn1TagValueSize);
    RETURN_POINTER_DIFF_AFTER_INVOCATION(p_,
        {
            POLARSSL_ERROR_HANDLER(
                ::asn1_write_len(&p_, start_, len)
            );
            POLARSSL_ERROR_HANDLER(
                ::asn1_write_tag(&p_, start_, ASN1_CONTEXT_SPECIFIC | ASN1_CONSTRUCTED | tag);
            );
        }
    );
}

size_t VirgilAsn1Writer::writeData(const VirgilByteArray& data) {
    checkState();
    ensureBufferEnough(data.size());
    RETURN_POINTER_DIFF_AFTER_INVOCATION(p_,
        {
            POLARSSL_ERROR_HANDLER(
                ::asn1_write_raw_buffer(&p_, start_, VIRGIL_BYTE_ARRAY_TO_PTR_AND_LEN(data))
            );
        }
    );
}


size_t VirgilAsn1Writer::writeOID(const std::string& oid) {
    checkState();
    ensureBufferEnough(kAsn1TagValueSize + oid.size());
    RETURN_POINTER_DIFF_AFTER_INVOCATION(p_,
        {
            POLARSSL_ERROR_HANDLER(
                ::asn1_write_oid(&p_, start_, oid.c_str(), oid.size())
            );
        }
    );
}

size_t VirgilAsn1Writer::writeSequence(size_t len) {
    checkState();
    ensureBufferEnough(kAsn1TagValueSize + kAsn1LengthValueSize);
    RETURN_POINTER_DIFF_AFTER_INVOCATION(p_,
        {
            POLARSSL_ERROR_HANDLER(
                ::asn1_write_len(&p_, start_, len)
            );
            POLARSSL_ERROR_HANDLER(
                ::asn1_write_tag(&p_, start_, ASN1_CONSTRUCTED | ASN1_SEQUENCE)
            );
        }
    );
}

size_t VirgilAsn1Writer::writeSet(const std::vector<VirgilByteArray>& set) {
    std::vector<VirgilByteArray> orderedSet = set;
    makeOrderedSet(orderedSet);
    RETURN_POINTER_DIFF_AFTER_INVOCATION(p_,
        {
            size_t len = 0;
            for (std::vector<VirgilByteArray>::const_reverse_iterator it = orderedSet.rbegin();
                    it != orderedSet.rend(); ++it) {
                len += it->size();
                ensureBufferEnough(it->size());
                POLARSSL_ERROR_HANDLER(
                    ::asn1_write_raw_buffer(&p_, start_, VIRGIL_BYTE_ARRAY_TO_PTR_AND_LEN((*it)))
                );
            }
            ensureBufferEnough(kAsn1LengthValueSize + kAsn1TagValueSize);
            POLARSSL_ERROR_HANDLER(
                ::asn1_write_len(&p_, start_, len)
            );
            POLARSSL_ERROR_HANDLER(
                ::asn1_write_tag(&p_, start_, ASN1_CONSTRUCTED | ASN1_SET)
            );
        }
    );
}

VirgilByteArray VirgilAsn1Writer::makeComparePadding(const VirgilByteArray& asn1, size_t finalSize) {
    VirgilByteArray result = asn1;
    if (result.size() >= finalSize) {
        return result;
    }
    VirgilByteArray::value_type smallestByte = 0x00;
    if (result.size() > 0) {
        smallestByte = *std::min_element(result.begin(), result.end());
        if (smallestByte != 0x00) {
            --smallestByte;
        }
    }
    result.resize(finalSize, smallestByte);
    return result;
}

bool VirgilAsn1Writer::compare(const VirgilByteArray& first, const VirgilByteArray& second) {
    if (first.size() > second.size()) {
        VirgilByteArray paddedSecond = makeComparePadding(second, first.size());
        return std::lexicographical_compare(first.begin(), first.end(), paddedSecond.begin(), paddedSecond.end());
    } else if (second.size() > first.size()) {
        VirgilByteArray paddedFirst = makeComparePadding(first, second.size());
        return std::lexicographical_compare(paddedFirst.begin(), paddedFirst.end(), second.begin(), second.end());
    } else {
        return std::lexicographical_compare(first.begin(), first.end(), second.begin(), second.end());
    }
}

void VirgilAsn1Writer::makeOrderedSet(std::vector<VirgilByteArray>& set) {
    std::sort(set.begin(), set.end(), VirgilAsn1Writer::compare);
}

void VirgilAsn1Writer::checkState() {
    if (p_ == 0 || start_ == 0) {
        throw VirgilCryptoException("Writer was not initialized - 'reset' method was not called.");
    }
}

void VirgilAsn1Writer::relocateBuffer(size_t newBufLen) {
    if (newBufLen < bufLen_) {
        throw VirgilCryptoException("ASN.1 buffer relocation failed: could not reserve space less than current.");
    }
    unsigned char *newBuf = new unsigned char[newBufLen];
    size_t writtenBytes = 0;
    memset(newBuf, 0x00, newBufLen);
    if (buf_ && p_ && start_) {
        writtenBytes = bufLen_ - (p_ - start_);
        memcpy(newBuf + newBufLen - writtenBytes, p_, writtenBytes);
        delete[] buf_;
    }
    buf_ = newBuf;
    bufLen_ = newBufLen;
    p_ = buf_ + bufLen_ - writtenBytes;
    start_ = buf_;
}

void VirgilAsn1Writer::ensureBufferEnough(size_t len) {
    checkState();
    size_t unusedSpace = (size_t)(p_ - start_);
    if (unusedSpace < len) {
        size_t usedSpace = size_t(start_ + bufLen_ - p_);
        size_t newBufLen = bufLen_;
        do {
            if (newBufLen < (UINT_MAX >> 1)) {
                newBufLen <<= 1;
            } else {
                throw std::overflow_error(std::string("VirgilAsn1Writer: ") +
                        "Internal buffer cannot be enlarged. Maximum size is reached.");
            }
        } while (newBufLen < usedSpace + len);
        relocateBuffer(newBufLen);
    }
}

void VirgilAsn1Writer::dispose() throw() {
    p_ = 0;
    start_ = 0;
    bufLen_ = 0;
    if (buf_) {
        delete[] buf_;
        buf_ = 0;
    }
}

