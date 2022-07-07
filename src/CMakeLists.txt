set(SOURCES main.cpp
			CanvasView.cpp
			Line.cpp
			)

set(HEADERS 
			CanvasView.h
			Line.h
			)


add_executable(${MAIN} ${HEADERS} ${SOURCES})

target_link_libraries(${MAIN} Qt6::Widgets
							  )