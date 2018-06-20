VoIP Phone.module
--------------------------------------------------------------------------------
This module provides API for web browser VoIP phones. As part of this modules are two submodules: VoIP Phono and VoIP Twilio Client.
VoIP Phone widgets are available as CCK fields display formatters, or as website blocks.

--------------------------
Installation

1. Extract VoIP Phone to your sites/all/modules directory.
2. Enable the VoIP Phono and VoIP Phono or VoIP Twilio Client modules in admin/build/modules.
3. Configure your VoIP client provider (either Phono or Twilio client, see below for further instructions)  
4. Go to configuration form at admin/settings/client
5. Choose which VoIP Client provider to use. Also here you can set number of VoIP Phone blocks created (by default its 2)
6. Save


Phono configuration
--------------------------
This module enables administrators and developers to create Phono widgets that, when pressed, call the given phone number directly from user 
web browser. To learn more about Phono services, visit this link: http://phono.com/docs

1. Open account at http://phono.com/ and get Phono API Key
2. Go to admin/client/phono and enter your Phono API key.
3. Go to configuration form at admin/settings/client and set Phono as default VoIP Client.


Using Phono your browser can place calls to SIP Voice over IP devices, other Phono clients, any Voxeo or Tropo Application and of course regular phone numbers. 
Under the block settings in "Number to call" you can use any of following formats that will call our demo script:
3108531787  - to dial using regular phone number.
9996137592@sip.tropo.com - to dial our using sip number.
app:9996137592 - to dial directly to our Tropo application id.

Twilio Client configuration
--------------------------
1. Login into your Twilio account
2. In the "Numbers" section of the account, click on the "Edit" link associated with the phone number you would like to use for your Drupal site
3. In the "Apps" section click on "Create app"
   - Fill the "URL" field with
    http://mysite.com/voip/twilioclient/callhandler/ (for clean URLs)
    or http://mysite.com/?q=voip/twilioclient/callhandler
   - Press the "Save" button 
4. Back in your site go to admin/client/twilio and fill in the required fields associated with your Twilio account. 
   "Account SID" "Auth Token" can be found in the "API Credentials" section of your account's "Dashboard", while "Twilio Application SID" can be found by going
   to newly created application in Twilio and "Caller id number" is found under "Numbers" section.
   
--------------------------
Usage
To use the VoIP Phone in CCK fields:
1. Create a Phone* field or VoIP Number field in your content type.
2. Go to "display fields" settings. 
3. Choose one of VoIP Phone formatters as Display Field type.

Notes:
* When using Phone field, only the "Phone Numbers - US & Canada" field is supported.


To use VoIP Phone Blocks
1. Go to admin/build/block and you will see the VoIP Phone blocks that are already available in the system.
2. Click on 'configure', enter the 'Number to call' and choose 'Phone Skin'.
3. Fill in the other optional fields and press 'Save block'. 
4. Assign the block to a region and press 'Save blocks'. Once you do that, the new block will be displayed in the selected region with a VoIP Phone widget. 
   When selected, a call will be placed to given number.

Note: 
* By default, this module provides two VoIP Phone blocks. To create additional blocks, go to admin/settings/client and enter the number of blocks you wish 
to have.


---
The VoIP Phone module is part of the VoIP Drupal framework.  This module has been originally developed by Tamer Zoubi and Leo Burd under the sponsorship of the MIT Center for Future Civic Media (http://civic.mit.edu).