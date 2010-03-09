find_package (Doxygen)

if (DOXYGEN_FOUND)
	add_custom_target (doc ALL ${DOXYGEN_EXECUTABLE} Doxyfile)
endif (DOXYGEN_FOUND)
