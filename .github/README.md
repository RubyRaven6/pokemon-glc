# The Pokémon Global League Conference
You've been cordially invited to be part of the Pokémon Global League Conference, where powerful trainers across the world test their mettle against each other! You'll face off against the venerable roster of nine different regions, fighting your way to become the undisputed Ultimate Champion!

# Features
### Trainer Party Pools (Expansion Feature by Hedara90)
Each gym leader has a pool of 9 Pokémon which they make a team of 6 out of. A pool may also have static members, who are present in any permutation.

### Techniques
The romhack boasts brand new moves for each Gym Leader, called Techniques. Powerful new moves that can change the way you play the game!

### EV System
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

### Pokémon EV and IV Editor by Archie (TeamAquasHideout)
Allows the player to easily edit a Pokémon's EVs and IVs.

### SWSH User Interfaces by Montblanc
Looks pretty :)

# Trainer Teams
Trainer Teams can be found in the following docs:
- [Kanto Leader Teams](../docs/gameplay/kanto_parties.md)
- [Johto Leader Teams](../docs/gameplay/johto_parties.md)
- [Hoenn Leader Teams](../docs/gameplay/hoenn_parties.md)
- [Sinnoh Leader Teams](../docs/gameplay/sinnoh_parties.md)
- [Unova Leader Teams](../docs/gameplay/unova_parties.md)

# Pokémon Changes
## General Changes
- Movesets for all the Pokémon available in the game (and more) can be found in [gen_pglc.h](../src/data/pokemon/level_up_learnsets/gen_pglc.h).
- New ability *Mettle*, which raises the user's Special Attack after fainting an opponent.
- Color Change buffed to proc *before* being hit with an attack rather than after.

## [Changes Per Generation](../docs/gameplay/pokemon_changes.md)

# Team Credits
| Position                              | Name                                                            |
| :--------------------------------------| :---------------------------------------------------------------:|
| Developer                             | Ruby                                                            |
| Start Screen,<br>Player Sprite Screen | Mudskipper13                                                    |
| Gym Leader<br>Team Designers          | Ruby, Turtleye, jtebbe,<br>Kithri, Hedara, Noodle,<br>Iriv, Kit |
| Gym Leader<br>Technique Designers     | Ruby, Turtleye, jtebbe,<br>Kithri, Hedara                       |
| Pokémon Movesets<br>and Balancing     | Ruby, Lemmanade                                                 |
| Scripting and Mapping                 | Ruby                                                            |
| Tournament Logic                      | Ruby, Estellarc                                                 |

# Credits
| Credit                | Feature                                                                               |
| :----------------------| :-------------------------------------------------------------------------------------:|
| pokeemerald-expansion | RHH and all<br>the Expansion Contributors                                             |
| EndlessTGX            | [Crystal Sprite](https://www.deviantart.com/endlesstgx/art/Crystal-Sprites-704463782) |

