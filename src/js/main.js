'use strict';

var Traveler = require('Traveler');
var proto = require('proto');
var mod_file = require('loop_mod');
var bin_file = require('loop');//or 'loop_optimised'

let opts = {};
opts.wasmBinary = bin_file;
opts.print = opts.print || ((text) => console.log(`[C]: ${text}`));
opts.printf = opts.printf || ((text) => console.log(`[C]: ${text}`));
opts.printErr = opts.printErr || ((text) => console.log(`[C_ERR]: ${text}`));
opts.onAbort = opts.onAbort || (() => console.log(`[C_ABORT]: WASM Aborted!`));
opts.noInitialRun = true;
opts.noExitRuntime = true;

var mod = mod_file(opts);
if(!Utils.privateServer()) {
	//cause this makes it work on official server? :S
	mod.then(d => mod = d);
}

Utils.roomMemCopy = function(roomName,pointer){
	var heapView = new Uint8Array(mod.HEAPU8, pointer);
	Game.map.getRoomTerrain(roomName).getRawBuffer(heapView);
}

var runInitialise = false;

module.exports.loop = function () {
	let t = Game.cpu.getUsed();
	if (mod.loop) {
		if (!runInitialise) {
			if (mod.init) {
				runInitialise = true;
				try {
					mod.init();
				} catch (exception) {
					console.error(mod.except(exception));
				}
			} else {
				console.log('[J]: Init method missing');
				return;
			}
		}
		try {
			mod.loop();
		} catch (exception) {
			console.error(mod.except(exception));
		}
	} else {
		console.log('[J]: WasmNotLoadedYet');
	}
	// give all shards our script is running on access to each others memory.
	 if(!Utils.privateServer()) {//make sure we arent on pvt server first.
		 InterShardMemory.setLocal(JSON.stringify(Memory));
	 }
	let dt = Game.cpu.getUsed() - t;
	console.log("[J]: Loop = "+dt+" CPU");
};
