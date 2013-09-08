 .pragma library

// Pet Constants
var PET_MOVEMENT = 10
var PET_WIDTH = 100
var PET_HEIGHT = 100
var PET_ANIMATION_TIMER = 300 //in ms
var PET_POOP_TIMER = 10000 //in ms
var PET_POOP_CHANCE = (.25/*5 times/day*/) * (PET_POOP_TIMER / 1000/*in ms*/ ) / 24/*hr*/ / 60/*min/hr*/ / 60/*s/min*/
var STAT_TIMER = 10000 //in ms

// Game Object Constants
var GAME_OBJECT_WIDTH = 50
var GAME_OBJECT_HEIGHT = 50

// Sprite Constants
var MAX_POOP_OBJECTS = 25
