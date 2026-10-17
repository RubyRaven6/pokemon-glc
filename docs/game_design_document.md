# The Pokémon Global League Conference

## Summary
The Pokémon World Tournament is a romhack where the player can challenge the Gym Leaders from across the Pokémon Series and beyond. The player begins the challenge with the Kantonian gym leaders, working their way through each Pokémon generation’s gym leader until they finally reach the Champion’s tournament.

## Gameplay
### Pokémon Acquisition
The player will always have all the fully evolved Pokémon from the latest generation they have unlocked, except for legendaries. The player is given access to legendaries upon purchasing them using their Battle Points. (See Battle Points for more information).

At the start, the player has access to all the fully-evolved Pokémon from Kanto, along with any of their regional forms. When they do, all the Pokémon are level 100.

The player can also gain the Legendary Pokémon of each generation, 

### EV Training
The PGLC provides an overhaul of the commonly known effort value training system, ensuring a much more streamlined experience for trainers. Each Pokémon has a number of EVs determined by their level. Being level 100, they have 128 total EVs instead of the old 512 total EVs a Pokémon could have. To accommodate this change, the formula to calculate a Pokémon’s statistic has been changed to thus:

HP:
```math
(((2 * baseHP + hpIV) * level) / 100) + level + (10 + hpEV)
```
Other Stats:
```math
(((2 * baseStat + iv) * level) / 100)+ (5 + ev)
```

As usual, the final calculation will be rounded down. In this new schema, the EVs are simply additive to the final calculation of a stat, making them more visually impactful and tangible.

Additionally, in order to mirror the previous limits of the EV system, a Pokémon can have a maximum of 63 EVs in a single stat.

### Items
The player has access to all the battle items from Generations 1 to 9. At the start, they’ll be given a select number of battle items and be able to buy more with more battle points. (See Battle Points for more information). Buying items unlocks it for the player, letting them give an item any number of their party Pokémon.

Whenever the player accesses their Pokémon storage, the party’s items are cleared.

### Battle Points
After each successful battle, the player is awarded a number of points. These points can then be used throughout the facility for various uses. Namely: battle items, berries, unlocking legendary Pokémon.

### Tournament
There are 10 planned tournaments for the PLGC: one for each generation of Pokémon until Gen 9, with the final one being the Championship Tournament. Each tournament is 3 rounds: elimination, semi-finals, and finals. Each round will be seeded in such a way that the elimination round will be a gym leader the player has defeated, while the semi-finals and finals will be new. In the 11 player formats, a cracked player can defeat all the leaders in a roster in 4 passes.

The next generation will be unlocked once the player has won the latest roster they have.

### Pokémon, Teambuilding, and Techniques
The player will have access to Pokémon from Generations 1 to 9, including Mythical and Paradox Pokémon.

Each time a player defeats a gym leader in the finals, they gain the signature move of that gym leader. These will be teachable to all Pokémon except Mythical and Paradox Pokémon. 

The Gym Leaders, and Kahunas will use Pokémon across Generation 1 to 9, while the Champions will only use Pokémon from their home reigon, or any regionals of said Pokémon.

## Music
The music will feature original tracks made in the same spirit as the original songs made for the Pokémon World Tournament, remixing different motifs and melodies associated with their original regions.
