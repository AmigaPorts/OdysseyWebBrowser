/*
 * Copyright (C) 2014 Apple Inc. All rights reserved.
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

#ifndef WKImmediateActionController_h
#define WKImmediateActionController_h

#if PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101000

#import "WKImmediateActionTypes.h"
#import "WebHitTestResult.h"
#import <WebCore/NSImmediateActionGestureRecognizerSPI.h>
#import <wtf/RetainPtr.h>

namespace WebKit {
class WebPageProxy;

enum class ImmediateActionState {
    None = 0,
    Pending,
    TimedOut,
    Ready
};
}

@class DDActionContext;
@class QLPreviewMenuItem;
@class WKView;

@interface WKImmediateActionController : NSObject <NSImmediateActionGestureRecognizerDelegate> {
@private
    WebKit::WebPageProxy *_page;
    WKView *_wkView;

    WebKit::ImmediateActionState _state;
    WebKit::WebHitTestResult::Data _hitTestResultData;
    BOOL _contentPreventsDefault;
    RefPtr<API::Object> _userData;
    _WKImmediateActionType _type;
    RetainPtr<NSImmediateActionGestureRecognizer> _immediateActionRecognizer;

    BOOL _hasActivatedActionContext;
    RetainPtr<DDActionContext> _currentActionContext;
    RetainPtr<QLPreviewMenuItem> _currentQLPreviewMenuItem;

    BOOL _hasActiveImmediateAction;
}

- (instancetype)initWithPage:(WebKit::WebPageProxy&)page view:(WKView *)wkView recognizer:(NSImmediateActionGestureRecognizer *)immediateActionRecognizer;
- (void)willDestroyView:(WKView *)view;
- (void)didPerformActionMenuHitTest:(const WebKit::WebHitTestResult::Data&)hitTestResult contentPreventsDefault:(BOOL)contentPreventsDefault userData:(API::Object*)userData;
- (void)dismissContentRelativeChildWindows;
- (BOOL)hasActiveImmediateAction;

@end

#endif // PLATFORM(MAC) && __MAC_OS_X_VERSION_MIN_REQUIRED >= 101000

#endif // WKImmediateActionController_h
