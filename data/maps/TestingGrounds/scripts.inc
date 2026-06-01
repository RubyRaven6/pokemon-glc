TestingGrounds_MapScripts::
	.byte 0


GenerationSelector::
# 6 "data/maps/TestingGrounds/scripts.pory"
	lock
# 7 "data/maps/TestingGrounds/scripts.pory"
	dynmultichoice 0, 0, FALSE, 3, 0, DYN_MULTICHOICE_CB_NONE, GenerationSelector_Text_0, GenerationSelector_Text_1, GenerationSelector_Text_2
# 9 "data/maps/TestingGrounds/scripts.pory"
	switch VAR_RESULT
# 10 "data/maps/TestingGrounds/scripts.pory"
	case 0, GenerationSelector_3
# 13 "data/maps/TestingGrounds/scripts.pory"
	case 1, GenerationSelector_4
# 16 "data/maps/TestingGrounds/scripts.pory"
	case 2, GenerationSelector_5
# 20 "data/maps/TestingGrounds/scripts.pory"
	bufferstring STR_VAR_1, GenerationSelector_Text_6
GenerationSelector_1:
# 23 "data/maps/TestingGrounds/scripts.pory"
	msgbox GenerationSelector_Text_7
# 24 "data/maps/TestingGrounds/scripts.pory"
	closemessage
# 25 "data/maps/TestingGrounds/scripts.pory"
	release
	return

GenerationSelector_3:
# 11 "data/maps/TestingGrounds/scripts.pory"
	choosegeneration 1
# 12 "data/maps/TestingGrounds/scripts.pory"
	bufferstring STR_VAR_1, GenerationSelector_Text_3
	goto GenerationSelector_1

GenerationSelector_4:
# 14 "data/maps/TestingGrounds/scripts.pory"
	choosegeneration 2
# 15 "data/maps/TestingGrounds/scripts.pory"
	bufferstring STR_VAR_1, GenerationSelector_Text_4
	goto GenerationSelector_1

GenerationSelector_5:
# 17 "data/maps/TestingGrounds/scripts.pory"
	choosegeneration 3
# 18 "data/maps/TestingGrounds/scripts.pory"
	bufferstring STR_VAR_1, GenerationSelector_Text_5
	goto GenerationSelector_1


PickerEventObject::
# 29 "data/maps/TestingGrounds/scripts.pory"
	lock
# 30 "data/maps/TestingGrounds/scripts.pory"
	callnative ChooseRandomGymLeader
# 31 "data/maps/TestingGrounds/scripts.pory"
	msgbox PickerEventObject_Text_0
# 32 "data/maps/TestingGrounds/scripts.pory"
	closemessage
# 33 "data/maps/TestingGrounds/scripts.pory"
	release
	return


PWT_Battler1::
# 37 "data/maps/TestingGrounds/scripts.pory"
	call_pwt_script VAR_GYM_LEADER_1
	return


PWT_Battler2::
# 41 "data/maps/TestingGrounds/scripts.pory"
	call_pwt_script VAR_GYM_LEADER_2
	return


PWT_Battler3::
# 45 "data/maps/TestingGrounds/scripts.pory"
	call_pwt_script VAR_GYM_LEADER_3
	return


GenerationSelector_Text_0:
# 7 "data/maps/TestingGrounds/scripts.pory"
	.string "Generation 1$"

GenerationSelector_Text_1:
# 7 "data/maps/TestingGrounds/scripts.pory"
	.string "Generation 2$"

GenerationSelector_Text_2:
# 7 "data/maps/TestingGrounds/scripts.pory"
	.string "Generation 3$"

GenerationSelector_Text_3:
# 12 "data/maps/TestingGrounds/scripts.pory"
	.string "1$"

GenerationSelector_Text_4:
# 15 "data/maps/TestingGrounds/scripts.pory"
	.string "2$"

GenerationSelector_Text_5:
# 18 "data/maps/TestingGrounds/scripts.pory"
	.string "3$"

GenerationSelector_Text_6:
# 20 "data/maps/TestingGrounds/scripts.pory"
	.string "0$"

GenerationSelector_Text_7:
# 23 "data/maps/TestingGrounds/scripts.pory"
	.string "You've chosen Generation\n"
	.string "{STR_VAR_1}.$"

PickerEventObject_Text_0:
# 31 "data/maps/TestingGrounds/scripts.pory"
	.string "Random gym leaders chosen.$"
