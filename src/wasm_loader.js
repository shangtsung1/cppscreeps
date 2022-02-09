'use strict';

module.exports = ((mod_js, mod_wasm, opts) => {

	const mod_file = require(mod_js);
	const bin_file = require(mod_wasm);

	opts = opts || {};

	opts.wasmBinary = bin_file;
	opts.print = opts.print || ((text) => console.log(`[C]: ${text}`));
	opts.printf = opts.printf || ((text) => console.log(`[C]: ${text}`));
	opts.printErr = opts.printErr || ((text) => console.log(`[C_ERR]: ${text}`));
	opts.onAbort = opts.onAbort || (() => console.log(`[C_ABORT]: WASM Aborted!`));

	opts.noInitialRun = true;
	opts.noExitRuntime = true;

	return mod_file(opts);
});
