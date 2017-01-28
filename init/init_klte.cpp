/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <stdio.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_msm8974.h"

#define ISMATCH(a, b) (!strncmp((a), (b), PROP_VALUE_MAX))

void cdma_properties(char const *default_cdma_sub,
        char const *operator_numeric, char const *operator_alpha)
{
    property_set("ril.subscription.types", "NV,RUIM");
    property_set("ro.cdma.home.operator.numeric", operator_numeric);
    property_set("ro.cdma.home.operator.alpha", operator_alpha);
    property_set("ro.telephony.default_cdma_sub", default_cdma_sub);
    property_set("ro.telephony.default_network", "10");
    property_set("ro.telephony.ril.config", "newDriverCallU,newDialCode");
    property_set("telephony.lteOnCdmaDevice", "1");
}

void init_target_properties()
{
    char platform[PROP_VALUE_MAX];
    char bootloader[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.bootloader", bootloader);

    if (strstr(bootloader, "G860P")) {
        /* kltesprsports */
        property_set("ro.build.fingerprint", "samsung/kltesprsports/kltesprsports:6.0.1/MMB29M/G860PVPU2CPD1:user/release-keys");
        property_set("ro.build.description", "kltesprsports-user 6.0.1 MMB29M G860PVPU2CPD1 release-keys");
        property_set("ro.product.model", "SM-G860P");
        property_set("ro.product.device", "kltesprsports");
        property_set("telephony.sms.pseudo_multipart", "1");
        cdma_properties("1", "310120", "Sprint");
    }
    /* TODO: Add Sprint MVNOs */

    property_get("ro.product.device", device);
    strlcpy(devicename, device, sizeof(devicename));
    INFO("Found bootloader id %s setting build properties for %s device\n", bootloader, devicename);
}
