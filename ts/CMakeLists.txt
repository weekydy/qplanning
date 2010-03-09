set(
ts_FILES
QPLanning_fr.ts
)

qt4_create_translation(
	qm_FILES
	${ts_FILES}
	${sources_FILES}
)

add_custom_target(qm ALL DEPENDS ${qm_files})
