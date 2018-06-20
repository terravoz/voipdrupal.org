	
Drupal.behaviors.vvd = function (context) {
  var workspaceEl = document.getElementById('sbWorkspace');
  sb.ScriptBlocks.init();
  var workspace = sb.ScriptBlocks.createWorkspace(workspaceEl, true);
  var drawer = new sb.Drawer('Script handling');
      workspace.addDrawer(drawer);
      createScriptBlocks(drawer);
									
      drawer = new sb.Drawer('Call control');
      workspace.addDrawer(drawer);
      createCallHandlingBlocks(drawer)
									
      drawer = new sb.Drawer('Input and output');
      workspace.addDrawer(drawer);
      createIOBlocks(drawer);
      
      drawer = new sb.Drawer('Expressions');
      workspace.addDrawer(drawer);
      createExpresionBlocks(drawer);
			
      drawer = new sb.Drawer('Flow control');
      workspace.addDrawer(drawer);
      createFlowBlocks(drawer);
      
      drawer = new sb.Drawer('Voice and Sound');
      workspace.addDrawer(drawer);
      createVoiceBlocks(drawer);
      
      var page1 = new sb.Page('Workspace area');
      //var page2 = new sb.Page('Workspace2');
      //var page3 = new sb.Page('Workspace3');
      
      workspace.addPage(page1);
      //workspace.addPage(page2);
      //workspace.addPage(page3);
     
  var json = $("#edit-field-vvd-editor-0-script-json").val();
  if (!json) {
    //If creating new node then load Hello world script
    json = JSON.stringify([{"id":"1", "spec":{"name":"ScriptName","label":"Script @scriptName \n @cmdStack","arguments":[{"name":"scriptName","dataType":"string","socketType":"internal","value":"hello_world"},{"name":"cmdStack","dataType":"command","socketType":"nested"}],"connections":[],"color":"#87ceeb","returnType":"block","position":{"x":271,"y":108.79998779296875}}, "connectedblocks":[{"socket": 1, "id": "2"}]}, {"id":"2", "spec":{"name":"VoipCmdSay","label":"Say \n @promptArg","arguments":[{"name":"promptArg","dataType":"string","socketType":"internal","value":"Hello world!"}],"connections":["before","after"],"color":"#87ceeb","returnType":"command","position":null}, "connectedblocks":[{"socket": "after", "id": "3"}]}, {"id":"3", "spec":{"name":"VoipCmdHangup","label":"Hangup","arguments":[],"connections":["before"],"color":"#87ceeb","returnType":"command","position":null}, "connectedblocks":[]}]);
  }
  sb.ScriptBlocksJSON.init(workspace);
  sb.ScriptBlocksJSON.loadBlockStructureFromJSON(json);

  //Add resizable option to workspace
  $("#sbWorkspace-wrapper").Resizable({
    minHeight: 505,
    handlers: {
      s: '#sbWorkspace-resize'
    },
    onResize: function(size){
      $('#sbWorkspace, #sbWorkspace .sbPageHolder, #sbWorkspace #page1', this).css('height', size.height - 6 + 'px');
      $("#sbWorkspace-wrapper").css('padding-bottom', '50px');
	}
  });
  
  //Collapsing blocks menu  
  $(".sbDrawer").slideUp(1);
  $(".sbDrawerHolder").hover(function() {
    $(".sbDrawer:hidden").slideDown(50);
  }, function() {});  

  $(".sbPageHolder").hover(function() {
    $(".sbDrawer").slideUp(50);
  }); 

  /*$("#block36").mousedown(function() {
    alert("Handler for .click() called.");
  });*/
}

function createScriptBlocks(drawer) {

      var scriptBlock = new sb.Block({
        label: "Script @scriptName \n @cmdStack", 
        name: "ScriptName",
        arguments: [
        {
          name: "scriptName",
          dataType: "string",
          socketType: "internal",
          value: "name"
        },
        {
          name: "cmdStack",
          dataType: "command",
          socketType: "nested",
        }],
        returnType: "block",
        color: "#87ceeb"
      });
      drawer.addBlock(scriptBlock);
	
      var returnBlock = new sb.Block({
        label: "Return",
        name: "VoipCmdReturn",
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(returnBlock);
      
       var gosubBlock = new sb.Block({
        label: "Jump to @scriptArg",
        name: "VoipCmdGoSub",
        arguments: [{
          name: "scriptArg",
          dataType: "string",
          socketType: "internal",
          value: "script name"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(gosubBlock);
    }
//99FF99
//--------------
    function createCallHandlingBlocks(drawer) {

      var dialBlock = new sb.Block({
        label: "Redirect to @numberArg",
        name: "VoipCmdDial",
        arguments: [{
          name: "numberArg",
          dataType: "string",
          socketType: "internal",
          value: "phone number"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(dialBlock);
				
      var conferenceBlock = new sb.Block({
        label: "Join conference \n @confArg",
        name: "VoipCmdJoinConference",
        arguments: [{
          name: "confArg",
          dataType: "string",
          socketType: "internal",
          value: "conference id"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(conferenceBlock);
				
      var rejectBlock = new sb.Block({
        label: "Reject call",
        name: "VoipCmdReject",
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(rejectBlock);
			
      var hangupBlock = new sb.Block({
        label: "Hangup",
        name: "VoipCmdHangup",
        returnType: "command",
        connections: ["before"],
        color: "#87ceeb"
      });
      drawer.addBlock(hangupBlock);
			
      /*var hangupParamBlock = new sb.Block({
        label: "Hangup @optionsArg",
        name: "VoipCmdHangupwithParam",
        arguments: [{
          name: "optionsArg",
          dataType: "string",
          socketType: "list",
          options: ["End session", "Reset", "Resume"]
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(hangupParamBlock);*/
				
    }
						
//--------------
    function createIOBlocks(drawer) {

      var sayBlock = new sb.Block({
        label: "Say \n @promptArg",
        name: "VoipCmdSay",
        arguments: [{
          name: "promptArg",
          dataType: "string",
          socketType: "internal",
          value: "prompt text or audio URL"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(sayBlock);
      
      var sayBlock2 = new sb.Block({
        label: "Say \n @promptArg \n as @asArg",
        name: "VoipCmdSaywithAs",
        arguments: [{
          name: "promptArg",
          dataType: "string",
          socketType: "internal",
          value: "prompt text or audio URL"
        }, 
        {
          name: "asArg",
          dataType: "string",
          socketType: "list",
          options: ["Digits", "Date"],
          value: "Digits"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(sayBlock2);

      var recordBlock = new sb.Block({
        label: "Record \n @promptArg",
        name: "VoipCmdRecord",
        arguments: [{
          name: "promptArg",
          dataType: "string",
          socketType: "internal",
          value: "prompt text or audio URL"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(recordBlock);
      
      var recordBlock2 = new sb.Block({
        label: "Record \n @promptArg \n for up to @secArg seconds",
        name: "VoipCmdRecordwithTime",
        arguments: [{
          name: "promptArg",
          dataType: "string",
          socketType: "internal",
          value: "prompt text or audio URL"
        }, 
        {
          name: "secArg",
          dataType: "number",
          socketType: "internal",
          value: "30"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(recordBlock2);
      
      var variableRecordingURL = new sb.Block({
        label: "recording_public_url",
        name: "VoipVarRecordingURL",
        returnType: "string",
        color: "#EECC66"
      });
      drawer.addBlock(variableRecordingURL);
      
      var variableRecordingDur = new sb.Block({
        label: "recording_duration",
        name: "VoipVarRecordingDur",
        returnType: "string",
        color: "#EECC66"
      });
      drawer.addBlock(variableRecordingDur);

      var getInputBlock = new sb.Block({
        label: "Get input \n @promptArg",
        name: "VoipCmdGetInput",
        arguments: [{
          name: "promptArg",
          dataType: "string",
          socketType: "internal",
          value: "prompt text or audio URL"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(getInputBlock);
      
      var getInputBlock2 = new sb.Block({
        label: "Get input \n @promptArg \n for up to @digitsArg digits",
        name: "VoipCmdGetInputwithDigits",
        arguments: [{
          name: "promptArg",
          dataType: "string",
          socketType: "internal",
          value: "prompt text or audio URL"
        }, 
        {
          name: "digitsArg",
          dataType: "number",
          socketType: "internal",
          value: "3"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(getInputBlock2);
      
      var variableInputDigits = new sb.Block({
        label: "input_digits",
        name: "VoipVarInputDigits",
        returnType: "string",
        color: "#EECC66"
      });
      drawer.addBlock(variableInputDigits);
      
      var sendTextBlock = new sb.Block({
        label: "Send SMS @promptArg",
        name: "VoipCmdSendText",
        arguments: [{
          name: "promptArg",
          dataType: "string",
          socketType: "internal",
          value: "text"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(sendTextBlock);
      
      var sendTextBlock2 = new sb.Block({
        label: "Send SMS @promptArg \r\n to @numArg",
        name: "VoipCmdSendTextwithNum",
        arguments: [{
          name: "promptArg",
          dataType: "string",
          socketType: "internal",
          value: "text"
        },
        {
          name: "numArg",
          dataType: "string",
          socketType: "internal",
          value: "destination number"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(sendTextBlock2);
      
      var logBlock = new sb.Block({
        label: "Log @promptArg",
        name: "VoipCmdLog",
        arguments: [{
          name: "promptArg",
          dataType: "string",
          socketType: "internal",
          value: "text"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(logBlock);
    }
    
    function createExpresionBlocks(drawer) {

      var variableBlock = new sb.Block({
        label: "Set @nameArg to @valueArg",
        name: "VoipVarSet",
        arguments: [{
          name: "nameArg",
          dataType: "string",
          socketType: "internal",
          value: "variable"
        }, 
        {
          name: "valueArg",
          dataType: "string",
          socketType: "internal",
          value: "value"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(variableBlock);
      
      var variableGetCustom = new sb.Block({
        label: "Get @nameArg",
        name: "VoipVarGetCustom",
        arguments: [{
          name: "nameArg",
          dataType: "string",
          socketType: "internal",
          value: "variable"
        }],
        returnType: "string",
        color: "#EECC66"
      });
      drawer.addBlock(variableGetCustom);
      
      var variableGetPredefined = new sb.Block({
        label: "Get @nameArg",
        name: "VoipVarGetPredefined",
        arguments: [{
          name: "nameArg",
          dataType: "string",
          socketType: "list",
          options: ["call_id", "caller_number", "dest_number", "input_digits", "current_voice", "call_status"],
          value: "call_id"
        }],
        returnType: "string",
        color: "#EECC66"
      });
      drawer.addBlock(variableGetPredefined);
      
      var concatBlock = new sb.Block({
        label: "Concat @arg1 \n AND @arg2",
        name: "VoipConcatBlock",
        arguments: [{
          name: "arg1",
          dataType: "string",
          socketType: "internal",
          value: "argument1"
        }, 
        {
          name: "arg2",
          dataType: "string",
          socketType: "internal",
          value: "argument2"
        }],
        returnType: "string",
        color: "#EECC66"
      });
      drawer.addBlock(concatBlock);
      
      var concatWith3Block = new sb.Block({
        label: "Concat @arg1 \n AND @arg2 \n AND @arg3",
        name: "VoipConcatWith3Block",
        arguments: [{
          name: "arg1",
          dataType: "string",
          socketType: "internal",
          value: "argument1"
        }, 
        {
          name: "arg2",
          dataType: "string",
          socketType: "internal",
          value: "argument2"
        }, 
        {
          name: "arg3",
          dataType: "string",
          socketType: "internal",
          value: "argument3"
        }],
        returnType: "string",
        color: "#EECC66"
      });
      drawer.addBlock(concatWith3Block);
      
      var variableExpStringBlock = new sb.Block({
        label: "@value1 @optionsArg @value2",
        name: "VoipExpString",
        arguments: [{
          name: "value1",
          dataType: "string",
          socketType: "internal",
          value: "variable"
        },
        {
          name: "optionsArg",
          dataType: "string",
          socketType: "list",
          options: ["==", "!=", ">", ">=", "<", "=<"],
          value: "=="
        },
        {
          name: "value2",
          dataType: "string",
          socketType: "internal",
          value: "variable"
        }],
        returnType: "boolean",
        color: "#EECC66"
      });
      drawer.addBlock(variableExpStringBlock);
      
      var variableExpStringBoolBlock = new sb.Block({
        label: "@value1 @optionsArg @value2",
        name: "VoipExpStringBool",
        arguments: [{
          name: "value1",
          dataType: "string",
          socketType: "internal",
          value: "variable"
        },
        {
          name: "optionsArg",
          dataType: "string",
          socketType: "list",
          options: ["==", "!="],
          value: "=="
        },
        {
          name: "value2",
          dataType: "boolean",
          socketType: "internal",
          value: "variable"
        }],
        returnType: "boolean",
        color: "#EECC66"
      });
      drawer.addBlock(variableExpStringBoolBlock);
      
      var variableExpBoolean = new sb.Block({
        label: "@optionsArg",
        name: "VoipExpBoolean",
        arguments: [
        {
          name: "optionsArg",
          dataType: "string",
          socketType: "list",
          options: ["TRUE", "FALSE"],
          value: "TRUE"
        }],
        returnType: "boolean",
        color: "#EECC66"
      });
      drawer.addBlock(variableExpBoolean);

    }    
    
// ---------------------			
    function createFlowBlocks(drawer) {
							
      var labelBlock = new sb.Block({
        label: "Label @labelArg",
        name: "VoipCmdLabel",
        arguments: [{
          name: "labelArg",
          dataType: "string",
          socketType: "internal",
          value: "label name"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(labelBlock);

      var gotoBlock = new sb.Block({
        label: "Go to @labelArg",
        name: "VoipCmdGoto",
        arguments: [{
          name: "labelArg",
          dataType: "string",
          socketType: "internal",
          value: "label name"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(gotoBlock);

      var gotoIfBlock = new sb.Block({
        label: "Go to @labelArg \nif @condArg",
        name: "VoipCmdGotoIf",
        arguments: [
        {
          name: "labelArg",
          dataType: "string",
          socketType: "internal",
          value: "label name"
        },
        {
          name: "condArg",
          dataType: "boolean",
          socketType: "internal",
          value: "true expression"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(gotoIfBlock);

      var voiceMenuBlock = new sb.Block({
        label: "Voice menu @promptArg \r\n1 @arg1\r\n2 @arg2\r\n3 @arg3\r\n4 @arg4\r\n5 @arg5\r\n6 @arg6\r\n7 @arg7\r\n8 @arg8\r\n9 @arg9\r\n0 @arg0\r\n* @argStar\r\n# @argHash\r\ninvalid @argInvalid\r\ntimeout @argTimeout",
        name: "VoipCmdIvrMenu",
        arguments: [{
          name: "promptArg",
          dataType: "string",
          socketType: "internal",
          value: "prompt"
        },
        {
          name: "arg1",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        {
          name: "arg2",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        {
          name: "arg3",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },{
          name: "arg4",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        {
          name: "arg5",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        {
          name: "arg6",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },{
          name: "arg7",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        {
          name: "arg8",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        {
          name: "arg9",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        {
          name: "arg0",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        {
          name: "argStar",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        {
          name: "argHash",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        {
          name: "argInvalid",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        {
          name: "argTimeout",
          dataType: "string",
          socketType: "internal",
          value: "optional label"
        },
        ],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(voiceMenuBlock);
      
      var variableIVROption = new sb.Block({
        label: "selected label",
        name: "VoipVarIVROption",
        returnType: "string",
        color: "#EECC66"
      });
      drawer.addBlock(variableIVROption);
      
      var waitBlock = new sb.Block({
        label: "Wait @secArg seconds",
        name: "VoipCmdWait",
        arguments: [{
          name: "secArg",
          dataType: "number",
          socketType: "internal",
          value: "1"
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(waitBlock);

    }
    
    function createVoiceBlocks(drawer) {
							
      var beepBlock = new sb.Block({
        label: "Beep",
        name: "VoipCmdBeep",
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(beepBlock);

      var voiceBlock = new sb.Block({
        label: "Set voice \n @voiceArg",
        name: "VoipCmdSetVoice",
        arguments: [{
          name: "voiceArg",
          dataType: "string",
          socketType: "list",
          options: Drupal.settings.vvd_voices,
          value: Drupal.settings.vvd_voices[0]
        }],
        returnType: "command",
        connections: ["before", "after"],
        color: "#87ceeb"
      });
      drawer.addBlock(voiceBlock);
    }

var code = new Array();
function vvd_json() {
   code = new Array();
   //var workspaceEl = document.getElementById('sbWorkspace');
	
      sb.ScriptBlocks.init();
      var workspace = sb.ScriptBlocks.getWorkspace();
      var current_page =workspace.getCurrentPage();
      var pages = workspace.getPages();
      var script_names = new Array();
      var script_index = 0;
      for(var j in pages)
      {
        var blocks = pages[j].getAllBlocks();
        for(var i in blocks)
        {

          var name = blocks[i].getName();
          var stack = blocks[i].getStack();
          var parent = stack[0].getParent();
          if(name != "ScriptName" && parent.name_!="ScriptName") {
            //ignore orphan blocks
            continue;
          }

        switch(name) {
          case "ScriptName":
            var child = blocks[i].getChildBlocks();
            if(child.length <1) {
              //get rid of empty scripts
              continue;
            }
            script_index++;
            code[script_index] = "";
            var name = blocks[i].getArgument("scriptName");
            if(!name.value_) {
              //var timestamp = new Date().getTime();
              //script_names[script_index] = "VVD Script "+timestamp;
               script_names[script_index] = "";
            }
            else {
              name = vvdGetArg(name);
              script_names[script_index] = name;
            }
            
          break;
          case "VoipCmdReturn":
             code[script_index] += "$script->addReturn();";
          break;  
          case "VoipCmdGoSub":
            var script = blocks[i].getArgument("scriptArg");
            script = vvdGetArg(script);
            code[script_index] += "$script->addGosub('"+script+"');";
          break; 
          case "VoipCmdDial":
            var number = blocks[i].getArgument("numberArg");
            number = vvdGetArg(number);
            code[script_index] += "$script->addDial('"+number+"');";
          break;
          case "VoipCmdJoinConference":
            var room = blocks[i].getArgument("confArg");
            room = vvdGetArg(room);
            code[script_index] += "$script->addJoinConference('"+room+"');";
          break;
          case "VoipCmdReject":
            code[script_index] += "$script->addReject();";
          break;
          case "VoipCmdHangup":
            code[script_index] += "$script->addHangup();";
          break;
          case "VoipCmdSay":
            var prompt = blocks[i].getArgument("promptArg");
            prompt = vvdGetArg(prompt);
            code[script_index] +=  "$script->addSay('"+prompt+"');";
          break; 
          case "VoipCmdSaywithAs":
            var prompt = blocks[i].getArgument("promptArg");
            prompt = vvdGetArg(prompt);
            var as = blocks[i].getArgument("asArg");
            switch(options.value_){
              case "Digits":
                prompt = "VoipVoice::getDigits('"+prompt+"')";
              break;
              case "Date":
                prompt = "VoipVoice::getDate('"+prompt+"')";
              break;
            }
            code[script_index] +=  "$script->addSay('"+prompt+"');";
          break;
          case "VoipCmdRecord":
            var prompt = blocks[i].getArgument("promptArg");
            prompt = vvdGetArg(prompt);
            code[script_index] += "$script->addRecord("+prompt+");";
          break;
          case "VoipCmdRecordwithTime":
            var prompt = blocks[i].getArgument("promptArg");
            var sec = blocks[i].getArgument("secArg");
            
            prompt = vvdGetArg(prompt);
            sec = vvdGetArg(sec);
            code[script_index] += "$script->addRecord('"+prompt+"', 5, '#', '"+sec+"');";
          break;
          case "VoipCmdGetInput":
            var prompt = blocks[i].getArgument("promptArg");
            prompt = vvdGetArg(prompt);
            code[script_index] += "$script->addGetInput('"+prompt+"');";
          break;  
          case "VoipCmdGetInputwithDigits":
            var prompt = blocks[i].getArgument("promptArg");
            var digits = blocks[i].getArgument("digitsArg");
            
            prompt = vvdGetArg(prompt);
            digits = vvdGetArg(digits);
            code[script_index] += "$script->addGetInput('"+prompt+"', '"+digits+"');";
          break;  
          case "VoipCmdLog":
            var prompt = blocks[i].getArgument("promptArg");
            prompt = vvdGetArg(prompt);
            code[script_index] += "$script->addLog('"+prompt+"');";
          break; 
          case "VoipCmdSendText":
            var prompt = blocks[i].getArgument("promptArg");
            prompt = vvdGetArg(prompt);
            code[script_index] += "$script->addSendText('"+prompt+"');";
          break;
          case "VoipCmdSendTextwithNum":
            var prompt = blocks[i].getArgument("promptArg");
            var destination = blocks[i].getArgument("numArg");
            
            prompt = vvdGetArg(prompt);
            destination = vvdGetArg(destination);
            code[script_index] += "$script->addSendText('"+prompt+"', '"+destination+"');";
          break;
          case "VoipCmdLabel":
            var label = blocks[i].getArgument("labelArg");
            label = vvdGetArg(label);
            code[script_index] += "$script->addLabel('"+label+"');";
          break;
          case "VoipCmdGoto":
             var label = blocks[i].getArgument("labelArg");
             label = vvdGetArg(label);
            code[script_index] += "$script->addGoto('"+label+"');";
          break;
          case "VoipCmdGotoIf":
            var label = blocks[i].getArgument("labelArg");
            var condition = blocks[i].getArgument("condArg");
            
            label = vvdGetArg(label);
            condition = vvdGetArg(condition);
            code[script_index] += "$script->addGotoIf('"+label+"', '"+condition+"');";
          break;
          case "VoipCmdIvrMenu":
          
            var prompt = vvdGetArg(blocks[i].getArgument("promptArg"));
            
            var arg1 = vvdGetArg(blocks[i].getArgument("arg1")).replace("optional label","");
            var arg2 = vvdGetArg(blocks[i].getArgument("arg2")).replace("optional label","");
            var arg3 = vvdGetArg(blocks[i].getArgument("arg3")).replace("optional label","");
            var arg4 = vvdGetArg(blocks[i].getArgument("arg4")).replace("optional label","");
            var arg5 = vvdGetArg(blocks[i].getArgument("arg5")).replace("optional label","");
            var arg6 = vvdGetArg(blocks[i].getArgument("arg6")).replace("optional label","");
            var arg7 = vvdGetArg(blocks[i].getArgument("arg7")).replace("optional label","");
            var arg8 = vvdGetArg(blocks[i].getArgument("arg8")).replace("optional label","");
            var arg9 = vvdGetArg(blocks[i].getArgument("arg9")).replace("optional label","");
            var arg0 = vvdGetArg(blocks[i].getArgument("arg0")).replace("optional label","");
            
            var argStar = vvdGetArg(blocks[i].getArgument("argStar")).replace("optional label","");
            var argHash = vvdGetArg(blocks[i].getArgument("argHash")).replace("optional label","");
            var argInvalid = vvdGetArg(blocks[i].getArgument("argInvalid")).replace("optional label","");
            var argTimeout = vvdGetArg(blocks[i].getArgument("argTimeout")).replace("optional label","");
            code[script_index] += "$input_options = array_filter(array('1' => '"+arg1+"','2' => '"+arg2+"', '3' =>'"+arg3+"', '4' => '"+arg4+"', '5' => '"+arg5+"', '6' => '"+arg6+"', '7' => '"+arg7+"', '8' => '"+arg8+"', '9' => '"+arg9+"', '0' => '"+arg0+"', '#' => '"+argHash+"', '*' => '"+argStar+"'));";
            code[script_index] += "$script->addRunIvrMenu('"+prompt+"', $input_options, '"+argInvalid+"', '"+argTimeout+"');";
          break;
          case "VoipCmdWait":
            var sec = blocks[i].getArgument("secArg");
            sec = vvdGetArg(sec);
            code[script_index] += "$script->addWait('"+sec+"');";
          break;
          case "VoipCmdBeep":
            code[script_index] += "$script->addBeep();";
          break;
          case "VoipCmdSetVoice":
            var voice = blocks[i].getArgument("voiceArg");
            voice = vvdGetArg(voice);
            code[script_index] += "$script->addSetVoice('"+voice+"');";
          break; 
          case "VoipVarSet":
            var var_name = blocks[i].getArgument("nameArg");
            var value = blocks[i].getArgument("valueArg");
            //pick up any other variables inside
            var_name = vvdGetArg(var_name);
            value = vvdGetArg(value);
            code[script_index] += "$script->addSet('"+var_name+"', '"+value+"');";
          break;
        }
      }
      }
      
      //alert(code);
      code = js_array_to_php_array(code);
      
      script_names = js_array_to_php_array(script_names);
      
      var json = sb.ScriptBlocksJSON.saveJSON();
      $("#edit-field-vvd-editor-0-script-json").val(json);
      $("#edit-field-vvd-editor-0-script-code").val(script_names+"||**||"+code);
}

//Additional argument processing
function vvdGetArg(arg) {

  
  //Check if argument is call variable
  if(typeof(arg.value_) == 'object') {
    var call_variable = arg.value_;
    var name = call_variable.getName();
    
    switch(name) {
      case "VoipVarGetCustom":
        var var_name = call_variable.getArgument("nameArg");
        var_name = vvdGetArg(var_name);
        //return argument as script name
        argument = "%"+var_name;
      break;
      case "VoipVarGetPredefined":
        var var_name = call_variable.getArgument("nameArg");
        //return argument as variable name
        argument = "%"+var_name.value_;
      break;
      case "VoipVarRecordingURL":
      case "VoipVarRecordingDur":
      case "VoipVarInputDigits":
        var var_name = call_variable.getLabel();
        //return argument as variable name
        argument = "%"+var_name;
      break;
      case "VoipVarIVROption":
        var var_name = "ivr_option_selected";
        argument = "%"+var_name;
      break;
      case "VoipExpString":
      case "VoipExpStringBool":
        var value1 = call_variable.getArgument("value1");
        var value2 = call_variable.getArgument("value2");
        
        if(typeof(value1.value_) == 'object') {
          value1 = vvdGetArg(value1).replace("^","");
        }
        else {
          value1 = "\""+value1.value_+"\"";
        }
        
        if(typeof(value2.value_) == 'object') {
          value2 = vvdGetArg(value2).replace("^","");
        }
        else {
          value2 = "\""+value2.value_+"\"";
        }
        
        
        var expression = call_variable.getArgument("optionsArg");
        argument = "^("+value1+") "+expression.value_+" ("+value2+")";
      break;
      case "VoipExpBoolean":
        var bool = call_variable.getArgument("optionsArg");
        argument = bool.value_;
      break;
      case "VoipConcatBlock":
        var arg1 = call_variable.getArgument("arg1");
        var arg2 = call_variable.getArgument("arg2");
        
        arg1 = vvdGetArg(arg1);
        arg2 = vvdGetArg(arg2);
        argument = arg1+" "+arg2;
      break;
      case "VoipConcatWith3Block":
        var arg1 = call_variable.getArgument("arg1");
        var arg2 = call_variable.getArgument("arg2");
        var arg3 = call_variable.getArgument("arg3");
        
        arg1 = vvdGetArg(arg1);
        arg2 = vvdGetArg(arg2);
        arg3 = vvdGetArg(arg3);
        argument = arg1+" "+arg2+" "+arg3;
      break;
      
    }
    
  }
  else {
    var argument = arg.value_;
    //replace single quotes so it doesn't break php.
    argument = argument.replace(/(['])/g, "\\$1");
    //argument = "'"+argument+"'";
  }
    
  return argument;
}
/** {{{ http://code.activestate.com/recipes/414334/ (r1) */
function js_array_to_php_array (a)
// This converts a javascript array to a string in PHP serialized format.
// This is useful for passing arrays to PHP. On the PHP side you can 
// unserialize this string from a cookie or request variable. For example,
// assuming you used javascript to set a cookie called "php_array"
// to the value of a javascript array then you can restore the cookie 
// from PHP like this:
//    <?php
//    session_start();
//    $my_array = unserialize(urldecode(stripslashes($_COOKIE['php_array'])));
//    print_r ($my_array);
//    ?>
// This automatically converts both keys and values to strings.
// The return string is not URL escaped, so you must call the
// Javascript "escape()" function before you pass this string to PHP.
{
    var a_php = "";
    var total = 0;
    for (var key in a)
    {
        ++ total;
        a_php = a_php + "s:" +
                String(key).length + ":\"" + String(key) + "\";s:" +
                String(a[key]).length + ":\"" + String(a[key]) + "\";";
    }
    a_php = "a:" + total + ":{" + a_php + "}";
    return a_php;
}
/** end of http://code.activestate.com/recipes/414334/ }}} */
