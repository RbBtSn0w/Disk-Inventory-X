// Generated by Apple Swift version 5.1.2 (swiftlang-1100.0.278 clang-1100.0.33.9)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wgcc-compat"

#if !defined(__has_include)
# define __has_include(x) 0
#endif
#if !defined(__has_attribute)
# define __has_attribute(x) 0
#endif
#if !defined(__has_feature)
# define __has_feature(x) 0
#endif
#if !defined(__has_warning)
# define __has_warning(x) 0
#endif

#if __has_include(<swift/objc-prologue.h>)
# include <swift/objc-prologue.h>
#endif

#pragma clang diagnostic ignored "-Wauto-import"
#include <Foundation/Foundation.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#if !defined(SWIFT_TYPEDEFS)
# define SWIFT_TYPEDEFS 1
# if __has_include(<uchar.h>)
#  include <uchar.h>
# elif !defined(__cplusplus)
typedef uint_least16_t char16_t;
typedef uint_least32_t char32_t;
# endif
typedef float swift_float2  __attribute__((__ext_vector_type__(2)));
typedef float swift_float3  __attribute__((__ext_vector_type__(3)));
typedef float swift_float4  __attribute__((__ext_vector_type__(4)));
typedef double swift_double2  __attribute__((__ext_vector_type__(2)));
typedef double swift_double3  __attribute__((__ext_vector_type__(3)));
typedef double swift_double4  __attribute__((__ext_vector_type__(4)));
typedef int swift_int2  __attribute__((__ext_vector_type__(2)));
typedef int swift_int3  __attribute__((__ext_vector_type__(3)));
typedef int swift_int4  __attribute__((__ext_vector_type__(4)));
typedef unsigned int swift_uint2  __attribute__((__ext_vector_type__(2)));
typedef unsigned int swift_uint3  __attribute__((__ext_vector_type__(3)));
typedef unsigned int swift_uint4  __attribute__((__ext_vector_type__(4)));
#endif

#if !defined(SWIFT_PASTE)
# define SWIFT_PASTE_HELPER(x, y) x##y
# define SWIFT_PASTE(x, y) SWIFT_PASTE_HELPER(x, y)
#endif
#if !defined(SWIFT_METATYPE)
# define SWIFT_METATYPE(X) Class
#endif
#if !defined(SWIFT_CLASS_PROPERTY)
# if __has_feature(objc_class_property)
#  define SWIFT_CLASS_PROPERTY(...) __VA_ARGS__
# else
#  define SWIFT_CLASS_PROPERTY(...)
# endif
#endif

#if __has_attribute(objc_runtime_name)
# define SWIFT_RUNTIME_NAME(X) __attribute__((objc_runtime_name(X)))
#else
# define SWIFT_RUNTIME_NAME(X)
#endif
#if __has_attribute(swift_name)
# define SWIFT_COMPILE_NAME(X) __attribute__((swift_name(X)))
#else
# define SWIFT_COMPILE_NAME(X)
#endif
#if __has_attribute(objc_method_family)
# define SWIFT_METHOD_FAMILY(X) __attribute__((objc_method_family(X)))
#else
# define SWIFT_METHOD_FAMILY(X)
#endif
#if __has_attribute(noescape)
# define SWIFT_NOESCAPE __attribute__((noescape))
#else
# define SWIFT_NOESCAPE
#endif
#if __has_attribute(warn_unused_result)
# define SWIFT_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
# define SWIFT_WARN_UNUSED_RESULT
#endif
#if __has_attribute(noreturn)
# define SWIFT_NORETURN __attribute__((noreturn))
#else
# define SWIFT_NORETURN
#endif
#if !defined(SWIFT_CLASS_EXTRA)
# define SWIFT_CLASS_EXTRA
#endif
#if !defined(SWIFT_PROTOCOL_EXTRA)
# define SWIFT_PROTOCOL_EXTRA
#endif
#if !defined(SWIFT_ENUM_EXTRA)
# define SWIFT_ENUM_EXTRA
#endif
#if !defined(SWIFT_CLASS)
# if __has_attribute(objc_subclassing_restricted)
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_subclassing_restricted)) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# else
#  define SWIFT_CLASS(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
#  define SWIFT_CLASS_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_CLASS_EXTRA
# endif
#endif
#if !defined(SWIFT_RESILIENT_CLASS)
# if __has_attribute(objc_class_stub)
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME) __attribute__((objc_class_stub))
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) __attribute__((objc_class_stub)) SWIFT_CLASS_NAMED(SWIFT_NAME)
# else
#  define SWIFT_RESILIENT_CLASS(SWIFT_NAME) SWIFT_CLASS(SWIFT_NAME)
#  define SWIFT_RESILIENT_CLASS_NAMED(SWIFT_NAME) SWIFT_CLASS_NAMED(SWIFT_NAME)
# endif
#endif

#if !defined(SWIFT_PROTOCOL)
# define SWIFT_PROTOCOL(SWIFT_NAME) SWIFT_RUNTIME_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
# define SWIFT_PROTOCOL_NAMED(SWIFT_NAME) SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_PROTOCOL_EXTRA
#endif

#if !defined(SWIFT_EXTENSION)
# define SWIFT_EXTENSION(M) SWIFT_PASTE(M##_Swift_, __LINE__)
#endif

#if !defined(OBJC_DESIGNATED_INITIALIZER)
# if __has_attribute(objc_designated_initializer)
#  define OBJC_DESIGNATED_INITIALIZER __attribute__((objc_designated_initializer))
# else
#  define OBJC_DESIGNATED_INITIALIZER
# endif
#endif
#if !defined(SWIFT_ENUM_ATTR)
# if defined(__has_attribute) && __has_attribute(enum_extensibility)
#  define SWIFT_ENUM_ATTR(_extensibility) __attribute__((enum_extensibility(_extensibility)))
# else
#  define SWIFT_ENUM_ATTR(_extensibility)
# endif
#endif
#if !defined(SWIFT_ENUM)
# define SWIFT_ENUM(_type, _name, _extensibility) enum _name : _type _name; enum SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# if __has_feature(generalized_swift_name)
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) enum _name : _type _name SWIFT_COMPILE_NAME(SWIFT_NAME); enum SWIFT_COMPILE_NAME(SWIFT_NAME) SWIFT_ENUM_ATTR(_extensibility) SWIFT_ENUM_EXTRA _name : _type
# else
#  define SWIFT_ENUM_NAMED(_type, _name, SWIFT_NAME, _extensibility) SWIFT_ENUM(_type, _name, _extensibility)
# endif
#endif
#if !defined(SWIFT_UNAVAILABLE)
# define SWIFT_UNAVAILABLE __attribute__((unavailable))
#endif
#if !defined(SWIFT_UNAVAILABLE_MSG)
# define SWIFT_UNAVAILABLE_MSG(msg) __attribute__((unavailable(msg)))
#endif
#if !defined(SWIFT_AVAILABILITY)
# define SWIFT_AVAILABILITY(plat, ...) __attribute__((availability(plat, __VA_ARGS__)))
#endif
#if !defined(SWIFT_WEAK_IMPORT)
# define SWIFT_WEAK_IMPORT __attribute__((weak_import))
#endif
#if !defined(SWIFT_DEPRECATED)
# define SWIFT_DEPRECATED __attribute__((deprecated))
#endif
#if !defined(SWIFT_DEPRECATED_MSG)
# define SWIFT_DEPRECATED_MSG(...) __attribute__((deprecated(__VA_ARGS__)))
#endif
#if __has_feature(attribute_diagnose_if_objc)
# define SWIFT_DEPRECATED_OBJC(Msg) __attribute__((diagnose_if(1, Msg, "warning")))
#else
# define SWIFT_DEPRECATED_OBJC(Msg) SWIFT_DEPRECATED_MSG(Msg)
#endif
#if !defined(IBSegueAction)
# define IBSegueAction
#endif
#if __has_feature(modules)
#if __has_warning("-Watimport-in-framework-header")
#pragma clang diagnostic ignored "-Watimport-in-framework-header"
#endif
@import Foundation;
@import ObjectiveC;
@import Security;
#endif

#import <OmniFoundation/OmniFoundation.h>

#pragma clang diagnostic ignored "-Wproperty-attribute-mismatch"
#pragma clang diagnostic ignored "-Wduplicate-method-arg"
#if __has_warning("-Wpragma-clang-attribute")
# pragma clang diagnostic ignored "-Wpragma-clang-attribute"
#endif
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wnullability"

#if __has_attribute(external_source_symbol)
# pragma push_macro("any")
# undef any
# pragma clang attribute push(__attribute__((external_source_symbol(language="Swift", defined_in="OmniFoundation",generated_declaration))), apply_to=any(function,enum,objc_interface,objc_category,objc_protocol))
# pragma pop_macro("any")
#endif


@interface NSBundle (SWIFT_EXTENSION(OmniFoundation))
@property (nonatomic, readonly, copy) NSString * _Nonnull displayName;
- (BOOL)contains:(NSBundle * _Nonnull)bundle SWIFT_WARN_UNUSED_RESULT;
@end

@class NSMutableDictionary;

/// A CMSRecipient instance corresponds to the <a href="https://tools.ietf.org/html/rfc5652#section-6.2">RecipientInfo</a> datatype in CMS; it gives enough information to derive the CEK for one recipient.
SWIFT_PROTOCOL_NAMED("CMSRecipient")
@protocol OFCMSRecipient
/// Produce the CMS recipient information for this recipient, given the current file’s content encryption key (CEK).
/// Use <code>canWrap()</code> to discover whether the receiver actually has enough information to wrap a new CEK.
/// \param cek The Content-Encryption Key to be used by the receiver.
///
///
/// returns:
/// The DER-encoded RecipientInformation structure.
- (NSData * _Nullable)recipientInfoWithWrapping:(NSData * _Nonnull)cek error:(NSError * _Nullable * _Nullable)error SWIFT_WARN_UNUSED_RESULT;
/// Tests whether the receiver has enough information to encrypt a new CEK.
- (BOOL)canWrap SWIFT_WARN_UNUSED_RESULT;
@property (nonatomic, readonly) enum OFCMSRecipientType type;
@optional
@property (nonatomic, readonly) SecCertificateRef _Nullable certificate;
@required
- (NSMutableDictionary * _Nonnull)debugDictionary SWIFT_WARN_UNUSED_RESULT;
@end


SWIFT_CLASS_NAMED("Diagnostics")
@interface OFDiagnostics : NSObject <OFBundleRegistryTarget>
+ (void)registerItemName:(NSString * _Nonnull)itemName bundle:(NSBundle * _Nonnull)bundle description:(id _Nonnull)description;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end



@protocol OFCMSKeySource;

/// Encapsulates the encryption settings of a document
SWIFT_CLASS("_TtC14OmniFoundation28OFDocumentEncryptionSettings")
@interface OFDocumentEncryptionSettings : NSObject
/// Decrypts an encrypted document file, if necessary.
/// If the file is encrypted, it is unwrapped and a new file wrapper is returned, and information about the encryption settings is stored in <code>info</code>. Otherwise the original file wrapper is returned. If the file is encrypted but cannot be decrypted, an error is thrown, but <code>info</code> may still be filled in with whatever information is publicly visible on the encryption wrapper.
/// \param wrapper The possibly-encrypted document.
///
/// \param info (out) May be filled in with a new instance of <code>OFDocumentEncryptionSettings</code>.
///
/// \param keys Will be used to resolve password/key queries.
///
+ (NSFileWrapper * _Nullable)decryptFileWrapper:(NSFileWrapper * _Nonnull)wrapper info:(OFDocumentEncryptionSettings * _Nullable * _Nonnull)info keys:(id <OFCMSKeySource> _Nullable)keys error:(NSError * _Nullable * _Nullable)error SWIFT_WARN_UNUSED_RESULT;
/// Tests whether a given filewrapper looks like an encrypted document.
/// *
/// * May return false positives for other CMS-formatted objects, such as PKCS#7 or PKCS#12 objects, iTunes store receipts, etc.
+ (BOOL)fileWrapperMayBeEncrypted:(NSFileWrapper * _Nonnull)wrapper SWIFT_WARN_UNUSED_RESULT;
/// Encrypts a file wrapper using the receiver’s settings.
- (NSFileWrapper * _Nullable)encryptFileWrapper:(NSFileWrapper * _Nonnull)wrapper schema:(NSDictionary<NSString *, id> * _Nullable)schema error:(NSError * _Nullable * _Nullable)error SWIFT_WARN_UNUSED_RESULT;
@property (nonatomic) OFCMSOptions cmsOptions;
/// The unencrypted, outer identifier for this document.
/// This is used to match the document with a password keychain item.
@property (nonatomic, copy) NSData * _Nullable documentIdentifier;
/// The unencrypted password hint text for this document.
@property (nonatomic, copy) NSString * _Nullable passwordHint;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
- (nonnull instancetype)initWithSettings:(OFDocumentEncryptionSettings * _Nullable)other_ OBJC_DESIGNATED_INITIALIZER;
@property (nonatomic, readonly, strong) NSMutableDictionary * _Nonnull debugDictionary;
@end


@interface OFDocumentEncryptionSettings (SWIFT_EXTENSION(OmniFoundation))
/// Returns a short, localized description of a document’s encryption state.
+ (NSString * _Nonnull)describeEncryptionSettings:(OFDocumentEncryptionSettings * _Nullable)settings SWIFT_WARN_UNUSED_RESULT;
- (void)addMetadata:(NSMutableDictionary * _Nonnull)into;
/// Returns the total number of recipients.
- (NSUInteger)countOfRecipients SWIFT_WARN_UNUSED_RESULT;
/// Returns YES if the receiver allows decryption using a password.
- (BOOL)hasPassword SWIFT_WARN_UNUSED_RESULT;
/// Removes any existing password recipients, and adds one given a plaintext passphrase.
/// <ul>
///   <li>
///     parameter: The password to set. Pass nil to remove the passphrase.
///   </li>
/// </ul>
- (void)setPassword:(NSString * _Nullable)password;
/// Tests whether the receiver was decrypted using the given password.
/// (Note that a receiver can potentially be unlocked using any of several passwords, although we don’t currently expose that possibility in the UI, and probably never will — it’d be pretty confusing.)
/// This cannot necessarily test whether a password matches if we didn’t actually decrypt with it at some point in the past, because we don’t retain enough intermediate keying material to determine that. However, again, this is probably not a situation a user can get into without dedicated effort.
/// Passing nil for the password tests whether <em>any</em> password did match, i.e., whether it’s possible for this method to ever return true for the current state of the receiver.
- (BOOL)passwordDidMatch:(NSString * _Nullable)password SWIFT_WARN_UNUSED_RESULT;
/// Returns YES if the receiver allows decryption using asymmetric cryptography.
- (BOOL)hasPublicKeyRecipients SWIFT_WARN_UNUSED_RESULT;
/// Returns all public-key recipients.
- (NSArray<id <OFCMSRecipient>> * _Nonnull)publicKeyRecipients SWIFT_WARN_UNUSED_RESULT;
/// Adds a PK recipient for the supplied certificate.
///
/// returns:
/// the new recipient, or an existing recipient if there already is one for this certificate. Nil if the certificate was not usable for some reason.
- (id <OFCMSRecipient> _Nullable)addRecipientWithCertificate:(SecCertificateRef _Nonnull)certificate SWIFT_WARN_UNUSED_RESULT;
/// Removes a recipient, returning true if the recipient was found and removed.
- (BOOL)removeRecipient:(id <OFCMSRecipient> _Nonnull)recip SWIFT_WARN_UNUSED_RESULT;
@end






@interface NSProcessInfo (SWIFT_EXTENSION(OmniFoundation))
@property (nonatomic, readonly) BOOL isRunningUnitTests;
@end

@class OFResourceLocation;

SWIFT_PROTOCOL_NAMED("ResourceLocationDelegate")
@protocol OFResourceLocationDelegate
- (void)resourceLocationDidUpdateResourceURLs:(OFResourceLocation * _Nonnull)location;
- (void)resourceLocationDidMove:(OFResourceLocation * _Nonnull)location;
@end


SWIFT_CLASS_NAMED("ResourceBookmarks")
@interface OFResourceBookmarks : NSObject <OFResourceLocationDelegate>
@property (nonatomic, readonly, copy) NSArray<OFResourceLocation *> * _Nonnull bookmarkedResourceLocations;
- (BOOL)isResourceInKnownResourceLocation:(NSURL * _Nonnull)resourceURL SWIFT_WARN_UNUSED_RESULT;
- (BOOL)addResourceFolderURL:(NSURL * _Nonnull)url error:(NSError * _Nullable * _Nullable)error;
- (void)removeResourceFolderURL:(NSURL * _Nonnull)fileURL;
- (void)resourceLocationDidUpdateResourceURLs:(OFResourceLocation * _Nonnull)location;
- (void)resourceLocationDidMove:(OFResourceLocation * _Nonnull)location;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

@protocol OFResourceTypePredicate;
@class NSOperationQueue;

SWIFT_CLASS_NAMED("ResourceLocation")
@interface OFResourceLocation : NSObject <NSFilePresenter>
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly) NSNotificationName _Nonnull WillStartScanning;)
+ (NSNotificationName _Nonnull)WillStartScanning SWIFT_WARN_UNUSED_RESULT;
SWIFT_CLASS_PROPERTY(@property (nonatomic, class, readonly) NSNotificationName _Nonnull DidFinishScanning;)
+ (NSNotificationName _Nonnull)DidFinishScanning SWIFT_WARN_UNUSED_RESULT;
@property (nonatomic, readonly, copy) NSURL * _Nonnull folderURL;
@property (nonatomic, readonly, copy) NSData * _Nullable bookmark;
- (nullable instancetype)initWithBookmark:(NSData * _Nonnull)bookmark resourceTypes:(NSDictionary<NSString *, id <OFResourceTypePredicate>> * _Nonnull)resourceTypes delegate:(id <OFResourceLocationDelegate> _Nonnull)delegate synchronousInitialScan:(BOOL)synchronousInitialScan error:(NSError * _Nullable * _Nullable)error;
- (nullable instancetype)initWithBuiltInFolderURL:(NSURL * _Nonnull)folderURL resourceTypes:(NSDictionary<NSString *, id <OFResourceTypePredicate>> * _Nonnull)resourceTypes delegate:(id <OFResourceLocationDelegate> _Nonnull)delegate synchronousInitialScan:(BOOL)synchronousInitialScan error:(NSError * _Nullable * _Nullable)error;
- (nullable instancetype)initWithFolderURL:(NSURL * _Nonnull)folderURL resourceTypes:(NSDictionary<NSString *, id <OFResourceTypePredicate>> * _Nonnull)resourceTypes delegate:(id <OFResourceLocationDelegate> _Nonnull)delegate synchronousInitialScan:(BOOL)synchronousInitialScan error:(NSError * _Nullable * _Nullable)error;
- (void)updateNowThatObservedLocationExists;
- (void)invalidate;
@property (nonatomic, readonly, copy) NSURL * _Nullable presentedItemURL;
@property (nonatomic, readonly, strong) NSOperationQueue * _Nonnull presentedItemOperationQueue;
- (void)presentedItemDidChange;
- (void)presentedItemDidMoveToURL:(NSURL * _Nonnull)newURL;
- (void)relinquishPresentedItemToWriter:(void (^ _Nonnull)(void (^ _Nullable)(void)))writer;
- (void)accommodatePresentedItemDeletionWithCompletionHandler:(void (^ _Nonnull)(NSError * _Nullable))completionHandler;
- (void)presentedSubitemAtURL:(NSURL * _Nonnull)oldURL didMoveToURL:(NSURL * _Nonnull)newURL;
- (void)accommodatePresentedSubitemDeletionAtURL:(NSURL * _Nonnull)url completionHandler:(void (^ _Nonnull)(NSError * _Nullable))completionHandler;
- (void)presentedSubitemDidAppearAtURL:(NSURL * _Nonnull)url;
- (void)presentedSubitemDidChangeAtURL:(NSURL * _Nonnull)url;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end


@interface OFResourceLocation (SWIFT_EXTENSION(OmniFoundation)) <NSCopying>
- (id _Nonnull)copyWithZone:(struct _NSZone * _Nullable)zone SWIFT_WARN_UNUSED_RESULT;
@end

@class OFFileEdit;

SWIFT_CLASS_NAMED("ResourceLocationContents")
@interface OFResourceLocationContents : NSObject
@property (nonatomic, copy) NSSet<OFFileEdit *> * _Nonnull fileEdits;
- (nonnull instancetype)init OBJC_DESIGNATED_INITIALIZER;
@end



SWIFT_PROTOCOL_NAMED("ResourceTypePredicate")
@protocol OFResourceTypePredicate
- (BOOL)matchesFileType:(NSString * _Nonnull)fileType SWIFT_WARN_UNUSED_RESULT;
@end


SWIFT_CLASS_NAMED("UTIResourceTypePredicate")
@interface OFUTIResourceTypePredicate : NSObject <OFResourceTypePredicate>
@property (nonatomic, readonly, copy) NSString * _Nonnull description;
- (BOOL)matchesFileType:(NSString * _Nonnull)fileType SWIFT_WARN_UNUSED_RESULT;
- (nonnull instancetype)init SWIFT_UNAVAILABLE;
+ (nonnull instancetype)new SWIFT_UNAVAILABLE_MSG("-init is unavailable");
@end

#if __has_attribute(external_source_symbol)
# pragma clang attribute pop
#endif
#pragma clang diagnostic pop