#ifndef __CC_NETWORK_H_
#define __CC_NETWORK_H_

#include "platform/CCPlatformMacros.h"

NS_CC_BEGIN

#define kCCNetworkStatusNotReachable     0
#define kCCNetworkStatusReachableViaWiFi 1
#define kCCNetworkStatusReachableViaWWAN 2

class Network
{
public:
    /** @brief Checks whether a local wifi connection is available */
    static bool isLocalWiFiAvailable(void);
    
    /** @brief Checks whether the default route is available */
    static bool isInternetConnectionAvailable(void);
    
    /** @brief Checks the reachability of a particular host name */
    static bool isHostNameReachable(const char* hostName);
    
    /** @brief Checks Internet connection reachability status */
    static int getInternetConnectionStatus(void);
    
private:
    Network(void) {}
};

NS_CC_END

#endif // __CC_NETWORK_H_
