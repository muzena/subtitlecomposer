file(GLOB _po_files *.po)
gettext_process_po_files(it ALL INSTALL_DESTINATION ${LOCALE_INSTALL_DIR} PO_FILES ${_po_files})
