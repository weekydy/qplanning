set(
	ts_FILES
	QPlanning_fr.ts
)

foreach(${cpp_FILES} ${ui_FILES} cpp_ui_FILE)
	set(cpp_ui_FILES ${cpp_ui_FILES} ../src/${cpp_ui_FILE})
endforeach(${cpp_FILES} ${ui_FILES} cpp_ui_FILE)

foreach (${ts_FILES} ts_FILE)
	if (NOT EXISTS ${ts_FILE})
		set(ts_UNEXISTANT_FILES ${ts_UNEXISTANT_FILES} ts_FILE)
	else (NOT EXISTS ${ts_FILE})
		set(ts_EXISTANT_FILES ${ts_EXISTANT_FILES} ts_FILE)
	endif (NOT EXISTS ${ts_FILE})
endforeach (${ts_FILES} ts_FILE)

qt4_create_translation(
	qm_UNEXISTANT_FILES
	${ts_UNEXISTANT_FILES}
	${cpp_ui_FILES}
)

qt4_add_translation(
	qm_EXISTANT_FILES
	${ts_EXISTANT_FILES}
)

qt4_create_translation(
	qm_FILES
	${ts_FILES}
	${cpp_ui_FILES}
)

add_custom_target(qm ALL DEPENDS ${qm_UNEXISTANT_FILES} ${qm_EXISTANT_FILES})
add_custom_target(update_ts ALL DEPENDS ${qm_FILES})
install(FILES ${qm_EXISTANT_FILES} DESTINATION ${PREFIX}/${TRANSLATION_DIR})
