$Id: README.txt,v 1.1.4.5 2009/10/06 05:48:18 yhager Exp $

= Overview =
imagefield_crop provides a widget for cropping an image after upload.


= Usage =
When the user uploads an image, the image is presented inside a cropping area.
A cropping box is shown inside, and the user can resize and move it. Upon
clicking 'preview' or 'submit', the image is cropped and the result is saved
within the node.

== Features ==

* Dynamic preview is presented during cropping
* Original image is displayed every time for re-cropping
* The original image is used for cropping, for best quality
* Ability to define the crop interface resolution
* Ability to define the output image resolution and enforce it


= Prerequisites =
You will need imagefield and imageapi enabled in order to use this module, along with a graphics processing engine (gd, imagemagick, or anything else imageapi.module can work with).


= Installation =
* Install the module and enable it.
* Set appropriate permissions at (/admin/user/permissions) under sections "content_permissions module", "node module".
* On the imagefield configuration page (admin/content/types/<content_type>/fields/<your_image_field>) choose the 'Image with cropping' widget.
* Save your field. You can set the widget settings form where you can choose the cropping box size, and other configuration options.
* Upon uploading an image, or editing an existing node, the image cropping interface will be presented.

