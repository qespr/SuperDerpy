if(UNIX AND NOT APPLE)
  install(FILES 16/superderpy.png DESTINATION ${ICON_INSTALL_DIR}/hicolor/16x16/apps)
  install(FILES 32/superderpy.png DESTINATION ${ICON_INSTALL_DIR}/hicolor/32x32/apps)
  install(FILES 48/superderpy.png DESTINATION ${ICON_INSTALL_DIR}/hicolor/48x48/apps)
  install(FILES 64/superderpy.png DESTINATION ${ICON_INSTALL_DIR}/hicolor/64x64/apps)
  install(FILES 128/superderpy.png DESTINATION ${ICON_INSTALL_DIR}/hicolor/128x128/apps)
  install(FILES 256/superderpy.png DESTINATION ${ICON_INSTALL_DIR}/hicolor/256x256/apps)
  install(FILES superderpy.svg DESTINATION ${ICON_INSTALL_DIR}/hicolor/scalable/apps)
endif(UNIX AND NOT APPLE)
install(FILES superderpy.png DESTINATION ${DATADIR}/icons)
