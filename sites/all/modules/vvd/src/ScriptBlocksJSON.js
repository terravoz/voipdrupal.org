goog.provide('sb.ScriptBlocksJSON');

goog.require('sb.ScriptBlocks');
goog.require('sb.Block');
goog.require('sb.BlockSpec');
goog.require('sb.Drawer');
goog.require('sb.Page');
goog.require('sb.Workspace');

goog.require('goog.string');

/**
 * ScriptBlocksJSON.js - a convenience class with static methods for initializing,
 * loading, and saving ScriptBlocks workspaces from and to JSON.
 *
 * @author djwendel
 */



sb.ScriptBlocksJSON.genusMap = {}; //maps genus name to BlockSpec for that genus
sb.ScriptBlocksJSON.workspace = null; //the sb.Workspace associated with this SBJSON


sb.ScriptBlocksJSON.init = function(workspace) {
	sb.ScriptBlocksJSON.workspace = workspace;
}

sb.ScriptBlocksJSON.loadJSON = function(genusJSON, drawersJSON, projectStr) {
	sb.ScriptBlocksJSON.initGenusMapfromJSON(genusJSON);
	sb.ScriptBlocksJSON.initWorkspaceFromJSON(drawersJSON);
	sb.ScriptBlocksJSON.loadBlockStructureFromJSON(projectStr);
}

sb.ScriptBlocksJSON.saveJSON = function() {
	var project_str = sb.ScriptBlocksJSON.getBlockStructureAsJSON();
	sb.Logger.log(project_str);
	return project_str;
}

/*sb.ScriptBlocksJSON.parseColor = function(colorStr) {
	var rgb = colorStr.split(' ');
	return "#" + (parseInt(rgb[0], 10) * 0x010000 + parseInt(rgb[1], 10) * 0x000100 + parseInt(rgb[2], 10)).toString(16);
}*/

sb.ScriptBlocksJSON.initDrawersFromJSON = function(drawerJSON) {
	var drawersArray = JSON.parse(drawerJSON);
	var drawer;
	var blocks;
	var block;

	for (var i = 0; i < drawersArray.length; i++) {
		var drawerName = drawersArray[i].name;
		drawer = new sb.Drawer(drawerName);
		sb.ScriptBlocksJSON.workspace.addDrawer(drawer);
		blocks = drawersArray[i].blocks;
		for (var j = 0; j < blocks.length; j++) {
			if (sb.ScriptBlocksJSON.genusMap[blocks[j]] == undefined) {
				sb.Logger.log("No genus definition for " + blocks[j]);
				continue;
			}
			block = new sb.Block(sb.ScriptBlocksJSON.genusMap[blocks[j]]);
			drawer.addBlock(block);
		}
	}
}
/**
 * Adds a generated block to a given drawer. NOTE: These blocks are not fully implemented,
 * only enough to allow for the ActionScript to read them in.
 *
 * @param {string} jsonstr - the JSON 
 * @param {string} drawer - the name of the drawer to add the block to
 */
sb.ScriptBlocksJSON.generateNewBlock = function(jsonstr, drawer) {
	var blockElts;
	if (jsonstr != null && jsonstr != '') {
		blockElts = JSON.parse(jsonstr);
	}
	
	var spec = new sb.BlockSpec();
	spec = sb.BlockSpec.extend(spec, blockElts[i].spec);

	var block = new sb.Block(spec);

	// save spec to the genus spec map
	sb.ScriptBlocksJSON.genusMap[spec.name] = spec;
	var addDrawer;
	for (var i = 0; i < sb.ScriptBlocksJSON.workspace.getDrawers().length; i++) {
		if (sb.ScriptBlocksJSON.workspace.getDrawers()[i].name_ == drawer) {
			addDrawer = drawers[i];
		}
	}
	addDrawer.addBlock(new sb.Block(spec));
}
/**
 * loads language definition JSON which includes block specs and drawer specs (for now assuming only one page)
 * @param {string} JSON
 */
sb.ScriptBlocksJSON.initWorkspaceFromJSON = function(drawersJSON) {
	sb.ScriptBlocksJSON.initDrawersFromJSON(drawersJSON);
}
/**
 * Loads the GenusMap from a JSON-formatted string
 * @param {string} JSONstr the JSON-formatted string containing the contents of the GenusMap
 */
sb.ScriptBlocksJSON.initGenusMapfromJSON = function(JSONstr) {
	sb.ScriptBlocksJSON.genusMap = JSON.parse(JSONstr);
}
/**
 * loads a "project" - a set of blocks which are potentially interconnected, from saved JSON
 * @param {string} JSON
 */
sb.ScriptBlocksJSON.loadBlockStructureFromJSON = function(JSONstr) {
	var blockElts;
	var spec;
	var blocksByID = {};

	try {

		if (JSONstr != null && JSONstr != '') {
			blockElts = JSON.parse(JSONstr);
		}

		for (var i = 0; i < blockElts.length; i++) {
			spec = new sb.BlockSpec();
			spec = sb.BlockSpec.extend(spec, blockElts[i].spec);

			var specReturnType = spec.returnType;
			var blockID = blockElts[i].id;

			// ID-block mapping (for connection next)
			var block = new sb.Block(spec);
			blocksByID[blockID] = block;
		}

		// now loop through and make all of the required connections
		for (i = 0; i < blockElts.length; i++) {

			blockID = blockElts[i].id;
			var connections = blockElts[i].connectedblocks;

			// make all of the saved connections
			for (var j = 0; j < connections.length; j++) {
				var conBlockID = connections[j].id;
				var argName;
				if (connections[j].socket != "after") {
					argName = blockElts[i].spec.arguments[connections[j].socket].name;
					// connect the child block (ID = conBlockID) to this block in this socket
					blocksByID[blockID].connectChildBlock(blocksByID[conBlockID], argName);
				} else {
					blocksByID[blockID].connectAfterBlock(blocksByID[conBlockID]);
				}
			}
		}

		// add the top-level blocks to the page
		for (blockID in blocksByID) {
			var topBlock = blocksByID[blockID];

			// you know it's a top level block if it has no parent or beforeBlock
			if (topBlock.getParent() === null && topBlock.getBefore() === null) {
				sb.ScriptBlocksJSON.workspace.getPages()[0].addBlock(topBlock);
			}
		}
	} catch (err) {
		sb.Logger.log(err);
	}

}
/**
 * returns a JSON string representation of the block structure on the page.
 * @return {string}
 */
sb.ScriptBlocksJSON.getBlockStructureAsJSON = function() {
	var pages = sb.ScriptBlocks.getWorkspace().getPages();
	var JSONstr = '[';
	var idcounter = 1; //non-zero ID's just to be safe
	var color;
	var mt1connection = false; // have to track # of connections to add commas, grr

	// first, assign every Block an ID to make linking much easier
	for (var i = 0; i < pages.length; i++) {
		var pageBlocks = pages[i].getAllBlocks();
		for (var j = 0; j < pageBlocks.length; j++) {
			pageBlocks[j].id = idcounter;
			idcounter++;
		}
	}

	// now go through again and generate JSON for each block
	for (i = 0; i < pages.length; i++) {
		pageBlocks = pages[i].getAllBlocks();
		for (j = 0; j < pageBlocks.length; j++) {
			if (j > 0) { // have to add commas before subsequent entries
				JSONstr += ', ';
			}
			JSONstr += '{';
			JSONstr += '"id":"' + pageBlocks[j].id + '", ';
			
			// grab the spec but insert argument values here before stringifying it
			var spec = pageBlocks[j].getJSONSpec();
			for (var k = 0; k < pageBlocks[j].getArguments().length; k += 1) {
				var arg = pageBlocks[j].getArguments()[k];
				if (!(arg.getValue() instanceof sb.Block)) {
					spec.arguments[k].value = arg.getValue();
				}
			}
            spec.position= pageBlocks[j].getPosition();
			
			JSONstr += '"spec":' + JSON.stringify(spec) + ', ';
			JSONstr += '"connectedblocks":[';

			mt1connection = false; // reset connections counting
			// add entries for each connection this block has
			for (var k = 0; k < pageBlocks[j].getArguments().length; k += 1) {
				var arg = pageBlocks[j].getArguments()[k];
				if (arg.getValue() instanceof sb.Block) {
					if (mt1connection) {
						JSONstr += ','; // comma between subsequent entries
					}
					JSONstr += '{"socket": '+ k +', "id": "' + arg.getValue().id + '"}';
					mt1connection = true;
				}
			}
			if (pageBlocks[j].getAfterBlock() instanceof sb.Block) {
				if (mt1connection) {
					JSONstr += ','; // comma between subsequent entries
				}
				JSONstr += '{"socket": '+ '"after"' +', "id": "' + pageBlocks[j].getAfterBlock().id + '"}';
			}
			JSONstr += ']}';
		}
	}
	JSONstr += ']';

	return JSONstr;
}