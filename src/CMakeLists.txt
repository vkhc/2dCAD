set(SOURCES main.cpp
			)

set(HEADERS )


add_executable(${MAIN} ${HEADERS} ${SOURCES})

target_link_libraries(${MAIN} Qt6::Widgets
							  )