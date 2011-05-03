//
//  WebSocket.h
//  WebSocketCore
//
//  Created by Mirek Rusin on 07/03/2011.
//  Copyright 2011 Inteliv Ltd. All rights reserved.
//

#ifndef __CORE_WEB_SOCKET__
#define __CORE_WEB_SOCKET__ 1

#include <CoreFoundation/CoreFoundation.h>
#include <unistd.h>
#include <netdb.h>

#import <CommonCrypto/CommonDigest.h>

#if (TARGET_OS_IPHONE)
#include <CFNetwork/CFNetwork.h>
#else
#include <CoreServices/CoreServices.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#endif

#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "WebSocketTypes.h"
#include "WebSocketClient.h"

#define __WebSocketMaxHeaderKeyLength 4096

#pragma mark Lifecycle

WebSocketRef WebSocketCreate  (CFAllocatorRef allocator, CFStringRef host, UInt16 port, void *userInfo);

// Create WebSocketRef using any host and any available port.
WebSocketRef WebSocketCreateWithUserInfo(CFAllocatorRef allocator, void *userInfo);

WebSocketRef WebSocketRetain  (WebSocketRef webSocket);
WebSocketRef WebSocketRelease (WebSocketRef webSocket);

UInt16 WebSocketGetPort(WebSocketRef webSocket);

void    WebSocketWriteWithString               (WebSocketRef webSocket, CFStringRef value);
CFIndex WebSocketWriteWithStringAndClientIndex (WebSocketRef webSocket, CFStringRef value, CFIndex index);

#pragma mark Callbacks

void WebSocketSetClientReadCallback(WebSocketRef webSocket, WebSocketDidClientReadCallback callback);

#pragma mark Internal, client management

CFIndex __WebSocketAppendClient (WebSocketRef webSocket, WebSocketClientRef client);
CFIndex __WebSocketRemoveClient (WebSocketRef webSocket, WebSocketClientRef client);

#pragma mark Internal, socket callback

void __WebSocketAcceptCallBack(CFSocketRef socket, CFSocketCallBackType type, CFDataRef address, const void *data, void *info);

#endif

