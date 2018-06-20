Soundcloud Tools.module
--------------------------------------------------------------------------------
This module provides API for Soundcloud based modules.

--------------------------
Installation

1. Extract Soundcloud Tools to your sites/all/modules directory.
2. Enable the Soundcloud API and Soundcloud Upload or Soundcloud playlist modules in admin/build/modules.
3. Login to Soundcloud and create new application at http://soundcloud.com/you/apps/new
   - Fill the Redirect URI field with: 
     http://mysite.com/soundcloud-callback.html (for clean URLs)
     or http://mysite.com/?q=soundcloud-callback.html
   - Press the "Save" button  
4. Go to configuration form at admin/settings/soundcloud_tools
5. Enter Client ID and Client Secret from the application you just created. Press "Next"
6. Press "Authorize". You'll be redirected to Soundcloud page where you must authorize your website on behalf of Soundcloud application, 
   so that website can upload tracks to your Soundcloud account. Press "Connect". You'll be returned to your website with message saying that token was 
   sucessfully saved.
7. Now you can start using Soundcloud Tools!   

Soundcloud Upload
--------------------------
This module adds ability to upload audio files from supported CCK fields (FileField, AudioField, AudioRecorderField, PhoneRecorderField) to the 
Soundcloud(http://soundcloud.com). SoundCloud is a platform that puts your sound at the heart of communities, websites and even apps. 
Configuration

1. Go to configuration form at admin/settings/soundcloud_upload
   - Soundcloud Upload time: choose when to upload audio from selected fields to Soundcloud (either at node save or cron)
   - Serve local file: check to serve audio from your server until it gets uploaded to Soundcloud (recommended for when upload time is set to cron)

--------------------------
Usage
1. In your content type choose any supported existing fields (FileField, AudioField, AudioRecorderField, PhoneRecorderField) and click "Configure".
2. Under "Soundcloud Tools Settings" check "Automatically upload content to Soundcloud".
3. Save field settings
4. Go to "display fields" for this content type and set formatter to "Audio for Soundcloud". This will start serving audios from soundcloud.
5. Create new content, upload the audio and press save.
6. View the content and you'll see your audio served in Soundcloud player!


Soundcloud Playlist
--------------------------------------------------------------------------------
This module adds ability to display your Soundcloud playlists in block. It also lets you add new tracks to playlist directly from your cck fields.


--------------------------
Installation

1. Extract Soundcloud Playlist to your sites/all/modules directory. Make sure to enable Soundcloud Upload module.
2. Enable the Soundcloud Playlist module in admin/build/modules.
3. Make sure to have at least one playlist in Souncloud account used by website. (http://soundcloud.com/you/sets)

--------------------------
Usage
As a block:
1. Go to admin/build/block
2. Each playlist will appear as a block. Select a region where you want to display it.

Adding new tracks from cck:
1. In your content type choose any supported existing fields (FileField, AudioField, AudioRecorderField, PhoneRecorderField) and click "Configure".
2. Under "Soundcloud Upload Settings" select playlist from "Add to Playlist". Make sure to enable "Automatically upload content to Soundcloud" as well.
3. Save field settings
5. Create new content, upload the audio and press save.
6. Your new audio will be added to selected playlist!


---
The Soundcloud Tools module is part of the VoIP Drupal framework.  This module has been originally developed by Tamer Zoubi and Leo Burd under the sponsorship of the MIT Center for Future Civic Media (http://civic.mit.edu).