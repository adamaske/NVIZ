cmake_minimum_required(VERSION 3.16)
project(NVIZ LANGUAGES CXX)

# --- Qt Setup ---
find_package(Qt6 COMPONENTS Widgets OpenGLWidgets REQUIRED)
set(CMAKE_AUTOUIC ON) # Automatically processes .ui files
set(CMAKE_AUTOMOC ON) # Automatically processes Q_OBJECT files
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(VENDOR_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Vendor")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")
set(SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Source")
set(FORMS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Forms")

file(GLOB_RECURSE INCS "${INCLUDE_DIR}/*.h")
file(GLOB_RECURSE SRCS "${SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE FORMS "${FORMS_DIR}/*.ui")
qt_wrap_ui(UI_HEADERS ${FORMS})

# --- External Dependencies ---
set(HDF5_ROOT "C:/Program Files/HDF_Group/HDF5/1.14.6")
find_package(HDF5 REQUIRED)

add_subdirectory(${VENDOR_DIR}/spdlog)

# --- TARGET ---
add_executable(${PROJECT_NAME} 
                ${SRCS} 
                ${INCS} 
                ${VENDOR_DIR}/glad/src/glad.cpp 
                ${UI_HEADERS}   
)	

set_property(TARGET ${PROJECT_NAME} 
             PROPERTY AUTOUIC_SEARCH_PATHS 
             ${FORMS_DIR}
)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR}/pch.h)

target_include_directories(${PROJECT_NAME} PUBLIC
    ${INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR} 
    ${VENDOR_DIR}/glad/include
    ${VENDOR_DIR}/spdlog/include
    ${VENDOR_DIR}/glm
    ${VENDOR_DIR}/HighFive/include
    ${VENDOR_DIR}/Eigen/include 
)

target_link_libraries(  ${PROJECT_NAME} PRIVATE 

                        Qt6::Widgets
                        Qt6::OpenGLWidgets

                        spdlog::spdlog 
                        HDF5::HDF5
)