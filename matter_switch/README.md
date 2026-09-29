# Overview

activate it

source ~/.espressif/tools/activate_idf_v5.4.1.sh

change to the project folder

install matter dependency

idf.py add-dependency "espressif/esp_matter=1.4.2"

fresh build

rm -rf build sdkconfig

idf.py set-target esp32c6

ls /dev/cu.usb*

idf.py -p /dev/cu.usbmodem3134101 erase-flash

idf.py -p /dev/cu.usbmodem3134101 build flash monitor

# Managed Component Switch

This example creates a Switch device using the esp_matter component downloaded from [Espressif Component Registry](https://components.espressif.com/) instead of the extra component in local, so the example can work without setting the esp-matter environment.

See the [docs](https://docs.espressif.com/projects/esp-matter/en/latest/esp32/developing.html) for more information about building and flashing the firmware.

