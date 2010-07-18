set(QT_USE_QTXML true)
set(QT_USE_QTXMLPATTERNS true)
set(QT_USE_QTSQL true)

include(${QT_USE_FILE})
configure_file(define_cmake.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/define_cmake.h)

set(
	ui_FILES
	SubjectDataWindow.ui
	TimeTableWindow.ui
	CACHE FILEPATH "ui files" FORCE
)

set(
	h_FILES
	Control.h
	define.h
	MainWindow.h
	XmlPlanning.h
	SubjectDataWindow.h
	SubjectData.h
	TimeTableWindow.h
	KeyValue.h
	TimeTable.h
	DrawTimetable.h
	FullTimetable.h
	QGraphicsItemBoundedText.h
        SqlModelGenerating.h
        AdvencedItemDelegate.h
        AsyncListView.h
        SqlTable.h
        debug_printf.h
        MyCheckBox.h
        StreachedHeaderView.h
	${CMAKE_CURRENT_BINARY_DIR}/define_cmake.h
	CACHE FILEPATH "header files" FORCE
)

set(
	cpp_FILES
	main.cpp
	Control.cpp
	MainWindow.cpp
	XmlPlanning.cpp
	SubjectDataWindow.cpp
	TimeTableWindow.cpp
	DrawTimetable.cpp
	QGraphicsItemBoundedText.cpp
        SqlModelGenerating.cpp
        AdvencedItemDelegate.cpp
        AsyncListView.cpp
        SqlTable.cpp
        debug_printf.cpp
        MyCheckBox.cpp
        StreachedHeaderView.cpp
	CACHE FILEPATH "source files" FORCE
)
QT4_WRAP_UI(ui_h_FILES ${ui_FILES})
QT4_WRAP_CPP(moc_FILES ${h_FILES})

set(
	sources_FILES
	${ui_h_FILES}
	${moc_FILES}
	${cpp_FILES}
	${h_FILES}
)

set(
	ts_FILES
	../ts/QPlanning_fr.ts
)

qt4_add_translation(
	qm_FILES
	${ts_FILES}
)

include_directories(${QT_INCLUDE_DIR} ${CMAKE_BINARY_DIR}/src)
add_executable(QPlanning ${sources_FILES} ${qm_FILES})
target_link_libraries(QPlanning ${QT_LIBRARIES})
set_target_properties(QPlanning PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)

install(TARGETS QPlanning DESTINATION ${PREFIX}/${PROGRAM_DIR_EXECUTABLE})
install(FILES ${qm_FILES} DESTINATION ${PREFIX}/${TRANSLATION_DIR})
