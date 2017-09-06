//
//  CLVOAuthManager.h
//  CleverSDK
//
//  Created by Nikhil Pandit on 4/3/15.
//  Copyright (c) 2015 Clever, Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CLVOauthDelegate
- (void) signIn:(NSString*)accessToken withError:(NSString*)error;
@end

@protocol CLVOAuthUIDelegate
- (void) presentViewController:(UIViewController*)viewControllerToPresent animated:(BOOL)flag completion:(void (^)(void))completion;
- (void) dismissViewControllerAnimated:(BOOL)flag completion:(void (^)(void))completion;
@end

/**
 CLVOAuthManager
 */
@interface CLVOAuthManager : NSObject

/**
 delegate is the receiver of successful signIn completions
 */
@property (weak) id<CLVOauthDelegate> delegate;
@property (weak) id<CLVOAuthUIDelegate> uiDelegate;

/**
 * Initializes the CLVOauthManager. Sets the clientId which is used for constructing the OAuth URL and logging in.
 */
+ (void)startWithClientId:(NSString *)clientId;

+ (void)setDelegate:(id<CLVOauthDelegate>) delegate;

+ (void)setUIDelegate:(id<CLVOAuthUIDelegate>) uiDelegate;

/**
 This method sets the state value used in the OAuth fow.
 It should be called before every login attempt to ensure a unique, random state value is used.
*/
+ (void)setState:(NSString *)state;

/**
 This method should be called under `application:openURL:sourceApplication:annotation:` method in the AppDelegate
 
 This method parses the `access_token` from the URL and returns it to the user in the success handler specified on the `CLVLoginButton`.
 This will also store the `access_token` and attach it automatically for requests made using `CLVApiRequest`
 */
+ (BOOL)handleURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation;

/**
 It is important to call this method when the user tries to logout. This clears the `access_token` locally, and invalidates any stored state on the device.
 It also makes a call to the server to logout the user from the app.
 */
+ (void)logout;

/**
 Return the access token.
 Use this as the bearer token when constructing network requests to the Clever API.
 See https://dev.clever.com/ for more information on using the accessToken.
 Alternatively, use the CLVApiRequest class to make requests.
 */
+ (NSString *)accessToken;

/**
 Return the state
*/
+ (NSString *)state;


///----------------------------------------
/// Methods used by other classes of the SDK
///----------------------------------------

/**
 Simple helper method to determine whether or not the clientId was set
 */
+ (BOOL)clientIdIsNotSet;

/**
 Return the saved clientId to the caller
 */
+ (NSString *)clientId;

/**
 Return the redirectURI to the caller
 */
+ (NSString *)redirectUri;

/**
 Set the success hander and failure handler sent to the `CLVLoginButton`
 */
+ (void)successHandler:(void (^)(NSString *accessToken))successHandler failureHandler:(void (^)(NSString *errorMessage))failureHandler;

/**
 Call the success handler
 */
+ (void)callSucessHandler;

/**
 Call the failure handler
 */
+ (void)callFailureHandler;

/**
 Allows setting the access token. Users of the SDK should not need to call this method directly.
 */
+ (void)setAccessToken:(NSString *)accessToken;

/**
 Start the login flow
 */
+ (void)login;

@end

NS_ASSUME_NONNULL_END
