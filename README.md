# Hello ESP-IDF: a starter project

This is the outline of a project using the ESP-IDF framework.
It has reasonable defaults and supports multiple configurations.


# Build from Source

Install and configure ESP-IDF.  [Espressif
documentation](https://docs.espressif.com/projects/esp-idf/en/v5.5.1/esp32s3/get-started/index.html)
explains how.

This is a [multi-config
workspace](https://github.com/espressif/esp-idf/blob/master/examples/build_system/cmake/multi_config/README.md).
You can build the default board, defined in `default-board.cmake`, or
you can build from a profile defined in `profiles/*`.  Each profile uses
its own build directory, so you can switch boards without having to
rebuild the world.

## Build the default board for the first time

  1. (optional) Edit `default-board.cmake` to set the default board.
  2. `idf.py set-target esp32s3`
  3. Attach your ESP32 board with USB and find its serial port.
  4. `idf.py --port=[port] build flash monitor`

  Note the screen is normally dark for about 15 seconds after the app
  starts.

## Build from a profile for the first time

  1. Find your board's profile in `profiles/`.
  2. Attach your board with USB and find its serial port.
  3. `idf.py @profiles/[your_board] --port=[port] build flash monitor`

## Rebuilding after changing the app

After the app is flashed, there's no need to keep reflashing the
bootloader.  You can update just the app with this command.
```
    $ idf.py --port=[port] app-flash monitor
```
(add `@profiles/[your_board]` if you're using a profile)


# Add Support for a New Board

It should be possible to make this project run on more ESP32-based
boards. The process of adding a new board should go like this.
(I haven't done it yet, so *caveat developer*.)

 - Pick a `shortname`.  Shell-friendly\*, unique, easy to type.
   
   E.g., `ws-128`, `ws-t169`.

 - Pick a `boardname`.  Shell-friendly\*, complete product name.
   
   E.g., `waveshare-esp32-s3-lcd-1.28`.

 - Pick a `configname`.  It must be a legal C identifier, uppercase.
   Transliterate `boardname` to uppercase and change punctuation to
   "\_".  It will have `BOARD_` prepended.

   E.g., `BOARD_WAVESHARE_ESP32_S3_LCD_1_28`.

   N.B., in some contexts, the build system prepends `CONFIG_` to the
   configname.

   E.g., `CONFIG_BOARD_WAVESHARE_ESP32_S3_LCD_1_28`.

 - Define `builddir` as `build/[shortname]`.

   E.g., `build/ws-128`.

 - Create `boards/sdkconfig.[boardname]`. sdkconfig parameters specific
   to this board.  This file should define `CONFIG_[configname]` and
   `CONFIG_IDF_TARGET`, among other things.

 - Create `profiles/[shortname]`.  It is is an
   [idf.py options file](https://docs.espressif.com/projects/esp-idf/en/v5.5.1/esp32s3/api-guides/tools/idf-py.html#global-options).
   It should define:
    + `-B [builddir]`
    + `-D IDF_TARGET=esp32s3` (or whatever chip your board has)
    + `-D SDKCONFIG=[builddir]/sdkconfig`
    + `D board_config="boards/sdkconfig.[boardname]"`

 - Add `[configname]` to the board list in `main/Kconfig.projbuild`.

 - Add definitions to `main/include/board_defs.h`.
   Use the existing boards as examples.

\*"Shell friendly" means good for use in a shell or filename:

 - no whitespace
 - no punctuation characters with meaning to a shell (&lt; &gt; ~ etc.)
 - alphanumeric characters are okay.
 - "-", "\_", "." are okay.  Prefer "-" to "\_".
