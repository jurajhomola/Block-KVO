//
//  MTKObservingMacros.h
//  Block Key-Value Observing
//
//  Created by Martin Kiss on 9.2.13.
//  Copyright (c) 2013 iMartin Kiss. All rights reserved.
//



#define MTKObservePropertySelf(KEYPATH, TYPE, CODE) \
[self observeProperty:@(((void)(NO && ((void)self.KEYPATH, NO)), # KEYPATH)) withBlock:^(__weak typeof(self) self, TYPE old, TYPE new) CODE ];

#define MTKSelector(SELECTOR) \
{ [self SELECTOR]; }
