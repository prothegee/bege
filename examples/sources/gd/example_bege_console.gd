extends Node

func _ready() -> void:
	bege_console.log(["log"]);
	bege_console.log_debug(["log ", 1, " debug mode"]);
	
	bege_console.warning(["warn"]);
	bege_console.warning_debug(["warn ", 2, " debug mode"]);
	
	bege_console.error(["err"]);
	bege_console.error_debug(["err ", 3, " debug mode"]);
