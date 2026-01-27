copy_files_to_build_dir(*.c)
add_library(SRGLLVMArrayPass MODULE ArrayPass.cpp)

get_property(MODULE_FILE TARGET SRGLLVMArrayPass PROPERTY LOCATION)
configure_file(run.sh.in run.sh @ONLY)
