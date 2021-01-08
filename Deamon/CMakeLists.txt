project(Deamon)
add_executable(Deamon main.cpp
        Tip/tip.h Tip/src/tip.cpp
        Report/report.h Report/src/report.cpp
        Mail/mail.h Mail/src/mail.cpp)
target_link_libraries(Deamon ${SDL2_LIBRARY} ${SDL2_TTF_LIBRARY})
install(TARGETS Deamon RUNTIME DESTINATION ${BIN_DIR})