//
//  MTKPropertyObserver.h
//  Block Key-Value Observing
//
//  Created by Martin Kiss on 14.9.13.
//  Copyright (c) 2013 iMartin Kiss. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>





#pragma mark Options



/// Options that alter behavior of MTKPropertyObserver
typedef enum : NSInteger {
    
    /// No special options, default behavior.
    MTKPropertyObserverOptionNone = 0,
    
    /// Initial observation will be ignored.
    MTKPropertyObserverOptionSkipInitial = 1 << 0,
    
    /// Changes will be reported 'before' instead of 'after' the change.
    MTKPropertyObserverOptionPriorChange = 1 << 1,
    
    /// Observer will also report changes that don't really change value using `-isEqual:` and `==`.
    MTKPropertyObserverOptionIncludeEqualChanges = 1 << 2,
    
    /// Observer will not report insertion, removal or replacement in case the targeted key-path is relationship.
    MTKPropertyObserverOptionRelationshipSettingsOnly = 1 << 4,
    
} MTKPropertyObserverOptions;





#pragma mark - Property Observer

@class MTKPropertyChange;



/// Object that can be used to observe properties that are KVO compliant.
@interface MTKPropertyObserver : NSObject



#pragma mark Configuration

/// Initializes property observer.
- (instancetype)initWithTarget:(NSObject *)object keyPath:(NSString *)keyPath options:(MTKPropertyObserverOptions)options;

/// Object on which the receiver is observing.
@property (nonatomic, readonly, assign) NSObject *target;

/// Key-path which is the receiver observing on its target.
@property (nonatomic, readonly, copy) NSString *keyPath;

/// Options specified during initialization.
@property (nonatomic, readonly, assign) MTKPropertyObserverOptions options;



#pragma mark Control

/// Booelan value indicating whether the receiver reports changes.
@property (nonatomic, readwrite, assign) BOOL enabled;

/// Invokes the block and the receiver will be disabled during that. Recursion-safe.
- (void)disableInBlock:(void (^)(void))block;

/// Removes the receiver from KVO observation. The receiver cannot be re-added again.
- (void)removeFromTarget;



#pragma mark Actions
/// All the following methods returns the receiver. They can be called on the receiver multiple times and they specify what actions the observer should perform when it detects changed property.


/// Reports changes with all available information into block. Main reporting method.
- (instancetype)reportChange:(void (^)(MTKPropertyChange *change))block;

/// Reports only current value.
- (instancetype)reportCurrentValue:(void (^)(id value))block;
/// Reports current and previous values.
- (instancetype)reportCurrentAndPreviousValues:(void (^)(id current, id previous))block;

/// Reports only current value that is unwrapped using `-boolValue`.
- (instancetype)reportBoolean:(void (^)(BOOL value))block;
/// Reports only current value that is unwrapped using `-integerValue`.
- (instancetype)reportInteger:(void (^)(NSInteger value))block;
/// Reports only current value that is unwrapped using `-doubleValue`.
- (instancetype)reportFloating:(void (^)(CGFloat value))block;

/// Reports only current value that is unwrapped using `-CGRectValue`.
- (instancetype)reportPoint:(void (^)(CGPoint point))block;
/// Reports only current value that is unwrapped using `-CGSizeValue`.
- (instancetype)reportSize:(void (^)(CGSize size))block;
/// Reports only current value that is unwrapped using `-CGRectValue`.
- (instancetype)reportRect:(void (^)(CGRect rect))block;
/// Reports only current value that is unwrapped using `-UIEdgeInsetsValue`.
- (instancetype)reportEdgeInsets:(void (^)(UIEdgeInsets insets))block;

/// Posts notification with given name.
- (instancetype)postNotificationName:(NSString *)name;
/// Posts notification with given name and includes the current value in user info under given key.
- (instancetype)postNotificationName:(NSString *)name currentValueKey:(NSString *)currentValueKey;

/// Sets the current value to another property using replacement for null, if any.
- (instancetype)setObject:(NSObject *)object keyPath:(NSString *)keyPath replacement:(id)nullReplacement;
/// Sets the current value to another property using transfomration block, if any.
- (instancetype)setObject:(NSObject *)object keyPath:(NSString *)keyPath transform:(id (^)(id value))transform;



@end





#pragma mark - Property Change



/// Object that represents proeprty change with many detailed values. You do not create objects of this class, they are produced by MTKPropertyObserver.
@interface MTKPropertyChange : NSObject



#pragma mark Common

/// Object whose property did (or will) change.
@property (nonatomic, readonly, strong) NSObject *target;

/// Key-path of proeprty on target which did (or will) change.
@property (nonatomic, readonly, copy) NSString *keyPath;

/// Current value of the given property.
@property (nonatomic, readonly, strong) id currentValue;

/// Whether the receiver represents future change. In case of YES, the current value of proeprty didn't change yet and the future value is not known.
@property (nonatomic, readonly) BOOL isPrior;

/// Whether this change was created as a part of observation initialization. In case of YES, the previous value is `nil`.
@property (nonatomic, readonly) BOOL isInitial;

/// Kind of the KVO change the receiver represents.
@property (nonatomic, readonly) NSKeyValueChange kind;



#pragma mark Setting

/// Previous value of property. Available only if the kind is NSKeyValueChangeSetting.
@property (nonatomic, readonly, strong) id previousValue;



#pragma mark Insertion

/// Inserted objects into relationship . Available only if the kind is NSKeyValueChangeInsertion, otherwise `nil`.
@property (nonatomic, readonly) id<NSFastEnumeration> inserted;

/// Indexes of inserted object into ordered relationship . Available only if the kind is NSKeyValueChangeInsertion and the container is ordered (NSArray or NSOrderedSet).
@property (nonatomic, readonly) NSIndexSet *insertedIndexes;



#pragma mark Removal

/// Removed objects from relationship . Available only if the kind is NSKeyValueChangeRemoval, otherwise `nil`.
@property (nonatomic, readonly) id<NSFastEnumeration> removed;

/// Past indexes of removed objects from ordered relationship. Available only if the kind is NSKeyValueChangeRemoval and the container is ordered (NSArray or NSOrderedSet).
@property (nonatomic, readonly) NSIndexSet *removedIndexes;



#pragma mark Replacement

/// Old objects in relationship, that were replaced by new ones. Available only if the kind is NSKeyValueChangeReplacement, otherwise `nil`.
@property (nonatomic, readonly) id<NSFastEnumeration> replaced;

/// New objects in relationship, that replaced old ones. Available only if the kind is NSKeyValueChangeReplacement, otherwise `nil`.
@property (nonatomic, readonly) id<NSFastEnumeration> replacements;

/// Indexes in ordered relationship, on which the replacement occured. Available only if the kind is NSKeyValueChangeReplacement and the container is ordered (NSArray or NSOrderedSet).
@property (nonatomic, readonly) NSIndexSet *replacedIndexes;



@end




