set(QT_USE_QTXML true)
set(QT_USE_QTXMLPATTERNS true)
include(${QT_USE_FILE})

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

include_directories(${QT_INCLUDE_DIR})
add_executable(QPlanning ${sources_FILES})
target_link_libraries(QPlanning ${QT_LIBRARIES})
set_target_properties(QPlanning PROPERTIES RUNTIME_OUTPUT_DIRECTORY ../bin)
