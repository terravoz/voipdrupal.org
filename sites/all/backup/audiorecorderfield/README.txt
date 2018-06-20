AudioRecorderField.module
--------------------------------------------------------------------------------
The AudioRecorderField.module provides a new CCK field that enables both the recording and playing of .wav audio files directly from the web browser. 

The new field is based on AudioField module and records audio via the Nanogong applet (http://gong.ust.hk/nanogong). 
Note that Nanogong applet is limited to 20 mins of audio recording per file.

In order to convert the new audio files to .mp3, please refer to the AudioConverter module (http://www.drupal.org/project/audioconverter/).


Installation

1. Extract AudioRecorderField to your sites/all/modules directory. Make sure you have installed CCK, FileField and AudioField modules.
2. Download Nanogong applet from the following link: http://gong.ust.hk/nanogong/downloads_form.html
3. Extract the Nanogong archive and copy nanogong.jar file to sites/all/modules/audiorecorderfield/recorders
4. Enable the AudioRecorderField module in admin/build/modules.
5. Choose any content type from admin/content/types and go to "manage fields".
6. Add a new field, select File as its field type and Audio Recorder as the widget.
7. Save.
8. Create new content and you will see the Nanogong Audio Recorder!

Java player configuration

In order to use the Nanogong applet to play .wav content directly from AudioFields, you should:
1. Go to admin/content/types and choose the content type that includes the audio field you would like to play with Nanogong
2. Go to "display fields"
3. Choose "Audio" for either the "teaser" or the "full node" display modes
4. Go to admin/settings/audiofield and select the Nanogong player as the default player for .wav files
5. Now you should be all set!


FileField Sources support

This module also adds new "recorder" uploading method for FileField Sources module. Its possible to create one field with multiple uploading choices.
1. Download and install FileField Sources module.
2. Change your Audio Recorder widget to File Upload widget.
3. Under File Sources fieldset you will see various uploading methods (Audio recorder method is added by this module).


---
The AudioRecorderField module has been originally developed by Leo Burd and Tamer Zoubi under the sponsorship of the MIT Center for Future Civic Media (http://civic.mit.edu).

