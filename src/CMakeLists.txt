set(SOURCES main.cpp
			CanvasView.cpp
			"Shapes.cpp"
			#Drawing.cpp
			)

set(HEADERS 
			CanvasView.h
			"Shapes.h"
			Drawing.h
			)


add_executable(${MAIN} ${HEADERS} ${SOURCES})

target_link_libraries(${MAIN} Qt6::Widgets
							  )