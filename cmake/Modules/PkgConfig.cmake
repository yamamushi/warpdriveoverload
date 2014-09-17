# An interface for pkg-config similar to the one written with
# m4 macros for the GNU autotools system
# 
# Author: Pablo Yanez Trujillo <yanezp@informatik.uni-freiburg.de>
# Licence: GPL-2
#
# Interface documentation
# -----------------------
#
# Once you include this module a new cache entry is generated with
# the location of the pkg-config utility. This cache entry (PKG_CONFIG_BIN)
# is marked as advanced to protect it from any CMake GUI. You shouldn't change
# the path saved in the cache unless you know what your are doing!
#
# A new command is declared: 'PKG_CONFIG'
#   PKG_CONFIG(expression
#   	<RESULT VAR>
#   	<CFLAGS VAR>
#   	<LDFLAGS VAR>
#   )
#
#   The expression should be a string that is accepted by pkg-config. For
#   example "gtk-2,0 >= 2.10".
#
#   <RESULT VAR> is a boolean variable that saves the result of 
#   'pkg-config --modversion ${expression}', NOT the exit status. That means
#   that <RESULT VAR> is set to TRUE iff pkg-config returns 0.
#
#   <CFLAGS VAR> is a string variable that saves the cflags requiered by
#   the package you are searching for.
#
#   <LDFLAGS VAR> is a string variable that saves the ldflags requiered by
#   the package you are searching for.
#
#   Example:
#	SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/modules")
#	INCLUDE(PkgConfig)
#
#	PKG_CONFIG("gtk-2.0 >= 2.10" GTK_FOUND GTK_CFLAGS GTK_LIBS)
#	IF(GTK_FOUND)
#		ADD_EXECUTABLE(hello-world main.c)
#		SET_TARGET_PROPERTIES(hello-world
#			PROPERTIES 
#			COMPILE_FLAGS ${GTK_CFLAGS}
#			LINK_FLAGS ${GTK_LIBS}
#		)
#	ENDIF(GTK_FOUND)


FIND_PROGRAM(PKG_CONFIG_BIN pkg-config
	DOC "Path of pkg-config utility")

MARK_AS_ADVANCED(PKG_CONFIG_BIN)


MACRO(PKG_CONFIG PKG_CONFIG_ARGS PTR_LIB_FOUND PTR_CFLAGS PTR_LDFLAGS)

	# resetting default values
	SET(${PTR_LIB_FOUND} FALSE)
	SET(PKG_CONFIG_CFLAGS "")
	SET(PKG_CONFIG_LDFLAGS "")

	IF(NOT PKG_CONFIG_BIN STREQUAL "PKG_CONFIG_BIN-NOTFOUND")
		
		# pkg-config was found. Execute pkg-config with --modversion
		# flags to determinate if such a version is found

		EXECUTE_PROCESS(COMMAND
			${PKG_CONFIG_BIN} --modversion "${PKG_CONFIG_ARGS}"
			ERROR_QUIET
			OUTPUT_VARIABLE PKG_CONFIG_FOUND_VERSION
			RESULT_VARIABLE PKG_CONFIG_EXEC
		)

		# removing the last \n 
		STRING(REGEX REPLACE "\n$" "" PKG_CONFIG_FOUND_VERSION "${PKG_CONFIG_FOUND_VERSION}")

		IF(NOT PKG_CONFIG_EXEC)
			# ${PKG_CONFIG_ARGS} found :)
			MESSAGE("-- ${PKG_CONFIG_ARGS} found: '${PKG_CONFIG_FOUND_VERSION}'")

			EXECUTE_PROCESS(COMMAND
				${PKG_CONFIG_BIN} --cflags "${PKG_CONFIG_ARGS}"
				ERROR_QUIET
				OUTPUT_VARIABLE PKG_CONFIG_CFLAGS
			)
			# removing the last \n
			STRING(REGEX REPLACE "\n" " " PKG_CONFIG_CFLAGS "${PKG_CONFIG_CFLAGS}")

			EXECUTE_PROCESS(COMMAND
				${PKG_CONFIG_BIN} --libs "${PKG_CONFIG_ARGS}"
				ERROR_QUIET
				OUTPUT_VARIABLE PKG_CONFIG_LDFLAGS
			)
			# removing the last \n
			STRING(REGEX REPLACE "\n" " " PKG_CONFIG_LDFLAGS "${PKG_CONFIG_LDFLAGS}")

			# pkg-config found the requiered package
			SET(${PTR_LIB_FOUND} TRUE)
			SET(${PTR_CFLAGS} "${PKG_CONFIG_CFLAGS}")
			SET(${PTR_LDFLAGS} "${PKG_CONFIG_LDFLAGS}")


		ELSE(NOT PKG_CONFIG_EXEC)
			MESSAGE("-- ${PKG_CONFIG_ARGS} was not found :(")
		ENDIF(NOT PKG_CONFIG_EXEC)


	ENDIF(NOT PKG_CONFIG_BIN STREQUAL "PKG_CONFIG_BIN-NOTFOUND")

ENDMACRO(PKG_CONFIG)
