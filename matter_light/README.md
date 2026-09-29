# Overview

This worked and could be commissioned

The starting point was the component example

    esp-matter-1.4.2/examples/managed_component_light

The key to get this to work was to allow the Matter Server to accept test devices.

Many of the examples default to matter over wifi and on principle I wanted to get matter over thread to work.

I have copied all of the common libraries from the matter repo into this repo.

This copied the code and library locally

git clone --depth 1 -b release/v1.4.2 https://github.com/espressif/esp-matter.git esp-matter-1.4.2

to install a precise version of idy.py

eim install -i v5.4.1

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


# Managed Component Light

This example creates a Color Temperature Light device using the esp_matter component downloaded from [Espressif Component Registry](https://components.espressif.com/) instead of the extra component in local, so the example can work without setting the esp-matter environment.

See the [docs](https://docs.espressif.com/projects/esp-matter/en/latest/esp32/developing.html) for more information about building and flashing the firmware.
# matter_light
