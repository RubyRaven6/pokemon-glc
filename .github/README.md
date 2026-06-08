# The Pokémon Global League Conference
You've been cordially invited to be part of the Pokémon Global League Conference, where powerful trainers across the world test their mettle against each other! You'll face off against the venerable roster of nine different regions, fighting your way to become the undisputed Ultimate Champion!

# Features
## Trainer Party Pools (Expansion Feature by Hedara90)
Each gym leader has a pool of 9 Pokémon which they make a team of 6 out of. A pool may also have static members, who are present in any permutation.

## Techniques
The romhack boasts brand new moves for each Gym Leader, called Techniques. Powerful new moves that can change the way you play the game!

## EV System
The EV system has been simplified and streamlined. The calculation for each stat is as follows:

HP:
```math
(((2 * baseHP + hpIV) * level) / 100) + level + (10 + hpEV)
```
Other Stats:
```math
(((2 * baseStat + iv) * level) / 100)+ (5 + ev)
```

As such, the caps for Max EVs have also been changed to 63 to mirror their vanilla values.

## Pokémon EV and IV Editor by Archie (TeamAquasHideout)
Allows the player to easily edit a Pokémon's EVs and IVs.

## SWSH User Interfaces by Montblanc
Looks pretty :)

# Pokémon Changes
## General Changes
- Movesets for all the Pokémon available in the game (and more) can be found in [gen_pglc.h](../../src/data/pokemon/level_up_learnsets/gen_pglc.h).
- New ability *Mettle*, which raises the user's Special Attack after fainting an opponent.

## Generation 1
- **Wigglytuff**: Abilities changed from Cute Charm and Competitive to Fluffy and Battle Armor
- **Slowbro**: Ability changed from Own Tempo to Unaware
- **Jolteon**: Gained Ability Unnerve

## Generation 2
- **Ariados**: Gained Skill Link. Rebalanced with the following stats:

| Stat            | Value |
| :----------------| :-----:|
| HP              | 70    |
| Attack          | 90    |
| Defense         | 60    |
| Special Attack  | 40    |
| Special Defense | 70    |
| Speed           | 70    |

## Generation 4
- **Wormadam**: Each form has been given a new ability:

| Stat         | Value     |
| :-------------| :----------|
| Plant Cloak  | Harvest   |
| Sandy Cloak  | Stamina   |
| Trashy Cloak | Heatproof |

- **Tangrowth**: Replaces Ability Leaf Guard with Grass Pelt

## Generation 5
- **Leavanny**: Replaced Overcoat with Sharpness
- **Archeops**: Gained Klutz

# Team Credits
| Position                          | Name                                                    |
| :----------------------------------| :-------------------------------------------------------:|
| Developer                         | Ruby                                                    |
| Gym Leader<br>Team Designers      | Ruby, Turtleye, Jordan,<br>Kithri, Hedara, Noodle, Iriv |
| Gym Leader<br>Technique Designers | Ruby, Turtleye, Jordan,<br>Kithri, Hedara               |
| Pokémon Movesets<br>and Balancing | Ruby                                                    |
| Scripting and Mapping             | Ruby                                                    |

# Credits
| Credit                | Feature                                |
| :----------------------| :--------------------------------------:|
| pokeemerald-expansion | RHH and all<br>the Expansion Contributors |
| Mudskip               | Pokemon GLC Logo                       |

