# exifsort

## Why exifsort ##
exifsort is a very purpose-specific application. I hope, for your sake, that you never need to use it. But if you do, I'm glad that I could help.

I created exifsort to help batch organize photos that were deleted, and later restored using data recovery software. If you have any experience with recovering deleted files, you know that often, filenames are not restored correctly, and a lot of filepaths and directories will not be restored to their original state. 

Where exifsort helps, is when you have thousands of photos that were recovered and all thrown into one directory, reguardless of who they belong to, who took the photos, and what their contents are. Exifsort will batch read metadata from images (and some other file formats) to filter images that it believes are worthy of keeping from images that should be separated into a deleted. 

## How it works ##
Exifsort uses the ExifTool Library to parse metadata and create exclusionary and inclusionary parameters. It saves these parameters to a JSON file for the image filtering process. If it finds photos worthy of keeping, it will move them to a directory with the same name as the camera type used to take that photo for organizational purposes. When a photo is found not worthy of keeping, it gets moved to a folder titled 'deleted'.

Exifsort follows a general work flow. 

- Before you use this tool, **always** make a backup of the files that you plan on filtering in case something goes wrong.

- Next, prepare your inclusionaries. Find a large chunk of photos that you **know** that you wish to keep and put them in a folder like `'images/photos - devices to included'`. Ideally, you want to find **at least one photo from each and every model phone and/or camera that you owned**. The reason is that for the inclusionary parameters, exifsort is very strict in order to filter out as much junk as possible. Exifsort builds a list of devices that were used to take the photos in the inclusionary filepath and stores this list in a JSON file for filtering. The phones that are **not** on this list will be automatically moved to the deleted folder during the filtering process. That is why it is important to get **all** of your devices on this list (we can manually edit this list later).

- Now we can actually build our inclusionary parameters. From a terminal inside the exifsort root directory, run `./exifsort -build-inclusions 'images/photos - devices to include'`. Done. Check the to_include.json file in the root directory and make sure that it has been updated to contain your devices. 

- Not recommended: You may add more devices to the inclusionary list if you wish, but you must be sure to get the capitalization, spelling, and spacing exactly right. To be sure, run exiftool on your directory and search for the Model tag. Ex. 'exiftool recovered/images/ | grep 'Model''. The better thing to do however, is continue to add photos to your inclusionary directory and run `-build-inclusions` again until you think you have all of your devices.

- 

- This repository should be OS independant, but is currently only tested on Linux.

- In order for this to work, exiftool must be present on system.

- for linux, you may install using `sudo apt-get install exiftool`

# Usage:

Before the first run, exifsort must be compiled. On Linux, this can be done by running `make` in the program's root directory.

`./exifsort -build-exclusions (Optionally: -r <radius>) <filepath_to_exclusions>`

- This option recursively writes the GPS coordinates of all images in the directory provided to a JSON file as an exclusionary parameter to be utilized during the filtering process. During filtering, any image tested within radius (provided with -r <float>) of an exclusionary parameter will be moved to the deleted folder.

`./exifsort -build-inclusions <filepath_to_inclusions>`

- This option recursively writes the model of phone/camera of all images in the directory provided to a JSON file as an inclusionary parameter to be utilized during the filtering process. During filtering, any image tested that was taken with a camera or phone model that is not an inclusionary parameter will be moved to the deleted folder.

`./exifsort -filter <filepath_to_filter>`

- This filtering process utilizes two methods to screen image files. 1) This option recursively checks the Model of camera and/or phone used to take the photo, and compares it to a list of inclusionary parameters saved in a JSON file. These inclusionary parameters can be created using the `-build-inclusions` flag. If the camera or phone's model checked is not an inclusionary parameter, it will be immediately moved to the deleted folder. 2) This option also recursively checks the GPS coordinates of all images in the directory provided, comparing the GPS coordinates with exclusion parameters saved in a JSON file. These exclusionary parameters can be created using the `-build-exclusions` flag. If any image in the directory provided is within radius of an exclusion parameter, it will be moved to the deleted folder.
