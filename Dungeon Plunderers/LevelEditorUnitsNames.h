#pragma once

enum class LevelEditorUnitsNames {
	player = -1,
	brick, //blocks
	dirt,
	concrete,
	granite,
	coin,
	deadlyFlower, //ground Enemies(Not moving)
	spikes,
	hidingSpikes,
	showingAfterDamageSpikes,
	gunEnemy,
	zombie,//ground Enemies(moving)
	skeleton,
	gunEnemyOnFakeBlock,//flying Enemies
	fly,		//moving flying Enemies
	movingGunEnemyOnFakeBlock,
	movingBrick, //moving blocks
	movingDirt,
	movingConcrete,
	movingGranite,

	counter //<--- keep number of names
};