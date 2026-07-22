function(add_husk_test test_name test_source)
    add_executable(${test_name} ${test_source} ${ARGN})
    
    target_include_directories(${test_name} PRIVATE 
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/src
    )
    
    target_link_libraries(${test_name} PRIVATE husk_lib)
    
    add_test(NAME ${test_name} COMMAND ${test_name})
endfunction()

add_husk_test(test_asm_string asm/test_strlen.c)

