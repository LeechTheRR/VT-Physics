

PROJECT(VPSolver-mysph)

FIND_PACKAGE(CUDAToolkit)
FIND_PACKAGE(nlohmann_json CONFIG REQUIRED)

FILE(GLOB_RECURSE MYSPH_FILES
        ${VP_RUNTIME_ROOT}/Include/Solvers/MYSPH/*.hpp
        ${VP_RUNTIME_ROOT}/Source/Solvers/MYSPH/*.cpp
        ${VP_RUNTIME_ROOT}/Source/Solvers/MYSPH/*.cuh
        ${VP_RUNTIME_ROOT}/Source/Solvers/MYSPH/*.cu
)

ADD_LIBRARY(vpmysph STATIC ${MYSPH_FILES})
TARGET_LINK_LIBRARIES(vpmysph PRIVATE vpcore vpugns vpda)
TARGET_INCLUDE_DIRECTORIES(vpmysph PRIVATE ${VP_LIB_ROOT}/Include ${NLOHMANN_JSON_INCLUDE_DIRS})
ADD_DEPENDENCIES(vpmysph vpcore vpugns)
ADD_COMPILE_OPTIONS("/utf-8")




