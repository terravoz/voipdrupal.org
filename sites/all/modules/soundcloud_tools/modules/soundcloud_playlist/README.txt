Soundcloud Playlist.module
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
The Soundcloud Playlist module is part of the VoIP Drupal framework.  This module has been originally developed by Tamer Zoubi and Leo Burd under the sponsorship of the MIT Center for Future Civic Media (http://civic.mit.edu).