option(MORE_WARNINGS "Enable more warnings reports by the compiler" ON)
option(WARNINGS_AS_ERRORS "Treat warnings as errors" ON)

function(add_warnings target)
    if(MORE_WARNINGS)
        set(MSVC_WARNINGS "/W4")
        set(GCC_WARNINGS "-Wall -Wextra")
    endif()
    
    if(WARNINGS_AS_ERRORS)
        set(MSVC_WARNINGS "${MSVC_WARNINGS} /WX")
        set(GCC_WARNINGS "${GCC_WARNINGS} -Werror")
    endif()

    target_compile_options(
        ${target} PRIVATE
        $<$<CXX_COMPILER_ID:MSVC>:/W4 /WX>
        $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Werror>
    )
endfunction(add_warnings)
