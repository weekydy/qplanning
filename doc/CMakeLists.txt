find_package (Doxygen)

if (DOXYGEN_FOUND)
	add_custom_target (doc ${DOXYGEN_EXECUTABLE}
			       ${CMAKE_SOURCE_DIR}/doc/Doxyfile)
endif (DOXYGEN_FOUND)
