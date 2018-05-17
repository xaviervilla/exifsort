# sort-by-exif

sort-by-exif uses the ExifTool Library to parse metadata and organize photos in a directory by camera type. It creates a new directory for each camera type and places photos taken by that camera inside the folder.

- This repository should be OS independant, but is currently only tested on Linux.

- In order for this to work, exiftool must be present on system.

- for linux, you may install using `sudo apt-get install exiftool`

# Usage:


`./exifsort -build-exclusions (Optionally: -r <radius>) <filepath_to_exclusions>`

- This option recursively writes the GPS coordinates of all images in the directory provided to a JSON file as an exclusionary parameter to be utilized during the filtering process. During filtering, any image tested within radius (provided with -r <float>) of an exclusionary parameter will be moved to the deleted folder.

`./exifsort -build-inclusions <filepath_to_inclusions>`

- This option recursively writes the model of phone/camera of all images in the directory provided to a JSON file as an inclusionary parameter to be utilized during the filtering process. During filtering, any image tested that was taken with a camera or phone model that is not an inclusionary parameter will be moved to the deleted folder.

`./exifsort -filter <filepath_to_filter>`

- This filtering process utilizes two methods to screen image files. 1) This option recursively checks the Model of camera and/or phone used to take the photo, and compares it to a list of inclusionary parameters saved in a JSON file. These inclusionary parameters can be created using the `-build-inclusions` flag. If the camera or phone's model checked is not an inclusionary parameter, it will be immediately moved to the deleted folder. 2) This option also recursively checks the GPS coordinates of all images in the directory provided, comparing the GPS coordinates with exclusion parameters saved in a JSON file. These exclusionary parameters can be created using the `-build-exclusions` flag. If any image in the directory provided is within radius of an exclusion parameter, it will be moved to the deleted folder.
