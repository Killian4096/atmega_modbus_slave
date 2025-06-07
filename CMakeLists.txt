set(LIBRARY_NAME atmega_modbus_slave)

add_library(${LIBRARY_NAME} src/atmega_modbus_slave.c)

target_include_directories(${LIBRARY_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${LIBRARY_NAME} PUBLIC modbus_slave)
