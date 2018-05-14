# sort-by-exif

sort-by-exif uses the exiv2 Library to parse metadata and organize photos in a directory by camera type. It creates a new directory for each camera type and places photos taken by that camera inside the folder.

- This repository should be OS independant, but is currently only tested on Linux.

- In order for this to work, exiftool must be present on system.

- for linux, you may install using `sudo apt-get install exiftool`
