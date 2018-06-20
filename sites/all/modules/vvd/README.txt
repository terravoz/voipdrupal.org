== Introduction ==

VoIP Drupal depends on scripts -- written sequences of programming instructions -- to integrate telephones with Web sites. Visual VoIP Drupal takes much of the fuss out of writing these scripts. Although you need to understand the basic features offered by VoIP Drupal (which function accepts input, which speaks a message, etc.) you don't have to worry about syntax and typing.

== Installation ==

1. Extract the vvd.module to your sites/all/modules directory.

2. Enable the "Visual VoIP Drupal" module and related dependencies in Drupal's admin/build/modules screen.

3. Go to node/add/vvd and start creating VoIP Scripts!

== Usage ==

1. Go to node/add/vvd.

2. Move with the mouse to the left side menu (near "Script handling"). This will collapse the blocks menu. The Blocks menu is divided into several categories:  Script handling, Call control, Input and output, Expressions, Flow control, and Voice and sound. Each category contains appropriate Script blocks.

3. To create a VoIP Script, you must add a "Script" block in the Workspace. Then add appropriate command blocks inside that Script block.

!NOTE: Orphaned blocks are not considered part of any script.

4. There are two types of Script blocks: blue and brown. Blue blocks are commands and can be connected with other blocks. Brown blocks are variables whose data types can be either strings (represented as rectangles) or Booleans (represented as cylinders). Brown blocks can be inserted as arguments inside blue blocks with matching datatypes.

5. You can create multiple VoIP Scripts in a single Workspace by adding multiple Script blocks.

6. The argument "name" will be used as your unique Script name, so be sure to fill it uniquely for each Script block. Otherwise you might get a validation error.

7. When you save the VVD node, it will create a VoIP Script from each of your Script blocks.

8. Visual VoIP Scripts are treated just like any other VoIP Script in the system. Once they are created, they also become a choice in the dropdown list of VoIP Scripts in the Default Call Configuration - /admin/voip/call/settings.

== Export/Import ==
You can export VVD node to another Drupal website either by
 a) clicking on VVD Export tab when viewing the node.
 b) downloading the vvd export file from admin/content/vvd
 
To import VVD node to another Drupal website you can either:
 a) Load a VVD Node (recommended when you need to change some values of exported VVD): 
     Create new VVD node or go to existing one and click on Load tab.
     Paste the code exported from Export tab on other website.
     Click the Load button.
     This will take you to VVD edit interface where you can change the loaded script in Visual VoIP UI.
 b) Import VVD Node (faster):
     Go to admin/content/vvd/import
     Upload the file exported from admin/content/vvd in other website.
     Click the Import button.
     If no errors you will be redirected to admin/content/vvd

== Attributions ==

Visual VoIP Drupal is built on ScriptBlocks (http://code.google.com/p/scriptblocks/), a JavaScript/HMTL5 library specifically designed by MIT to support the creation of online blocks-based programming GUIs. 

The Visual VoIP Drupal module was developed by Leo Burd and Tamer Zoubi under the sponsorship of the MIT Center for Civic Media (http://civic.mit.edu).

