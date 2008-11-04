/*
 * domain_event.h: domain event queue processing helpers
 *
 * Copyright (C) 2008 VirtualIron
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
 *
 * Author: Ben Guthro
 */

#include "internal.h"


#ifndef __DOMAIN_EVENT_H__
#define __DOMAIN_EVENT_H__

struct _virDomainEventCallback {
    virConnectPtr conn;
    virConnectDomainEventCallback cb;
    void *opaque;
};
typedef struct _virDomainEventCallback virDomainEventCallback;
typedef virDomainEventCallback *virDomainEventCallbackPtr;

struct _virDomainEventCallbackList {
    unsigned int count;
    virDomainEventCallbackPtr *callbacks;
};
typedef struct _virDomainEventCallbackList virDomainEventCallbackList;
typedef virDomainEventCallbackList *virDomainEventCallbackListPtr;

void virDomainEventCallbackListFree(virDomainEventCallbackListPtr list);

int virDomainEventCallbackListAdd(virConnectPtr conn,
                                  virDomainEventCallbackListPtr cbList,
                                  virConnectDomainEventCallback callback,
                                  void *opaque);

int virDomainEventCallbackListRemove(virConnectPtr conn,
                                     virDomainEventCallbackListPtr cbList,
                                     virConnectDomainEventCallback callback);

/**
 * Dispatching domain events that come in while
 * in a call / response rpc
 */
struct _virDomainEvent {
    virDomainPtr dom;
    virDomainEventType event;
};
typedef struct _virDomainEvent virDomainEvent;
typedef virDomainEvent *virDomainEventPtr;

struct _virDomainEventQueue {
    unsigned int count;
    virDomainEventPtr *events;
};
typedef struct _virDomainEventQueue virDomainEventQueue;
typedef virDomainEventQueue *virDomainEventQueuePtr;

int virDomainEventCallbackQueuePush(virDomainEventQueuePtr evtQueue,
                                    virDomainPtr dom,
                                    virDomainEventType event);

virDomainEventPtr
virDomainEventCallbackQueuePop(virDomainEventQueuePtr evtQueue);

void virDomainEventQueueFree(virDomainEventQueuePtr queue);


#endif
