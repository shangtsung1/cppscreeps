

var Utils = {};
global.Utils = Utils;
Utils.DeleteProperty = function (object, property) {
	return delete object[property];
};
Utils.keyLength = function (object) {
	return Object.keys(object).length;
};
Utils.creepExists = function (name) {
	return Game.creeps[name] != null;
};
Utils.roomVisible = function (name) {
	return Game.rooms[name] != null;
};
Utils.privateServer = function(){
	return global.RESOURCE_PIXEL === undefined;
};
Utils.flagsInRoom = function(roomName){
	return Game.rooms[roomName].find(FIND_FLAGS);
};
Utils.flagsInRoomP = function(roomName,primaryColor){
	return Game.rooms[roomName].find(FIND_FLAGS,{filter: f => f.color == primaryColor});
};
Utils.flagsInRoomS = function(roomName,secondaryColor){
	return Game.rooms[roomName].find(FIND_FLAGS,{filter: f => f.secondaryColor == secondaryColor});
};
Utils.flagsInRoomPS = function(roomName,primaryColor,secondaryColor){
	return Game.rooms[roomName].find(FIND_FLAGS,{filter: f => f.color == primaryColor && f.secondaryColor == secondaryColor});
};

Creep.prototype.travelToRoom = function (rname) {
	this.travelTo(new RoomPosition(25, 25, rname));
	return 0;
};

Room.prototype.getDroppedEnergy = function(){
	return this.find(FIND_DROPPED_RESOURCES, {filter: f => f.resourceType == RESOURCE_ENERGY && f.amount > 0});
}

Room.prototype.getTombstonesWithEnergy = function(){
	return this.find(FIND_TOMBSTONES, {filter: f => f.store.energy > 0});
}

Creep.prototype.moveToIgnoreCreeps = function (dest) {
	return this.moveTo(dest, {ignoreCreeps: true});
};

Creep.prototype.findNextTarget = function () {
	let targets = this.room.getHostiles();
	if (targets.length > 0) {
		return this.pos.findClosestByRange(targets);
	} else {
		return null;
	}
};

Creep.prototype.constructionInRangeExt = function () {
	let construction = this.pos.findInRange(FIND_CONSTRUCTION_SITES, 2, {filter: f => f.structureType == STRUCTURE_ROAD});
	if (construction.length > 0) {
		return construction[0];
	} else {
		return null;
	}
};

Creep.prototype.damagedRoadInRangeExt = function () {
	let roads = this.pos.findInRange(FIND_STRUCTURES, 2, {filter: f => f.structureType == STRUCTURE_ROAD && f.hits < f.hitsMax});
	if (roads.length > 0) {
		return roads[0];
	} else {
		return null;
	}
};

Creep.prototype.moveToIgnoreSwamp = function (dest) {
	return this.moveTo(dest, {swampCost: 1.1});
};

Creep.prototype.depositAll = function (task) {
	if (!this.pos.isNearTo(Game.getObjectById(task.container))) {
		this.moveTo(Game.getObjectById(task.container));
		return false;
	}
	for (var rName in this.store) {
		if(this.transfer(Game.getObjectById(task.container), RESOURCE_ENERGY) == OK){
			return true;
		}
	}
	return false;
};

RoomPosition.prototype.makePos = function (x, y, z) {
	return new RoomPosition(x, y, z);
};

Creep.prototype.moveToRoom = function (rname) {
	return this.moveTo(new RoomPosition(25, 25, rname));
};

global.ROOM_CROSSROAD = 0;
global.ROOM_HIGHWAY = 1;
global.ROOM_CENTER = 2;
global.ROOM_SOURCE_KEEPER = 3;
global.ROOM_STANDARD = 4;

Room.prototype.getRoomType = function () {
	const [EW, NS] = this.name.match(/\d+/g);
	if (EW % 10 == 0 && NS % 10 == 0) {
		return ROOM_CROSSROAD;
	}
	else if (EW % 10 == 0 || NS % 10 == 0) {
		return ROOM_HIGHWAY;
	}
	else if (EW % 5 == 0 && NS % 5 == 0) {
		return ROOM_CENTER;
	}
	else if (Math.abs(5 - EW % 10) <= 1 && Math.abs(5 - NS % 10) <= 1) {
		return ROOM_SOURCE_KEEPER;
	} else {
		return ROOM_STANDARD;
	}
};
Room.prototype.getRoomTypeForName = function (name) {
	const [EW, NS] = name.match(/\d+/g);
	if (EW % 10 == 0 && NS % 10 == 0) {
		return ROOM_CROSSROAD;
	}
	else if (EW % 10 == 0 || NS % 10 == 0) {
		return ROOM_HIGHWAY;
	}
	else if (EW % 5 == 0 && NS % 5 == 0) {
		return ROOM_CENTER;
	}
	else if (Math.abs(5 - EW % 10) <= 1 && Math.abs(5 - NS % 10) <= 1) {
		return ROOM_SOURCE_KEEPER;
	} else {
		return ROOM_STANDARD;
	}
};

Room.prototype.getHostiles = function () {
	return this.find(FIND_HOSTILE_CREEPS, {filter: f => f.owner.username != 'rysade'});
};

Room.prototype.getMyTowers = function () {
	return this.find(FIND_MY_STRUCTURES, {filter: f => f.structureType == STRUCTURE_TOWER && f.isActive()});
};

Room.prototype.getTowers = function () {
	return this.find(FIND_STRUCTURES, {filter: f => f.structureType == STRUCTURE_TOWER && f.isActive()});
};

Room.prototype.getMySpawns = function () {
	return this.find(FIND_MY_STRUCTURES, {filter: f => f.structureType == STRUCTURE_SPAWN && f.isActive()});
};

Room.prototype.getSpawns = function () {
	return this.find(FIND_STRUCTURES, {filter: f => f.structureType == STRUCTURE_SPAWN && f.isActive()});
};

Room.prototype.getUnusedSpawns = function () {
	return this.find(FIND_STRUCTURES, {filter: f => f.structureType == STRUCTURE_SPAWN && !f.spawning && f.isActive()});
};

Room.prototype.getMyExtensions = function () {
	return this.find(FIND_MY_STRUCTURES, {filter: f => f.structureType == STRUCTURE_EXTENSION && f.isActive()});
};

Room.prototype.getExtensions = function () {
	return this.find(FIND_STRUCTURES, {filter: f => f.structureType == STRUCTURE_EXTENSION && f.isActive()});
};

Room.prototype.getEmptySpawnContainers = function () {
	return this.find(FIND_STRUCTURES, {filter: f => (f.structureType == STRUCTURE_EXTENSION || f.structureType == STRUCTURE_SPAWN || (f.structureType == STRUCTURE_TOWER && f.store.energy < 600)) && f.store.getFreeCapacity(RESOURCE_ENERGY) > 0 && f.isActive()});
};

Room.prototype.getContainers = function () {
	return this.find(FIND_STRUCTURES, {filter: f => f.structureType == STRUCTURE_CONTAINER && f.isActive()});
};

Room.prototype.getRoads = function () {
	return this.find(FIND_STRUCTURES, {filter: f => f.structureType == STRUCTURE_ROAD && f.isActive()});
};

Room.prototype.getRepairable = function () {
	return this.find(FIND_STRUCTURES, {filter: f => f.hits < f.hitsMax && f.hits < 10000000 && f.isActive()}).sort(sortHitsAscending);
};

Room.prototype.getDamagedRoads = function () {
	return this.find(FIND_STRUCTURES, {filter: f => f.structureType == STRUCTURE_ROAD && f.hits < (f.hitsMax / 2) && f.isActive()}).sort(sortHitsAscending);
};

Room.prototype.getDamagedRamparts = function () {
	return this.find(FIND_STRUCTURES, {filter: f => f.structureType == STRUCTURE_RAMPART && f.hits < 6000 && f.isActive()}).sort(sortHitsAscending);
};

Room.prototype.getMyLabs = function () {
	return this.find(FIND_MY_STRUCTURES, {filter: f => f.structureType == STRUCTURE_LAB && f.isActive()});
};

Room.prototype.getLabs = function () {
	return this.find(FIND_STRUCTURES, {filter: f => f.structureType == STRUCTURE_LAB && f.isActive()});
};

Room.prototype.getSources = function () {
	return this.find(FIND_SOURCES);
};

Room.prototype.getActiveSources = function () {
	return this.find(FIND_SOURCES, {filter: f => f.energy > 0});
};

Room.prototype.getActiveSourcesSorted = function () {
	return this.find(FIND_SOURCES, {filter: f => f.energy > 0}).sort(sortDecending);
};

function sortAscending (a, b) {
	return a.energy - b.energy;
}

function sortDecending (a, b) {
	return b.energy - a.energy;
}

function sortHitsAscending (a, b) {
	return a.hits - b.hits;
}

function sortHitsDecending (a, b) {
	return b.hits - a.hits;
}

function sortStoreDecending (a, b) {
	return b.store.energy - a.store.energy;
}

Room.prototype.getMineral = function () {
	return this.find(FIND_MINERALS)[0];
};

Room.prototype.getEmptySources = function () {
	return this.find(FIND_SOURCES, {filter: f => f.energy == 0});
};

Room.prototype.getContainersWithEnergy = function () {
	return this.find(FIND_STRUCTURES, {filter: f => f.structureType == STRUCTURE_CONTAINER && f.store.energy > 50 && f.isActive()}).sort(sortStoreDecending);
};

Room.prototype.getContainersWithEnergy2 = function (creep) {
	return this.find(FIND_STRUCTURES, {filter: f => f.structureType == STRUCTURE_CONTAINER && f.store.energy > (creep.carryCapacity/2) && f.isActive()}).sort(sortStoreDecending);
};

Source.prototype.containerInRange = function () {
	return this.pos.findInRange(FIND_STRUCTURES, 1, {filter: f => f.structureType == STRUCTURE_CONTAINER && f.isActive()});
};

Source.prototype.containerConstructionInRange = function () {
	return this.pos.findInRange(FIND_CONSTRUCTION_SITES, 1, {filter: f => f.structureType == STRUCTURE_CONTAINER});
};
