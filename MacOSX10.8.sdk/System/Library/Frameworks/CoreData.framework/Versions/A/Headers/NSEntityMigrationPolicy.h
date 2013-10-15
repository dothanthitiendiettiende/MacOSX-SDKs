/*
    NSEntityMigrationPolicy.h
    Core Data
    Copyright (c) 2004-2012 Apple Inc.
    All rights reserved.
*/

#import <Foundation/NSArray.h>
#import <Foundation/NSError.h>

#import <CoreData/CoreDataDefines.h>

/* To access the entity migration policy keys in property mapping value expressions implemented in source code use the constants as declared.  To access them in custom value expression strings in the mapping model editor in Xcode follow the syntax rules outlined in the predicate format string syntax guide and refer to them as:
 NSMigrationManagerKey           $manager
 NSMigrationSourceObjectKey      $source
 NSMigrationDestinationObjectKey $destination
 NSMigrationEntityMappingKey     $entityMapping
 NSMigrationPropertyMappingKey   $propertyMapping
 NSMigrationEntityPolicyKey      $entityPolicy
*/
COREDATA_EXTERN NSString * const NSMigrationManagerKey NS_AVAILABLE(10_5,3_0);
COREDATA_EXTERN NSString * const NSMigrationSourceObjectKey NS_AVAILABLE(10_5,3_0);
COREDATA_EXTERN NSString * const NSMigrationDestinationObjectKey NS_AVAILABLE(10_5,3_0);
COREDATA_EXTERN NSString * const NSMigrationEntityMappingKey NS_AVAILABLE(10_5,3_0);
COREDATA_EXTERN NSString * const NSMigrationPropertyMappingKey NS_AVAILABLE(10_5,3_0);
COREDATA_EXTERN NSString * const NSMigrationEntityPolicyKey NS_AVAILABLE(10_5,3_0);

@class NSManagedObject;
@class NSEntityMapping;
@class NSMigrationManager;

NS_CLASS_AVAILABLE(10_5,3_0)
@interface NSEntityMigrationPolicy : NSObject


/* Invoked by the migration manager at the start of a given entity mapping.  This is also the precursor to the creation step.
*/
- (BOOL)beginEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;


/* Invoked by the migration manager on each source instance (as specified by the sourceExpression in the mapping) to create the corresponding destination instance.  The method also associates the source and destination instances by calling NSMigrationManager's
associateSourceInstance:withDestinationInstance:forEntityMapping: method.  Subclass implementations of this method must be careful to 
associate the source and destination instances as required if super is not called. A return value of NO indicates an error.
*/
- (BOOL)createDestinationInstancesForSourceInstance:(NSManagedObject *)sInstance entityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;


/* Indicates the end of the creation step for the specified entity mapping, and the precursor to the next migration step.  Developers can override this method to set up or clean up information for further migration steps.
*/
- (BOOL)endInstanceCreationForEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;


/* Constructs the relationships between the newly-created destination instances.  The association lookup methods on the NSMigrationManager can be used to determine the appropriate relationship targets.  A return value of NO indicates an error.
*/
- (BOOL)createRelationshipsForDestinationInstance:(NSManagedObject *)dInstance entityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;

 
/* Indicates the end of the relationship creation step for the specified entity mapping.  This method is invoked after the createRelationshipsForDestinationInstance:entityMapping:manager:error: method, and can be used to clean up state from the creation of relationships, or prepare state for the performance of custom validation.
*/
- (BOOL)endRelationshipCreationForEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;


/* Invoked during the validation step of the entity migration policy, providing the option of performing custom validation on migrated objects.  (Implementors must manually obtain the collection of objects they are interested in validating.) 
*/
- (BOOL)performCustomValidationForEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;


/* Invoked by the migration manager at the end of a given entity mapping.  This is also the end to the validation step, which is the last step for migration.
*/
- (BOOL)endEntityMapping:(NSEntityMapping *)mapping manager:(NSMigrationManager *)manager error:(NSError **)error;

@end
