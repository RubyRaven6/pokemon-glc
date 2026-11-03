from typing import List
import json
import re
import sys

MON_PREFIX = "SPECIES_"

DEF_LEVEL_UP_MOVE = "#define LEVEL_UP_MOVE(lvl, moveLearned) {.move = moveLearned, .level = lvl}"
DEF_LEVEL_UP_END  = "#define LEVEL_UP_END {.move = LEVEL_UP_MOVE_END, .level = 0}"

FLAG_JSON = "--json-file"
FLAG_LIST = "--mon-list"
FLAG_OUTPUT = "--output"

def to_pascal_case(string: str) -> str:
    return "".join(w.capitalize() for w in re.split(r"[_\-\s]+", string))

def read_mon_list(file_name: str) -> List[str]:
    mon_list = []
    file = open(file_name, "r")

    for line in file:
        if line.startswith(MON_PREFIX):
            mon_list.append(line.removeprefix(MON_PREFIX).strip())

    file.close()
    return mon_list

def parse_learnsets(mon_list: List[str], file_name: str) -> str:

    file = open(file_name, "r")
    learnset_data = json.load(file)

    data_str = DEF_LEVEL_UP_MOVE + "\n" + DEF_LEVEL_UP_END + "\n\n"
    for mon in mon_list:
        if mon in learnset_data:
            data_str += f"static const struct LevelUpMove s{to_pascal_case(mon)}LevelUpLearnset[] = {{\n"
            data_str += parse_learnset_moves(learnset_data[mon]["LevelMoves"])
            data_str += parse_move_list(learnset_data[mon]["TMMoves"])
            data_str += parse_move_list(learnset_data[mon]["EggMoves"])
            data_str += parse_move_list(learnset_data[mon]["TutorMoves"])
            data_str += parse_move_list(learnset_data[mon]["PreEvoMoves"])
            data_str += "\tLEVEL_UP_END\n};\n\n"

    file.close()
    return data_str

def parse_learnset_moves(learnset) -> str:
    moves_c = ""
    for level_move in learnset:
        moves_c += f"\tLEVEL_UP_MOVE({level_move["Level"]}, {level_move["Move"]}),\n"
    return moves_c

def parse_move_list(move_list) -> str:
    moves_c = ""
    for move in move_list:
        moves_c += f"\tLEVEL_UP_MOVE(0, {move}),\n"
    return moves_c

def main():
    argc = len(sys.argv)

    json_filename = ""
    mon_list_filename = ""
    output_fileneme = ""

    i = 1
    while i < argc:

        if FLAG_JSON == sys.argv[i]:
            json_filename = sys.argv[i + 1]
            i += 1

        if FLAG_LIST == sys.argv[i]:
            mon_list_filename = sys.argv[i + 1]
            i += 1

        if FLAG_OUTPUT == sys.argv[i]:
            output_fileneme = sys.argv[i + 1]
            i += 1
        
        i += 1

    mon_list = read_mon_list(mon_list_filename)
    text_file = open(output_fileneme, "w")
    text_file.write(parse_learnsets(mon_list, json_filename))
    text_file.close()

if __name__ == "__main__":
    main()