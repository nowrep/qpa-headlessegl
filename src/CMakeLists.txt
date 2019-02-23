set(qpa_SRCS
    headlesseglintegration.cpp
    headlesseglbackingstore.cpp
    headlesseglcontext.cpp
    headlesseglscreen.cpp
    main.cpp
)

add_library(headlessegl MODULE ${qpa_SRCS})

target_link_libraries(headlessegl
    Qt5::Core
    Qt5::CorePrivate
    Qt5::Gui
    Qt5::GuiPrivate
    Qt5FontDatabaseSupport::Qt5FontDatabaseSupport
    Qt5EventDispatcherSupport::Qt5EventDispatcherSupport
    Qt5EglSupport::Qt5EglSupport
    ${EGL_LIBRARY}
)

query_qmake(qt_install_plugins QT_INSTALL_PLUGINS)
install(TARGETS headlessegl DESTINATION ${qt_install_plugins}/platforms/)