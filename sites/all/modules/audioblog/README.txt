== Introduction ==

The audioblog.module (Audio Blog) provides VoIP Scripts for both Voice and Text channels that handle Audio Blog entries directly from user telephones.
Audio Blogs are saved as nodes and can be accessed both by site and telephone.
This module uses Features to create new content type Audioblog which will contain user submitted Audio blogs.

== Requirements ==
Audio Blog module depends on this modules:
AudioRecorderField: http://drupal.org/project/audiorecorderfield
VoIP Drupal: http://drupal.org/project/voipdrupal
Features: http://drupal.org/project/features

== Installation ==

1. Extract audioblog.module to your sites/all/modules directory

2. Enable the "Audio Blog" module in admin/build/modules

3. Go to admin/voip/call/settings and set "audioblog_main_menu_script" as default inbound call script and "audioblog_sms_handler_script" as default 
inbound text script.

== Usage ==

Voice channel ("audioblog_main_menu_script"):

- the voice channel script presents the user with a voice menu in where they can either select to listen existing Audio Blogs or to record a new Audio Blog.
  Recorded audio will be saved in as new node of audioblog content type.

- the text channel scripts gives option for users to create new Audio Blog by sending text message "ADD" followed by space and actual Blog content.

---
The Audio Blog module has been originally developed under the sponsorship of the MIT Center for Future Civic Media (http://civic.mit.edu).