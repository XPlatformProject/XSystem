cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

function(xs_add_dependence target dependence)

add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${dependence}>
                $<TARGET_FILE_DIR:${target}>)


endfunction(xs_add_dependence)

function(xs_add_dependence_module target dependence)

add_custom_command(
        TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:${dependence}>
                $<TARGET_FILE_DIR:${target}>/Engine/${dependence}.dll)


endfunction(xs_add_dependence_module)

function(xs_copy_file target in_path out_path)

add_custom_command(
        TARGET ${target} COMMAND PRE_BUILD
         ${CMAKE_COMMAND} -E copy
                ${in_path}
                ${out_path}
)

endfunction(xs_copy_file)

function(xs_copy_folder target in_path out_path)

add_custom_command(
        TARGET ${target} COMMAND PRE_BUILD
         ${CMAKE_COMMAND} -E copy_directory
                ${in_path}
                ${out_path}
)

endfunction(xs_copy_folder)