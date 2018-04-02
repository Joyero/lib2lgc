if (CHECK_CODE)
include(CheckCXXCompilerFlag)

CHECK_CXX_COMPILER_FLAG("-fmax-errors=10" COMPILER_SUPPORTS_FMAX_ERRORS_10)
if(COMPILER_SUPPORTS_FMAX_ERRORS_10)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fmax-errors=10")
endif()
CHECK_CXX_COMPILER_FLAG("-fstrict-overflow" COMPILER_SUPPORTS_FSTRICT_OVERFLOW)
if(COMPILER_SUPPORTS_FSTRICT_OVERFLOW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstrict-overflow")
endif()
CHECK_CXX_COMPILER_FLAG("-Wall" COMPILER_SUPPORTS_WALL)
if(COMPILER_SUPPORTS_WALL)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()
CHECK_CXX_COMPILER_FLAG("-Wcast-align" COMPILER_SUPPORTS_WCAST_ALIGN)
if(COMPILER_SUPPORTS_WCAST_ALIGN)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-align")
endif()
CHECK_CXX_COMPILER_FLAG("-Wcast-qual" COMPILER_SUPPORTS_WCAST_QUAL)
if(COMPILER_SUPPORTS_WCAST_QUAL)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual")
endif()
CHECK_CXX_COMPILER_FLAG("-Wconditionally-supported" COMPILER_SUPPORTS_WCONDITIONALLY_SUPPORTED)
if(COMPILER_SUPPORTS_WCONDITIONALLY_SUPPORTED)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconditionally-supported")
endif()
CHECK_CXX_COMPILER_FLAG("-Wconversion" COMPILER_SUPPORTS_WCONVERSION)
if(COMPILER_SUPPORTS_WCONVERSION)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wconversion")
endif()
CHECK_CXX_COMPILER_FLAG("-Wextra" COMPILER_SUPPORTS_WEXTRA)
if(COMPILER_SUPPORTS_WEXTRA)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
endif()
CHECK_CXX_COMPILER_FLAG("-Wfloat-equal" COMPILER_SUPPORTS_WFLOAT_EQUAL)
if(COMPILER_SUPPORTS_WFLOAT_EQUAL)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-equal")
endif()
CHECK_CXX_COMPILER_FLAG("-Wformat=2" COMPILER_SUPPORTS_WFORMAT_2)
if(COMPILER_SUPPORTS_WFORMAT_2)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat=2")
endif()
CHECK_CXX_COMPILER_FLAG("-Wformat-nonliteral" COMPILER_SUPPORTS_WFORMAT_NONLITERAL)
if(COMPILER_SUPPORTS_WFORMAT_NONLITERAL)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat-nonliteral")
endif()
CHECK_CXX_COMPILER_FLAG("-Wformat-security" COMPILER_SUPPORTS_WFORMAT_SECURITY)
if(COMPILER_SUPPORTS_WFORMAT_SECURITY)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat-security")
endif()
CHECK_CXX_COMPILER_FLAG("-Wformat-extra-args" COMPILER_SUPPORTS_WFORMAT_EXTRA_ARGS)
if(COMPILER_SUPPORTS_WFORMAT_EXTRA_ARGS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat-extra-args")
endif()
CHECK_CXX_COMPILER_FLAG("-Wformat-zero-length" COMPILER_SUPPORTS_WFORMAT_ZERO_LENGTH)
if(COMPILER_SUPPORTS_WFORMAT_ZERO_LENGTH)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat-zero-length")
endif()
CHECK_CXX_COMPILER_FLAG("-Wformat-y2k" COMPILER_SUPPORTS_WFORMAT_Y2K)
if(COMPILER_SUPPORTS_WFORMAT_Y2K)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat-y2k")
endif()
CHECK_CXX_COMPILER_FLAG("-Wformat-signedness" COMPILER_SUPPORTS_WFORMAT_SIGNEDNESS)
if(COMPILER_SUPPORTS_WFORMAT_SIGNEDNESS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wformat-signedness")
endif()
CHECK_CXX_COMPILER_FLAG("-Winit-self" COMPILER_SUPPORTS_WINIT_SELF)
if(COMPILER_SUPPORTS_WINIT_SELF)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self")
endif()
CHECK_CXX_COMPILER_FLAG("-Winline" COMPILER_SUPPORTS_WINLINE)
if(COMPILER_SUPPORTS_WINLINE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winline")
endif()
CHECK_CXX_COMPILER_FLAG("-Wlogical-op" COMPILER_SUPPORTS_WLOGICAL_OP)
if(COMPILER_SUPPORTS_WLOGICAL_OP)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wlogical-op")
endif()
CHECK_CXX_COMPILER_FLAG("-Wmissing-format-attribute" COMPILER_SUPPORTS_WMISSING_FORMAT_ATTRIBUTE)
if(COMPILER_SUPPORTS_WMISSING_FORMAT_ATTRIBUTE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-format-attribute")
endif()
CHECK_CXX_COMPILER_FLAG("-Wno-comment" COMPILER_SUPPORTS_WNO_COMMENT)
if(COMPILER_SUPPORTS_WNO_COMMENT)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-comment")
endif()
CHECK_CXX_COMPILER_FLAG("-Wno-error=deprecated-declarations" COMPILER_SUPPORTS_WNO_ERROR_DEPRECATED_DECLARATIONS)
if(COMPILER_SUPPORTS_WNO_ERROR_DEPRECATED_DECLARATIONS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-error=deprecated-declarations")
endif()
CHECK_CXX_COMPILER_FLAG("-Wno-overloaded-virtual" COMPILER_SUPPORTS_WNO_OVERLOADED_VIRTUAL)
if(COMPILER_SUPPORTS_WNO_OVERLOADED_VIRTUAL)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-overloaded-virtual")
endif()
CHECK_CXX_COMPILER_FLAG("-Wno-unused-parameter" COMPILER_SUPPORTS_WNO_UNUSED_PARAMETER)
if(COMPILER_SUPPORTS_WNO_UNUSED_PARAMETER)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-parameter")
endif()
CHECK_CXX_COMPILER_FLAG("-Wold-style-cast" COMPILER_SUPPORTS_WOLD_STYLE_CAST)
if(COMPILER_SUPPORTS_WOLD_STYLE_CAST)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast")
endif()
CHECK_CXX_COMPILER_FLAG("-Wpacked" COMPILER_SUPPORTS_WPACKED)
if(COMPILER_SUPPORTS_WPACKED)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpacked")
endif()
CHECK_CXX_COMPILER_FLAG("-Wpedantic" COMPILER_SUPPORTS_WPEDANTIC)
if(COMPILER_SUPPORTS_WPEDANTIC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic")
endif()
CHECK_CXX_COMPILER_FLAG("-Wpointer-arith" COMPILER_SUPPORTS_WPOINTER_ARITH)
if(COMPILER_SUPPORTS_WPOINTER_ARITH)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpointer-arith")
endif()
CHECK_CXX_COMPILER_FLAG("-Wredundant-decls" COMPILER_SUPPORTS_WREDUNDANT_DECLS)
if(COMPILER_SUPPORTS_WREDUNDANT_DECLS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls")
endif()
CHECK_CXX_COMPILER_FLAG("-Wshadow" COMPILER_SUPPORTS_WSHADOW)
if(COMPILER_SUPPORTS_WSHADOW)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
endif()
CHECK_CXX_COMPILER_FLAG("-Wsign-conversion" COMPILER_SUPPORTS_WSIGN_CONVERSION)
if(COMPILER_SUPPORTS_WSIGN_CONVERSION)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-conversion")
endif()
CHECK_CXX_COMPILER_FLAG("-Wstrict-aliasing=1" COMPILER_SUPPORTS_WSTRICT_ALIASING_1)
if(COMPILER_SUPPORTS_WSTRICT_ALIASING_1)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-aliasing=1")
endif()
CHECK_CXX_COMPILER_FLAG("-fstrict-aliasing" COMPILER_SUPPORTS_FSTRICT_ALIASING)
if(COMPILER_SUPPORTS_FSTRICT_ALIASING)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fstrict-aliasing")
endif()
CHECK_CXX_COMPILER_FLAG("-Wstrict-overflow=5" COMPILER_SUPPORTS_WSTRICT_OVERFLOW_5)
if(COMPILER_SUPPORTS_WSTRICT_OVERFLOW_5)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-overflow=5")
endif()
CHECK_CXX_COMPILER_FLAG("-Wswitch-default" COMPILER_SUPPORTS_WSWITCH_DEFAULT)
if(COMPILER_SUPPORTS_WSWITCH_DEFAULT)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wswitch-default")
endif()
CHECK_CXX_COMPILER_FLAG("-Wswitch-enum" COMPILER_SUPPORTS_WSWITCH_ENUM)
if(COMPILER_SUPPORTS_WSWITCH_ENUM)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wswitch-enum")
endif()
CHECK_CXX_COMPILER_FLAG("-Wtrampolines" COMPILER_SUPPORTS_WTRAMPOLINES)
if(COMPILER_SUPPORTS_WTRAMPOLINES)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wtrampolines")
endif()
CHECK_CXX_COMPILER_FLAG("-Wuninitialized" COMPILER_SUPPORTS_WUNINITIALIZED)
if(COMPILER_SUPPORTS_WUNINITIALIZED)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuninitialized")
endif()
CHECK_CXX_COMPILER_FLAG("-Wunused-parameter" COMPILER_SUPPORTS_WUNUSED_PARAMETER)
if(COMPILER_SUPPORTS_WUNUSED_PARAMETER)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-parameter")
endif()
CHECK_CXX_COMPILER_FLAG("-Wuseless-cast" COMPILER_SUPPORTS_WUSELESS_CAST)
if(COMPILER_SUPPORTS_WUSELESS_CAST)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wuseless-cast")
endif()
CHECK_CXX_COMPILER_FLAG("-Wmissing-format-attribute" COMPILER_SUPPORTS_WMISSING_FORMAT_ATTRIBUTE)
if(COMPILER_SUPPORTS_WMISSING_FORMAT_ATTRIBUTE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wmissing-format-attribute")
endif()
CHECK_CXX_COMPILER_FLAG("-Wsuggest-final-types" COMPILER_SUPPORTS_WSUGGEST_FINAL_TYPES)
if(COMPILER_SUPPORTS_WSUGGEST_FINAL_TYPES)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsuggest-final-types")
endif()
CHECK_CXX_COMPILER_FLAG("-Wsuggest-final-methods" COMPILER_SUPPORTS_WSUGGEST_FINAL_METHODS)
if(COMPILER_SUPPORTS_WSUGGEST_FINAL_METHODS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsuggest-final-methods")
endif()
CHECK_CXX_COMPILER_FLAG("-Wwrite-strings" COMPILER_SUPPORTS_WWRITE_STRINGS)
if(COMPILER_SUPPORTS_WWRITE_STRINGS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wwrite-strings")
endif()
CHECK_CXX_COMPILER_FLAG("-Wzero-as-null-pointer-constant" COMPILER_SUPPORTS_WZERO_AS_NULL_POINTER_CONSTANT)
if(COMPILER_SUPPORTS_WZERO_AS_NULL_POINTER_CONSTANT)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wzero-as-null-pointer-constant")
endif()
CHECK_CXX_COMPILER_FLAG("-Wctor-dtor-privacy" COMPILER_SUPPORTS_WCTOR_DTOR_PRIVACY)
if(COMPILER_SUPPORTS_WCTOR_DTOR_PRIVACY)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wctor-dtor-privacy")
endif()
CHECK_CXX_COMPILER_FLAG("-Wc++11-compat" COMPILER_SUPPORTS_WC11_COMPAT)
if(COMPILER_SUPPORTS_WC11_COMPAT)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wc++11-compat")
endif()
# No -Weffc++ because it forces to initialise class that have a default
# constructor without argument.
# And clang also do this job.
CHECK_CXX_COMPILER_FLAG("-Wstrict-null-sentinel" COMPILER_SUPPORTS_WSTRICT_NULL_SENTINEL)
if(COMPILER_SUPPORTS_WSTRICT_NULL_SENTINEL)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wstrict-null-sentinel")
endif()
CHECK_CXX_COMPILER_FLAG("-Woverloaded-virtual" COMPILER_SUPPORTS_WOVERLOADED_VIRTUAL)
if(COMPILER_SUPPORTS_WOVERLOADED_VIRTUAL)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual")
endif()
CHECK_CXX_COMPILER_FLAG("-Winconsistent-missing-override" COMPILER_SUPPORTS_WINCONSISTENT_MISSING_OVERRIDE)
if(COMPILER_SUPPORTS_WINCONSISTENT_MISSING_OVERRIDE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winconsistent-missing-override")
endif()
CHECK_CXX_COMPILER_FLAG("-Wsuggest-override" COMPILER_SUPPORTS_WSUGGEST_OVERRIDE)
if(COMPILER_SUPPORTS_WSUGGEST_OVERRIDE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsuggest-override")
endif()
CHECK_CXX_COMPILER_FLAG("-Weverything" COMPILER_SUPPORTS_WEVERYTHING)
if(COMPILER_SUPPORTS_WEVERYTHING)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Weverything")
endif()
CHECK_CXX_COMPILER_FLAG("-Wc++98-compat" COMPILER_SUPPORTS_WC__98_COMPAT)
if(COMPILER_SUPPORTS_WC__98_COMPAT)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-compat")
endif()
CHECK_CXX_COMPILER_FLAG("-Wc++98-c++11-c++14-compat" COMPILER_SUPPORTS_WC__98_C__11_C__14_COMPAT)
if(COMPILER_SUPPORTS_WC__98_C__11_C__14_COMPAT)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c++98-c++11-c++14-compat")
endif()
CHECK_CXX_COMPILER_FLAG("-Wpadded" COMPILER_SUPPORTS_WPADDED)
if(COMPILER_SUPPORTS_WPADDED)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-padded")
endif()
# Pure abstract class exists
CHECK_CXX_COMPILER_FLAG("-Wweak-vtables" COMPILER_SUPPORTS_WWEAK_VTABLES)
if(COMPILER_SUPPORTS_WWEAK_VTABLES)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-weak-vtables")
endif()
CHECK_CXX_COMPILER_FLAG("-Wcovered-switch-default" COMPILER_SUPPORTS_WCOVERED_SWITCH_DEFAULT)
if(COMPILER_SUPPORTS_WCOVERED_SWITCH_DEFAULT)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-covered-switch-default")
endif()
CHECK_CXX_COMPILER_FLAG("-fcomment-block-commands=file" COMPILER_SUPPORTS_FCOMMENT_BLOCK_COMMANDS)
if(COMPILER_SUPPORTS_FCOMMENT_BLOCK_COMMANDS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fcomment-block-commands=file")
endif()

set(CMAKE_EXE_LINKER_FLAGS_SAVE "${CMAKE_EXE_LINKER_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
CHECK_CXX_COMPILER_FLAG("-fprofile-arcs -ftest-coverage" COMPILER_SUPPORTS_FPROFILE_ARCS)
if(COMPILER_SUPPORTS_FPROFILE_ARCS)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
else()
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS_SAVE}")
endif()

# analyzer-constraints=z3 is totally instlable.
#if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
#  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --analyze -Xanalyzer -analyzer-constraints=z3")
#endif()
endif()  # CHECK_CODE
