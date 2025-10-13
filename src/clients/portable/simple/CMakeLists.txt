project(simple)

add_executable(mclock mclock.c)
target_link_libraries(mclock PUBLIC mgr)
