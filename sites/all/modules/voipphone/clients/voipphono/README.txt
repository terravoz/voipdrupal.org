voipphono.module
--------------------------------------------------------------------------------

The voipphono.module enables administrators and developers to create Phono widgets that, when pressed, call the given phone number directly from user 
web browser. To learn more about Phono services, visit this link: http://phono.com/docs

VoIP Phono widgets are available as CCK fields display formatters, or as website blocks.

Widgets are avaialble is two different formats:
1. without dialpad - is simple button which calls the give number.
2. with dialpad - button when pressed has sliding dialpad, making possible the interaction between user and application.

--------------------------------------------------------------------------------
Installation

1. Extract voipphono.module to your sites/all/modules directory. 
2. Enable the VoIP Phono module in admin/build/modules.
3. Go to admin/settings/voipphono and enter your Phono API key.

To use the VoIP Phono in CCK fields:
1. Create a Phone field or VoIP Number field in your content type, 
2. Go to "display fields" settings. 
3. Choose one of VoIP Phono formatters as Display Field type.

Notes:
* When using Phone field, only the "Phone Numbers - US & Canada" field is supported.


To use VoIP Phono Blocks
1. Go to admin/build/block and you will see the VoIP Phono blocks that are already available in the system.
2. Click on 'configure', enter the 'Number to call' and choose 'Phono Skin'.
3. Fill in the other optional fields and press 'Save block'. 
4. Assign the block to a region and press 'Save blocks'. Once you do that, the new block will be displayed in the selected region with a Phono widget. 
   When selected, a call will be placed to given number.

Note: 
* By default, this module provides two VoIP Phono blocks. To create additional blocks, go to admin/settings/voipphono and enter the number of blocks you wish 
to have.

Usage:
Using Phono your browser can place calls to SIP Voice over IP devices, other Phono clients, any Voxeo or Tropo Application and of course regular phone numbers. 
Under the block settings in "Number to call" you can use any of following formats that will call our demo script:
3108531787  - to dial using regular phone number.
9996137592@sip.tropo.com - to dial our using sip number.
app:9996137592 - to dial directly to our Tropo application id.

--------------------------------------------------------------------------------
The VoIP Phono module is part of the VoIP Drupal platform. It has been originally developed by Tamer Zoubi and Leo Burd under the sponsorship of the MIT Center for Future Civic Media (http://civic.mit.edu).


