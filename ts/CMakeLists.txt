set(
	ts_FILES
	QPlanning_fr.ts
)

foreach(${cpp_FILES} ${ui_FILES} cpp_ui_FILE)
	set(cpp_ui_FILES ${cpp_ui_FILES} ../src/${cpp_ui_FILE})
endforeach(${cpp_FILES} ${ui_FILES} cpp_ui_FILE)

qt4_create_translation(
	qm_FILES
	${ts_FILES}
	${cpp_ui_FILES}
)

add_custom_target(qm ALL DEPENDS ${qm_FILES})
install(FILES ${qm_FILES} DESTINATION ${PREFIX}/${TRANSLATION_DIR})
