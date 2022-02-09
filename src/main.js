'use strict';


var Traveler = require('Traveler');
var proto = require('proto');

// load the webassembly module
const wasm_loader = require('wasm_loader');

// / Module by XXX.js and XXX.wasm files
var mod = wasm_loader('loop_mod', 'loop');
mod.then(d => mod = d);

var runInitialise = false;

module.exports.loop = function () {
	proto.loop();

	let t = Game.cpu.getUsed();
	if (mod.loop) {
		if (!runInitialise) {
			if (mod.init) {
				runInitialise = true;
				mod.init();
			} else {
				console.log('Init method missing');
				return;
			}
		}

		try {
			mod.loop();
		} catch (exception) {
			console.error(mod.except(exception));
		}
	} else {
		console.log('WasmNotLoadedYet');
	}
	// give all shards our script is running on access to each others memory.
	 if(RESOURCE_PIXEL !== undefined) {//make sure we arent on pvt server first.
		 InterShardMemory.setLocal(JSON.stringify(Memory));
	 }
	let dt = Game.cpu.getUsed() - t;
	console.log(`Loop = ${dt} CPU`);
};
