#include "platform/CCNetwork.h"
#include "base/CCConsole.h"

NS_CC_BEGIN

bool Network::isLocalWiFiAvailable(void)
{
    CCLOG("Network::isLocalWiFiAvailable() - not support this platform.");
    return true;
}

bool Network::isInternetConnectionAvailable(void)
{
    CCLOG("Network::isInternetConnectionAvailable() - not support this platform.");
    return true;
}

bool Network::isHostNameReachable(const char* hostName)
{
    CCLOG("Network::isHostNameReachable() - not support this platform.");
    return true;
}

int Network::getInternetConnectionStatus(void)
{
    CCLOG("Network::getInternetConnectionStatus() - not support this platform.");
    return kCCNetworkStatusReachableViaWiFi;
}

NS_CC_END
