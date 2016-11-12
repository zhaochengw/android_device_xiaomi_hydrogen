/*
   Copyright (c) 2016, The CyanogenMod Project

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
#include <fcntl.h>
#include <sys/sysinfo.h>

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"


char const *heapstartsize;
char const *heapgrowthlimit;
char const *heapsize;
char const *heapminfree;
char const *heapmaxfree;
char const *devicename;

void check_device()
{
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram > 3072ull * 1024 * 1024) {
        // from - phone-xxhdpi-4096-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "384m";
        heapsize = "1024m";
        heapminfree = "4m";
        heapmaxfree = "16m";
    } else {
        // from - phone-xxhdpi-3072-dalvik-heap.mk
        heapstartsize = "8m";
        heapgrowthlimit = "288m";
        heapsize = "768m";
        heapminfree = "512k";
        heapmaxfree = "8m";
    }
		
    char const *soc_file = "/sys/devices/soc0/soc_id";
    char buf[64];

    if(read_file2(soc_file, buf, sizeof(buf))) {
    /*
     * Setup devicename based on soc_id:
     * for hydrogen soc_id = 266
     * for helium soc_id = 278
     */
        if (buf[0] == '266') {
           devicename = "hydrogen";
        }else if (buf[0] == '278') {
           devicename = "helium";
        }
    }
}

static int read_file2(const char *fname, char *data, int max_size)
{
    int fd, rc;

    if (max_size < 1)
        return 0;

    fd = open(fname, O_RDONLY);
    if (fd < 0) {
        ERROR("failed to open '%s'\n", fname);
        return 0;
    }

    rc = read(fd, data, max_size - 1);
    if ((rc > 0) && (rc < max_size))
        data[rc] = '\0';
    else
        data[0] = '\0';
    close(fd);

    return 1;
}

void init_alarm_boot_properties()
{
    char const *alarm_file = "/proc/sys/kernel/boot_reason";
    char buf[64];

    if(read_file2(alarm_file, buf, sizeof(buf))) {

    /*
     * Setup ro.alarm_boot value to true when it is RTC triggered boot up
     * For existing PMIC chips, the following mapping applies
     * for the value of boot_reason:
     *
     * 0 -> unknown
     * 1 -> hard reset
     * 2 -> sudden momentary power loss (SMPL)
     * 3 -> real time clock (RTC)
     * 4 -> DC charger inserted
     * 5 -> USB charger insertd
     * 6 -> PON1 pin toggled (for secondary PMICs)
     * 7 -> CBLPWR_N pin toggled (for external power supply)
     * 8 -> KPDPWR_N pin toggled (power key pressed)
     */
  if (buf[0] == '0') {
        property_set("ro.boot.bootreason", "invalid");
        property_set("ro.alarm_boot", "false");
    }
  else if (buf[0] == '1') {
        property_set("ro.boot.bootreason", "hard_reset");
        property_set("ro.alarm_boot", "false");
    }
  else if (buf[0] == '2') {
        property_set("ro.boot.bootreason", "smpl");
        property_set("ro.alarm_boot", "false");
    }
  else if (buf[0] == '3'){
        property_set("ro.alarm_boot", "true");
    }
  else if (buf[0] == '4') {
        property_set("ro.boot.bootreason", "dc_chg");
        property_set("ro.alarm_boot", "false");
    }
  else if (buf[0] == '5') {
        property_set("ro.boot.bootreason", "usb_chg");
        property_set("ro.alarm_boot", "false");
    }
  else if (buf[0] == '6') {
        property_set("ro.boot.bootreason", "pon1");
        property_set("ro.alarm_boot", "false");
    }
  else if (buf[0] == '7') {
        property_set("ro.boot.bootreason", "cblpwr");
        property_set("ro.alarm_boot", "false");
    }
  else if (buf[0] == '8') {
        property_set("ro.boot.bootreason", "kpdpwr");
        property_set("ro.alarm_boot", "false");
    }

    }
}

void vendor_load_properties()
{
    check_device();
    property_set("dalvik.vm.heapstartsize", heapstartsize);
    property_set("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_set("dalvik.vm.heapsize", heapsize);
    property_set("dalvik.vm.heaptargetutilization", "0.75");
    property_set("dalvik.vm.heapminfree", heapminfree);
    property_set("dalvik.vm.heapmaxfree", heapmaxfree);
	property_set("ro.mk.device", devicename);
	property_set("ro.product.device", devicename);
    property_set("ro.product.model", "MI MAX");
    property_set("ro.mk.maintainer", "zhaochengw");
    init_alarm_boot_properties();
}

