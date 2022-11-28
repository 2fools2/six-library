set(MODULE_NAME hdf5)

if(CODA_ENABLE_HDF5)
    set(TARGET_LANGUAGE c++)
    coda_add_module(${MODULE_NAME} VERSION 1.13.2)
else()
    message("${MODULE_NAME} will not be built since HDF5 is not enabled")
endif()
