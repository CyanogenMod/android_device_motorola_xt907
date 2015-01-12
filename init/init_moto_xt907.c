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

#include "init_msm.h"

void init_msm_properties(unsigned long msm_id, unsigned long msm_ver, char *board_type)
{
    char platform[PROP_VALUE_MAX];
    char carrier[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    char devicename[PROP_VALUE_MAX];
    char modelno[PROP_VALUE_MAX];
    char bootdevice[PROP_VALUE_MAX];
    char hardware_variant[92];
    FILE *fp;
    int rc;

    UNUSED(msm_id);
    UNUSED(msm_ver);
    UNUSED(board_type);

    rc = property_get("ro.board.platform", platform);
    if (!rc || !ISMATCH(platform, ANDROID_TARGET))
        return;

    property_get("ro.boot.modelno", modelno);
    property_get("ro.boot.carrier", carrier);
    property_get("ro.boot.device", bootdevice);
    fp = popen("/system/xbin/sed -n '/Hardware/,/Revision/p' /proc/cpuinfo | /system/xbin/cut -d ':' -f2 | /system/xbin/head -1", "r");
    fgets(hardware_variant, sizeof(hardware_variant), fp);
    pclose(fp);
    if (ISMATCH(modelno, "XT901")) {
        property_set("ro.product.device", "solstice");
        property_set("ro.product.model", "ELECTRIFY M");
        property_set("ro.build.description", "solstice-user 4.1.2 9.8.2Q-50_SLS-13 44 release-keys");
        property_set("ro.build.fingerprint", "motorola/XT901_usc/solstice:4.1.2/9.8.2Q-50_SLS-13/44:user/release-keys");
        property_set("ro.sf.lcd_density", "240");
        property_set("ro.com.google.clientidbase.ms", "android-uscellular-us");
    } else if (ISMATCH(modelno, "XT905")) {
        property_set("ro.product.device", "smq_u");
        property_set("ro.product.model", "RAZR M");
        property_set("ro.build.description", "smq_u_ird-user 4.1.2 9.8.2Q_SMUIRD-7 1357751068 release-keys");
        property_set("ro.build.fingerprint", "motorola/XT905_RTAU/smq_u:4.1.2/9.8.2Q_SMUIRD-7/1357751068:user/release-keys");
        property_set("ro.sf.lcd_density", "240");
        property_set("telephony.lteOnGsmDevice", "1");
    } else if (((strstr(hardware_variant, "msm8960dt")) && (ISMATCH(carrier, "vzw"))) || (ISMATCH(bootdevice, "smq"))) {
        /* xt907 */
        property_set("ro.product.device", "smq");
        property_set("ro.product.model", "DROID RAZR M");
        property_set("ro.build.description", "smq_vzw-user 4.4.2 KDA20.62-15.1 15 release-keys");
        property_set("ro.build.fingerprint", "motorola/XT907_verizon/scorpion_mini:4.4.2/KDA20.62-15.1/15:user/release-keys");
        property_set("ro.sf.lcd_density", "240");
    }

    if (ISMATCH(carrier, "vzw")) {
        property_set("ro.mot.build.customerid ", "verizon");
        property_set("ro.config.svdo", "true");
        property_set("persist.radio.eons.enabled", "true");
        property_set("ro.cdma.nbpcd", "1");
        property_set("ro.mot.ignore_csim_appid", "true");
        property_set("ro.telephony.gsm-routes-us-smsc", "1");
        property_set("persist.radio.vrte_logic", "2");
        property_set("persist.radio.0x9e_not_callname", "1");
        property_set("persist.radio.skip_data_check", "1");
        property_set("persist.ril.max.crit.qmi.fails", "4");
        property_set("ro.cdma.home.operator.isnan", "1");
        property_set("ro.cdma.otaspnumschema", "SELC,1,80,99");
        property_set("ro.cdma.data_retry_config", "max_retries=infinite,0,0,10000,10000,100000,10000,10000,10000,10000,140000,540000,960000");
        property_set("ro.gsm.data_retry_config", "default_randomization=2000,max_retries=infinite,1000,1000,80000,125000,485000,905000");
        property_set("ro.gsm.2nd_data_retry_config", "max_retries=1,15000");
        property_set("ro.cdma.homesystem", "64,65,76,77,78,79,80,81,82,83");
        property_set("ro.cdma.home.operator.alpha", "Verizon Wireless");
        property_set("ro.cdma.home.operator.numeric", "310004");
        property_set("ro.telephony.get_imsi_from_sim", "true");
        property_set("ro.com.google.clientidbase.ms", "android-verizon");
        property_set("ro.com.google.clientidbase.am", "android-verizon");
        property_set("ro.com.google.clientidbase.yt", "android-verizon");
    } else if (ISMATCH(carrier, "usc")) {
        property_set("ro.cdma.nbpcd", "1");
        property_set("ro.cdma.data_retry_config", "max_retries=infinite,0,0,10000,10000,100000,10000,10000,10000,10000,140000,540000,960000");
        property_set("ro.cdma.international.eri", "2,74,124,125,126,157,158,159,193,194,195,196,197,198,228,229,230,231,232,233,234,235");
        property_set("ro.cdma.home.operator.isnan", "1");
        property_set("persist.radio.vrte_logic", "2");
        property_set("ro.cdma.subscription", "0");
        property_set("ro.config.svdo", "true");
        property_set("persist.radio.skip_data_check", "1");
        property_set("ro.mot.ignore_csim_appid", "true");
        property_set("ro.cdma.ecmexittimer", "600000");
        property_set("DEVICE_PROVISIONED", "1");
        property_set("persist.radio.0x9e_not_callname", "1");
        property_set("ro.cdma.home.operator.alpha", "U.S. Cellular");
        property_set("ro.cdma.home.operator.numeric", "311220");
        property_set("gsm.sim.operator.numeric", "311580");
    }

    property_get("ro.product.device", device);
    strlcpy(devicename, device, sizeof(devicename));
    ERROR("Found carrier id: %s hardware:%s model no: %s Setting build properties for %s device\n", carrier, hardware_variant, modelno, devicename);
}
