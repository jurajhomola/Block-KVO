//
//  NSObject+MTKObserving.h
//  MTK Key-Value Observing
//
//  Created by Martin Kiss on 14.7.12.
//  Copyright (c) 2012 iMartin Kiss. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MTKObserver.h"





@interface NSObject (MTKObserving)



#pragma mark Property Observations

- (MTKObserver *)observeProperty:(NSString *)keyPath;
- (MTKObserver *)map:(NSString *)sourceKeyPath to:(NSString *)destinationKeyPath transform:(id (^)(id value))transformationBlock;
- (MTKObserver *)map:(NSString *)sourceKeyPath to:(NSString *)destinationKeyPath null:(id)nullReplacement;



#pragma mark -

#pragma mark Legacy - Observe Properties
- (void)observeProperty:(NSString *)keyPath withBlock:(MTKBlockChange)observationBlock;
- (void)observeProperties:(NSArray *)keyPaths withBlock:(MTKBlockChangeMany)observationBlock;
- (void)observeProperty:(NSString *)keyPath withSelector:(SEL)observationSelector;
- (void)observeProperties:(NSArray *)keyPaths withSelector:(SEL)observationSelector;

#pragma mark Legacy - Observe Foreign Property
- (void)observeObject:(id)object property:(NSString *)keyPath withBlock:(MTKBlockForeignChange)block;
- (void)observeObject:(id)object properties:(NSArray *)keyPaths withBlock:(MTKBlockForeignChangeMany)block;
- (void)observeObject:(id)object property:(NSString *)keyPath withSelector:(SEL)selector;
- (void)observeObject:(id)object properties:(NSArray *)keyPaths withSelector:(SEL)selector;

#pragma mark Legacy - Observe Relationships
- (void)observeRelationship:(NSString *)keyPath changeBlock:(MTKBlockChange)changeBlock insertionBlock:(MTKBlockInsert)insertionBlock removalBlock:(MTKBlockRemove)removalBlock replacementBlock:(MTKBlockReplace)replacementBlock;
- (void)observeRelationship:(NSString *)keyPath changeBlock:(MTKBlockGeneric)changeBlock;

#pragma mark Legacy - Notifications
- (void)observeNotification:(NSString *)name fromObject:(id)object withBlock:(MTKBlockNotify)block;
- (void)observeNotification:(NSString *)name withBlock:(MTKBlockNotify)block;
- (void)observeNotifications:(NSArray *)names fromObjects:(NSArray *)objects withBlock:(MTKBlockNotify)block;

#pragma mark Legacy - Removing
- (void)removeAllObservations;
- (void)removeAllObservationsOfObject:(id)object;



@end



typedef id(^MTKMappingTransformBlock)(id);
extern MTKMappingTransformBlock const MTKMappingIsNilBlock;         // return @( value == nil );
extern MTKMappingTransformBlock const MTKMappingIsNotNilBlock;      // return @(  value != nil );
extern MTKMappingTransformBlock const MTKMappingInvertBooleanBlock; // return @( ! value.boolValue );
extern MTKMappingTransformBlock const MTKMappingURLFromString;      // return [NSURL URLWithString:value];




