set(qpa_SRCS
    headlesseglintegration.cpp
    headlesseglbackingstore.cpp
    headlesseglcontext.cpp
    headlessoffscreensurface.cpp
    headlesseglscreen.cpp
    main.cpp
)

add_library(headlessegl MODULE ${qpa_SRCS})

add_definitions(
    -DQT_EGL_NO_X11
    -DMESA_EGL_NO_X11_HEADERS
    ${EGL_DEFINITIONS}
)

if(USE_QT6)
    target_link_libraries(headlessegl
        Qt6::Core
        Qt6::Gui
        Qt6::GuiPrivate
        ${EGL_LIBRARIES}
    )
    set(QT6_PLATFORMS_PLUGIN_DIR lib/qt6/plugins/platforms CACHE STRING "Plugin install dir")
    install(TARGETS headlessegl DESTINATION ${QT6_PLATFORMS_PLUGIN_DIR})
else()
    target_link_libraries(headlessegl
        Qt5::Core
        Qt5::CorePrivate
        Qt5::Gui
        Qt5::GuiPrivate
        Qt5::EglSupportPrivate
        Qt5::FontDatabaseSupportPrivate
        Qt5::EventDispatcherSupportPrivate
        ${EGL_LIBRARIES}
    )
    set(QT5_PLATFORMS_PLUGIN_DIR lib/qt/plugins/platforms CACHE STRING "Plugin install dir")
    install(TARGETS headlessegl DESTINATION ${QT5_PLATFORMS_PLUGIN_DIR})
endif()
