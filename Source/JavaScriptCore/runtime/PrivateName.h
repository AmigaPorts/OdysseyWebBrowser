/*
 * Copyright (C) 2012 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PrivateName_h
#define PrivateName_h

#include <wtf/text/StringImpl.h>

namespace JSC {

class PrivateName {
public:
    PrivateName()
        : m_impl(StringImpl::createSymbolEmpty())
    {
    }

    explicit PrivateName(StringImpl* uid)
        : m_impl(uid)
    {
        ASSERT(m_impl->isSymbol());
    }

    explicit PrivateName(const String& description)
        : m_impl(StringImpl::createSymbol(description.impl()))
    {
    }

    AtomicStringImpl* uid() const { return static_cast<AtomicStringImpl*>(m_impl.get()); }

    bool operator==(const PrivateName& other) const { return uid() == other.uid(); }
    bool operator!=(const PrivateName& other) const { return uid() != other.uid(); }

private:
    RefPtr<StringImpl> m_impl;
};

}

#endif
