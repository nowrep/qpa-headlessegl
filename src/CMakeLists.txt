set(qpa_SRCS
    headlesseglintegration.cpp
    headlesseglbackingstore.cpp
    headlesseglcontext.cpp
    headlesseglscreen.cpp
    main.cpp
)

add_library(headlessegl MODULE ${qpa_SRCS})

add_definitions(
    -DMESA_EGL_NO_X11_HEADERS
    ${FREETYPE_DEFINITIONS}
    ${EGL_DEFINITIONS}
)

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
