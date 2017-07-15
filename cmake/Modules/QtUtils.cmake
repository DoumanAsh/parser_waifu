macro(find_qt5)
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTOUIC ON)
    add_definitions(-DQT_DEPRECATED_WARNINGS -DQT_DISABLE_DEPRECATED_BEFORE=0x060000)
    find_package(Qt5 COMPONENTS ${ARGN})

    if(Qt5_FOUND)
        if(WIN32 AND TARGET Qt5::qmake AND NOT TARGET Qt5::windeployqt)
            get_target_property(_qt5_qmake_location Qt5::qmake IMPORTED_LOCATION)

            execute_process(
                COMMAND "${_qt5_qmake_location}" -query QT_INSTALL_PREFIX
                RESULT_VARIABLE return_code
                OUTPUT_VARIABLE qt5_install_prefix
                OUTPUT_STRIP_TRAILING_WHITESPACE
            )

            set(imported_location "${qt5_install_prefix}/bin/windeployqt.exe")

            if(EXISTS ${imported_location})
                add_executable(Qt5::windeployqt IMPORTED)

                set_target_properties(Qt5::windeployqt PROPERTIES
                    IMPORTED_LOCATION ${imported_location}
                )
            endif()
        endif()
    else()
        message(FATAL_ERROR "Cannot find QT5!")
    endif()

endmacro(find_qt5)

macro(install_qt5_libs target dest)
    if(TARGET Qt5::windeployqt)
        # execute windeployqt in a tmp directory after build
        add_custom_command(TARGET ${target}
            POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E remove_directory "${CMAKE_CURRENT_BINARY_DIR}/windeployqt"
            COMMAND set PATH=%PATH%$<SEMICOLON>${qt5_install_prefix}/bin
            COMMAND Qt5::windeployqt --dir "${CMAKE_CURRENT_BINARY_DIR}/windeployqt" "$<TARGET_FILE_DIR:${target}>/$<TARGET_FILE_NAME:${target}>"
        )

        # copy deployment directory during installation
        install(
            DIRECTORY
            "${CMAKE_CURRENT_BINARY_DIR}/windeployqt/"
            DESTINATION ${dest}
        )
    endif()
endmacro(install_qt5_libs)

function(read_version priFile outMajor outMinor outPatch)
    file(STRINGS ${priFile} _priFileContents REGEX "^VER_.+")
    set(_regex "VER_MAJOR += +([0-9]+);VER_MINOR += +([0-9]+);VER_PATCH += +([0-9]+)")
     # note quotes around _regex, they are needed because the variable contains semicolons
    string(REGEX MATCH "${_regex}" _tmp "${_priFileContents}")
    if (NOT _tmp)
        message(FATAL_ERROR "Could not detect project version number from ${priFile}")
    endif()

    # message(STATUS "Matched version string: ${_tmp}")

    set(${outMajor} ${CMAKE_MATCH_1} PARENT_SCOPE)
    set(${outMinor} ${CMAKE_MATCH_2} PARENT_SCOPE)
    set(${outPatch} ${CMAKE_MATCH_3} PARENT_SCOPE)
endfunction()
