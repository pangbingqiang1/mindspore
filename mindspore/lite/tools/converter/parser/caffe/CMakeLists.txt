file(GLOB_RECURSE CAFFE_SRC_LIST ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

set_property(SOURCE ${CAFFE_SRC_LIST} PROPERTY COMPILE_DEFINITIONS SUBMODULE_ID=mindspore::SubModuleId::SM_LITE)

add_library(caffe_parser_mid OBJECT ${CAFFE_SRC_LIST})
